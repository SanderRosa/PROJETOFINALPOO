#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

#include <vector>
#include <stdexcept> // Para std::out_of_range

/**
 * Classe template para uma lista genérica dinâmica.
 * Requisito POO: uso de templates/generics para código reutilizável.
 * 
 * Funciona com qualquer tipo T:
 * - ListaGenerica<Item*> para armazenar ponteiros de items
 * - ListaGenerica<MovimentoEstoque*> para armazenar movimentos
 * - ListaGenerica<int> para armazenar inteiros (exemplo teórico)
 * 
 * Implementação: wrapper em torno de std::vector para abstrair detalhes
 * Conversão feita: changed indices from int to std::size_t para eliminar
 * warnings de comparação signed/unsigned com vector::size()
 *
 * @tparam T O tipo de dado genérico que a lista irá armazenar
 */
template <typename T>
class ListaGenerica {
private:
    // Contêiner real STL que armazena os elementos
    // std::vector gerencia memória dinamicamente, cresce conforme necessário
    std::vector<T> elementos;

public:
    /**
     * Adiciona um item ao final da lista.
     * Operação: O(1) amortizado (crescimento exponencial de capacidade)
     * 
     * Parâmetro:
     *   - item: elemento do tipo T a ser adicionado
     * 
     * Exemplo: lista.adicionar(novoItem);
     * Requisito POO: template permite tipo genérico T sem casting
     */
    void adicionar(T item) {
        elementos.push_back(item);  // push_back() adiciona ao final
    }

    /**
     * Remove um item em uma posição específica (índice).
     * Operação: O(n) pois pode exigir deslocamento de elementos
     * 
     * Parâmetro:
     *   - indice: posição do elemento (0-based), deve ser < tamanho()
     * 
     * Lança: std::out_of_range se indice >= tamanho()
     * 
     * Conversão feita: indice é std::size_t (unsigned) para evitar warnings
     * ao comparar com size() que também retorna std::size_t
     * 
     * Exemplo: lista.remover(0);  // Remove primeiro elemento
     */
    void remover(std::size_t indice) {
        // Verifica se índice está dentro dos limites válidos [0, tamanho)
        if (indice >= elementos.size()) {
            // Lança exceção padrão C++ - a chamadora deve capturar
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        // erase() remove elemento na posição indicada
        elementos.erase(elementos.begin() + indice);
    }

    /**
     * Obtém (acessa) um item em posição específica.
     * Operação: O(1) acesso direto ao vetor
     * 
     * Parâmetro:
     *   - indice: posição do elemento (0-based), deve ser < tamanho()
     * 
     * Retorna: cópia do elemento T na posição indice
     * 
     * const: método não modifica a lista
     * 
     * Lança: std::out_of_range se indice >= tamanho()
     * 
     * Nota: Para ponteiros (ex: Item*), retorna cópia do ponteiro
     * não cópia do objeto apontado
     * 
     * Exemplo: Item* item = lista.get(0);
     */
    T get(std::size_t indice) const {
        // Verifica se índice está dentro dos limites válidos [0, tamanho)
        if (indice >= elementos.size()) {
            // Lança exceção padrão C++ - a chamadora deve capturar
            throw std::out_of_range("Indice fora do intervalo da lista.");
        }
        // Retorna cópia do elemento na posição indice
        return elementos[indice];
    }

    /**
     * Retorna o número total de itens na lista.
     * Operação: O(1) - std::vector mantém tamanho cache
     * 
     * Retorna: std::size_t (unsigned) com quantidade de elementos
     * 
     * const: método não modifica a lista, apenas lê
     * 
     * Conversão feita: retorna std::size_t em vez de int
     * permite comparações seguras com tamanho() sem warnings
     * 
     * Exemplo: 
     *   if (lista.tamanho() > 0) { ... }  // Seguro: size_t > 0
     *   for (std::size_t i = 0; i < lista.tamanho(); i++) { ... }
     */
    std::size_t tamanho() const {
        // Retorna o tamanho do vector (número de elementos)
        return elementos.size();
    }
};

#endif // LISTAGENERICA_H