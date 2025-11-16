#ifndef IEXIBIVEL_H
#define IEXIBIVEL_H

/**
 * @brief Interface que define um contrato para classes que podem ser "exibidas".
 * Cumpre o requisito de implementação de uma interface.
 */
class IExibivel {
public:
    /**
     * @brief Destrutor virtual padrão. Essencial para classes base com funções virtuais.
     */
    virtual ~IExibivel() {}

    /**
     * @brief Função virtual pura para exibir os detalhes de um objeto.
     * As classes filhas deverão implementar este método.
     */
    virtual void exibirDetalhes() const = 0;
};

#endif // IEXIBIVEL_HH