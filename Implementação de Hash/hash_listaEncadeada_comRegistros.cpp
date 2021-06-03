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
		noh(unsigned newId);
		void confStruct();
		void exibeRegistro();
};

class lista{
	private:
		noh* begin;
		noh* end;
		unsigned size;
	public:
		lista();
		void insert_end(unsigned id);	
		bool remove(unsigned id);
		void exibe();
		void exibeRegistro(unsigned id);
};

class Hash{
	private:
		unsigned size;
		lista *tabela;
	
	public:
		Hash(unsigned tam);
		unsigned key(unsigned id);
		void insert(unsigned id);
		void remove(unsigned id);
		void exibe();
		void exibeRegistro(unsigned id);
};

// funões do noh

noh::noh(unsigned newId){
	id = newId;
	next = NULL;
	previous = NULL;
	registroNoh = new registro;
	confStruct();
}

void noh::confStruct(){
	cin.ignore();
	cout << "Digite o nome: ";
	cin >> registroNoh->nome;
	cout << "Digite o setor: ";
	cin >> registroNoh->setor;
	cout << "Digite a funcao: ";
	cin >> registroNoh->funcao;
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

void lista::insert_end(unsigned id){
	noh *newNoh = new noh(id);
	
	if(begin == NULL) begin = newNoh;
	else{
		end->next = newNoh;
		newNoh->previous = end;
	}
	end = newNoh;
	size++;
}

bool lista::remove(unsigned id){
	noh *aux = begin;
	noh *aux2;
	
	while(aux->id != id){
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
			
	while(aux != NULL){
		cout << aux->id << " ";
		aux = aux->next;
	}
}

void lista::exibeRegistro(unsigned id){
	noh *aux = begin;
			
	while(aux->id != id or aux != NULL) aux = aux->next;
	if(aux == NULL) cout << "Registro nao encontrado" << endl;
	else aux->exibeRegistro();

}

//funções da Hash

Hash::Hash(unsigned tam){
	size = tam;
	tabela = new lista[tam];
}
		
unsigned Hash::key(unsigned id){
	return id % size;
}

void Hash::insert(unsigned id){
	unsigned i = key(id);
	
	tabela[i].insert_end(id);
}

void Hash::remove(unsigned id){
	unsigned i = key(id);
	
	if(!tabela[i].remove(id)) cout << "Dado nao encontrado" << endl;
}

void Hash::exibe(){
	for(unsigned c=0; c<size; c++){
		cout << c << ": ";
		tabela[c].exibe();
		cout << endl;
	}
}

void Hash::exibeRegistro(unsigned id){
	unsigned i = key(id);
	
	tabela[i].exibeRegistro(id);	
}


int main(){
	unsigned aux;
	
	cout << "Digite o tamanho da tabela Hash: ";
	cin >> aux;
	
	Hash hash(aux);
	
	aux = 1;
	while(aux != 0){
		cout << endl;
		menu();
		cout << "Digite a funcao: ";
		cin >> aux;
	
		if(aux == 1){
			cout << "Digite o id a ser inserido: ";
			cin >> aux;
			hash.insert(aux);
			aux = 1;
		
		}else if(aux == 2){
			cout << "Digite o id a ser removido: ";
			cin >> aux;
			hash.remove(aux);
			aux = 2;
		
		}else if(aux == 3) hash.exibe();
		
		else if(aux == 4){
			cout << "Digite o id do registro: ";
			cin >> aux;
			hash.exibeRegistro(aux);
			aux = 4;
		}
	}
	
	return 0;
	
}
