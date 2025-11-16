#include <iostream>
#include "Estoque.h"
#include "ItemProduto.h"
#include "ItemMateria.h"

int main() {
    Estoque estoque; // carrega dados existentes

    // Criar e adicionar um produto
    Item* p = new ItemProduto("ParafusoAuto", "Parafuso automatico M4", 200, "http://google.com/search?q=\"ParafusoAuto\"", "FerragensAuto");
    estoque.adicionarItem(p);

    // Criar e adicionar uma matéria-prima
    Item* m = new ItemMateria("MadeiraAuto", "Madeira tratada", 50, "http://example.com/madeira", "FornecedorAuto");
    estoque.adicionarItem(m);

    // Salvar dados explicitamente
    estoque.salvarDados();

    std::cout << "Itens adicionados e dados salvos com sucesso." << std::endl;
    return 0;
}
