#include <iostream>
using namespace std;

class MaxHeap {
    private:
        int* heap;
        int capacidade;
        int tamanho;
        inline void swap(int &A, int &B);
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void arruma();
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
    public:
        MaxHeap(int cap);
        MaxHeap(int vet[], int tam, int cap);
        ~MaxHeap();
        void imprime();
        int espiaRaiz();
        int retiraRaiz();
        bool insere(int d);
};

MaxHeap::MaxHeap(int cap){
    capacidade = cap;
    tamanho = 0;
    heap = new int [capacidade];
}

MaxHeap::MaxHeap(int vet[], int tam, int cap){
    heap = vet;
    tamanho = tam;
    capacidade = cap;
    arruma();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::swap(int &A, int &B){
    int aux = A;
    A = B;
    B = aux;
}

int MaxHeap::pai(int i){
    return (i-1)/2;
}

int MaxHeap::esquerdo(int i){
    return (i*2)+1;
}

int MaxHeap::direito(int i){
    return (i*2)+2;
}

void MaxHeap::arruma(){
    int i = (tamanho - 1)/2;
    while(i >= 0){
        corrigeDescendo(i);
        i--;
    }
}

void MaxHeap::corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = i;
    
    if((esq <= tamanho-1) and (heap[maior] < heap[esq])){
        maior = esq;
    }
    if((dir <= tamanho-1) and (heap[maior] < heap[dir])){
        maior = dir;
    }
    if(maior != i){
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i){
    int p = pai(i);
    
    if((p >= 0) and (heap[i] > heap[p])){
        swap(heap[i], heap[p]);
        corrigeSubindo(p);
    }
}

// Metodo didatico e para depuração
void MaxHeap::imprime(){
    int i = 0;
    while(i < tamanho){
        cout << heap[i++] << " ";
    }
    cout << endl;
}

int MaxHeap::espiaRaiz(){
    return heap[0];
}

int MaxHeap::retiraRaiz(){
    if(tamanho == 0) return -1;
    int aux = heap[0];
    swap(heap[0], heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

bool MaxHeap::insere(int d){
    if(tamanho == capacidade) return false;
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
    return true;
}

int main (){
	MaxHeap *heap = new MaxHeap(10);
	
	cout << "passo 1: Colocando dados" << endl << endl;
	for(int c=0; c<10; c++){
		if(heap->insere(10-c));
		else cout << "ERRO" << endl;
	}
	
	cout << endl << "passo 2: Imprimindo os valores do Heap" << endl << endl;
	heap->imprime();
	
	cout << endl << "passo 3: Retirando metade do heap" << endl << endl;
	for(int c=0; c<5; c++){
		cout << "dado removido: " << heap->retiraRaiz() << endl;
	}
	
	cout << endl << "passo 4: Espionando a raiz" << endl << endl;
	cout << "a raiz: " << heap->espiaRaiz() << endl;
	
	cout << endl << "passo 5: Retirando todos os dados" << endl << endl;
	for(int c=0; c<5; c++){
		cout << "dado removido: " << heap->retiraRaiz() << endl;
	}
	
	delete heap;
	
	int vet[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	
	cout << endl << "passo 1: Passando o vetor" << endl << endl;
	heap = new MaxHeap(vet, 10, 10);
	
	cout << endl << "passo 2: Imprimindo os valores do Heap" << endl << endl;
	heap->imprime();
	
	cout << endl << "passo 3: Retirando metade do heap" << endl << endl;
	for(int c=0; c<5; c++){
		cout << "dado removido: " << heap->retiraRaiz() << endl;
	}
	
	cout << endl << "passo 4: Espionando a raiz" << endl << endl;
	cout << "a raiz: " << heap->espiaRaiz() << endl;
	
	cout << endl << "passo 5: Retirando todos os dados" << endl << endl;
	for(int c=0; c<5; c++){
		cout << "dado removido: " << heap->retiraRaiz() << endl;
	}
	
	delete heap;
		
	cout << "----- FIM '-' -----" << endl;
	return 0;
}
