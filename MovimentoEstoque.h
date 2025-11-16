#ifndef MOVIMENTOESTOQUE_H
#define MOVIMENTOESTOQUE_H

#include <string>
#include <ctime> // Para a data

// Enumeração conforme o diagrama de classes
enum TipoMovimento { ENTRADA, SAIDA };

/**
 * @brief Classe para registrar movimentações de estoque (entradas e saídas).
 */
class MovimentoEstoque {
private:
    int idMovimento;
    TipoMovimento tipo;
    std::string data; // Simples string para data/hora
    int quantidade;
    int idItem; // Armazena o ID do item, e não o ponteiro
    std::string nomeItem; // Armazena o nome para facilitar o resumo

    static int proximoId;

    /**
     * Retorna data e hora atual formatada.
     */
    std::string getDataAtual() {
        std::time_t t = std::time(nullptr);
        char buffer[100];
        if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) {
            return std::string(buffer);
        }
        return "";
    }

public:
    MovimentoEstoque(TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem);

    /**
     * Construtor para carregamento de arquivo.
     */
    MovimentoEstoque(int id, const std::string& data, TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem);

    /**
     * Gera um resumo em string da movimentação.
     */
    std::string gerarResumo() const;

    // Getters para salvar em arquivo
    int getId() const;
    std::string getData() const;
    TipoMovimento getTipo() const;
    int getQuantidade() const;
    int getIdItem() const;
    std::string getNomeItem() const;

    static void setProximoId(int id);
};

#endif // MOVIMENTOESTOQUE_H