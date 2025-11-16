#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "ListaGenerica.h"
#include "Item.h"
#include "MovimentoEstoque.h"
#include <string>

/**
 * Classe principal que gerencia todas as operações do sistema de estoque.
 * Padrão Arquitetural: Manager/Coordinator - coordena todas as operações
 * Requisito POO: classe que utiliza templates (ListaGenerica), herança (Item*),
 * polimorfismo (chamar getTipo() em Item* que pode ser ItemProduto ou ItemMateria)
 * e tratamento de exceções (EstoqueException)
 * 
 * Responsabilidades:
 * 1. Adicionar/remover/editar items (ItemProduto ou ItemMateria)
 * 2. Buscar items por ID ou nome
 * 3. Registrar ENTRADAS (adições) e SAIDAS (remoções) com histórico
 * 4. Persistência: salvar/carregar dados de arquivos (itens.txt, movimentos.txt)
 * 5. Exibir relatórios de items e movimentações
 * 
 * Padrão Persistência: arquivo-baseado com serialização em texto
 * Formato itens.txt: TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
 * Formato movimentos.txt: ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
 * 
 * Ciclo de vida:
 * - Construtor: carrega dados dos arquivos (se existem)
 * - Operações: add/remove/edit/registrar movimentos via interface
 * - Destrutor: salva dados e libera memória
 */
class Estoque {
private:
    // Lista genérica de ponteiros Item* (polimórficos)
    // Armazena tanto ItemProduto quanto ItemMateria através de ponteiro base
    // Requisito POO: demonstra polimorfismo (mesmo container, tipos diferentes)
    ListaGenerica<Item*> itens;
    
    // Lista genérica de movimentações (ENTRADA/SAIDA)
    // Histórico completo de todas transações para auditoria
    ListaGenerica<MovimentoEstoque*> historico;

    // Nomes dos arquivos para persistência de dados
    // Separação deliberada: items vs movimentos (responsabilidades diferentes)
    const std::string ARQUIVO_ITENS = "itens.txt";
    const std::string ARQUIVO_MOVIMENTOS = "movimentos.txt";

public:
    /**
     * Construtor do Estoque.
     * Chamado ao iniciar a aplicação.
     * 
     * Comportamento:
     * - Cria listas vazias (ListaGenerica<Item*>, ListaGenerica<MovimentoEstoque*>)
     * - Chama carregarDados() para tentar carregar estado anterior
     * - Se arquivos não existem, começa com estoque vazio
     * 
     * Requisito POO: construtor com inicialização de membros
     */
    Estoque();

    /**
     * Destrutor do Estoque.
     * Chamado ao encerrar aplicação.
     * 
     * Comportamento:
     * - Salva dados atuais em itens.txt e movimentos.txt
     * - Libera memória alocada dinamicamente:
     *   * delete cada Item* em itens
     *   * delete cada MovimentoEstoque* em historico
     * - Evita memory leaks
     * 
     * Requisito POO: destrutor com limpeza de recursos
     */
    ~Estoque();

    /**
     * Adiciona um novo item ao estoque.
     * 
     * Parâmetro:
     *   - item: ponteiro para Item alocado com new (ItemProduto ou ItemMateria)
     * 
     * Comportamento:
     * - Adiciona item à lista genérica itens
     * - Não aloca memória (já alocada pela chamadora)
     * - Não valida duplicatas de ID (Item::proximoId garante unicidade)
     * 
     * Exemplo: 
     *   Estoque e;
     *   e.adicionarItem(new ItemProduto("Parafuso", "M8", 100, "http://...", "Hardware"));
     * 
     * Requisito POO: recebe ponteiro Item* (polimórfico)
     */
    void adicionarItem(Item* item);

    /**
     * Remove um item do estoque pelo ID.
     * 
     * Parâmetro:
     *   - id: ID único do item a ser removido
     * 
     * Comportamento:
     * - Procura item com este ID na lista
     * - Se encontrado: deleta da lista e libera memória (delete)
     * - Se não encontrado: lança EstoqueException
     * 
     * Efeito colateral: movimentos históricos do item permanecem (auditoria)
     * 
     * Lança: EstoqueException("Item não encontrado") se ID inválido
     * 
     * Exemplo: e.removerItem(1);
     */
    void removerItem(int id);

    /**
     * Edita campos de um item existente (nome, descrição, quantidade, link).
     * 
     * Parâmetro:
     *   - id: ID único do item a ser editado
     * 
     * Comportamento:
     * - Busca item com este ID
     * - Se encontrado: permite edição interativa dos campos
     * - Se não encontrado: lança EstoqueException
     * 
     * Campos editáveis: nome, descrição, quantidade, link
     * NÃO editável: ID (único), tipo (PRODUTO/MATERIA), detalhe especial (categoria/fornecedor)
     * 
     * Lança: EstoqueException("Item não encontrado") se ID inválido
     * 
     * Exemplo: e.editarItem(1);
     */
    void editarItem(int id);

    /**
     * Busca um item no estoque pelo ID.
     * 
     * Parâmetro:
     *   - id: ID único do item
     * 
     * Retorna: ponteiro para o Item encontrado (pode fazer cast para ItemProduto/ItemMateria)
     * 
     * Lança: EstoqueException("Item não encontrado") se ID não existe
     * 
     * Requisito POO: retorna Item* (tipo base), polimórfico
     * 
     * Exemplo:
     *   Item* item = e.buscarItemPorId(1);
     *   if (item->getTipo() == "PRODUTO") { ... }
     */
    Item* buscarItemPorId(int id);

    /**
     * Busca um item no estoque pelo nome (procura substring/aproximada).
     * 
     * Parâmetro:
     *   - nome: nome (ou parte do nome) do item a buscar
     * 
     * Retorna: ponteiro para o primeiro Item encontrado com este nome
     * 
     * Lança: EstoqueException("Item não encontrado") se nome não existe
     * 
     * Comportamento: busca linear pela lista, compara nomes
     * 
     * Exemplo:
     *   Item* item = e.buscarItemPorNome("Aço");
     */
    Item* buscarItemPorNome(const std::string& nome);

    /**
     * Lista todos os items no estoque com seus detalhes.
     * 
     * Comportamento:
     * - Itera por todos os items
     * - Chama exibirDetalhes() em cada um (polimórfico)
     * - Exibe diferente para ItemProduto (com categoria) vs ItemMateria (com fornecedor)
     * 
     * const: método apenas lê, não modifica estoque
     * 
     * Requisito POO: demonstra polimorfismo (mesma chamada, comportamento diferente)
     * 
     * Exemplo: e.listarItens();
     */
    void listarItens() const;

    /**
     * Exibe o histórico de todas as movimentações (ENTRADA/SAIDA).
     * 
     * Comportamento:
     * - Itera por todos os MovimentoEstoque registrados
     * - Exibe resumo: ID, data, tipo, quantidade, item
     * - Permite auditoria completa das operações
     * 
     * const: método apenas lê, não modifica histórico
     * 
     * Exemplo: e.exibirHistorico();
     */
    void exibirHistorico() const;

    /**
     * Registra uma ENTRADA de items no estoque (recebimento/compra).
     * Aumenta quantidade e gera movimento no histórico.
     * 
     * Parâmetros:
     *   - idItem: ID do item que recebeu quantidade
     *   - qtd: quantidade adicionada
     * 
     * Comportamento:
     * - Busca item pelo ID
     * - Aumenta quantidade do item
     * - Cria MovimentoEstoque com tipo ENTRADA
     * - Adiciona movimento ao histórico
     * 
     * Lança: EstoqueException se ID inválido ou qtd negativa
     * 
     * Exemplo: e.registrarEntrada(1, 50);  // Adicionou 50 unidades de item 1
     */
    void registrarEntrada(int idItem, int qtd);

    /**
     * Registra uma SAIDA de items do estoque (venda/uso).
     * Diminui quantidade e gera movimento no histórico.
     * 
     * Parâmetros:
     *   - idItem: ID do item que foi removido
     *   - qtd: quantidade removida
     * 
     * Comportamento:
     * - Busca item pelo ID
     * - Diminui quantidade do item
     * - Cria MovimentoEstoque com tipo SAIDA
     * - Adiciona movimento ao histórico
     * - Valida que quantidade não fique negativa (lança EstoqueException)
     * 
     * Lança: EstoqueException se ID inválido, qtd negativa, ou insuficiente em estoque
     * 
     * Exemplo: e.registrarSaida(1, 10);  // Removeu 10 unidades de item 1
     */
    void registrarSaida(int idItem, int qtd);

    /**
     * Salva todos os dados (items e movimentos) em arquivos de texto.
     * Chamado no destrutor ou manualmente para checkpoint.
     * 
     * Processo:
     * 1. Abre ARQUIVO_ITENS em modo escrita
     * 2. Para cada item: escreve TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
     * 3. Abre ARQUIVO_MOVIMENTOS em modo escrita
     * 4. Para cada movimento: escreve ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
     * 
     * Serialização:
     * - getTipo() retorna "PRODUTO" ou "MATERIA"
     * - Todos campos convertidos para string
     * - Semicolon (;) como separador
     * 
     * Formato permite reconstruir exatamente os objetos na próxima carga
     * 
     * const: método apenas lê dados, não modifica
     * 
     * Requisito POO: demonstra persistência baseada em polimorfismo
     */
    void salvarDados() const;

    /**
     * Carrega todos os dados (items e movimentos) dos arquivos de texto.
     * Chamado no construtor ao iniciar aplicação.
     * 
     * Processo itens.txt:
     * 1. Abre ARQUIVO_ITENS
     * 2. Para cada linha: lê TYPE;ID;NAME;DESC;QTY;LINK;DETAIL
     * 3. Se TYPE=="PRODUTO": cria new ItemProduto(...) com detail como categoria
     * 4. Se TYPE=="MATERIA": cria new ItemMateria(...) com detail como fornecedor
     * 5. Chama Item::setProximoId() para continuar IDs
     * 6. Adiciona à lista itens
     * 
     * Processo movimentos.txt:
     * 1. Abre ARQUIVO_MOVIMENTOS
     * 2. Para cada linha: lê ID;DATA;TIPO;QTY;IDITEM;NOMEITEM
     * 3. Converte TIPO ("ENTRADA"/"SAIDA") para enum TipoMovimento
     * 4. Cria new MovimentoEstoque(...) com construtor de carregamento
     * 5. Chama MovimentoEstoque::setProximoId() para continuar IDs
     * 6. Adiciona à lista historico
     * 
     * Tratamento de erro:
     * - Se arquivo não existe: cria estoque vazio (primeira execução)
     * - Se arquivo corrompido: pode lançar exceção ou ignorar linha
     * 
     * Requisito POO: desserialização polimórfica baseada em getTipo()
     */
    void carregarDados();
};

#endif // ESTOQUE_H