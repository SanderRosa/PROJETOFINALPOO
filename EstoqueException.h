#ifndef ESTOQUEEXCEPTION_H
#define ESTOQUEEXCEPTION_H

#include <exception>
#include <string>

/**
 * Classe de exceção personalizada para o módulo de estoque.
 * Herda de std::exception para integrar com mecanismo padrão de exceções C++.
 * Requisito POO: tratamento de exceções para validação e controle de erro.
 * 
 * Usada para:
 * - Quantidade negativa em removerQtd()
 * - Item não encontrado em operações de busca
 * - Limite de quantidade excedido
 * - Erros de persistência (arquivo não pode ser lido/escrito)
 * 
 * Padrão: C++ permite throw/catch de EstoqueException em qualquer ponto do código
 * O try-catch em main.cpp captura e exibe mensagem personalizada do erro
 */
class EstoqueException : public std::exception {
private:
    // Mensagem de erro específica - será exibida ao usuário
    std::string mensagem;

public:
    /**
     * Construtor da exceção.
     * Parâmetro:
     *   - msg: mensagem descritiva do erro ocorrido
     * Exemplo: EstoqueException("Quantidade insuficiente em estoque")
     * 
     * Requisito POO: construtor com herança, chamando inicializador de membro
     */
    EstoqueException(const std::string& msg) : mensagem(msg) {}

    /**
     * Sobrescreve o método virtual what() de std::exception.
     * Retorna: ponteiro const char* com a mensagem de erro
     * 
     * noexcept: garante que este método nunca lança exceção
     * override: confirma que está sobrescrevendo método da classe base
     * 
     * Uso: catch(const EstoqueException& e) { std::cout << e.what(); }
     * 
     * Requisito POO: polimorfismo (método virtual com comportamento especializado)
     */
    virtual const char* what() const noexcept override {
        return mensagem.c_str();  // Retorna ponteiro C-string da mensagem
    }
};

#endif // ESTOQUEEXCEPTION_H