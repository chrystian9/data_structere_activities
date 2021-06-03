#include <iostream>
using namespace std;

typedef int Dado;

class noh {
	friend class pilha;
	private:
		Dado dado; 
		noh* proximo;
	public:
		noh(Dado d = 0){
			dado = d;
			proximo = NULL;
		}
};

class pilha{
	private:
		noh* topo;
		int tamanho;    
	public:
		pilha(){
			topo = NULL;
			tamanho = 0;
		}
		~pilha(){
			while(topo != NULL) desempilha();
		}
		void empilha(Dado valor){
			noh* newNoh = new noh(valor);
			
			if(topo != NULL) newNoh->proximo = topo;
			topo = newNoh;
			 
			tamanho++;
		}
		Dado desempilha(){
			noh* remove = topo;
			Dado aux = remove->dado;
			
			topo = topo->proximo;
			
			tamanho--;
			delete remove;
			
			return aux;
		}	
		Dado espia(){ return topo->dado; }
};

int main(){
	pilha Pilha;
	Dado aux;
	
	for(int c=0; c<5; c++){
		aux = rand();
		cout << "rand: " << aux << " | ";
		Pilha.empilha(aux);
	}
	cout << endl;
	
	for(int c=0; c<5; c++){
		cout << "removido " << Pilha.desempilha() << " | ";
		cout << "topo atual: " << Pilha.espia() << endl;
	}
	
	return 0;	
}
