// MovimentoEstoque.cpp - Implementação de registro de movimentações (ENTRADA/SAIDA)
#include "MovimentoEstoque.h"
#include <sstream>

// Inicialização do contador estático: próximo ID a ser atribuído
// Valor inicial: 1 (IDs começam do 1, não do 0)
// Incrementado cada vez que um novo movimento é criado
int MovimentoEstoque::proximoId = 1;

// Construtor principal: cria novo movimento com auto-geração de ID e data
// Parâmetros:
//   - tipo: ENTRADA (recebimento) ou SAIDA (retirada)
//   - qtd: quantidade movimentada
//   - idItem: ID do item afetado
//   - nomeItem: nome do item (armazenado para histórico)
// 
// Inicialização:
//   - idMovimento: atribui valor atual de proximoId, depois incrementa (proximoId++)
//   - tipo: cópia do parâmetro tipo
//   - data: chama getDataAtual() para gerar timestamp atual "YYYY-MM-DD HH:MM:SS"
//   - quantidade: cópia do parâmetro qtd
//   - idItem: cópia do parâmetro idItem
//   - nomeItem: cópia do parâmetro nomeItem
//
// Padrão pós-incremento (proximoId++): primeiro usa valor, depois incrementa
// Garante IDs únicos sequenciais: 1, 2, 3, ...
MovimentoEstoque::MovimentoEstoque(TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem)
    : idMovimento(proximoId++),       // Auto-incrementa ID
      tipo(tipo),                      // Tipo ENTRADA ou SAIDA
      data(getDataAtual()),            // Gera data/hora atual
      quantidade(qtd),                 // Quantidade movimentada
      idItem(idItem),                  // ID do item
      nomeItem(nomeItem)               // Nome do item para auditoria
{
    // Corpo vazio - toda inicialização em lista de inicializadores
}

// Construtor alternativo: carrega movimento existente de arquivo
// Usado durante desserialização em carregarDados()
// Parâmetros:
//   - id: ID do movimento (lido do arquivo, já existe)
//   - data: string de data/hora (lido do arquivo, ex: "2024-01-15 10:30:45")
//   - tipo: ENTRADA ou SAIDA (convertido de string no arquivo)
//   - qtd: quantidade (lida do arquivo)
//   - idItem: ID do item (lido do arquivo)
//   - nomeItem: nome do item (lido do arquivo)
//
// Inicialização:
//   - idMovimento: usa ID fornecido (NÃO incrementa)
//   - tipo: cópia do parâmetro
//   - data: cópia do parâmetro (não gera nova data)
//   - quantidade, idItem, nomeItem: cópias dos parâmetros
//
// Nota importante: proximoId não é incrementado aqui
// Incremento ocorre em Estoque::carregarDados() após ler todos os movimentos
MovimentoEstoque::MovimentoEstoque(int id, const std::string& data, TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem)
    : idMovimento(id),                 // Usa ID fornecido (não incrementa)
      tipo(tipo),                      // Tipo ENTRADA ou SAIDA
      data(data),                      // Data do arquivo
      quantidade(qtd),                 // Quantidade
      idItem(idItem),                  // ID do item
      nomeItem(nomeItem)               // Nome do item
{
    // Corpo vazio - toda inicialização em lista de inicializadores
}

// Gera um resumo textual formatado da movimentação
// Retorna: string legível com todos os detalhes do movimento
// 
// Formato: "[ID] DATA - TIPO - qtd: QTD - item: NOME (ID:IDITEM)"
// Exemplo: "[1] 2024-01-15 10:30:45 - ENTRADA - qtd: 50 - item: Aço 1020 (ID:1)"
//
// Uso: exibido em exibirHistorico() ou gerado para relatório
std::string MovimentoEstoque::gerarResumo() const {
    std::ostringstream oss;  // String stream para montagem formatada
    
    // Monta a string formatada com todos os detalhes
    oss << "[" << idMovimento << "] "           // [ID do movimento]
        << data << " - "                         // Data/hora
        << (tipo == ENTRADA ? "ENTRADA" : "SAIDA")  // Tipo (ENTRADA ou SAIDA)
        << " - qtd: " << quantidade              // Quantidade movimentada
        << " - item: " << nomeItem               // Nome do item
        << " (ID:" << idItem << ")";             // ID do item
    
    // Retorna a string montada
    return oss.str();
}

// === GETTERS: acesso aos campos privados ===
// Todos retornam simplesmente uma cópia do campo correspondente
// Utilizados para serialização e acesso após criar movimento

// Retorna o ID único deste movimento
int MovimentoEstoque::getId() const { 
    return idMovimento; 
}

// Retorna a data/hora formatada "YYYY-MM-DD HH:MM:SS"
std::string MovimentoEstoque::getData() const { 
    return data; 
}

// Retorna o tipo: ENTRADA ou SAIDA
TipoMovimento MovimentoEstoque::getTipo() const { 
    return tipo; 
}

// Retorna a quantidade movimentada
int MovimentoEstoque::getQuantidade() const { 
    return quantidade; 
}

// Retorna o ID do item que sofreu o movimento
int MovimentoEstoque::getIdItem() const { 
    return idItem; 
}

// Retorna o nome do item no momento do movimento
std::string MovimentoEstoque::getNomeItem() const { 
    return nomeItem; 
}

// Define o próximo ID a ser atribuído
// Essencial na recarga de dados do arquivo para evitar duplicação de IDs
//
// Parâmetro:
//   - id: novo valor mínimo de proximoId
//
// Lógica: só atualiza se id > proximoId (não rebaixa IDs já usados)
// Chamado após carregar todos os movimentos: setProximoId(maxIdNoArquivo + 1)
//
// Exemplo após carregar arquivo:
// Se movimentos.txt tem IDs: 1, 2, 3
// Chamamos: MovimentoEstoque::setProximoId(4)
// Próximo movimento criado terá ID = 4 (evita duplicação)
//
// Requisito POO: método estático para gerenciar estado compartilhado da classe
void MovimentoEstoque::setProximoId(int id) {
    if (id > proximoId)  // Só atualiza se valor é maior (não rebaixa)
        proximoId = id;
}
