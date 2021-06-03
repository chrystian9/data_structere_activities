#include <iostream>
using namespace std;

class MinHeap {
private:
    int* heap;
    int capacidade;
    int tamanho;
    inline void swap(int *A, int *B){
		int aux = *A;
		*A = *B;
		*B = aux;
	}
    inline int pai(int i){
		return (i-1)/2;
	}
    inline int esquerdo(int i){
		return (i*2)+1;
	}
    inline int direito(int i){
		return (i*2)+2;
	}
    void arruma(){
		int i = (tamanho - 1)/2;
		while(i >= 0){
			corrigeDescendo(i);
			i--;
		}
	}
    void corrigeDescendo(int i){
		int esq = esquerdo(i);
		int dir = direito(i);
		int menor = i;
		
		if((esq <= tamanho-1) and (heap[menor] > heap[esq])){
			menor = esq;
		}
		if((dir <=  tamanho-1) and (heap[menor] > heap[dir])){
			menor = dir;
		}
		if(menor != i){
			swap(&heap[i], &heap[menor]);
			corrigeDescendo(menor);
		}
	}
    void corrigeSubindo(int i){
		int p = pai(i);
		
		if((p >= 0) and (heap[i] < heap[p])){
			swap(&heap[i], &heap[p]);
			corrigeSubindo(p);
		}
	}
public:
    MinHeap(int cap){
		capacidade = cap;
		tamanho = 0;
		heap = new int [capacidade];
	}
    MinHeap(int vet[], int tam, int cap=0){
		heap = vet;
		tamanho = tam;
		capacidade = cap;
		arruma();
	}
    ~MinHeap(){
		delete[] heap;
	}
    void imprime(){
		int i = 0;
		while(i < tamanho){
			cout << heap[i] << " ";
			i++;
		}
		cout << endl;
	}
    int espiaRaiz(){
		return heap[0];
	}
	int retiraRaiz(){
		if(tamanho == 0) return -1;
		int aux = heap[0];
		swap(&heap[0], &heap[tamanho-1]);
		tamanho--;
		corrigeDescendo(0);
		cout << endl << "imprimindo: ";
		imprime();
		return aux;
	}
    bool insere(int d){
		if(tamanho == capacidade) return false;
		tamanho++;
		heap[tamanho-1] = d;
		corrigeSubindo(tamanho-1);
		return true;
	}
};

int main (){
	MinHeap *heap = new MinHeap(10);
	
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
	heap = new MinHeap(vet, 10, 10);
	
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
