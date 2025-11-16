// main.cpp - Interface do usuário: menu e funções de interação
// Ponto de entrada da aplicação, gerencia a interface com o usuário
// Demonstra: tratamento de exceções, I/O, menu-driven architecture

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> // Para system()

#include "Estoque.h"
#include "EstoqueException.h"
#include "ItemProduto.h"
#include "ItemMateria.h"

// Usings para o std namespace (simplifica escrita)
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;
using std::numeric_limits;
using std::streamsize;
using std::getline;


// === PROTÓTIPOS DE FUNÇÕES AUXILIARES ===
// (Implementadas ao fim do arquivo)

// Exibe menu na tela e retorna opção escolhida
int exibirMenu();

// Limpa tela (cross-platform: Windows vs Linux/Mac)
void limparTela();

// Pausa para o usuário pressionar ENTER
void pausar();

// Lê inteiro com validação (loop até entrada válida)
int lerInteiro(const string& prompt);

// Lê string simples (pode estar vazia)
string lerString(const string& prompt);

// Lê string garantindo que não é vazia
string lerStringNaoVazia(const string& prompt);

// === PROTÓTIPOS DE FUNÇÕES DE FUNCIONALIDADE ===
// (Implementadas ao fim do arquivo)

// Menu opção 1: Adiciona novo item (PRODUTO ou MATERIA)
void adicionarItem(Estoque& estoque);

// Menu opção 2: Remove item pelo ID
void removerItem(Estoque& estoque);

// Menu opção 3: Edita dados de item existente
void editarItem(Estoque& estoque);

// Menu opção 4: Busca e exibe detalhes de item
void localizarItem(Estoque& estoque);

// Menu opção 6: Registra entrada (recebimento) de items
void registrarEntrada(Estoque& estoque);

// Menu opção 7: Registra saída (venda/uso) de items
void registrarSaida(Estoque& estoque);

// Menu opção 9: Abre link do item no navegador
void buscarInternet(Estoque& estoque);

/**
 * Função principal - Ponto de entrada da aplicação.
 * 
 * Responsabilidades:
 * 1. Cria objeto Estoque (carrega dados dos arquivos)
 * 2. Exibe menu repetidamente em loop
 * 3. Captura opção do usuário
 * 4. Chama função correspondente
 * 5. Trata exceções EstoqueException
 * 6. Ao sair (opção 0): destrutor de Estoque salva dados
 * 
 * Fluxo:
 *   - Loop while(opcao != 0)
 *   - Try/catch para EstoqueException e std::exception
 *   - Pausa após cada operação (exceto sair)
 *   - Destrutor automático ao final salva dados
 * 
 * Retorna: 0 (sucesso)
 */
int main() {
    // Cria objeto Estoque (construtor carrega dados de arquivos)
    Estoque estoque;
    int opcao;

    // Loop principal: menu-driven
    do {
        limparTela();  // Limpa tela antes de exibir menu
        opcao = exibirMenu();  // Exibe menu e obtém opção

        try {
            // Switch baseado na opção escolhida
            // Cada caso chama função correspondente
            switch (opcao) {
                // Opção 1: Adicionar novo item
                case 1:
                    adicionarItem(estoque);
                    break;
                // Opção 2: Remover item pelo ID
                case 2:
                    removerItem(estoque);
                    break;
                // Opção 3: Editar item existente
                case 3:
                    editarItem(estoque);
                    break;
                // Opção 4: Localizar e exibir item
                case 4:
                    localizarItem(estoque);
                    break;
                // Opção 5: Listar todos os items
                case 5:
                    estoque.listarItens();
                    break;
                // Opção 6: Registrar entrada de items
                case 6:
                    registrarEntrada(estoque);
                    break;
                // Opção 7: Registrar saída de items
                case 7:
                    registrarSaida(estoque);
                    break;
                // Opção 8: Exibir histórico de movimentos
                case 8:
                    estoque.exibirHistorico();
                    break;
                // Opção 9: Buscar item na internet
                case 9:
                    buscarInternet(estoque);
                    break;
                // Opção 0: Salvar e sair
                case 0:
                    cout << "Salvando dados e saindo..." << endl;
                    // Destrutor de 'estoque' será chamado automaticamente
                    // ao final de main() - ele salva dados em arquivos
                    break;
                // Opção inválida
                default:
                    cout << "Opcao invalida. Tente novamente." << endl;
            }
        } catch (const EstoqueException& e) {
            // Captura exceções específicas do módulo estoque
            cerr << "ERRO: " << e.what() << endl;
        } catch (const std::exception& e) {
            // Captura outras exceções STL (por segurança)
            cerr << "ERRO INESPERADO: " << e.what() << endl;
        }

        // Se não saiu (opcao != 0), pausa para usuário ver mensagem
        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);  // Continua até opção 0

    return 0;  // Sucesso
}

// === IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ===

/**
 * Exibe menu na tela com todas as opções disponíveis.
 * Retorna: inteiro com opção escolhida pelo usuário
 */
int exibirMenu() {
    cout << "=================================" << endl;
    cout << "   MODULO ESTOQUE" << endl;
    cout << "=================================" << endl;
    cout << "1. Adicionar Item" << endl;
    cout << "2. Remover Item" << endl;
    cout << "3. Modificar Item" << endl;
    cout << "4. Localizar Item (Mostrar)" << endl;
    cout << "5. Listar Itens (Imprimir Listagem)" << endl;
    cout << "6. Registrar ENTRADA" << endl;
    cout << "7. Registrar SAIDA" << endl;
    cout << "8. Exibir Historico de Movimentacao" << endl;
    cout << "9. Buscar Item na Internet" << endl;
    cout << "---------------------------------" << endl;
    cout << "0. Salvar e Sair" << endl;
    cout << "=================================" << endl;
    return lerInteiro("Escolha uma opcao: ");
}

/**
 * Limpa a tela do console.
 * Cross-platform: Windows (cls) vs Linux/Mac (clear)
 */
void limparTela() {
#ifdef _WIN32
    // Windows: usar comando 'cls'
    system("cls");
#else
    // Linux/Mac: usar comando 'clear'
    system("clear");
#endif
}

/**
 * Pausa a execução até que usuário pressione ENTER.
 * Essencial para ler mensagens antes de próxima tela.
 */
void pausar() {
    cout << "\nPressione ENTER para continuar..." << endl;
    
    // Descarta caractere newline no buffer (se houver de input anterior)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    // Se cin falhou antes, limpa estado de erro
    if (cin.fail()) {
        cin.clear();
    }
    
    // Lê uma linha (até ENTER) - descarta o valor
    string dummy;
    getline(cin, dummy);
}

/**
 * Lê um inteiro do usuário com validação.
 * Loop até entrada válida (protege contra letras, símbolos, etc)
 * 
 * Parâmetro:
 *   - prompt: mensagem a exibir (ex: "Digite ID: ")
 * 
 * Retorna: inteiro válido lido
 * 
 * Comportamento:
 * - Exibe prompt
 * - Se cin falha (não é número): limpa erro e pede novamente
 * - Se EOF (fim de entrada): detecta e sai com exit(0)
 * - Descarta resto da linha no buffer
 * - Retorna valor lido
 * 
 * Tratamento de EOF: essencial para programas automatizados
 * (testes) que fecham stdin - evita loops infinitos
 */
int lerInteiro(const string& prompt) {
    int valor;
    while (true) {
        cout << prompt;
        
        // Tenta ler inteiro de cin
        if (!(cin >> valor)) {
            // Falha na leitura
            if (cin.eof()) {
                // EOF: entrada foi fechada/interrompida
                cout << "Entrada interrompida (EOF). Saindo..." << endl;
                std::exit(0);  // Sai da aplicação
            }
            
            // Outro erro: limpa estado de erro
            cin.clear();
            
            // Descarta resto da linha inválida
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // Pede novamente
            cout << "Entrada invalida. Por favor, digite um numero." << endl;
        } else {
            // Sucesso: limpa o buffer (remove newline)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

/**
 * Lê uma string do usuário.
 * String pode estar vazia (diferente de lerStringNaoVazia).
 * 
 * Parâmetro:
 *   - prompt: mensagem a exibir (ex: "Link: ")
 * 
 * Retorna: string lida (pode estar vazia "")
 * 
 * Comportamento:
 * - Exibe prompt
 * - Lê uma linha completa até ENTER
 * - Se EOF: detecta e sai com exit(0)
 * - Retorna string (vazia ou com conteúdo)
 * 
 * Tratamento de EOF: essencial para programas automatizados
 */
string lerString(const string& prompt) {
    string valor;
    cout << prompt;
    
    // Lê uma linha de cin (até ENTER)
    if (!std::getline(cin, valor)) {
        // getline falhou: EOF
        cout << "Entrada interrompida (EOF). Saindo..." << endl;
        std::exit(0);  // Sai da aplicação
    }
    
    return valor;  // Retorna string (pode estar vazia)
}

/**
 * Lê uma string do usuário garantindo que não é vazia.
 * Loop até usuário digitar algo não vazio.
 * 
 * Parâmetro:
 *   - prompt: mensagem a exibir (ex: "Nome: ")
 * 
 * Retorna: string não-vazia lida
 * 
 * Comportamento:
 * - Exibe prompt
 * - Se string vazia: exibe erro e pede novamente
 * - Se EOF: detecta e sai com exit(0)
 * - Continua até ter string com conteúdo
 * 
 * Uso: campos obrigatórios como nome, descrição
 */
string lerStringNaoVazia(const string& prompt) {
    string valor;
    while (true) {
        cout << prompt;
        
        // Lê uma linha
        if (!std::getline(cin, valor)) {
            // getline falhou: EOF
            cout << "Entrada interrompida (EOF). Saindo..." << endl;
            std::exit(0);  // Sai da aplicação
        }
        
        // Verifica se está vazia
        if (valor.empty()) {
            cout << "Este campo nao pode ficar vazio." << endl;
            // Loop continua pedindo
        } else {
            return valor;  // Retorna string não-vazia
        }
    }
}

// === IMPLEMENTAÇÃO DAS FUNÇÕES DE FUNCIONALIDADE ===

/**
 * Menu opção 1: Adiciona novo item ao estoque.
 * 
 * Fluxo:
 * 1. Pede tipo: 1 = PRODUTO, 2 = MATERIA-PRIMA
 * 2. Pede dados comuns: nome, descrição, quantidade, link
 * 3. Pede detalhe específico:
 *    - PRODUTO: categoria
 *    - MATERIA: fornecedor
 * 4. Cria ItemProduto ou ItemMateria apropriado
 * 5. Adiciona ao estoque
 * 
 * Requisito POO:
 * - Demonstra especialização: PRODUTO vs MATERIA diferem
 * - Cria objetos polimórficos (ItemProduto/ItemMateria via Item*)
 * - Usa try/catch implícito (exceções capturadas em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (modifica adicionando item)
 */
void adicionarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Adicionar Novo Item ---" << endl;
    
    // Pede tipo: 1 = PRODUTO, 2 = MATERIA
    int tipo = 0;
    while (tipo != 1 && tipo != 2) {
        tipo = lerInteiro("Tipo (1 - Produto, 2 - Materia-Prima): ");
    }

    // Pede dados comuns a ambos os tipos
    string nome = lerStringNaoVazia("Nome: ");
    string desc = lerStringNaoVazia("Descricao: ");
    int qtd = lerInteiro("Quantidade inicial: ");
    string link = lerString("Link para info (ex: http://...): ");
    
    // Se usuário deixou link vazio: gera automático (Google Search)
    if (link.empty()) {
        link = "http://google.com/search?q=\"" + nome + "\"";
    }

    // Cria item apropriado baseado em tipo
    if (tipo == 1) {
        // Tipo 1: PRODUTO
        // Pede categoria específica de produto
        string categoria = lerStringNaoVazia("Categoria do Produto: ");
        // Cria ItemProduto (neto de Item) com new (alocação dinâmica)
        Item* produto = new ItemProduto(nome, desc, qtd, link, categoria);
        // Adiciona ao estoque (armazenado como Item* - polimórfico)
        estoque.adicionarItem(produto);
    } else {
        // Tipo 2: MATERIA-PRIMA
        // Pede fornecedor específico de matéria-prima
        string fornecedor = lerStringNaoVazia("Fornecedor da Materia-Prima: ");
        // Cria ItemMateria (neto de Item) com new (alocação dinâmica)
        Item* materia = new ItemMateria(nome, desc, qtd, link, fornecedor);
        // Adiciona ao estoque (armazenado como Item* - polimórfico)
        estoque.adicionarItem(materia);
    }
    
    cout << "Item '" << nome << "' adicionado com sucesso." << endl;
}

/**
 * Menu opção 2: Remove item do estoque pelo ID.
 * 
 * Fluxo:
 * 1. Pede ID do item a remover
 * 2. Chama estoque.removerItem(id)
 * 3. Se não encontrado: EstoqueException lançada e capturada em main
 * 4. Destrutor do item libera memória
 * 
 * Exceções:
 * - EstoqueException se ID não existe (tratada em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (modifica removendo item)
 */
void removerItem(Estoque& estoque) {
    limparTela();
    cout << "--- Remover Item ---" << endl;
    
    // Pede ID do item a remover
    int id = lerInteiro("Digite o ID do item a ser removido: ");
    
    // Chama removerItem do Estoque
    // Exceção EstoqueException será tratada no loop principal (main)
    estoque.removerItem(id);
}

/**
 * Menu opção 3: Edita dados de item existente.
 * 
 * Fluxo:
 * 1. Pede ID do item a editar
 * 2. Chama estoque.editarItem(id)
 * 3. Função pede novos valores para:
 *    - Nome
 *    - Descrição
 *    - Link
 * 4. Se deixar em branco: mantém valor anterior
 * 5. Se não encontrado: EstoqueException lançada e capturada em main
 * 
 * Não editável:
 * - ID (único, gerado no ato da criação)
 * - Tipo (PRODUTO/MATERIA define estrutura)
 * - Categoria/Fornecedor (específico)
 * 
 * Exceções:
 * - EstoqueException se ID não existe (tratada em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (modifica editando item)
 */
void editarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Modificar Item ---" << endl;
    
    // Pede ID do item a editar
    int id = lerInteiro("Digite o ID do item a ser modificado: ");
    
    // Chama editarItem do Estoque
    // Função pede novos valores e valida
    // Exceção EstoqueException será tratada no loop principal (main)
    estoque.editarItem(id);
}

/**
 * Menu opção 4: Busca e localiza um item no estoque.
 * 
 * Fluxo:
 * 1. Oferece duas opções de busca:
 *    - 1: Por ID (busca rápida - O(n))
 *    - 2: Por Nome (busca linear - O(n))
 * 2. Pede critério de busca
 * 3. Chama função de busca apropriada
 * 4. Se encontrado: exibe detalhes via exibirDetalhes()
 * 5. Se não encontrado: EstoqueException lançada e capturada em main
 * 
 * Polimorfismo:
 * - itemEncontrado->exibirDetalhes() chama método virtual
 * - Se for ItemProduto: exibe com categoria
 * - Se for ItemMateria: exibe com fornecedor
 * 
 * Exceções:
 * - EstoqueException se não encontrado (tratada em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (apenas lê, busca)
 */
void localizarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Localizar Item (Mostrar) ---" << endl;
    
    // Pede tipo de busca: 1 = ID, 2 = Nome
    int tipoBusca = 0;
    while (tipoBusca != 1 && tipoBusca != 2) {
        tipoBusca = lerInteiro("Buscar por (1 - ID, 2 - Nome): ");
    }

    // Variável para armazenar resultado da busca
    Item* itemEncontrado = nullptr;
    
    // Executa busca apropriada
    if (tipoBusca == 1) {
        // Busca por ID
        int id = lerInteiro("Digite o ID: ");
        itemEncontrado = estoque.buscarItemPorId(id);  // Pode lançar exceção
    } else {
        // Busca por Nome
        string nome = lerStringNaoVazia("Digite o Nome: ");
        itemEncontrado = estoque.buscarItemPorNome(nome);  // Pode lançar exceção
    }

    // Se chegou aqui, encontrou o item
    if (itemEncontrado) {
        cout << "Item encontrado:" << endl;
        itemEncontrado->exibirDetalhes();  // Polimorfismo: ItemProduto vs ItemMateria
    }
    // Exceção de "não encontrado" é tratada no try-catch da main
}

/**
 * Menu opção 6: Registra uma ENTRADA de items no estoque.
 * Entrada = recebimento/compra de items.
 * 
 * Fluxo:
 * 1. Pede ID do item
 * 2. Pede quantidade a adicionar
 * 3. Chama estoque.registrarEntrada(id, qtd)
 * 4. Função aumenta quantidade do item
 * 5. Cria MovimentoEstoque e adiciona ao histórico
 * 6. Se não encontrado ou qtd inválida: EstoqueException em main
 * 
 * Exceções:
 * - EstoqueException se ID não existe
 * - EstoqueException se qtd negativa (tratada em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (modifica quantidade e histórico)
 */
void registrarEntrada(Estoque& estoque) {
    limparTela();
    cout << "--- Registrar Entrada ---" << endl;
    
    // Pede ID do item que recebe quantidade
    int id = lerInteiro("Digite o ID do item: ");
    
    // Pede quantidade a adicionar
    int qtd = lerInteiro("Digite a quantidade de ENTRADA: ");
    
    // Registra entrada (aumenta quantidade, cria movimento)
    estoque.registrarEntrada(id, qtd);
}

/**
 * Menu opção 7: Registra uma SAIDA de items no estoque.
 * Saída = venda/uso de items.
 * 
 * Fluxo:
 * 1. Pede ID do item
 * 2. Pede quantidade a remover
 * 3. Chama estoque.registrarSaida(id, qtd)
 * 4. Função diminui quantidade do item (valida quantidade suficiente)
 * 5. Cria MovimentoEstoque e adiciona ao histórico
 * 6. Se não encontrado, qtd inválida, ou insuficiente: EstoqueException em main
 * 
 * Validações:
 * - ID deve existir
 * - Quantidade não pode ser negativa
 * - Quantidade em estoque deve ser suficiente (não pode ficar negativo)
 * 
 * Exceções:
 * - EstoqueException se ID não existe
 * - EstoqueException se qtd negativa
 * - EstoqueException se quantidade em estoque é insuficiente (tratadas em main)
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (modifica quantidade e histórico)
 */
void registrarSaida(Estoque& estoque) {
    limparTela();
    cout << "--- Registrar Saida ---" << endl;
    
    // Pede ID do item que perde quantidade
    int id = lerInteiro("Digite o ID do item: ");
    
    // Pede quantidade a remover
    int qtd = lerInteiro("Digite a quantidade de SAIDA: ");
    
    // Registra saída (diminui quantidade, cria movimento)
    estoque.registrarSaida(id, qtd);
}

/**
 * Menu opção 9: Busca item na internet abrindo navegador com link.
 * 
 * Fluxo:
 * 1. Pede ID do item
 * 2. Busca item no estoque
 * 3. Obtém link do item (campo linkInfo)
 * 4. Constrói comando de sistema apropriado:
 *    - Windows: start "URL"
 *    - macOS: open "URL"
 *    - Linux: xdg-open "URL" (mais genérico que firefox)
 * 5. Executa comando com system()
 * 6. Se falhar: exibe erro
 * 
 * Exceções:
 * - EstoqueException se ID não existe (tratada em main)
 * - Erros de system(): exibidos mas não interrompem
 * 
 * Cross-platform:
 * - #ifdef para detectar SO em tempo de compilação
 * - Cada SO tem seu comando de abertura
 * 
 * Parâmetro:
 *   - estoque: referência ao Estoque (apenas lê para buscar item)
 */
void buscarInternet(Estoque& estoque) {
    limparTela();
    cout << "--- Buscar Item na Internet ---" << endl;
    
    // Pede ID do item
    int id = lerInteiro("Digite o ID do item para buscar: ");
    
    // Busca item (exceção se não encontrado - capturada em main)
    Item* item = estoque.buscarItemPorId(id);

    // Obtém URL do item
    string url = item->getLink();
    string comando;

    // Constrói comando apropriado para cada SO
#ifdef _WIN32
    // Windows: usar comando 'start'
    comando = "start \"\" \"" + url + "\"";
#elif __APPLE__
    // macOS: usar comando 'open'
    comando = "open \"" + url + "\"";
#else
    // Linux e outros Unix: usar 'xdg-open' (mais genérico que firefox)
    // 'xdg-open' abre com navegador padrão
    comando = "xdg-open \"" + url + "\"";
    // Alternativa específica para Firefox (menos portável):
    // comando = "firefox \"" + url + "\"";
#endif

    // Informa ao usuário
    cout << "Abrindo navegador com o link: " << url << endl;
    
    // Executa comando (retorna 0 se sucesso, outro valor se erro)
    int resultado = system(comando.c_str());

    // Verifica resultado
    if (resultado != 0) {
        cerr << "Erro: Nao foi possivel abrir o navegador." << endl;
        cerr << "Comando executado: " << comando << endl;
    }
}