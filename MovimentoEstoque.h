#ifndef MOVIMENTOESTOQUE_H
#define MOVIMENTOESTOQUE_H

#include <string>
#include <ctime> // Para a data

// Enumeração que identifica tipo de movimentação
// ENTRADA: item foi recebido (quantidade aumenta)
// SAIDA: item foi removido (quantidade diminui)
// Conforme o diagrama de classes entregue no projeto
enum TipoMovimento { ENTRADA, SAIDA };

/**
 * Classe para registrar movimentações de estoque (entradas e saídas).
 * Requisito POO: classe especializada para registrar transações.
 * 
 * Padrão usado: Audit Trail - mantém histórico completo de todas operações
 * com data/hora, permitindo rastreabilidade e análise temporal
 * 
 * Dados armazenados:
 * - ID único do movimento (auto-incremento)
 * - Tipo de operação (ENTRADA ou SAIDA)
 * - Data/hora da operação (string formatada)
 * - Quantidade movimentada
 * - ID do item afetado (não o ponteiro, para persistência segura)
 * - Nome do item (para relatórios sem precisar buscar)
 * 
 * Persistência: serializado em movimentos.txt com formato:
 * ID;DATA;TIPO;QTD;IDITEM;NOMEITEM
 */
class MovimentoEstoque {
private:
    // ID único do movimento - auto incrementado
    int idMovimento;
    
    // Tipo de operação: ENTRADA (recebimento) ou SAIDA (saída)
    TipoMovimento tipo;
    
    // Data/hora formatada: "YYYY-MM-DD HH:MM:SS"
    std::string data;
    
    // Quantidade de itens movimentada nesta operação
    int quantidade;
    
    // ID do item afetado (armazenado como int, não ponteiro)
    // Essencial para persistência: ponteiros não sobrevivem desligamento
    int idItem;
    
    // Nome do item no momento do movimento (armazenado para histórico)
    // Se item for deletado depois, ainda vemos seu nome no movimento
    std::string nomeItem;

    // Contador estático: próximo ID a ser atribuído
    // Incrementado a cada novo movimento criado
    // Requer setProximoId() para sincronizar com arquivo após carregar
    static int proximoId;

    /**
     * Retorna string com data e hora atual formatada.
     * Formato: "YYYY-MM-DD HH:MM:SS"
     * Usa: std::time() para timestamp, std::strftime() para formatação
     * 
     * Retorna: string com data formatada ou "" se erro
     * 
     * Chamado: apenas pelo construtor principal (não no de carregamento)
     */
    std::string getDataAtual() {
        std::time_t t = std::time(nullptr);  // Obtém timestamp Unix atual
        char buffer[100];  // Buffer para string formatada
        // Converte timestamp para string "YYYY-MM-DD HH:MM:SS"
        if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t))) {
            return std::string(buffer);  // Sucesso: retorna string formatada
        }
        return "";  // Falha: retorna string vazia
    }

public:
    /**
     * Construtor principal: cria novo movimento (auto-gera ID e data).
     * 
     * Parâmetros:
     *   - tipo: ENTRADA ou SAIDA
     *   - qtd: quantidade movimentada
     *   - idItem: ID do item que sofreu movimento
     *   - nomeItem: nome do item no momento (para histórico)
     * 
     * Comportamento:
     * - Atribui proximoId ao idMovimento, depois incrementa proximoId
     * - Gera data atual com getDataAtual()
     * - Cria registro completo do movimento
     * 
     * Exemplo: MovimentoEstoque m(ENTRADA, 50, 1, "Aço 1020");
     */
    MovimentoEstoque(TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem);

    /**
     * Construtor alternativo: carrega movimento existente de arquivo.
     * Usado quando desserializando movimentos.txt.
     * 
     * Parâmetros:
     *   - id: ID do movimento (já existe no arquivo)
     *   - data: data/hora no formato do arquivo
     *   - tipo: ENTRADA ou SAIDA
     *   - qtd: quantidade
     *   - idItem: ID do item
     *   - nomeItem: nome do item
     * 
     * Nota: NÃO incrementa proximoId (ocorre em Estoque::carregarDados())
     * 
     * Exemplo: MovimentoEstoque m(1, "2024-01-15 10:30:45", ENTRADA, 50, 1, "Aço");
     */
    MovimentoEstoque(int id, const std::string& data, TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem);

    /**
     * Gera um resumo em string da movimentação.
     * Formato legível para exibição em menu/relatórios
     * 
     * Retorna: string como "ID:1 | ENTRADA | Item: Aço 1020 | Qtd: 50 | Data: 2024-01-15 10:30:45"
     * 
     * Conversão: TipoMovimento convertido para "ENTRADA" ou "SAIDA"
     * 
     * Usado em: Estoque::listarHistorico() para exibir movimentos ao usuário
     */
    std::string gerarResumo() const;

    // === GETTERS: acesso aos campos privados ===
    // Utilizados para:
    // 1. Serialização em gerarResumo() de Estoque
    // 2. Salvamento em arquivo (Estoque::salvarDados())
    // 3. Leitura em menus de exibição
    
    /**
     * Retorna ID único deste movimento.
     */
    int getId() const;
    
    /**
     * Retorna data/hora formatada "YYYY-MM-DD HH:MM:SS".
     */
    std::string getData() const;
    
    /**
     * Retorna tipo da movimentação: ENTRADA ou SAIDA.
     */
    TipoMovimento getTipo() const;
    
    /**
     * Retorna quantidade movimentada.
     */
    int getQuantidade() const;
    
    /**
     * Retorna ID do item que sofreu movimento.
     */
    int getIdItem() const;
    
    /**
     * Retorna nome do item no momento do movimento.
     */
    std::string getNomeItem() const;

    /**
     * Define o valor do próximo ID a ser atribuído.
     * Essencial na recarga de dados: garante IDs únicos após carregar arquivo.
     * 
     * Parâmetro:
     *   - id: novo valor de proximoId (geralmente max_id_no_arquivo + 1)
     * 
     * Chamado por: Estoque::carregarDados() após ler movimentos.txt
     * 
     * Padrão: evita duplicação de IDs após recarregar programa
     * 
     * Requisito POO: método estático para gerenciar estado compartilhado
     */
    static void setProximoId(int id);
};

#endif // MOVIMENTOESTOQUE_H