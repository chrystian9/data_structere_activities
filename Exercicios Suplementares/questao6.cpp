#include <iostream>
using namespace std;

typedef int Dado; 

class noh {
friend class fila;
private:
    Dado dado; 
    noh* proximo;
public:
    noh(Dado d = 0){
		dado = d;
		proximo = NULL;
	}
};

class fila {
private:
    noh* inicio;
    noh* fim;
    int tamanho;
public:
	fila(){
		inicio = NULL;
		fim = NULL;
		tamanho = 0;
	}
	~fila(){
		while(inicio != NULL) desenfileira();
	}
    void enfileira(Dado valor){
		noh* newNoh = new noh(valor);
		
		if(inicio == NULL) inicio = newNoh;
		else fim->proximo = newNoh;
		fim = newNoh;
		
		tamanho++;
	}
    Dado desenfileira(){
		noh* remove = inicio;
		Dado removido = remove->dado;
		
		if(inicio == fim) inicio = fim = NULL;
		else inicio = inicio->proximo;
		
		tamanho--;
		delete remove;
		
		return removido;
	}	
    Dado espia(){ return inicio->dado; }
};

int main(){
	fila Fila;
	Dado aux;
	
	for(int c=0; c<5; c++){
		aux = rand();
		cout << "rando: " << aux << " | ";
		Fila.enfileira(aux);
	}
	cout << endl;
	
	for(int c=0; c<5; c++){
		cout << "removido " << Fila.desenfileira() << " | ";
		cout << "primeiro atual " << Fila.espia() << endl;
	 }
	 
	 return 0;
}
