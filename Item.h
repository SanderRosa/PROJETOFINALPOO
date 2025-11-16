// Guarda de header para evitar inclusão múltipla
#ifndef ITEM_H
#define ITEM_H

// Inclui biblioteca padrão para strings
#include <string>
// Inclui interface para exibição de objetos
#include "IExibivel.h"
// Inclui classe de exceção personalizada
#include "EstoqueException.h"

/**
 * Classe base abstrata que representa um item genérico no estoque.
 * Herda de IExibivel para garantir que todos os itens possam ser exibidos.
 * Requisito de POO: classe base para hierarquia de herança.
 */
class Item : public IExibivel {
protected:
    // Identificador único do item (autoincremento)
    int idItem;
    // Nome descritivo do item
    std::string nome;
    // Descrição detalhada do item
    std::string descricao;
    // Quantidade atual em estoque
    int quantidade;
    // Link para buscar informações do item na internet
    std::string linkInfo;

    // Contador estático compartilhado por todos os itens para gerar IDs únicos
    static int proximoId;

public:
    /**
     * Construtor: inicializa um novo item com nome, descrição, quantidade e link.
     * Atribui automaticamente um ID único incrementando proximoId.
     */
    Item(const std::string& nome, const std::string& desc, int qtd, const std::string& link);

    /**
     * Destrutor virtual: essencial pois é classe base com métodos virtuais.
     * Garante destruição correta de objetos derivados.
     */
    virtual ~Item() {}

    // === MÉTODOS DE ACESSO (GETTERS) ===
    // Retorna o ID único do item
    int getId() const;
    // Retorna o nome do item
    std::string getNome() const;
    // Retorna a quantidade atual em estoque
    int getQuantidade() const;
    // Retorna o link de informação do item
    std::string getLink() const;
    // Retorna a descrição do item
    std::string getDescricao() const;

    // === MÉTODOS PARA MANIPULAÇÃO DE QUANTIDADE ===
    // Adiciona uma quantidade positiva ao estoque (entrada)
    void adicionarQtd(int qtd);
    // Remove uma quantidade do estoque (saída), com validação
    void removerQtd(int qtd);

    /**
     * Atualiza os campos básicos do item (nome, descrição, link).
     * Útil para edição de informações via menu.
     */
    void atualizarDados(const std::string& novoNome, const std::string& novaDesc, const std::string& novoLink);

    // === MÉTODOS VIRTUAIS PUROS (POLIMORFISMO) ===
    // Estes métodos devem ser implementados obrigatoriamente pelas classes filhas
    // Permitem comportamentos específicos de cada tipo de item

    /**
     * Retorna uma string indicando o tipo: "PRODUTO" ou "MATERIA".
     * Método puro: cada subclasse implementa sua versão.
     */
    virtual std::string getTipo() const = 0;

    /**
     * Retorna o detalhe específico: categoria (produto) ou fornecedor (materia).
     * Método puro: cada subclasse implementa sua versão.
     */
    virtual std::string getDetalheEspecifico() const = 0;

    /**
     * Define o próximo ID a ser usado (usado ao carregar dados do arquivo).
     * Método estático: pertence à classe, não aos objetos.
     */
    static void setProximoId(int id);
};

// Fecha guarda de header
#endif // ITEM_H