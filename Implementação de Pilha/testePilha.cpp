#include <iostream>
using namespace std;

class noh{
	friend class pilha;
	private:
		int dado;
		noh* prox;
	public:
		noh(){
			dado = 0;
			prox = NULL;
		}
		~noh(){
			prox = NULL;
			delete prox;
		}
};

class pilha{
	private:
		noh* topo;
		unsigned tam;
		unsigned dado;
	public:
		pilha(){
			topo = NULL;
			tam = 0;
		}
		~pilha(){
			retirada_Pop();
			delete topo;
		}
		unsigned tamanho(){
			return tam;
		}
		void inserir_Push(int valor){
			noh* novo = new noh;
			
			novo->dado = valor;
			novo->prox = topo;	
			topo = novo;
			tam++;
			
			novo = NULL;
			delete novo;
		}
		void retirada_Pop(){
			noh* aux = NULL;
			
			aux = topo;
			dado = aux->dado;
			topo = aux->prox;
			tam--;
			exibeDado();
			
			aux->~noh();
			delete aux;
		}
		bool vazia(){
			if(topo == NULL) return true;
			else return false;
		}
		void exibeDado(){
			cout << "Dado retirado do topo: " << dado << endl;
		}
		void espia(){
			if(topo != NULL){
				cout << topo->dado << endl;
			}else cout << "NULL" << endl;
		}
};

int main (){
	pilha pilha1;
	int aux[10] = {12, 15, 16, 20, 25, 33, 1, 5, 7, 66};
	
	cout << "inserindo" << endl << endl;
	for(int c=0; c<10; c++){
		pilha1.inserir_Push(aux[c]);
		
		cout << "Em c = " << c << ", o topo e ";
		pilha1.espia();
	}
	cout << endl;
	cout << "Tamanho da pilha: " << pilha1.tamanho() << endl << endl;
	
	cout << "retirando" << endl << endl;
	for(int c=0; c<10; c++){
		pilha1.retirada_Pop();
		
		cout << "Em c = " << c << ", o topo e ";
		pilha1.espia();
	}
	
	return 0;
}
