// ItemMateria.cpp - Implementação da classe especializada para Matéria-Prima
#include "ItemMateria.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Construtor: inicializa Item base e depois inicializa o fornecedor específico
// Ordem de inicialização: primeiro a classe base Item (com nome, desc, qtd, link)
// depois o campo específico fornecedor
// Requisito POO: construtor com cadeia de inicialização de classe base
ItemMateria::ItemMateria(const string& nome, const string& desc, int qtd, const string& link, const string& fornecedor)
    : Item(nome, desc, qtd, link),  // Inicializa classe base
      fornecedor(fornecedor)          // Inicializa membro de ItemMateria
{
    // Corpo vazio - toda inicialização feita em lista de inicializadores
}

// Exibe todos os detalhes deste item de matéria-prima no console
// Requer acesso a campos privados da classe base (Item)
// Funciona porque ItemMateria herda de Item (acesso protected)
void ItemMateria::exibirDetalhes() const {
    // Imprime linhas de separação para melhor visualização
    cout << "---------------------------------" << endl;
    // Exibe ID com marcador "(MATERIA-PRIMA)" para identificar tipo
    cout << "ID: " << idItem << " (MATERIA-PRIMA)" << endl;
    // Exibe nome da matéria-prima (ex: "Aço 1020")
    cout << "Nome: " << nome << endl;
    // Exibe descrição técnica ou de especificação
    cout << "Descricao: " << descricao << endl;
    // Exibe nome da empresa fornecedora - CAMPO ESPECIALIZADO
    cout << "Fornecedor: " << fornecedor << endl;
    // Exibe quantidade atual em estoque
    cout << "Quantidade: " << quantidade << endl;
    // Exibe link para ficha técnica ou documentação
    cout << "Link: " << linkInfo << endl;
    // Fechamento das linhas de separação
    cout << "---------------------------------" << endl;
}

// Retorna tipo "MATERIA" identificando este como item de matéria-prima
// Usado no método gerarResumo() para serializar corretamente
// Quando carrega do arquivo, lê primeiro getTipo() para saber se cria ItemProduto ou ItemMateria
string ItemMateria::getTipo() const {
    return "MATERIA";  // Constante que identifica tipo - "MATERIA" para matéria-prima
}

// Retorna detalhe específico de ItemMateria: o nome do fornecedor
// Em ItemProduto, este método retorna categoriaProduto
// Permite polimorfismo: mesma interface, dados diferentes por subclasse
// Requisito POO: polimorfismo (mesmo método, comportamento diferente)
string ItemMateria::getDetalheEspecifico() const {
    return fornecedor;  // Retorna o campo específico de ItemMateria
}