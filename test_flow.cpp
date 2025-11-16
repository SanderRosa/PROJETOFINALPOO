#include <iostream>
#include <exception>
#include "Estoque.h"

int main() {
    std::cout << "---- Iniciando testes funcionais do Estoque ----" << std::endl;
    Estoque estoque;

    std::cout << "\n[1] Listar itens iniciais:" << std::endl;
    estoque.listarItens();

    try {
        std::cout << "\n[2] Buscar item por ID (2):" << std::endl;
        Item* it = estoque.buscarItemPorId(2);
        it->exibirDetalhes();
    } catch (const std::exception& e) {
        std::cerr << "Erro ao buscar por ID: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n[3] Buscar item por nome ('MadeiraAuto'):" << std::endl;
        Item* itn = estoque.buscarItemPorNome("MadeiraAuto");
        itn->exibirDetalhes();
    } catch (const std::exception& e) {
        std::cerr << "Erro ao buscar por nome: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n[4] Modificar item ID 2 (atualizar dados)..." << std::endl;
        Item* im = estoque.buscarItemPorId(2);
        im->atualizarDados("MadeiraEditada", "Descricao editada", "http://edicao.local/madeira");
        std::cout << "Dados apos edicao:" << std::endl;
        im->exibirDetalhes();
    } catch (const std::exception& e) {
        std::cerr << "Erro ao editar item: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n[5] Registrar entrada (ID 2, +10) e saida (ID 2, -5)" << std::endl;
        estoque.registrarEntrada(2, 10);
        estoque.registrarSaida(2, 5);
        std::cout << "Quantidade apos movimentos:" << std::endl;
        estoque.buscarItemPorId(2)->exibirDetalhes();
    } catch (const std::exception& e) {
        std::cerr << "Erro ao registrar movimento: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n[6] Tentar saida invalida (ID 2, quantidade muito alta) para gerar excecao..." << std::endl;
        estoque.registrarSaida(2, 9999);
    } catch (const std::exception& e) {
        std::cout << "Excecao capturada (esperada): " << e.what() << std::endl;
    }

    std::cout << "\n[7] Exibir historico de movimentacoes:" << std::endl;
    estoque.exibirHistorico();

    std::cout << "\n[8] Salvando dados finalizados..." << std::endl;
    estoque.salvarDados();

    std::cout << "\n[9] Conteudo de arquivos de persistencia:" << std::endl;
    std::cout << "--- itens.txt ---" << std::endl;
    system("cat itens.txt || true");
    std::cout << "--- movimentos.txt ---" << std::endl;
    system("cat movimentos.txt || true");

    std::cout << "\n---- Testes finalizados ----" << std::endl;
    return 0;
}
