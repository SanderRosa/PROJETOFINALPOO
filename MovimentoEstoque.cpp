#include "MovimentoEstoque.h"
#include <sstream>

int MovimentoEstoque::proximoId = 1;

MovimentoEstoque::MovimentoEstoque(TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem)
    : idMovimento(proximoId++), tipo(tipo), data(getDataAtual()), quantidade(qtd), idItem(idItem), nomeItem(nomeItem) {
}

MovimentoEstoque::MovimentoEstoque(int id, const std::string& data, TipoMovimento tipo, int qtd, int idItem, const std::string& nomeItem)
    : idMovimento(id), tipo(tipo), data(data), quantidade(qtd), idItem(idItem), nomeItem(nomeItem) {
}

std::string MovimentoEstoque::gerarResumo() const {
    std::ostringstream oss;
    oss << "[" << idMovimento << "] " << data << " - "
        << (tipo == ENTRADA ? "ENTRADA" : "SAIDA") << " - qtd: " << quantidade
        << " - item: " << nomeItem << " (ID:" << idItem << ")";
    return oss.str();
}

int MovimentoEstoque::getId() const { return idMovimento; }
std::string MovimentoEstoque::getData() const { return data; }
TipoMovimento MovimentoEstoque::getTipo() const { return tipo; }
int MovimentoEstoque::getQuantidade() const { return quantidade; }
int MovimentoEstoque::getIdItem() const { return idItem; }
std::string MovimentoEstoque::getNomeItem() const { return nomeItem; }

void MovimentoEstoque::setProximoId(int id) {
    if (id > proximoId) proximoId = id;
}
