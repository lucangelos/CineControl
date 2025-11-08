#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*Criando os bancos de dados*/
struct Filme {
	int id;
	string titulo;
	float avaliacao;
	bool dublado = true;
};

struct Sala {
	int id;
	int idFilme;
	string tituloFilme;
	float precoIngresso;
};

struct Pagamento {
	int codigo;
	int idSala;
	float preco_ingresso;
	int quantidade_ingresso;

	float precoFinal() const {
		return preco_ingresso * quantidade_ingresso;
	}

	bool debito = true;
};

vector<Pagamento> pagamentos;
vector<Sala> salas;
vector<Filme> filmes;

/*FUNÇÕES DOS FILMES*/
void adicionarFilme() {
	Filme f;
	cout << "\nDigite o titulo do filme: ";
	cin.ignore();
	getline(cin, f.titulo);

	cout << "\nAvaliacao (0 a 10): ";
	cin >> f.avaliacao;

	if (f.avaliacao < 0) f.avaliacao = 0;
	if (f.avaliacao > 10) f.avaliacao = 10;

	char resposta;
	do {
		cout << "\nO filme esta dublado? (S/N): ";
		cin >> resposta;

		if (resposta == 'S' || resposta == 's') {
			f.dublado = true;
		} else if (resposta == 'N' || resposta == 'n') {
			f.dublado = false;
		} else {
			cout << "\n[ERRO] Opcao invalida! Digite apenas S ou N.\n";
		}
	} while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

	f.id = filmes.size() + 1;
	filmes.push_back(f);

	cout << "\nFilme adicionado com sucesso!\n";
	cout << "-----------------------------\n";
}

void listarFilme() {
	if (filmes.empty()) {
		cout << "\nNenhum filme cadastrado.\n";
		return;
	}

	for (auto &f : filmes) {
		cout << "\n----------------------\n";
		cout << "ID: " << f.id << endl;
		cout << "Titulo: " << f.titulo << endl;
		cout << "Avaliacao: " << f.avaliacao << endl;
		cout << "Dublado: " << (f.dublado ? "Sim" : "Nao") << endl;
	}
}

/*FUNÇÕES DA SALA*/
void criarSala() {
	if (filmes.empty()) {
		cout << "\nNao eh possivel criar uma sala. Cadastre um filme primeiro.\n";
		return;
	}

	Sala s;
	s.id = salas.size() + 1;

	cout << "\n------------------------\n";
	cout << "Filmes disponiveis:\n";
	for (auto &f : filmes) {
		cout << "ID: " << f.id << " - " << f.titulo << endl;
	}

	int idEscolhido;
	cout << "\nDigite o ID do filme que sera adicionado nessa sala: ";
	cin >> idEscolhido;

	bool encontrado = false;
	for (auto &f : filmes) {
		if (f.id == idEscolhido) {
			s.idFilme = f.id;
			s.tituloFilme = f.titulo;
			encontrado = true;
			break;
		}
	}

	if (!encontrado) {
		cout << "\n[ERRO] O filme nao foi encontrado. Sala nao criada.\n";
		return;
	}

	cout << "\nPreco do ingresso: ";
	cin >> s.precoIngresso;

	salas.push_back(s);
	cout << "\nSala criada com sucesso!\n";
}

void listarSalas() {
	if (salas.empty()) {
		cout << "\nNenhuma sala foi criada ainda.\n";
		return;
	}

	for (auto &s : salas) {
		cout << "\n--------------------------\n";
		cout << "ID da sala: " << s.id << endl;
		cout << "Titulo do filme: " << s.tituloFilme << endl;
		cout << "Preco do ingresso: R$" << s.precoIngresso << endl;
	}
}

/*FUNÇÕES DE PAGAMENTO*/
void pagamento() {
	Pagamento p;
	if (salas.empty()) {
		cout << "\nNao ha salas disponiveis no momento. Tente novamente mais tarde.\n";
		return;
	}

	cout << "\n----------------------\n";
	cout << "-- SALAS DISPONIVEIS --\n";
	listarSalas();

	int idEscolhido;
	cout << "\nDigite o ID da sala em que voce ira comprar: ";
	cin >> idEscolhido;

	bool encontrado = false;
	for (auto &s : salas) {
		if (s.id == idEscolhido) {
			p.idSala = s.id;
			p.preco_ingresso = s.precoIngresso;
			encontrado = true;
			break;
		}
	}

	if (!encontrado) {
		cout << "\n[ERRO] Sala nao encontrada.\n";
		return;
	}

	p.codigo = pagamentos.size() + 1;

	cout << "\nQuantidade de ingressos: ";
	cin >> p.quantidade_ingresso;

	float total = p.precoFinal();
	cout << "\nPreco total: R$" << total << endl;

	char forma_pagamento;
	do {
		cout << "\nPagamento sera no debito (D) ou credito (C)? ";
		cin >> forma_pagamento;

		if (forma_pagamento == 'D' || forma_pagamento == 'd') {
			p.debito = true;
		} else if (forma_pagamento == 'C' || forma_pagamento == 'c') {
			p.debito = false;
		} else {
			cout << "\n[ERRO] Valor invalido! Digite apenas D ou C.\n";
		}
	} while (forma_pagamento != 'D' && forma_pagamento != 'd' && forma_pagamento != 'C' && forma_pagamento != 'c');

	pagamentos.push_back(p);

	cout << "\nPagamento registrado com sucesso!\n";
	cout << "Codigo: " << p.codigo << endl;
	cout << "Sala ID: " << p.idSala << endl;
	cout << "Total pago: R$" << total << endl;
	cout << "Forma de pagamento: " << (p.debito ? "Debito" : "Credito") << endl;
}

void folhaPagamento() {
	if (pagamentos.empty()) {
		cout << "\nNenhum pagamento efetuado.\n";
		return;
	}

	float total_arrecadado = 0;
	for (auto &p : pagamentos) {
		cout << "\nCodigo do pagamento: " << p.codigo << endl;
		cout << "ID da sala: " << p.idSala << endl;
		cout << "Quantidade de ingressos: " << p.quantidade_ingresso << endl;
		cout << "Preco final: R$" << p.precoFinal() << endl;
		cout << "Forma de pagamento: " << (p.debito ? "Debito" : "Credito") << endl;
		cout << "------------------------------------\n";

		total_arrecadado += p.precoFinal();
	}

	cout << "\nTOTAL ARRECADADO: R$" << total_arrecadado << endl;
}

/*Parte administrativa*/
void administrador() {
	int opc;
	do {
		cout << "\n--- CINEMA ALEGRIA ---\n";
		cout << "--  Menu do Administrador  --\n";
		cout << "1 - Adicionar filme\n";
		cout << "2 - Listar filmes\n";
		cout << "3 - Adicionar sala\n";
		cout << "4 - Listar salas\n";
		cout << "5 - Folha de Pagamento\n";
		cout << "0 - Voltar\n";
		cout << "\nEscolha uma das opcoes: ";
		cin >> opc;
		cin.ignore();

		switch (opc) {
			case 1: adicionarFilme(); break;
			case 2: listarFilme(); break;
			case 3: criarSala(); break;
			case 4: listarSalas(); break;
			case 5: folhaPagamento(); break;
			case 0: cout << "\nVoltando ao menu principal...\n"; break;
			default: cout << "\n[ERRO] Valor invalido!\n"; break;
		}
	} while (opc != 0);
}

/*Parte do cliente*/
void cliente() {
	int opc;
	do {
		cout << "\n--- CINEMA ALEGRIA ---\n";
		cout << "--  Menu do Cliente  --\n";
		cout << "1 - Salas e Filmes disponiveis\n";
		cout << "2 - Pagar ingresso\n";
		cout << "0 - Voltar\n";
		cout << "\nEscolha uma das opcoes: ";
		cin >> opc;
		cin.ignore();

		switch (opc) {
			case 1: listarSalas(); break;
			case 2: pagamento(); break;
			case 0: cout << "\nVoltando ao menu principal...\n"; break;
			default: cout << "\n[ERRO] Valor invalido!\n"; break;
		}
	} while (opc != 0);
}

int main() {
	int opc;
	do {
		cout << "\n======= CINEMA ALEGRIA =======\n";
		cout << "1 - Administrador\n";
		cout << "2 - Cliente\n";
		cout << "0 - Finalizar\n";
		cout << "\nEscolha uma das opcoes: ";
		cin >> opc;
		cin.ignore();

		switch (opc) {
			case 1: administrador(); break;
			case 2: cliente(); break;
			case 0: cout << "\nFinalizando...\n"; break;
			default: cout << "\n[ERRO] Valor invalido!\n"; break;
		}
	} while (opc != 0);

	return 0;
}
