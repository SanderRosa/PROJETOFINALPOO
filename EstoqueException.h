#ifndef ESTOQUEEXCEPTION_H
#define ESTOQUEEXCEPTION_H

#include <exception>
#include <string>

/**
 * @brief Classe de exceção personalizada para o módulo de estoque.
 * Cumpre o requisito de tratamento de exceções.
 */
class EstoqueException : public std::exception {
private:
    std::string mensagem;

public:
    /**
     * @brief Construtor que recebe a mensagem de erro.
     * @param msg A mensagem de erro.
     */
    EstoqueException(const std::string& msg) : mensagem(msg) {}

    /**
     * @brief Sobrescreve o método what() da classe std::exception.
     * @return A mensagem de erro como uma string C.
     */
    virtual const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

#endif // ESTOQUEEXCEPTION_HEXCEPTION_H