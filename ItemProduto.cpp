// ItemProduto.cpp - Implementação da classe especializada para Produto Final
#include "ItemProduto.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Construtor: inicializa Item base e depois inicializa a categoria específica
// Ordem de inicialização: primeiro a classe base Item (com nome, desc, qtd, link)
// depois o campo específico categoriaProduto
// Requisito POO: construtor com cadeia de inicialização de classe base
ItemProduto::ItemProduto(const string& nome, const string& desc, int qtd, const string& link, const string& categoria)
    : Item(nome, desc, qtd, link),  // Inicializa classe base
      categoriaProduto(categoria)     // Inicializa membro de ItemProduto
{
    // Corpo vazio - toda inicialização feita em lista de inicializadores
}

// Exibe todos os detalhes deste item de produto no console
// Requer acesso a campos privados da classe base (Item)
// Funciona porque ItemProduto herda de Item (acesso protected)
void ItemProduto::exibirDetalhes() const {
    // Imprime linhas de separação para melhor visualização
    cout << "---------------------------------" << endl;
    // Exibe ID com marcador "(PRODUTO)" para identificar tipo
    cout << "ID: " << idItem << " (PRODUTO)" << endl;
    // Exibe nome do produto (ex: "Parafuso M8")
    cout << "Nome: " << nome << endl;
    // Exibe descrição técnica ou de especificação
    cout << "Descricao: " << descricao << endl;
    // Exibe categoria de produto - CAMPO ESPECIALIZADO
    cout << "Categoria: " << categoriaProduto << endl;
    // Exibe quantidade atual em estoque
    cout << "Quantidade: " << quantidade << endl;
    // Exibe link para ficha técnica ou documentação
    cout << "Link: " << linkInfo << endl;
    // Fechamento das linhas de separação
    cout << "---------------------------------" << endl;
}

// Retorna tipo "PRODUTO" identificando este como item de produto final
// Usado no método gerarResumo() para serializar corretamente
// Quando carrega do arquivo, lê primeiro getTipo() para saber se cria ItemProduto ou ItemMateria
string ItemProduto::getTipo() const {
    return "PRODUTO";  // Constante que identifica tipo - "PRODUTO" para produto final
}

// Retorna detalhe específico de ItemProduto: a categoria do produto
// Em ItemMateria, este método retorna fornecedor
// Permite polimorfismo: mesma interface, dados diferentes por subclasse
// Requisito POO: polimorfismo (mesmo método, comportamento diferente)
string ItemProduto::getDetalheEspecifico() const {
    return categoriaProduto;  // Retorna o campo específico de ItemProduto
}