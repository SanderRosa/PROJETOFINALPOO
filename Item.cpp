// Inclui definição da classe Item
#include "Item.h"
// Inclui iostream para debug
#include <iostream>

// Usa namespace std para string evitar repeti std::string
using std::string;

// Inicializa o contador estático de IDs (começando em 1)
int Item::proximoId = 1;

// Construtor: inicializa atributos do item e atribui ID único
Item::Item(const string& nome, const string& desc, int qtd, const string& link)
    // Lista de inicialização: atribui ID (pós-incrementa proximoId), depois inicializa outros atributos
    : idItem(proximoId++), nome(nome), descricao(desc), quantidade(qtd), linkInfo(link) {
}

// Getter para ID: retorna o ID único do item
int Item::getId() const { return idItem; }
// Getter para nome: retorna o nome armazenado
string Item::getNome() const { return nome; }
// Getter para quantidade: retorna quantidade em estoque
int Item::getQuantidade() const { return quantidade; }
// Getter para link: retorna URL para busca de informações
string Item::getLink() const { return linkInfo; }
// Getter para descrição: retorna descrição do item
string Item::getDescricao() const { return descricao; }


// Método para adicionar quantidade: aumenta estoque
void Item::adicionarQtd(int qtd) {
    // Valida se quantidade é positiva
    if (qtd > 0) {
        // Incrementa a quantidade
        quantidade += qtd;
    } else {
        // Lança exceção se quantidade é inválida
        throw EstoqueException("Quantidade a ser adicionada deve ser positiva.");
    }
}

// Método para remover quantidade: diminui estoque com validação
void Item::removerQtd(int qtd) {
    // Verifica se quantidade é positiva
    if (qtd <= 0) {
        throw EstoqueException("Quantidade a ser removida deve ser positiva.");
    }
    // Verifica se há quantidade suficiente em estoque
    if (quantidade - qtd < 0) {
        throw EstoqueException("Nao ha quantidade suficiente em estoque para remover.");
    }
    // Decrementa a quantidade
    quantidade -= qtd;
}

// Método para atualizar dados básicos do item
void Item::atualizarDados(const string& novoNome, const string& novaDesc, const string& novoLink) {
    // Atualiza nome
    this->nome = novoNome;
    // Atualiza descrição
    this->descricao = novaDesc;
    // Atualiza link de informação
    this->linkInfo = novoLink;
}

// Método estático para definir o próximo ID a usar (importante ao carregar dados)
void Item::setProximoId(int id) {
    // Apenas atualiza se o novo ID for maior (mantém continuidade)
    if (id > proximoId) {
        proximoId = id;
    }
}