# Documentação do Projeto: Gestor de Estoque (Etapa 1)

## 1. Estrutura Geral do Projeto

Este projeto implementa um **Gestor de Estoque em C++** utilizando programação orientada a objetos (POO) com as seguintes características:

- **Classe Base Abstrata**: `Item` (classe base para todos os itens)
- **Classes Filhas**: `ItemProduto` e `ItemMateria` (especialização via herança)
- **Interface**: `IExibivel` (contrato para exibição de objetos)
- **Templates**: `ListaGenerica<T>` (lista genérica reutilizável)
- **Exceções**: `EstoqueException` (tratamento personalizado de erros)
- **Gerenciador**: `Estoque` (classe principal que coordena operações)
- **Registro**: `MovimentoEstoque` (rastreia entradas e saídas)

---

## 2. Descrição de Cada Arquivo

### **Headers (.h)**

#### **Item.h**
- **Classe base abstrata** que define atributos e métodos comuns a todos os itens
- **Atributos**:
  - `idItem`: identificador único (auto-incrementado)
  - `nome`: nome do item
  - `descricao`: descrição detalhada
  - `quantidade`: quantidade em estoque
  - `linkInfo`: URL para buscar informações
- **Métodos principais**:
  - `getId()`, `getNome()`, `getQuantidade()`, etc. (getters)
  - `adicionarQtd(qtd)`: aumenta estoque (com validação)
  - `removerQtd(qtd)`: diminui estoque (com validação de quantidade)
  - `atualizarDados()`: edita informações básicas
  - `getTipo()`: retorna "PRODUTO" ou "MATERIA" (virtual puro)
  - `getDetalheEspecifico()`: retorna categoria ou fornecedor (virtual puro)

#### **ItemProduto.h**
- **Classe filha de Item** que representa um produto final
- **Atributo adicional**: `categoriaProduto` (ex: "Eletrônicos", "Roupas")
- **Implementação**: `getTipo()` retorna "PRODUTO", `getDetalheEspecifico()` retorna categoria
- **Método**: `exibirDetalhes()` mostra informações com categoria

#### **ItemMateria.h**
- **Classe filha de Item** que representa uma matéria-prima
- **Atributo adicional**: `fornecedor` (ex: "Fornecedor A", "Distribuidor B")
- **Implementação**: `getTipo()` retorna "MATERIA", `getDetalheEspecifico()` retorna fornecedor
- **Método**: `exibirDetalhes()` mostra informações com fornecedor

#### **IExibivel.h**
- **Interface (classe abstrata pura)** que define contrato para exibição
- **Único método**: `exibirDetalhes() const` (virtual puro)
- **Uso**: qualquer classe que implemente IExibivel pode ser exibida na tela

#### **EstoqueException.h**
- **Classe de exceção personalizada** que herda de `std::exception`
- **Armazena**: mensagem de erro específica
- **Método**: `what()` retorna a mensagem de erro
- **Uso**: lançada em operações inválidas (quantidade negativa, item não encontrado, etc)

#### **ListaGenerica.h**
- **Template de classe** que implementa lista genérica
- **Baseada em**: `std::vector<T>`
- **Métodos**:
  - `adicionar(T item)`: insere item
  - `remover(size_t indice)`: remove item por índice
  - `get(size_t indice)`: obtém item por índice
  - `tamanho()`: retorna número de itens
- **Uso**: armazena listas de itens e movimentos sem duplicar código

#### **Estoque.h**
- **Classe principal** que gerencia o estoque
- **Atributos**:
  - `itens`: lista genérica de ponteiros para Item
  - `historico`: lista genérica de movimentações
  - Nomes de arquivos para persistência
- **Métodos principais**:
  - `adicionarItem()`: adiciona novo item
  - `removerItem(id)`: remove item pelo ID
  - `editarItem(id)`: modifica dados do item
  - `buscarItemPorId()`, `buscarItemPorNome()`: localização
  - `listarItens()`: exibe todos os itens
  - `registrarEntrada()`, `registrarSaida()`: movimentações
  - `exibirHistorico()`: mostra histórico
  - `salvarDados()`, `carregarDados()`: persistência em arquivo

#### **MovimentoEstoque.h**
- **Classe que registra movimentações** (entradas e saídas)
- **Atributos**:
  - `idMovimento`: ID único do movimento
  - `tipo`: ENTRADA ou SAIDA
  - `data`: data/hora do movimento
  - `quantidade`: quantidade movimentada
  - `idItem`, `nomeItem`: referência ao item
- **Métodos**:
  - `gerarResumo()`: retorna string formatada do movimento
  - Getters para todos os atributos

---

### **Implementações (.cpp)**

#### **Item.cpp**
- Implementa construtor e métodos da classe base
- **Construtor**: atribui ID único via `proximoId++` e inicializa atributos
- **Getters**: simples retornos de atributos
- **adicionarQtd()**: valida positivo, incrementa quantidade
- **removerQtd()**: valida positivo e quantidade suficiente, decrementa
- **atualizarDados()**: atualiza nome, descrição, link
- **setProximoId()**: atualiza contador ao carregar dados

#### **ItemProduto.cpp**
- Implementa construtor e métodos de `ItemProduto`
- **Construtor**: chama construtor base + define categoria
- **getTipo()**: retorna "PRODUTO"
- **getDetalheEspecifico()**: retorna categoria
- **exibirDetalhes()**: imprime item com rótulo "PRODUTO" e categoria

#### **ItemMateria.cpp**
- Implementa construtor e métodos de `ItemMateria`
- **Construtor**: chama construtor base + define fornecedor
- **getTipo()**: retorna "MATERIA"
- **getDetalheEspecifico()**: retorna fornecedor
- **exibirDetalhes()**: imprime item com rótulo "MATERIA-PRIMA" e fornecedor

#### **Estoque.cpp**
- Implementa gerenciador principal de estoque
- **Construtor**: chama `carregarDados()` para recuperar dados persistidos
- **Destrutor**: chama `salvarDados()` e libera memória dos itens/movimentos
- **adicionarItem()**: insere ponteiro na lista `itens`
- **removerItem()**: localiza por ID, libera memória, remove da lista
- **buscarItemPorId()**, **buscarItemPorNome()**: buscas com exceção se não encontrado
- **registrarEntrada()**: busca item, adiciona quantidade, cria movimento
- **registrarSaida()**: busca item, remove quantidade, cria movimento
- **salvarDados()**: escreve itens e movimentos em arquivos .txt
- **carregarDados()**: lê arquivos .txt e recria objetos em memória

#### **MovimentoEstoque.cpp**
- Implementa registro de movimentações
- **Construtores**: dois - um para criar novo, outro para carregar
- **gerarResumo()**: retorna string formatada com ID, data, tipo, quantidade, item

#### **main.cpp**
- Programa principal com interface interativa via console
- **Menu**: 10 opções para gerenciar estoque
- **Funções auxiliares**: `lerInteiro()`, `lerString()`, `lerStringNaoVazia()`, `pausar()`, `limparTela()`
- **Funções de operação**:
  - `adicionarItem()`: cria ItemProduto ou ItemMateria
  - `removerItem()`: remove por ID
  - `editarItem()`: modifica dados
  - `localizarItem()`: busca por ID ou nome
  - `registrarEntrada()`, `registrarSaida()`: movimentações
  - `buscarInternet()`: abre navegador com link do item
- **Tratamento de exceções**: captura e exibe erros

---

## 3. Fluxo de Operação

```
PROGRAMA INICIA
  ↓
Estoque::Estoque() carrega dados de itens.txt e movimentos.txt
  ↓
Loop do Menu (enquanto não sair)
  ├─ Exibe menu com 10 opções
  ├─ Lê opção do usuário
  ├─ Executa operação correspondente
  ├─ Trata exceções se houver
  └─ Retorna ao menu
  ↓
Usuário escolhe opção 0 (Sair)
  ↓
Estoque::~Estoque() salva dados em itens.txt e movimentos.txt
  ↓
PROGRAMA ENCERRA
```

---

## 4. Requisitos de POO Atendidos

| Requisito | Implementação |
|-----------|--------------|
| **Classe Base** | Classe `Item` (abstrata) |
| **Herança** | `ItemProduto` e `ItemMateria` herdam de `Item` |
| **Polimorfismo** | Métodos virtuais `getTipo()`, `getDetalheEspecifico()`, `exibirDetalhes()` |
| **Interface** | Classe `IExibivel` com método virtual puro `exibirDetalhes()` |
| **Templates** | Classe `ListaGenerica<T>` genérica |
| **Exceções** | Classe `EstoqueException` lançada em operações inválidas |
| **Encapsulamento** | Atributos privados/protegidos, métodos públicos |
| **ID Único** | Contador estático `proximoId` em `Item` |

---

## 5. Funcionalidades Principais

1. **Adicionar Item**: cria novo produto ou matéria-prima
2. **Remover Item**: deleta item do estoque
3. **Modificar Item**: edita nome, descrição, link
4. **Localizar Item**: busca por ID ou nome
5. **Listar Itens**: exibe todos os itens (com polimorfismo)
6. **Registrar Entrada**: aumenta quantidade (cria movimento)
7. **Registrar Saída**: diminui quantidade (cria movimento)
8. **Exibir Histórico**: mostra todas as movimentações
9. **Buscar Internet**: abre navegador com link do item
10. **Persistência**: salva/carrega dados em arquivos .txt

---

## 6. Persistência de Dados

### **itens.txt**
Formato: `TIPO;ID;NOME;DESCRICAO;QUANTIDADE;LINK;DETALHE`

Exemplo:
```
PRODUTO;1;Parafuso;Parafuso M3;100;http://google.com/search?q="Parafuso";Ferragens
MATERIA;2;Madeira;Madeira de pinho;50;http://example.com/madeira;FornecedorX
```

### **movimentos.txt**
Formato: `ID;DATA;TIPO;QUANTIDADE;ID_ITEM;NOME_ITEM`

Exemplo:
```
1;2025-11-16 14:30:45;ENTRADA;50;1;Parafuso
2;2025-11-16 14:35:20;SAIDA;10;1;Parafuso
```

---

## 7. Compilação e Execução

**Compilar:**
```bash
g++ -std=c++17 main.cpp Estoque.cpp Item.cpp ItemProduto.cpp ItemMateria.cpp MovimentoEstoque.cpp -Wall -Wextra -o estoque_app
```

**Executar:**
```bash
./estoque_app
```

---

## 8. Tratamento de Erros

- **Quantidade negativa**: `EstoqueException` ("Quantidade deve ser positiva")
- **Estoque insuficiente**: `EstoqueException` ("Quantidade insuficiente")
- **Item não encontrado**: `EstoqueException` ("Item com ID X não encontrado")
- **Arquivo não encontrado**: aviso, inicia com estoque vazio

---

## 9. Notas Técnicas

- **Gerenciamento de Memória**: ponteiros com `new` e `delete` gerenciados manualmente
- **Templates**: `ListaGenerica<T>` baseado em `std::vector` interno
- **Índices**: conversão de `int` para `std::size_t` para evitar warnings
- **EOF Handling**: trata fim de entrada para evitar loops infinitos
- **ID Estático**: `Item::proximoId` garante IDs únicos globalmente
- **Polimorfismo em Runtime**: métodos virtuais garantem chamadas corretas

---

## 10. Utilitários Auxiliares

Arquivo | Função
---------|--------
`add_items.cpp` | Adiciona dois itens de teste via API (não via stdin)
`remove_item.cpp` | Remove item por ID (aceita ID como argumento)
`test_flow.cpp` | Testa todas as funcionalidades de forma automatizada

---

**Projeto finalizado e testado. Todos os requisitos de POO atendidos.**
