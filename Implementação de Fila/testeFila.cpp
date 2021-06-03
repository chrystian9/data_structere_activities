#include <iostream>
using namespace std;

class noh{
	friend class fila;
	private:
		noh* next;
		unsigned dado;
	public:
		noh(unsigned valor){
			next = NULL;
			dado = valor;
		}
		~noh(){
			next = NULL;
			delete next;
		}
		
};

class fila{
	private:
		noh* begin;
		noh* end;
		unsigned size;
		unsigned dado;
	public:
		fila(){
			begin = NULL;
			end = NULL;
			size = 0;
		}
		~fila(){
			while (filaEmpty() != true) retirar_dequeue();
			delete begin;
			delete end;
		}
		
		bool filaEmpty(){
			if(begin == NULL) return true;
			else return false;
		}
		
		void exibeDado(){
			cout << dado << endl;
		}
		
		void sizeShow(){
			cout << size << endl;
		}
		
		void inserir_enqueue(unsigned valor){
			noh* novo = new noh (valor);
			
			if(filaEmpty()){
				begin = novo;
			}else{
				end->next = novo;
			}
			end = novo;
			size++;
			
			novo = NULL;
			delete novo;
		}
		
		void retirar_dequeue(){
			noh* aux;
			
			aux = begin;
			begin = aux->next;
			dado = aux->dado;
			
			if(filaEmpty()){
				end = NULL;
			}
			
			aux->~noh();
			delete aux;
			
			size--;
		}
		
		void espia(){
			if(begin == NULL){
				cout << "Inicio igual a NULL" << endl;
			}else cout << "Dado no inicio: " << begin->dado << endl << "Dado no fim: " << end->dado << endl;
		}
};

int main (){
	fila* fila1 = new fila;
	
	int aux[10] = {12, 15, 16, 20, 25, 33, 1, 5, 7, 66};
	
	cout << "inserindo" << endl << endl;
	for(int c=0; c<10; c++){
		fila1->inserir_enqueue(aux[c]);
		
		cout << "Em c = " << c << endl;
		fila1->espia();
		cout << endl;
	}
	
	cout << endl << "Tamanho da fila: ";
	fila1->sizeShow();
	cout << endl << endl;
	
	cout << "retirando" << endl << endl;
	for(int c=0; c<10; c++){
		fila1->retirar_dequeue();
		
		cout << "Dado retirado: ";
		fila1->exibeDado();
		
		cout << "Em c = " << c << endl;
		fila1->espia();
		cout << endl;
	}
	
	delete fila1;
	return 0;
}
