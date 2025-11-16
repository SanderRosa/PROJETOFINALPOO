#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> // Para system()

#include "Estoque.h"
#include "EstoqueException.h"
#include "ItemProduto.h"
#include "ItemMateria.h"

// Usings para o std
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::cerr;
using std::numeric_limits;
using std::streamsize;
using std::getline;


// Protótipos das funções auxiliares
int exibirMenu();
void limparTela();
void pausar();
int lerInteiro(const string& prompt);
string lerString(const string& prompt);
string lerStringNaoVazia(const string& prompt);

// Protótipos das funções de funcionalidade
void adicionarItem(Estoque& estoque);
void removerItem(Estoque& estoque);
void editarItem(Estoque& estoque);
void localizarItem(Estoque& estoque);
void registrarEntrada(Estoque& estoque);
void registrarSaida(Estoque& estoque);
void buscarInternet(Estoque& estoque);

/**
 * @brief Função principal - Ponto de entrada do programa.
 */
int main() {
    Estoque estoque; // O construtor já tenta carregar os dados
    int opcao;

    do {
        limparTela();
        opcao = exibirMenu();

        try {
            switch (opcao) {
                case 1:
                    adicionarItem(estoque);
                    break;
                case 2:
                    removerItem(estoque);
                    break;
                case 3:
                    editarItem(estoque);
                    break;
                case 4:
                    localizarItem(estoque);
                    break;
                case 5:
                    estoque.listarItens();
                    break;
                case 6:
                    registrarEntrada(estoque);
                    break;
                case 7:
                    registrarSaida(estoque);
                    break;
                case 8:
                    estoque.exibirHistorico();
                    break;
                case 9:
                    buscarInternet(estoque);
                    break;
                case 0:
                    cout << "Salvando dados e saindo..." << endl;
                    // O destrutor de 'estoque' será chamado automaticamente
                    // e salvará os dados.
                    break;
                default:
                    cout << "Opcao invalida. Tente novamente." << endl;
            }
        } catch (const EstoqueException& e) {
            cerr << "ERRO: " << e.what() << endl;
        } catch (const std::exception& e) { // Mantém std::exception por clareza
            cerr << "ERRO INESPERADO: " << e.what() << endl;
        }

        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções Auxiliares ---

int exibirMenu() {
    cout << "=================================" << endl;
    cout << "   MODULO ESTOQUE" << endl;
    cout << "=================================" << endl;
    cout << "1. Adicionar Item" << endl;
    cout << "2. Remover Item" << endl;
    cout << "3. Modificar Item" << endl;
    cout << "4. Localizar Item (Mostrar)" << endl;
    cout << "5. Listar Itens (Imprimir Listagem)" << endl;
    cout << "6. Registrar ENTRADA" << endl;
    cout << "7. Registrar SAIDA" << endl;
    cout << "8. Exibir Historico de Movimentacao" << endl;
    cout << "9. Buscar Item na Internet" << endl;
    cout << "---------------------------------" << endl;
    cout << "0. Salvar e Sair" << endl;
    cout << "=================================" << endl;
    return lerInteiro("Escolha uma opcao: ");
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\nPressione ENTER para continuar..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Se o cin falhou antes, limpa
    if (cin.fail()) {
        cin.clear();
    }
    string dummy;
    getline(cin, dummy);
}

int lerInteiro(const string& prompt) {
    int valor;
    while (true) {
        cout << prompt;
        if (!(cin >> valor)) {
            if (cin.eof()) {
                cout << "Entrada interrompida (EOF). Saindo..." << endl;
                std::exit(0);
            }
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta a entrada inválida
            cout << "Entrada invalida. Por favor, digite um numero." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            return valor;
        }
    }
}

string lerString(const string& prompt) {
    string valor;
    cout << prompt;
    if (!std::getline(cin, valor)) {
        cout << "Entrada interrompida (EOF). Saindo..." << endl;
        std::exit(0);
    }
    return valor;
}

string lerStringNaoVazia(const string& prompt) {
    string valor;
    while (true) {
        cout << prompt;
        if (!std::getline(cin, valor)) {
            cout << "Entrada interrompida (EOF). Saindo..." << endl;
            std::exit(0);
        }
        if (valor.empty()) {
            cout << "Este campo nao pode ficar vazio." << endl;
        } else {
            return valor;
        }
    }
}

// --- Implementação das Funções de Funcionalidade ---

void adicionarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Adicionar Novo Item ---" << endl;
    int tipo = 0;
    while (tipo != 1 && tipo != 2) {
        tipo = lerInteiro("Tipo (1 - Produto, 2 - Materia-Prima): ");
    }

    string nome = lerStringNaoVazia("Nome: ");
    string desc = lerStringNaoVazia("Descricao: ");
    int qtd = lerInteiro("Quantidade inicial: ");
    string link = lerString("Link para info (ex: http://...): ");
    if (link.empty()) {
        link = "http://google.com/search?q=\"" + nome + "\"";
    }

    if (tipo == 1) {
        string categoria = lerStringNaoVazia("Categoria do Produto: ");
        Item* produto = new ItemProduto(nome, desc, qtd, link, categoria);
        estoque.adicionarItem(produto);
    } else {
        string fornecedor = lerStringNaoVazia("Fornecedor da Materia-Prima: ");
        Item* materia = new ItemMateria(nome, desc, qtd, link, fornecedor);
        estoque.adicionarItem(materia);
    }
    cout << "Item '" << nome << "' adicionado com sucesso." << endl;
}

void removerItem(Estoque& estoque) {
    limparTela();
    cout << "--- Remover Item ---" << endl;
    int id = lerInteiro("Digite o ID do item a ser removido: ");
    // A exceção será tratada no loop principal (main)
    estoque.removerItem(id);
}

void editarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Modificar Item ---" << endl;
    int id = lerInteiro("Digite o ID do item a ser modificado: ");
    estoque.editarItem(id); // Já busca e trata exceção
}

void localizarItem(Estoque& estoque) {
    limparTela();
    cout << "--- Localizar Item (Mostrar) ---" << endl;
    int tipoBusca = 0;
    while (tipoBusca != 1 && tipoBusca != 2) {
        tipoBusca = lerInteiro("Buscar por (1 - ID, 2 - Nome): ");
    }

    Item* itemEncontrado = nullptr;
    if (tipoBusca == 1) {
        int id = lerInteiro("Digite o ID: ");
        itemEncontrado = estoque.buscarItemPorId(id);
    } else {
        string nome = lerStringNaoVazia("Digite o Nome: ");
        itemEncontrado = estoque.buscarItemPorNome(nome);
    }

    if (itemEncontrado) {
        cout << "Item encontrado:" << endl;
        itemEncontrado->exibirDetalhes(); // Polimorfismo
    }
    // A exceção de "não encontrado" é tratada na main
}

void registrarEntrada(Estoque& estoque) {
    limparTela();
    cout << "--- Registrar Entrada ---" << endl;
    int id = lerInteiro("Digite o ID do item: ");
    int qtd = lerInteiro("Digite a quantidade de ENTRADA: ");
    estoque.registrarEntrada(id, qtd);
}

void registrarSaida(Estoque& estoque) {
    limparTela();
    cout << "--- Registrar Saida ---" << endl;
    int id = lerInteiro("Digite o ID do item: ");
    int qtd = lerInteiro("Digite a quantidade de SAIDA: ");
    estoque.registrarSaida(id, qtd);
}

void buscarInternet(Estoque& estoque) {
    limparTela();
    cout << "--- Buscar Item na Internet ---" << endl;
    int id = lerInteiro("Digite o ID do item para buscar: ");
    Item* item = estoque.buscarItemPorId(id);

    string url = item->getLink();
    string comando;

#ifdef _WIN32
    // Comando para Windows (usando 'start')
    comando = "start \"\" \"" + url + "\"";
#elif __APPLE__
    // Comando para macOS (usando 'open')
    comando = "open \"" + url + "\"";
#else
    // Comando para Linux e outros (usando 'xdg-open' ou 'firefox')
    // 'xdg-open' é mais genérico
    comando = "xdg-open \"" + url + "\"";
    // O comando 'firefox' pedido na especificação:
    // comando = "firefox \"" + url + "\"";
#endif

    cout << "Abrindo navegador com o link: " << url << endl;
    int resultado = system(comando.c_str());

    if (resultado != 0) {
        cerr << "Erro: Nao foi possivel abrir o navegador." << endl;
        cerr << "Comando executado: " << comando << endl;
    }
}