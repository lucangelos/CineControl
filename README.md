# 🎬 CineControl

Recebi um desafio do meu professor Kayã para fazer um projeto backend, e durante os dias 03 - 08 de novembro estive estudando e fazendo outros projetos para aprendizagem para chegar em um mais complexo, resultando no **CineControl**.
Antes de explicar o que é o CineControl, irei explicar o por que eu escolhi a linguagem **C++** para fazer este projeto.
Comecei a aprender lógica de programação com C++ durante as aulas da Etec com o professor Rafael Moura (excelente professor), através da aula dele eu tive um boom de interesse sobre programação backend. E ao receber o desafio, eu pensei em entregá-lo o mais rápido possível (evitando erros e falhas de interpretação), então cheguei a conclusão que C++ seria a linguagem mais adequada para esta proposta feita pelo professor Kayã.

## 💡 Explicação do projeto

**CineControl** é um sistema de gerenciamento de cinema desenvolvido em **C++**, com foco em simular o funcionamento básico de um cinema: cadastro de filmes, criação de salas, controle de pagamentos e exibição de informações administrativas e de cliente.


---

## 📋 Funcionalidades

### 🎞️ Módulo de Administrador
- Adicionar filmes ao catálogo;
- Listar todos os filmes cadastrados;
- Criar salas de exibição e definir o preço do ingresso;
- Listar salas disponíveis;
- Visualizar a folha de pagamento, que será efetuado após os pagamentos da clientela.

### 🎟️ Módulo de Cliente
- Consultar as salas e os filmes em cartaz;
- Comprar ingressos (com opção de débito ou crédito);
- Visualizar o total a pagar.


## ⚙️ Estrutura do Projeto

O sistema utiliza **structs** e **vetores (`vector`)** como base para simular o banco de dados em memória.
Levei em consideração que este é o meu primeiro projeto em C++, então decidi que simularia o banco de dados dentro do C++.

### Principais Structs:
- **`Filme`** → armazena título, avaliação e status de dublagem.  
- **`Sala`** → associa um filme e define o preço do ingresso.  
- **`Pagamento`** → controla as compras, formas de pagamento e cálculo do total (essencial para a folha de pagamento e para o cliente).  

---

## 🧠 Conceitos Envolvidos

- Estruturas (`struct`);
- Vetores (`vector`);
- Funções e modularização;
- Estruturas de repetição e controle de fluxo (`do...while`, `switch`);
- Simulação de CRUD básico (Create, Read);
- Boas práticas de organização de código em C++.

## 🚀 Como Executar

### Pré-requisitos:
- Copiar o código **main.cpp** disponível;
- Compilar (compiladores específicos (como **g++**, **clang**, ou **Dev-C++**) ou em um próprio compilador online (**https://www.onlinegdb.com/online_c++_compiler**).
