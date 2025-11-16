#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "IExibivel.h"
#include "EstoqueException.h"

/**
 * @brief Classe base abstrata para todos os itens do estoque.
 * Cumpre o requisito de definição de uma classe base.
 * Também implementa a interface IExibivel.
 */
class Item : public IExibivel {
protected:
    int idItem;
    std::string nome;
    std::string descricao;
    int quantidade;
    std::string linkInfo;

    // ID estático para garantir identificadores únicos
    static int proximoId;

public:
    /**
     * Construtor da classe Item.
     */
    Item(const std::string& nome, const std::string& desc, int qtd, const std::string& link);

    /**
     * Destrutor virtual.
     */
    virtual ~Item() {}

    // Métodos de acesso (Getters)
    int getId() const;
    std::string getNome() const;
    int getQuantidade() const;
    std::string getLink() const;
    std::string getDescricao() const;

    // Métodos para manipulação da quantidade
    void adicionarQtd(int qtd);
    void removerQtd(int qtd);

    /**
     * Atualiza os dados básicos do item.
     */
    void atualizarDados(const std::string& novoNome, const std::string& novaDesc, const std::string& novoLink);

    // Métodos virtuais puros para serem implementados pelas classes filhas
    // Usados para polimorfismo (ex. ao salvar em arquivo)

    /**
     * Retorna o tipo do item ("PRODUTO" ou "MATERIA").
     */
    virtual std::string getTipo() const = 0;

    /**
     * Retorna o detalhe específico da classe filha (categoria ou fornecedor).
     */
    virtual std::string getDetalheEspecifico() const = 0;

    /**
     * Define o próximo ID a ser usado ao carregar dados.
     */
    static void setProximoId(int id);
};

#endif // ITEM_H