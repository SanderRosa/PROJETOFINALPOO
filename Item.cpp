#include "Item.h"
#include <iostream>

using std::string;

// Inicialização do ID estático
int Item::proximoId = 1;

Item::Item(const string& nome, const string& desc, int qtd, const string& link)
    : idItem(proximoId++), nome(nome), descricao(desc), quantidade(qtd), linkInfo(link) {
}

int Item::getId() const { return idItem; }
string Item::getNome() const { return nome; }
int Item::getQuantidade() const { return quantidade; }
string Item::getLink() const { return linkInfo; }
string Item::getDescricao() const { return descricao; }


void Item::adicionarQtd(int qtd) {
    if (qtd > 0) {
        quantidade += qtd;
    } else {
        throw EstoqueException("Quantidade a ser adicionada deve ser positiva.");
    }
}

void Item::removerQtd(int qtd) {
    if (qtd <= 0) {
        throw EstoqueException("Quantidade a ser removida deve ser positiva.");
    }
    if (quantidade - qtd < 0) {
        throw EstoqueException("Nao ha quantidade suficiente em estoque para remover.");
    }
    quantidade -= qtd;
}

void Item::atualizarDados(const string& novoNome, const string& novaDesc, const string& novoLink) {
    this->nome = novoNome;
    this->descricao = novaDesc;
    this->linkInfo = novoLink;
}

void Item::setProximoId(int id) {
    if (id > proximoId) {
        proximoId = id;
    }
}