// Guarda de header para evitar inclusão múltipla
#ifndef IEXIBIVEL_H
#define IEXIBIVEL_H

/**
 * Interface (classe abstrata pura) que define contrato para classes exibíveis.
 * Requisito de POO: implementação de interface.
 * Qualquer classe que implemente IExibivel deve definir exibirDetalhes().
 */
class IExibivel {
public:
    /**
     * Destrutor virtual: essencial para interfaces com métodos virtuais.
     * Garante que objetos derivados sejam destruídos corretamente.
     */
    virtual ~IExibivel() {}

    /**
     * Método virtual puro que deve ser implementado por todas as subclasses.
     * Responsável por exibir os detalhes do objeto na tela/console.
     * const: não modifica o estado do objeto.
     */
    virtual void exibirDetalhes() const = 0;
};

// Fecha guarda de header
#endif // IEXIBIVEL_HH