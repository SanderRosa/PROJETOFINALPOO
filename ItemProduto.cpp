#include "ItemProduto.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

ItemProduto::ItemProduto(const string& nome, const string& desc, int qtd, const string& link, const string& categoria)
    : Item(nome, desc, qtd, link), categoriaProduto(categoria) {
}

void ItemProduto::exibirDetalhes() const {
    cout << "---------------------------------" << endl;
    cout << "ID: " << idItem << " (PRODUTO)" << endl;
    cout << "Nome: " << nome << endl;
    cout << "Descricao: " << descricao << endl;
    cout << "Categoria: " << categoriaProduto << endl;
    cout << "Quantidade: " << quantidade << endl;
    cout << "Link: " << linkInfo << endl;
    cout << "---------------------------------" << endl;
}

string ItemProduto::getTipo() const {
    return "PRODUTO";
}

string ItemProduto::getDetalheEspecifico() const {
    return categoriaProduto;
}