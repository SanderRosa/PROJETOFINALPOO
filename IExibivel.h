#ifndef IEXIBIVEL_H
#define IEXIBIVEL_H

/**
 * @brief Interface que define um contrato para classes que podem ser "exibidas".
 * Cumpre o requisito de implementação de uma interface.
 */
class IExibivel {
public:
    /**
     * Destrutor virtual (essencial para classes base com funções virtuais).
     */
    virtual ~IExibivel() {}

    /**
     * Função virtual pura para exibir detalhes (implementar nas filhas).
     */
    virtual void exibirDetalhes() const = 0;
};

#endif // IEXIBIVEL_HH