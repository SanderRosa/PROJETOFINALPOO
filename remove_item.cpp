#include <iostream>
#include "Estoque.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: remove_item <ID>\n";
        return 1;
    }

    int id = std::stoi(argv[1]);
    Estoque estoque;
    try {
        estoque.removerItem(id);
        estoque.salvarDados();
        std::cout << "Item com ID " << id << " removido e dados salvos." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao remover item: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
