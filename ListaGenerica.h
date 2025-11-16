#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

#include <vector>
#include <stdexcept> // Para std::out_of_range

/**
 * @brief Classe de template para uma lista genérica.
 * Cumpre o requisito de uso de templates.
 *
 * @tparam T O tipo de dado que a lista irá armazenar.
 */
template <typename T>
class ListaGenerica {
private:
    std::vector<T> elementos;

public:
    /**
     * Adiciona um item ao final da lista.
     */
    void adicionar(T item) {
        elementos.push_back(item);
    }

    /**
     * Remove um item de um índice específico.
     */
    void remover(std::size_t indice) {
        if (indice >= elementos.size()) {
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        elementos.erase(elementos.begin() + indice);
    }

    /**
     * Obtém um item de um índice específico.
     */
    T get(std::size_t indice) const {
        if (indice >= elementos.size()) {
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        return elementos[indice];
    }

    /**
     * Retorna o número de itens na lista.
     */
    std::size_t tamanho() const {
        return elementos.size();
    }
};

#endif // LISTAGENERICA_H