#include <iostream>
using namespace std;

typedef char Dado;

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
	pilha Pilha1, Pilha2;
	string aux;
	bool test = true;
	int tamanho;
	
	cout << "Digite uma string de A e B: ";
	cin >> aux;
	tamanho = aux.length();
	
	for(int c=0; c<tamanho; c++){
		cout << "empilhando: " << aux[c] << " ";
		Pilha1.empilha(aux[c]);
	}
	cout << endl;
	
	cout << "Digite outra string de A e B: ";
	cin >> aux;
	
	if(tamanho != aux.length()) test = false;
	else{
		for(int c=aux.length()-1; c>=0; c--){
			cout << "empilhando: " << aux[c] << " ";
			Pilha2.empilha(aux[c]);
		}
		cout << endl;
		
		for(int c=0; c<tamanho; c++){
			if(Pilha1.desempilha() == Pilha2.desempilha() and test != false) test = true;
			else test = false;
		}
	}
	
	if(test == true) cout << "Sao inversas" << endl;
	else if(test == false) cout << "Nao sao inversas" << endl;
	
	return 0;
}
