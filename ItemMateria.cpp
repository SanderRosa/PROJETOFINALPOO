#include "ItemMateria.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

ItemMateria::ItemMateria(const string& nome, const string& desc, int qtd, const string& link, const string& fornecedor)
    : Item(nome, desc, qtd, link), fornecedor(fornecedor) {
}

void ItemMateria::exibirDetalhes() const {
    cout << "---------------------------------" << endl;
    cout << "ID: " << idItem << " (MATERIA-PRIMA)" << endl;
    cout << "Nome: " << nome << endl;
    cout << "Descricao: " << descricao << endl;
    cout << "Fornecedor: " << fornecedor << endl;
    cout << "Quantidade: " << quantidade << endl;
    cout << "Link: " << linkInfo << endl;
    cout << "---------------------------------" << endl;
}

string ItemMateria::getTipo() const {
    return "MATERIA";
}

string ItemMateria::getDetalheEspecifico() const {
    return fornecedor;
}