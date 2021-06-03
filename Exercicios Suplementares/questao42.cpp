#include <iostream>
using namespace std;

void menu(){
	cout << "1. Inserir novo int" << endl;
	cout << "2. Remover int" << endl;
	cout << "3. Exibir Hash" << endl;
	cout << "0. Terminar" << endl;	
}

class noh{
	friend class lista;
	private:
		int dado;
		noh* next;
		noh* previous;
	public:
		noh(int valor);
};

class lista{
	private:
		noh* begin;
		noh* end;
		unsigned size;
	public:
		lista();
		void insert_end(int dado);	
		bool remove(int dado);
		void exibe();
};

class Hash{
	private:
		unsigned size;
		lista *tabela;
	
	public:
		Hash(unsigned tam);
		unsigned key(int dado);
		void insert(int dado);
		void remove(int removido);
		void exibe();
};

// construtor do noh

noh::noh(int valor){
	dado = valor;
	next = NULL;
	previous = NULL;
}

// funções da lista

lista::lista(){
	begin = NULL;
	end = NULL;
	size = 0;
}

void lista::insert_end(int dado){
	noh *newNoh = new noh(dado);
	
	if(begin == NULL) begin = newNoh;
	else{
		end->next = newNoh;
		newNoh->previous = end;
	}
	end = newNoh;
	size++;
}

bool lista::remove(int dado){
	noh *aux = begin;
	noh *aux2;
			
	while(aux->dado != dado){
		aux = aux->next;
		if(aux == NULL){
			cout << "Dado nao encontrado" << endl;
			return false;
		}
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
		cout << aux->dado << " ";
		aux = aux->next;
	}
}

//funções da Hash

Hash::Hash(unsigned tam){
	size = tam;
	tabela = new lista[tam];
}
		
unsigned Hash::key(int dado){
	return dado % size;
}

void Hash::insert(int dado){
	unsigned i = key(dado);
	
	tabela[i].insert_end(dado);
}

void Hash::remove(int removido){
	unsigned i = key(removido);
	
	tabela[i].remove(removido);
}

void Hash::exibe(){
	for(unsigned c=0; c<size; c++){
		cout << c << ": ";
		tabela[c].exibe();
		cout << endl;
	}
}


int main(){
	int aux;
	
	cout << "Digite o tamanho da tabela Hash: ";
	cin >> aux;
	
	Hash hash((unsigned)aux);
	
	aux = 1;
	while(aux != 0){
		cout << endl;
		menu();
		cout << "Digite a funcao: ";
		cin >> aux;
	
		if(aux == 1){
			cout << "Digite o int a ser inserido: ";
			cin >> aux;
			hash.insert(aux);
			aux = 1;
		
		}else if(aux == 2){
			cout << "Digite o int a ser removido: ";
			cin >> aux;
			hash.remove(aux);
			aux = 2;
		
		}else if(aux == 3) hash.exibe();
	}
	
	return 0;
	
}
