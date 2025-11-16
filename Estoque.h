#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "ListaGenerica.h"
#include "Item.h"
#include "MovimentoEstoque.h"
#include <string>

/**
 * @brief Classe principal que gerencia o estoque.
 * Utiliza as Listas Genéricas para armazenar itens e o histórico.
 */
class Estoque {
private:
    ListaGenerica<Item*> itens;
    ListaGenerica<MovimentoEstoque*> historico;

    // Nomes dos arquivos para persistência
    const std::string ARQUIVO_ITENS = "itens.txt";
    const std::string ARQUIVO_MOVIMENTOS = "movimentos.txt";

public:
    /**
     * @brief Construtor. Tenta carregar os dados dos arquivos.
     */
    Estoque();

    /**
     * @brief Destrutor. Salva os dados e libera a memória dos ponteiros.
     */
    ~Estoque();

    /**
     * @brief Adiciona um novo item ao estoque.
     * @param item Ponteiro para o item a ser adicionado.
     */
    void adicionarItem(Item* item);

    /**
     * @brief Remove um item do estoque pelo ID.
     * @param id O ID do item a ser removido.
     */
    void removerItem(int id);

    /**
     * @brief Edita os dados de um item existente.
     * @param id O ID do item a ser editado.
     */
    void editarItem(int id);

    /**
     * @brief Busca um item pelo ID.
     * @param id O ID do item.
     * @return Ponteiro para o item encontrado.
     * @throws EstoqueException se o item não for encontrado.
     */
    Item* buscarItemPorId(int id);

    /**
     * @brief Busca um item pelo nome.
     * @param nome O nome do item.
     * @return Ponteiro para o item encontrado.
     * @throws EstoqueException se o item não for encontrado.
     */
    Item* buscarItemPorNome(const std::string& nome);

    /**
     * @brief Lista todos os itens do estoque.
     */
    void listarItens() const;

    /**
     * @brief Exibe o histórico de movimentações.
     */
    void exibirHistorico() const;

    /**
     * @brief Registra a entrada de itens no estoque.
     * @param idItem O ID do item.
     * @param qtd A quantidade a ser adicionada.
     */
    void registrarEntrada(int idItem, int qtd);

    /**
     * @brief Registra a saída de itens no estoque.
     * @param idItem O ID do item.
     * @param qtd A quantidade a ser removida.
     */
    void registrarSaida(int idItem, int qtd);

    /**
     * @brief Salva os dados (itens e movimentos) em arquivos de texto.
     */
    void salvarDados() const;

    /**
     * @brief Carrega os dados (itens e movimentos) dos arquivos de texto.
     */
    void carregarDados();
};

#endif // ESTOQUE_H