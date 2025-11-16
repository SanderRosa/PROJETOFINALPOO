// Estoque.cpp - Implementação do gerenciador central de estoque
// Coordena todas operações: add/remove/edit items, registra movimentos, persiste dados
#include "Estoque.h"
#include "ItemProduto.h"
#include "ItemMateria.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits> // Para std::numeric_limits

using std::string;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::stoi;
using std::to_string;
using std::exception;

// Função utilitária local: lê string do usuário via std::cin
// Usada apenas em editarItem()
// static: escopo local ao arquivo (não visível em outras compilações)
static string lerString(const string& prompt) {
    string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);  // Lê até enter (inclui espaços)
    return valor;
}

// Nota: leitura de inteiros e outras interações com o usuário
// são feitas em `main.cpp`. Mantemos aqui apenas helpers de string
// que são usados internamente por `Estoque::editarItem`.

// === CONSTRUTOR E DESTRUTOR ===

// Construtor do Estoque
// Comportamento:
// - Cria listas vazias (itens, historico)
// - Chama carregarDados() para carregar estado anterior dos arquivos
// - Se arquivos não existem: começa com estoque vazio
Estoque::Estoque() {
    // Ao criar o objeto, tenta carregar dados persistidos
    carregarDados();
}

// Destrutor do Estoque
// Comportamento:
// - Salva dados atuais em arquivo (itens.txt, movimentos.txt)
// - Libera memória alocada dinamicamente:
//   * Itera por todos Item* e chama delete
//   * Itera por todos MovimentoEstoque* e chama delete
// - Evita memory leaks críticos
Estoque::~Estoque() {
    // Salva dados antes de destruir (persistência)
    salvarDados();

    // Libera a memória alocada para os itens (cada ponteiro Item* foi criado com new)
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        delete itens.get(i);  // delete chama destrutor do Item antes de liberar memória
    }

    // Libera a memória alocada para o histórico (cada MovimentoEstoque* foi criado com new)
    for (std::size_t i = 0; i < historico.tamanho(); ++i) {
        delete historico.get(i);  // delete chama destrutor do MovimentoEstoque
    }
}

// === GERENCIAMENTO DE ITEMS ===

// Adiciona um novo item ao estoque
// Parâmetro:
//   - item: ponteiro para Item alocado (ItemProduto ou ItemMateria)
// 
// Validação:
//   - Verifica se item != nullptr (não valida duplicata de ID)
// 
// Requisito POO: recebe Item* (tipo base, polimórfico)
void Estoque::adicionarItem(Item* item) {
    if (item != nullptr) {  // Validação básica: não é nullptr
        itens.adicionar(item);  // Adiciona à lista genérica
    }
}

// Busca um item pelo ID (procura linear)
// Parâmetro:
//   - id: ID único do item
// 
// Retorna: ponteiro para o Item encontrado
// 
// Lança: EstoqueException se ID não existe
// 
// Algoritmo: iteração linear pela lista até encontrar
// Complexidade: O(n) onde n = número de items
Item* Estoque::buscarItemPorId(int id) {
    // Itera por todos os items
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        // Testa se ID corresponde
        if (itens.get(i)->getId() == id) {
            return itens.get(i);  // Encontrou! Retorna o ponteiro
        }
    }
    // Se chegar aqui, não encontrou
    throw EstoqueException("Item com ID " + to_string(id) + " nao encontrado.");
}

// Busca um item pelo nome (procura linear)
// Parâmetro:
//   - nome: nome do item (busca exata)
// 
// Retorna: ponteiro para o Item encontrado
// 
// Lança: EstoqueException se nome não existe
// 
// Algoritmo: iteração linear pela lista até encontrar
// Complexidade: O(n) onde n = número de items
Item* Estoque::buscarItemPorNome(const string& nome) {
    // Itera por todos os items
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        // Testa se nome corresponde
        if (itens.get(i)->getNome() == nome) {
            return itens.get(i);  // Encontrou! Retorna o ponteiro
        }
    }
    // Se chegar aqui, não encontrou
    throw EstoqueException("Item com nome '" + nome + "' nao encontrado.");
}

// Remove um item do estoque pelo ID
// Parâmetro:
//   - id: ID único do item a remover
// 
// Comportamento:
//   - Busca item com este ID
//   - delete libera memória do Item
//   - Remove ponteiro da lista
//   - Exibe mensagem de sucesso
// 
// Lança: EstoqueException se ID não existe
// 
// Nota: movimentos históricos do item permanecem (auditoria)
void Estoque::removerItem(int id) {
    // Itera por todos os items
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        // Testa se ID corresponde
        if (itens.get(i)->getId() == id) {
            delete itens.get(i);  // Libera a memória do Item
            itens.remover(i);     // Remove o ponteiro da lista
            cout << "Item removido com sucesso." << endl;
            return;  // Saiu
        }
    }
    // Se chegar aqui, não encontrou
    throw EstoqueException("Item com ID " + to_string(id) + " nao encontrado para remocao.");
}

// Edita dados de um item existente
// Parâmetro:
//   - id: ID único do item a editar
// 
// Campos editáveis:
//   - Nome
//   - Descrição
//   - Link
// 
// Campos NÃO editáveis:
//   - ID (único, criado na adição)
//   - Tipo (PRODUTO/MATERIA, define estrutura)
//   - Categoria/Fornecedor (especializado)
// 
// Lança: EstoqueException se ID não existe
void Estoque::editarItem(int id) {
    // Busca o item ou lança exceção se não existe
    Item* item = buscarItemPorId(id);

    cout << "Editando item: " << item->getNome() << endl;
    cout << "(Deixe em branco para manter o valor atual)" << endl;

    // Lê novos valores com dica de valor atual
    string novoNome = lerString("Novo nome [" + item->getNome() + "]: ");
    string novaDesc = lerString("Nova descricao [" + item->getDescricao() + "]: ");
    string novoLink = lerString("Novo link [" + item->getLink() + "]: ");

    // Se usuário deixou em branco (string vazia), mantém valor anterior
    if (novoNome.empty()) novoNome = item->getNome();
    if (novaDesc.empty()) novaDesc = item->getDescricao();
    if (novoLink.empty()) novoLink = item->getLink();

    // Atualiza dados do item
    item->atualizarDados(novoNome, novaDesc, novoLink);

    // Nota: A especificação não pede para editar categoria/fornecedor,
    // mas poderia ser adicionado aqui com um dynamic_cast para ItemProduto/ItemMateria.

    cout << "Item atualizado com sucesso." << endl;
}

// === EXIBIÇÃO ===

// Lista todos os items do estoque com detalhes
// 
// Comportamento:
// - Se vazio: exibe mensagem "Nenhum item"
// - Se tem items: chama exibirDetalhes() para cada um
// 
// Polimorfismo demonstrado:
// - Item* pode ser ItemProduto ou ItemMateria
// - exibirDetalhes() é virtual, chama método correto
// - ItemProduto exibe categoria, ItemMateria exibe fornecedor
// 
// const: método apenas lê, não modifica estoque
void Estoque::listarItens() const {
    // Verifica se há items
    if (itens.tamanho() == 0) {
        cout << "Nenhum item no estoque." << endl;
        return;
    }
    
    // Polimorfismo acontece aqui!
    // A lista chama o método exibirDetalhes() correto
    // para ItemProduto ou ItemMateria conforme tipo real.
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        itens.get(i)->exibirDetalhes();  // Chamada virtual - comportamento polimórfico
    }
}

// Exibe o histórico de todas as movimentações (ENTRADA/SAIDA)
// 
// Comportamento:
// - Se vazio: exibe mensagem "Nenhuma movimentação"
// - Se tem movimentos: lista todos com gerarResumo()
// 
// const: método apenas lê, não modifica histórico
void Estoque::exibirHistorico() const {
    // Verifica se há movimentos
    if (historico.tamanho() == 0) {
        cout << "Nenhuma movimentacao no historico." << endl;
        return;
    }
    
    // Itera e exibe cada movimento com resumo formatado
    for (std::size_t i = 0; i < historico.tamanho(); ++i) {
        cout << historico.get(i)->gerarResumo() << endl;
    }
}

// === MOVIMENTAÇÕES ===

// Registra uma ENTRADA de items (recebimento/compra)
// 
// Parâmetros:
//   - idItem: ID do item que recebe quantidade
//   - qtd: quantidade adicionada
// 
// Comportamento:
// 1. Busca item pelo ID (lança exceção se não existe)
// 2. Aumenta quantidade via adicionarQtd()
// 3. Cria MovimentoEstoque com tipo ENTRADA
// 4. Adiciona movimento ao histórico
// 
// Lança: EstoqueException se ID inválido ou qtd negativa
void Estoque::registrarEntrada(int idItem, int qtd) {
    // Busca o item ou falha
    Item* item = buscarItemPorId(idItem);
    
    // Aumenta quantidade do item (valida e lança exceção se qtd < 0)
    item->adicionarQtd(qtd);

    // Cria novo movimento registrando esta operação
    MovimentoEstoque* mov = new MovimentoEstoque(ENTRADA, qtd, item->getId(), item->getNome());
    historico.adicionar(mov);  // Adiciona ao histórico para auditoria

    cout << "Entrada registrada com sucesso." << endl;
}

// Registra uma SAIDA de items (venda/uso)
// 
// Parâmetros:
//   - idItem: ID do item que perde quantidade
//   - qtd: quantidade removida
// 
// Comportamento:
// 1. Busca item pelo ID (lança exceção se não existe)
// 2. Diminui quantidade via removerQtd()
// 3. Cria MovimentoEstoque com tipo SAIDA
// 4. Adiciona movimento ao histórico
// 
// Validações:
// - ID deve existir (buscarItemPorId)
// - qtd não pode ser negativa (removerQtd)
// - quantidade não pode ficar negativa (removerQtd)
// 
// Lança: EstoqueException se ID inválido, qtd negativa, ou insuficiente em estoque
void Estoque::registrarSaida(int idItem, int qtd) {
    // Busca o item ou falha
    Item* item = buscarItemPorId(idItem);
    
    // Diminui quantidade do item (valida quantidade suficiente e lança exceção se problema)
    item->removerQtd(qtd);

    // Cria novo movimento registrando esta operação
    MovimentoEstoque* mov = new MovimentoEstoque(SAIDA, qtd, item->getId(), item->getNome());
    historico.adicionar(mov);  // Adiciona ao histórico para auditoria

    cout << "Saida registrada com sucesso." << endl;
}

// === PERSISTÊNCIA ===

// Salva todos os dados (items e movimentos) em arquivos de texto
// 
// Processo:
// 1. Abre itens.txt, escreve cada item em formato:
//    TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
// 2. Abre movimentos.txt, escreve cada movimento em formato:
//    ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
// 
// Polimorfismo usado:
// - getTipo() retorna "PRODUTO" ou "MATERIA"
// - getDetalheEspecifico() retorna categoria ou fornecedor conforme tipo
// 
// const: método apenas lê dados, não modifica
void Estoque::salvarDados() const {
    // === Salvar Items ===
    ofstream arqItens(ARQUIVO_ITENS);  // Abre arquivo para escrita
    if (!arqItens.is_open()) {  // Verifica se abriu corretamente
        cerr << "Erro: Nao foi possivel abrir o arquivo " << ARQUIVO_ITENS << " para salvar." << endl;
        return;  // Falha silenciosa (não interrompe programa)
    }

    // Itera por todos os items
    for (std::size_t i = 0; i < itens.tamanho(); ++i) {
        Item* item = itens.get(i);  // Obtém ponteiro do item
        
        // Escreve em formato: TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
        // Polimorfismo: getTipo() e getDetalheEspecifico() variam por tipo
        arqItens << item->getTipo() << ";"              // PRODUTO ou MATERIA
                 << item->getId() << ";"
                 << item->getNome() << ";"
                 << item->getDescricao() << ";"
                 << item->getQuantidade() << ";"
                 << item->getLink() << ";"
                 << item->getDetalheEspecifico() << "\n";  // categoria ou fornecedor
    }
    arqItens.close();  // Fecha arquivo

    // === Salvar Movimentos ===
    ofstream arqMov(ARQUIVO_MOVIMENTOS);  // Abre arquivo para escrita
    if (!arqMov.is_open()) {  // Verifica se abriu corretamente
        cerr << "Erro: Nao foi possivel abrir o arquivo " << ARQUIVO_MOVIMENTOS << " para salvar." << endl;
        return;  // Falha silenciosa
    }

    // Itera por todos os movimentos
    for (std::size_t i = 0; i < historico.tamanho(); ++i) {
        MovimentoEstoque* mov = historico.get(i);  // Obtém ponteiro do movimento
        
        // Escreve em formato: ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
        arqMov << mov->getId() << ";"
               << mov->getData() << ";"
               << (mov->getTipo() == ENTRADA ? "ENTRADA" : "SAIDA") << ";"  // Converte enum para string
               << mov->getQuantidade() << ";"
               << mov->getIdItem() << ";"
               << mov->getNomeItem() << "\n";
    }
    arqMov.close();  // Fecha arquivo
    
    cout << "Dados salvos com sucesso." << endl;
}

// Carrega todos os dados (items e movimentos) dos arquivos de texto
// Chamado no construtor ao iniciar a aplicação
// 
// Processo Items:
// 1. Abre itens.txt
// 2. Para cada linha: parse TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
// 3. Se TYPE=="PRODUTO": cria new ItemProduto(...) com detail como categoria
// 4. Se TYPE=="MATERIA": cria new ItemMateria(...) com detail como fornecedor
// 5. Adiciona à lista items
// 6. Atualiza Item::proximoId para continuar IDs únicos
// 
// Processo Movimentos:
// 1. Abre movimentos.txt
// 2. Para cada linha: parse ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
// 3. Converte TIPO ("ENTRADA"/"SAIDA") para enum TipoMovimento
// 4. Cria new MovimentoEstoque(...) com construtor de carregamento
// 5. Adiciona à lista historico
// 6. Atualiza MovimentoEstoque::proximoId para continuar IDs únicos
// 
// Tratamento de erro:
// - Se arquivo não existe: aviso e continua (primeira execução)
// - Se linha corrompida: aviso e pula linha
void Estoque::carregarDados() {
    // === Carregar Items ===
    ifstream arqItens(ARQUIVO_ITENS);  // Abre arquivo para leitura
    if (!arqItens.is_open()) {  // Se não consegue abrir
        cout << "Aviso: Arquivo " << ARQUIVO_ITENS << " nao encontrado. Comecando com estoque vazio." << endl;
    } else {
        string linha, tipo, idStr, nome, desc, qtdStr, link, detalhe;
        int id, qtd;
        int maxId = 0;  // Rastreia maior ID encontrado

        // Lê arquivo linha por linha
        while (getline(arqItens, linha)) {
            stringstream ss(linha);  // String stream para parsing
            
            // Parse: separa campos por semicolon (;)
            getline(ss, tipo, ';');      // PRODUTO ou MATERIA
            getline(ss, idStr, ';');     // ID em string
            getline(ss, nome, ';');      // Nome
            getline(ss, desc, ';');      // Descrição
            getline(ss, qtdStr, ';');    // Quantidade em string
            getline(ss, link, ';');      // Link
            getline(ss, detalhe, ';');   // Categoria ou Fornecedor

            try {
                id = stoi(idStr);        // Converte string para int
                qtd = stoi(qtdStr);      // Converte string para int
                if (id > maxId) maxId = id;  // Rastreia maior ID

                // Cria item apropriado baseado em tipo
                Item* novoItem = nullptr;
                if (tipo == "PRODUTO") {
                    // Cria ItemProduto com categoria como detalhe
                    novoItem = new ItemProduto(nome, desc, qtd, link, detalhe);
                } else if (tipo == "MATERIA") {
                    // Cria ItemMateria com fornecedor como detalhe
                    novoItem = new ItemMateria(nome, desc, qtd, link, detalhe);
                }

                // Se conseguiu criar item, adiciona ao estoque
                if (novoItem) {
                    // Nota: O construtor incrementa proximoId automaticamente
                    // Isso é simplificação de projeto estudantil.
                    // Design melhor usaria construtor privado ou friend class.
                    this->adicionarItem(novoItem);
                }
            } catch (const exception& e) {
                cerr << "Erro ao ler linha do arquivo de itens: " << e.what() << endl;
                // Continua com próxima linha (ignora erro)
            }
        }
        // Atualiza ID estático para evitar duplicação quando criar novo item
        Item::setProximoId(maxId + 1);
        arqItens.close();
    }

    // === Carregar Movimentos ===
    ifstream arqMov(ARQUIVO_MOVIMENTOS);  // Abre arquivo para leitura
    if (!arqMov.is_open()) {  // Se não consegue abrir
        cout << "Aviso: Arquivo " << ARQUIVO_MOVIMENTOS << " nao encontrado. Comecando com historico vazio." << endl;
    } else {
        string linha, idStr, data, tipoStr, qtdStr, idItemStr, nomeItem;
        int id, qtd, idItem;
        int maxIdMov = 0;  // Rastreia maior ID encontrado

        // Lê arquivo linha por linha
        while (getline(arqMov, linha)) {
            stringstream ss(linha);  // String stream para parsing
            
            // Parse: separa campos por semicolon (;)
            getline(ss, idStr, ';');       // ID em string
            getline(ss, data, ';');        // Data/hora "YYYY-MM-DD HH:MM:SS"
            getline(ss, tipoStr, ';');     // ENTRADA ou SAIDA
            getline(ss, qtdStr, ';');      // Quantidade em string
            getline(ss, idItemStr, ';');   // ID do item em string
            getline(ss, nomeItem, ';');    // Nome do item

            try {
                id = stoi(idStr);          // Converte string para int
                qtd = stoi(qtdStr);        // Converte string para int
                idItem = stoi(idItemStr);  // Converte string para int
                if (id > maxIdMov) maxIdMov = id;  // Rastreia maior ID

                // Converte string "ENTRADA" ou "SAIDA" para enum TipoMovimento
                TipoMovimento tipo = (tipoStr == "ENTRADA" ? ENTRADA : SAIDA);
                
                // Cria novo movimento usando construtor de carregamento
                // (não incrementa proximoId - já tem ID do arquivo)
                MovimentoEstoque* mov = new MovimentoEstoque(id, data, tipo, qtd, idItem, nomeItem);
                historico.adicionar(mov);

            } catch (const exception& e) {
                cerr << "Erro ao ler linha do arquivo de movimentos: " << e.what() << endl;
                // Continua com próxima linha (ignora erro)
            }
        }
        // Atualiza ID estático para evitar duplicação quando criar novo movimento
        MovimentoEstoque::setProximoId(maxIdMov + 1);
        arqMov.close();
    }
}