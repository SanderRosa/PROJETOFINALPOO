#ifndef ITEMPRODUTO_H
#define ITEMPRODUTO_H

#include "Item.h"

/**
 * @brief Classe filha que representa um Produto final.
 * Cumpre o requisito de uso de herança.
 */
class ItemProduto : public Item {
private:
    std::string categoriaProduto;

public:
    /**     * Construtor do ItemProduto.
     */
    ItemProduto(const std::string& nome, const std::string& desc, int qtd, const std::string& link, const std::string& categoria);

    /**
     * Sobrescreve o método para exibir detalhes (polimorfismo).
     */
    virtual void exibirDetalhes() const override;

    // Implementação dos métodos virtuais da classe base
    virtual std::string getTipo() const override;
    virtual std::string getDetalheEspecifico() const override;
};

#endif // ITEMPRODUTO_H