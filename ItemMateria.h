#ifndef ITEMMATERIA_H
#define ITEMMATERIA_H

#include "Item.h"

/**
 * Classe que representa uma Matéria-Prima (Material de Entrada) no estoque.
 * Herda de Item e especializa para o tipo "MATERIA".
 * Requisito POO: herança para especialização de comportamento.
 * Diferença de ItemProduto: matéria-prima é insumo (entrada), produto é saída (final).
 */
class ItemMateria : public Item {
private:
    // Campo específico: identificação do fornecedor da matéria-prima
    std::string fornecedor;

public:
    /**
     * Construtor de ItemMateria.
     * Parâmetros:
     *   - nome: nome da matéria-prima (ex: "Aço 1020")
     *   - desc: descrição detalhada
     *   - qtd: quantidade inicial em estoque
     *   - link: URL para documentação/referência
     *   - fornecedor: empresa que fornece esta matéria-prima
     * Requer POO: chamada de construtor da classe base via inicializador
     */
    ItemMateria(const std::string& nome, const std::string& desc, int qtd, const std::string& link, const std::string& fornecedor);

    /**
     * Sobrescreve exibirDetalhes() da classe base.
     * Exibe: ID, nome, descrição, quantidade, link e fornecedor.
     * Demonstra polimorfismo: método virtual chamado através de ponteiro Item*.
     * Requisito POO: polimorfismo (mesmo nome, comportamento diferente).
     */
    virtual void exibirDetalhes() const override;

    /**
     * Retorna "MATERIA" identificando este item como matéria-prima.
     * Usado em serialização para desserializar corretamente ao carregar arquivo.
     * Requisito POO: polimorfismo (cada subclasse retorna seu tipo).
     */
    virtual std::string getTipo() const override;

    /**
     * Retorna o detalhe específico: nome do fornecedor.
     * Em ItemProduto, retorna categoria.
     * Permite acesso ao campo diferente para cada especialização.
     * Requisito POO: polimorfismo (método virtual com implementação diferente).
     */
    virtual std::string getDetalheEspecifico() const override;
};

#endif // ITEMMATERIA_H