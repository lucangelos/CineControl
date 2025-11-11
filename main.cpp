#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*Criandos os bancos de dados*/
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
	/*vector<vector<Assento>> assentos;*/
};

struct Pagamento {
	int codigo;
	int idSala;
	float preco_ingresso;
	int quantidade_ingresso;
	/*função para calcular o valor final*/
	float precoFinal() const{
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
	cout << "\nTitulo: ";
	getline(cin, f.titulo);
	cout << "\nAvaliacao (0 a 10): ";
	cin >> f.avaliacao;
	if (f.avaliacao < 0){
		f.avaliacao = 0;
	} 
	if (f.avaliacao > 10) {
		f.avaliacao = 10;
	}
	char resposta;
	do {
		cout << "\nO filme esta dublado? (S/N): ";
		cin >> resposta;
		if (resposta == 'S' || resposta == 's') {
			f.dublado = true;
		} else if (resposta == 'N' || resposta == 'n') {
			f.dublado = false;
		} else {
			cout << "Opcao invalida! Digite apenas S ou N." << endl;
		}
	} while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');
	
	f.id = filmes.size() + 1;
	filmes.push_back(f);
	cout << "Filme adicionado com sucesso!" << endl;
	cout << "--------------------" << endl;
}

void listarFilme() {
	if (filmes.empty()) {
		cout << "Nenhum filme cadastrado." << endl;
		return;
	}
	for (auto &f : filmes) {
		cout << "----------------------" << endl;
		cout << "ID: " << f.id << endl;
        cout << "Titulo: " << f.titulo << endl;
        cout << "Avaliacao: " << f.avaliacao << endl;
        cout << "Dublado: " << (f.dublado ? "Sim" : "Nao") << endl;
	}
}

void deletarFilme() {
	if (filmes.empty()) {
		cout << "Nenhum filme foi criado." << endl;
		return;
	}
	for (auto &f : filmes) {
		cout << "\nID: " << f.id << " - " << f.titulo << endl;
	}
	int idEscolhido;
	cout << "Digite o ID do filme em que deseja deletar: ";
	cin >> idEscolhido;
	bool encontrado = true;
	for (auto it = filmes.begin(); it != filmes.end(); it++) {
		if(it->id == idEscolhido) {
			cout << "\nFilme " << it->titulo << " deletado com sucesso!" << endl;
			cout << "\n--------------------------\n";
			filmes.erase(it);
			encontrado = true;
			break;
		}
	}
	if (!encontrado) {
		cout << "[ERROR] ID inexistente." << endl;
	}
}

/*FUNÇÕES DA SALA*/
void criarSala() {
	if (filmes.empty()) {
		cout << "Nao eh possivel criar uma sala. Cadastre um filme primeiro.";
		return;
	}
	Sala s;
	s.id = salas.size() + 1;
	cout << "------------------------" << endl;
	cout << "Filmes disponiveis: " << endl;
	for (auto &f : filmes) {
		cout << "ID :" << f.id << " - " << f.titulo << endl;
	}
	
	int idEscolhido;
	cout << "Digite o ID do filme que sera adicionado nessa sala: ";
	cin >> idEscolhido;
	
	bool encontrado = true;
	for(auto &f : filmes) {
		if (f.id == idEscolhido) {
			s.idFilme = f.id;
			s.tituloFilme = f.titulo;
			encontrado = true;
			break;
		}
	}
	if (!encontrado) {
		cout << "O filme não foi encontrado." << endl;
		cout << "Sala nao criada.";
		return;
	}
	
	cout << "Preco do ingresso: ";
	cin >> s.precoIngresso;
	salas.push_back(s);
	cout << "Sala criada com sucesso!";
}

void listarSalas() {
	if(salas.empty()) {
		cout << "Nenhuma sala foi criada ainda.";
		return;
	}
	for (auto &s : salas) {
		cout << "--------------------------";
		cout << "ID da sala: " << s.id << endl;
		cout << "Titulo do filme: " << s.tituloFilme << endl;
		cout << "Preco do ingresso: " << s.precoIngresso << endl;
	}
}

/*FUNÇÕES DE PAGAMENTO*/
void pagamento() {
	Pagamento p;
	if(salas.empty()) {
		cout << "Nao ha salas disponiveis no momento. Tente novamente mais tarde." << endl;
		return;
	}
	cout << "----------------------" << endl;
	cout << "-- SALAS DISPONIVEIS --";
	listarSalas();
	int idEscolhido;
	cout << "Digite o ID da sala em que voce ira pegar: ";
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
		cout << "Sala nao encontrada." << endl;
		return;
	}
	
	p.codigo = pagamentos.size() + 1;
	cout << "Quantidade de ingressos: ";
	cin >> p.quantidade_ingresso;
	
	float total = p.precoFinal();
	cout << "Preco total: " << total << endl;
	
	char forma_pagamento;
	cout << "Pagamento sera no debito (D) ou credito (C)?\n";
	cin >> forma_pagamento;
	do {
    	if (forma_pagamento == 'D' || forma_pagamento == 'd') {
    		p.debito = true;
    	} else if (forma_pagamento == 'C' || forma_pagamento == 'c'){
    		p.debito = false;
    	} else {
    	    cout << "[ERRO] Voce digitou um valor invalido" << endl;
    	    cout << "Digite apenas D ou C" << endl;
    	} 
	} while (forma_pagamento == 'D' || forma_pagamento == 'd' || forma_pagamento == 'C' || forma_pagamento == 'c');
	pagamentos.push_back(p);
	
	cout << "Pagamento registrado com sucesso!" << endl;
	cout << "Codigo: " << p.codigo << endl;
    cout << "Sala ID: " << p.idSala << endl;
    cout << "Total pago: R$" << total << endl;
    cout << "Forma de pagamento: " << (p.debito ? "Debito" : "Credito") << endl;
}

void folhaPagamento(){
	if(pagamentos.empty()) {
		cout << "Nenhum pagamento efetuado." << endl;
		return;
	}
	
	float total_arrecadado = 0;
	for(auto &p : pagamentos) {
		cout << "Codigo do pagamento: " << p.codigo << endl;
		cout << "ID da sala: " << p.idSala << endl;
		cout << "Quantidade de ingressos: " << p.quantidade_ingresso << endl;
		cout << "Preco final: " << p.precoFinal() << endl;
		cout << "Forma de pagamento: " << (p.debito ? "Debito" : "Credito") << endl;
		cout << "------------------------------------" << endl;
		
		total_arrecadado += p.precoFinal();
	}
	
	cout << "TOTAL ARRECADADO: R$" << total_arrecadado << endl;
}

/*Parte administrativa*/
void administrador(){
	int opc;
	do {
	
	cout << "--- CINEMA ALEGRIA ---" << endl;
	cout << "--  Todas opcoes  --" << endl;
	cout << "1- Adicionar filme" << endl;
	cout << "2- Listar filmes" << endl;
	cout << "3- Adicionar sala" << endl;
	cout << "4- Listar salas" << endl;
	cout << "5- Deletar filme" << endl;
	cout << "6- Folha de Pagamento" << endl;
	cout << "0- Voltar" << endl;
	cout << "-- Escolha uma das opcoes --" << endl;
	cin >> opc;
	cin.ignore();
	
		switch(opc) {
			case 1: adicionarFilme(); break;
			case 2: listarFilme(); break;
			case 3: criarSala(); break;
			case 4: listarSalas(); break; 
			case 5: deletarFilme(); break;
			case 6: folhaPagamento(); break;
			case 0: cout << "Voltando ao menu principal..." << endl; break;
			default: cout << "[ERROR] Valor invalido!" << endl; break;
		}
	} while (opc != 0);
}

/*Parte do cliente*/
void cliente() {
	int opc;
	do {
	
	cout << "--- CINEMA ALEGRIA ---";
	cout << "--  Todas opcoes  --" << endl;
	cout << "1- Salas e Filmes disponiveis" << endl;
	cout << "2- Pagar ingresso" << endl;
	cout << "0- Voltar" << endl;
	cout << "-- Escolha uma das opcoes --" << endl;
	cin >> opc;
	cin.ignore();
	
		switch(opc) {
			case 1: listarSalas(); break;
			case 2: pagamento(); break;
			case 0: cout << "Voltando ao menu principal..." << endl; break;
			default: cout << "[ERROR] Valor invalido!" << endl; break;
		}
	} while (opc != 0);
}

int main(){
	int opc;
	do {
		
	cout << "Escolha uma das opcoes: " << endl;
	cout << "1- Administrador" << endl;
	cout << "2- Cliente" << endl;
	cout << "0- Finalizar" << endl;
	cin >> opc;
	cin.ignore();	
		switch (opc) {
			case 1: administrador(); break;
			case 2: cliente(); break;
			case 0: cout << "Finalizando..." << endl; break;
			default: cout << "[ERROR] Valor invalido!";
		}
	} while (opc != 0);
	return 0;
}
