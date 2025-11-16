// Guarda de header para evitar inclusão múltipla
#ifndef ITEMPRODUTO_H
#define ITEMPRODUTO_H

// Inclui classe base Item
#include "Item.h"

/**
 * Classe que representa um Produto final no estoque.
 * Herda de Item e especializa para tipo "PRODUTO".
 * Requisito POO: herança para especialização de comportamento.
 * Atributo específico: categoria (eletrônicos, roupas, alimentos, etc).
 */
class ItemProduto : public Item {
private:
    // Campo específico: categoria do produto (ex: "Ferragens", "Eletrônicos")
    std::string categoriaProduto;

public:
    /**
     * Construtor: inicializa com dados de Item + categoria específica.
     * Chama construtor da classe base e define a categoria.
     */
    ItemProduto(const std::string& nome, const std::string& desc, int qtd, const std::string& link, const std::string& categoria);

    /**
     * Sobrescreve exibirDetalhes() para exibir com categoria.
     * override: marca que sobrescreve método virtual da classe base.
     * Demonstra polimorfismo: cada subclasse exibe de forma diferente.
     */
    virtual void exibirDetalhes() const override;

    // === IMPLEMENTAÇÃO DE MÉTODOS VIRTUAIS PUROS ===
    // Estes foram declarados como "= 0" na classe base Item
    // Cada subclasse DEVE implementá-los

    /**
     * Retorna string "PRODUTO" para identificar tipo.
     * Usado ao salvar em arquivo (serialização).
     */
    virtual std::string getTipo() const override;
    
    /**
     * Retorna a categoria (detalhe específico de produto).
     * Usado ao salvar em arquivo.
     */
    virtual std::string getDetalheEspecifico() const override;
};

// Fecha guarda de header
#endif // ITEMPRODUTO_H