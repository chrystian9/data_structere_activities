#include <iostream>
using namespace std;

void menu(){
	cout << "1. Inserir novo registro" << endl;
	cout << "2. Remover registro" << endl;
	cout << "3. Exibir Hash de registros" << endl;
	cout << "4. Exibir registro" << endl;
	cout << "0. Terminar" << endl;	
}

class noh{
	friend class lista;
	private:
		struct registro{
			string nome;
			string setor;
			string funcao;
		};
		registro *registroNoh;
		
		unsigned id;
		noh* next;
		noh* previous;
	public:
		noh();
		void confStruct();
		void exibeRegistro();
		string getNome(){
			return registroNoh->nome;
		}
};

class lista{
	private:
		noh* begin;
		noh* end;
		unsigned size;
	public:
		lista();
		void insert_end(noh *newNoh);	
		bool remove(string nome);
		void exibe();
		void exibeRegistro(string nome);
};

class Hash{
	private:
		unsigned size;
		lista *tabela;
		unsigned UMPRIMO;
	
	public:
		Hash(unsigned tam);
		void setUMPRIMO(unsigned num);
		unsigned funcaoHash(string nome);
		void insert();
		void remove();
		void exibe();
		void exibeRegistro();
};

// funões do noh

noh::noh(){
	next = NULL;
	previous = NULL;
	registroNoh = new registro;
	confStruct();
}

void noh::confStruct(){
	cin.ignore();
	cout << "Digite o nome: ";
	getline(cin, registroNoh->nome);

	cout << "Digite o setor: ";
	getline(cin, registroNoh->setor);

	cout << "Digite a funcao: ";
	getline(cin, registroNoh->funcao);
}

void noh::exibeRegistro(){
	cout << "Nome: " << registroNoh->nome << endl;
	cout << "Setor: " << registroNoh->setor << endl;
	cout << "Funcao: " << registroNoh->funcao << endl;
}

// funções da lista

lista::lista(){
	begin = NULL;
	end = NULL;
	size = 0;
}

void lista::insert_end(noh *newNoh){
	if(begin == NULL) begin = newNoh;
	else{
		end->next = newNoh;
		newNoh->previous = end;
	}
	end = newNoh;
	size++;
}

bool lista::remove(string nome){
	noh *aux = begin;
	noh *aux2;
	
	while(aux->getNome() != nome){
		aux = aux->next;
		if(aux == NULL) return false;
	}
	
	if(begin == end) begin = end = NULL;
	else{
		if(aux->previous != NULL){
			aux2 = aux->previous;
			aux2->next = aux->next;
		}
		if(aux->next != NULL){
			aux2 = aux->next;
			aux2->previous = aux->previous;
		}
		if(aux == end) end = aux->previous;
		if(aux == begin) begin = aux->next;
	}
	
	size--;
	
	delete aux;
	return true;
}
		
void lista::exibe(){
	noh *aux = begin;
	string auxString;
	
	while(aux != NULL){
		auxString = aux->getNome();
		cout << auxString << " ";
		aux = aux->next;
	}
}

void lista::exibeRegistro(string nome){
	noh *aux = begin;
			
	while(aux->getNome() != nome or aux != NULL) aux = aux->next;
	if(aux == NULL) cout << "Registro nao encontrado" << endl;
	else aux->exibeRegistro();

}

//funções da Hash

Hash::Hash(unsigned tam){
	size = tam;
	tabela = new lista[tam];
}

void Hash::setUMPRIMO(unsigned num){
	UMPRIMO = num;
}
		
unsigned Hash::funcaoHash(string s){
	long h = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        h = (UMPRIMO * h + s[i]) % size;   
    }
    return h;
}

void Hash::insert(){
	noh newNoh;
	unsigned i = funcaoHash(newNoh.getNome());
	
	tabela[i].insert_end(&newNoh);
}

void Hash::remove(){
	string nome;
	
	cin.ignore();
	cout << "Digite o nome a ser removido: ";
	cin >> nome;
	unsigned i = funcaoHash(nome);
	
	if(!tabela[i].remove(nome)) cout << "Dado nao encontrado" << endl;
}

void Hash::exibe(){
	for(unsigned c=0; c<size; c++){
		cout << c << ": ";
		tabela[c].exibe();
		cout << endl;
	}
}

void Hash::exibeRegistro(){
	string nome;
	
	cout << "Digite o nome do registro: ";
	cin >> nome;
	
	unsigned i = funcaoHash(nome);
	
	tabela[i].exibeRegistro(nome);	
}


int main(){
	unsigned aux;
	
	cout << "Digite o tamanho da tabela Hash: ";
	cin >> aux;
	
	Hash hash(aux);
	
	cout << "Digite o UMPRIMO: ";
	cin >> aux;
	
	hash.setUMPRIMO(aux);
	
	aux = 1;
	while(aux != 0){
		cout << endl;
		menu();
		cout << "Digite a funcao: ";
		cin >> aux;
	
		if(aux == 1){
			hash.insert();
		
		}else if(aux == 2){
			hash.remove();
		
		}else if(aux == 3) hash.exibe();
		
		else if(aux == 4){
			hash.exibeRegistro();
			
		}
	}
	
	return 0;
	
}
