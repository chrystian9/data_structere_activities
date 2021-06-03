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
		bool vazia(){ return topo == NULL; }
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
	pilha PilhaA, PilhaB, PilhaC;
	string aux;
	bool test = true;
	int tamanho;
	
	cout << "Digite uma string de A, B e C: ";
	cin >> aux;
	tamanho = aux.length();
	
	if(tamanho%2 != 0) test = false;
	else{
		for(int c=0; c<tamanho; c++){
			if(aux[c] == 'A') PilhaA.empilha(aux[c]);
			if(aux[c] == 'B') PilhaB.empilha(aux[c]);
			if(aux[c] == 'C') PilhaC.empilha(aux[c]);
		}
		
		int i = (tamanho-2)/4;
		char aux2[tamanho];
		
		for(int c=0; c<i; c++){
			if(!PilhaA.vazia()) aux2[c] = PilhaA.desempilha();
			else test = false;
		}
		
		if(!PilhaB.vazia()) aux2[i] = PilhaB.desempilha();
		else test = false;
		
		for(int c=i+1; c<tamanho-(i+1); c++){
			if(!PilhaC.vazia()) aux2[c] = PilhaC.desempilha();
			else test = false;
		}
		
		if(!PilhaB.vazia()) aux2[tamanho-(i+1)] = PilhaB.desempilha();
		else test = false;
		
		
		for(int c=tamanho-i; c<tamanho; c++){
			cout << "c " << c << endl;
			if(!PilhaA.vazia()) aux2[c] = PilhaA.desempilha();
			else test = false;
		}
		
		if(test != false){
			for(int c=0; c<tamanho; c++){
				if(aux[c] == aux2[c]) test = true;
				else test = false;
			}
		}else test = false;
	}
	cout << endl;

	if(test == true) cout << "Faz parte do conjunto L" << endl;
	else if(test == false) cout << "Nao faz parte do conjunto L" << endl;
	
	return 0;
}
