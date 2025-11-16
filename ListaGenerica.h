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
     * @brief Adiciona um item ao final da lista.
     * @param item O item a ser adicionado.
     */
    void adicionar(T item) {
        elementos.push_back(item);
    }

    /**
     * @brief Remove um item de um índice específico.
     * @param indice O índice do item a ser removido.
     */
    void remover(int indice) {
        if (indice < 0 || indice >= elementos.size()) {
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        elementos.erase(elementos.begin() + indice);
    }

    /**
     * @brief Obtém um item de um índice específico.
     * @param indice O índice do item a ser obtido.
     * @return O item no índice especificado.
     */
    T get(int indice) const {
        if (indice < 0 || indice >= elementos.size()) {
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        return elementos[indice];
    }

    /**
     * @brief Retorna o número de itens na lista.
     * @return O tamanho da lista.
     */
    int tamanho() const {
        return elementos.size();
    }
};

#endif // LISTAGENERICA_H