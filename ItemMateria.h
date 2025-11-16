#ifndef ITEMMATERIA_H
#define ITEMMATERIA_H

#include "Item.h"

/**
 * @brief Classe filha que representa uma Matéria-Prima.
 * Cumpre o requisito de uso de herança.
 */
class ItemMateria : public Item {
private:
    std::string fornecedor;

public:
    /**
     * @brief Construtor do ItemMateria.
     */
    ItemMateria(const std::string& nome, const std::string& desc, int qtd, const std::string& link, const std::string& fornecedor);

    /**
     * @brief Sobrescreve o método para exibir detalhes.
     * Demonstra polimorfismo.
     */
    virtual void exibirDetalhes() const override;

    // Implementação dos métodos virtuais da classe base
    virtual std::string getTipo() const override;
    virtual std::string getDetalheEspecifico() const override;
};

#endif // ITEMMATERIA_H_H