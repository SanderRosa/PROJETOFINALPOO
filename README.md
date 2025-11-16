Módulo de Gestão de Estoque (Trabalho Final POO)
Este repositório contém o código-fonte do Módulo de Gestão de Estoque, desenvolvido como projeto final para a disciplina de Programação Orientada a Objetos. O sistema implementa um gerenciador de estoque via console, capaz de adicionar, remover, editar e rastrear itens (Produtos e Matérias-Primas), além de registrar um histórico de movimentações.

Contexto Acadêmico
Disciplina: Programação Orientada a Objetos

Professor: André Borin Soares

Autor: Sander Cardoso da Rosa

🚀 Funcionalidades
O programa apresenta um menu de console com as seguintes opções:

1. Adicionar Item: Permite adicionar um novo ItemProduto (com categoria) ou ItemMateria (com fornecedor).

2. Remover Item: Remove um item do estoque permanentemente usando seu ID.

3. Modificar Item: Permite editar o nome, descrição e link de um item existente.

4. Localizar Item: Busca e exibe os detalhes de um item específico, por ID ou por Nome.

5. Listar Itens: Exibe os detalhes de todos os itens cadastrados no estoque.

6. Registrar ENTRADA: Adiciona uma quantidade ao estoque de um item.

7. Registrar SAIDA: Remove uma quantidade do estoque de um item.

8. Exibir Histórico: Mostra todas as movimentações de entrada e saída registradas.

9. Buscar Item na Internet: Abre o navegador padrão no link associado ao item.

0. Salvar e Sair: Salva o estado atual do estoque e do histórico em arquivos de texto (itens.txt, movimentos.txt) e encerra o programa.

🔧 Conceitos de POO Aplicados
Este projeto foi desenvolvido para atender aos requisitos da disciplina, aplicando diversos conceitos-chave de Programação Orientada a Objetos:

Classe Base (Abstrata): A classe Item (Item.h) serve como base abstrata para todos os itens do estoque, definindo atributos comuns e métodos virtuais puros como getTipo() e getDetalheEspecifico().

Herança: As classes ItemProduto (ItemProduto.h) e ItemMateria (ItemMateria.h) herdam de Item, especializando-a com seus próprios atributos (categoria e fornecedor, respectivamente).

Polimorfismo: Utilizado extensivamente na classe Estoque (Estoque.cpp). Os métodos listarItens() e salvarDados() iteram sobre a lista de Item* e chamam métodos (exibirDetalhes(), getTipo(), etc.) que se comportam de maneira diferente dependendo do objeto ser ItemProduto ou ItemMateria.

Interface: A classe IExibivel (IExibivel.h) define um contrato com o método exibirDetalhes(), que é então implementado pela classe Item e, por consequência, por suas filhas.

Templates: A classe ListaGenerica<T> (ListaGenerica.h) é uma classe de template usada para gerenciar as listas de Item* e MovimentoEstoque* dentro da classe Estoque.

Tratamento de Exceções: A classe EstoqueException (EstoqueException.h) é uma exceção customizada usada para tratar erros de lógica de negócios, como "item não encontrado" ou "estoque insuficiente".

Persistência de Dados: O sistema utiliza ifstream e ofstream (na classe Estoque) para carregar e salvar todos os itens e movimentações em arquivos de texto, garantindo que os dados não sejam perdidos.

📊 Diagrama de Classes
O diagrama abaixo ilustra a arquitetura e o relacionamento entre as classes do módulo de estoque.
https://github.com/SanderRosa/PROJETOFINALPOO/blob/main/Diagrama%20de%20Classes%20-%20Modulo%20Estoque.png?raw=true

⚙️ Como Compilar e Executar
O projeto é escrito em C++ padrão e pode ser compilado com qualquer compilador moderno (como g++ ou Clang).

Clone este repositório:

Bash

git clone <url-do-repositorio>
cd <nome-do-repositorio>
Compile todos os arquivos-fonte .cpp. (Nota: O arquivo MovimentoEstoque.cpp não estava entre os arquivos fornecidos, mas ele é necessário para a compilação, pois MovimentoEstoque.h declara métodos que precisam de definição).

Assumindo que MovimentoEstoque.cpp existe:

Bash

g++ main.cpp Estoque.cpp Item.cpp ItemProduto.cpp ItemMateria.cpp MovimentoEstoque.cpp -o gestor_estoque -std=c++11
Execute o programa:

Bash

./gestor_estoque
📝 Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo LICENSE para mais detalhes.
