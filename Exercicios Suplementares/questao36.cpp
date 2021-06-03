#include <iostream>
using namespace std;

class MaxHeap {
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
		int maior = i;
		
		if((esq <= tamanho-1) and (heap[maior] < heap[esq])){
			maior = esq;
		}
		if((dir <= tamanho-1) and (heap[maior] < heap[dir])){
			maior = dir;
		}
		if(maior != i){
			swap(&heap[i], &heap[maior]);
			corrigeDescendo(maior);
		}
	}
    void corrigeSubindo(int i){
		int p = pai(i);
		
		if((p >= 0) and (heap[i] > heap[p])){
			swap(&heap[i], &heap[p]);
			corrigeSubindo(p);
		}
	}
public:
    MaxHeap(int cap){
		capacidade = cap;
		tamanho = 0;
		heap = new int [capacidade];
	}
    MaxHeap(int vet[], int tam, int cap=0){
		heap = vet;
		tamanho = tam;
		capacidade = cap;
		arruma();
	}
    ~MaxHeap(){
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
	MaxHeap *heap = new MaxHeap(10);
	
	cout << "passo 1: Colocando dados" << endl << endl;
	for(int c=0; c<10; c++){
		if(heap->insere(c));
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
	
	int vet[10] = {1, 5, 6, 4, 3, 8, 7, 2, 0, 10};
	
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
