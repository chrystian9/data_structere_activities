#include <iostream>
using namespace std;

class noh{
	friend class arvore;
	private:
		int dado;
		noh* fDireita;
		noh* fEsquerda;
		noh* pai;
	public:
		noh(int valor){
			dado = valor;
			fDireita = NULL;
			fEsquerda = NULL;
			pai = NULL;
		}
};

class arvore{
	private:
		noh* raiz;
		
	public:
		arvore();
		~arvore();
		void limpaArvore();
		noh* buscaNoh(int valor);
		void busca(int valor);
		int minimo();
		noh *minimoNoh(noh *aux);
		int maximo();
		noh *maximoNoh(noh *aux);
		void percorreEmOrdem();
		void percorreEmOrdemAux(noh *raiz);
		void percorrePreOrdem();
		void percorrePreOrdemAux(noh *raiz);
		void percorrePosOrdem();
		void percorrePosOrdemAux(noh *raiz);
		void insertRecursivo(const int valor);
		noh* insertNewNoh(noh *raiz, const int valor);
		void transplanta(noh *antigo, noh *novo);
		void remove(const int valor);
		void removeRecursivo(const int valor);
		noh* removeRecAux(noh *umNoh, const int valor);
};	

arvore::arvore(){
	raiz = NULL;
}
		
arvore::~arvore(){
	limpaArvore();
}
		
void arvore::limpaArvore(){
	while(raiz != NULL){
		remove(raiz->dado);
	}
}
		
noh* arvore::buscaNoh(int valor){
	noh *aux = raiz;
	
	while(aux != NULL){
		if(aux->dado > valor) aux = aux->fEsquerda;
		else if(aux->dado < valor) aux = aux->fDireita;
		else if(aux->dado == valor) return aux;
	}
	return aux;
}
		
void arvore::busca(int valor){
	noh *aux = buscaNoh(valor);
		
	if(aux == NULL) cout << "nao encontrado" << endl;
	else cout << "encontrado" << endl;
}
		
int arvore::minimo(){
	if(raiz == NULL) cout << "arvore vazia" << endl;
	else{
		noh *nohMinimo = minimoNoh(raiz);
		return nohMinimo->dado;
	}
}
		
noh* arvore::minimoNoh(noh *aux){
	while(aux->fEsquerda != NULL) aux = aux->fEsquerda;
	return aux;
}
		
int arvore::maximo(){
	if(raiz == NULL) cout << "arvore vazia" << endl;
	else{
		noh* nohMaximo = maximoNoh(raiz);
		return nohMaximo->dado;
	}
}
		
noh* arvore::maximoNoh(noh *aux){
	while(aux->fDireita != NULL) aux = aux->fDireita;
	return aux;
}
		
void arvore::percorreEmOrdem(){
	percorreEmOrdemAux(raiz);
}
		
void arvore::percorreEmOrdemAux(noh *raiz){
	if(raiz != NULL){
		percorreEmOrdemAux(raiz->fEsquerda);
		cout << raiz->dado << " ";
		percorreEmOrdemAux(raiz->fDireita);
	}
}
		
void arvore::percorrePreOrdem(){
	percorrePreOrdemAux(raiz);
}
		
void arvore::percorrePreOrdemAux(noh *raiz){
	if(raiz != NULL){
		cout << raiz->dado << endl;
		percorreEmOrdemAux(raiz->fEsquerda);
		percorreEmOrdemAux(raiz->fDireita);
	}
}
		
void arvore::percorrePosOrdem(){
	percorrePosOrdemAux(raiz);
}
		
void arvore::percorrePosOrdemAux(noh *raiz){
	if(raiz != NULL){
		percorreEmOrdemAux(raiz->fEsquerda);
		percorreEmOrdemAux(raiz->fDireita);
		cout << raiz->dado << endl;
	}
}
		
void arvore::insertRecursivo(const int valor){
	raiz = insertNewNoh(raiz, valor);
}
		
noh* arvore::insertNewNoh(noh *raiz, const int valor){
	if(raiz == NULL){
		noh *novo = new noh(valor);
		return novo;
	}else{
		if(raiz->dado > valor){
			raiz->fEsquerda = insertNewNoh(raiz->fEsquerda, valor);
			raiz->fEsquerda->pai = raiz;
		}else if(raiz->dado < valor){
			raiz->fDireita = insertNewNoh(raiz->fDireita, valor);
			raiz->fDireita->pai = raiz;
		}else if(raiz->dado == valor) cout << "valor ja esta na arvore" << endl;
	}
	return raiz;
}
		
void arvore::transplanta(noh *antigo, noh *novo){
	if(antigo == raiz) raiz = novo;
	else if(antigo == antigo->pai->fDireita){
		antigo->pai->fDireita = novo;
	}else antigo->pai->fEsquerda = novo;
	if(novo != NULL) novo->pai = antigo->pai;
}	
		
void arvore::remove(const int valor){
	noh *removido = buscaNoh(valor);
	
	if(removido == NULL) cout << "nao encontrado" << endl;
	else{
		if(removido->fDireita == NULL) transplanta(removido, removido->fEsquerda);
		else if(removido->fEsquerda == NULL) transplanta(removido, removido->fDireita);
		else{
			noh *sucessor = minimoNoh(removido->fDireita);
			
			if(sucessor->pai != removido){
				transplanta(sucessor, sucessor->fDireita);
				sucessor->fDireita = removido->fDireita;
				sucessor->fDireita->pai = sucessor;
			}
			transplanta(removido, sucessor);
			sucessor->fEsquerda = removido->fEsquerda;
			sucessor->fEsquerda->pai = sucessor;
		}
		
		delete removido;
	}
}
		
void arvore::removeRecursivo(const int valor){
	raiz = removeRecAux(raiz, valor);
}

noh* arvore::removeRecAux(noh *umNoh, const int valor){
	if(umNoh == NULL){
		cout << "nao encontrado" << endl;
		return umNoh;
	}
	noh *novaRaiz = umNoh;
			
	if(umNoh->dado > valor) umNoh->fEsquerda = removeRecAux(umNoh->fEsquerda, valor);
	if(umNoh->dado < valor) umNoh->fDireita = removeRecAux(umNoh->fDireita, valor);
	else if(umNoh->dado == valor){
		if(umNoh->fEsquerda == NULL){
			novaRaiz = umNoh->fDireita;
			transplanta(umNoh, umNoh->fDireita);
		}else if(umNoh->fDireita == NULL){
			novaRaiz = umNoh->fEsquerda;
			transplanta(umNoh, umNoh->fEsquerda);
		}else{
			noh *sucessor = minimoNoh(umNoh->fDireita);
			novaRaiz = sucessor;
			if(sucessor->pai != umNoh){
				transplanta(sucessor, sucessor->fDireita);
				sucessor->fDireita = umNoh->fDireita;
				sucessor->fDireita->pai = sucessor;
			}
			transplanta(umNoh, sucessor);
			sucessor->fEsquerda = umNoh->fEsquerda;
			sucessor->fEsquerda->pai = sucessor;
		}
		delete umNoh;
	}
	return novaRaiz; 
}

int main(){
	arvore Arvore;
	int *vetor;
	
	cout << "Inserindo 15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16, na arvore" << endl;
	vetor = new int[16] {15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16};
	
	for(int c=0; c<16; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Removendo 9, 10, 11, 12, 1, 2, 3, da arvore" << endl;
	vetor = new int[7] {9, 10, 11, 12, 1, 2, 3};
	
	for(int c=0; c<7; c++){
		cout << endl << "Removendo " << vetor[c] << endl;
		Arvore.removeRecursivo(vetor[c]);
	}
	delete[] vetor;
	
	cout << endl << "Inserindo 11, 17, 18, 19, 20, 1, na arvore" << endl;
	vetor = new int[6] {11, 17, 18, 19, 20, 1};
	
	for(int c=0; c<6; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout <<  endl << "Buscando  1, 2, 3, 18, 19, 20, na arvore" << endl;
	vetor = new int[6] { 1, 2, 3, 18, 19, 20};
	
	for(int c=0; c<6; c++){
		cout << endl << "Buscando " << vetor[c] << endl;
		Arvore.busca(vetor[c]);
	}
	delete[] vetor;
	
	return 0;
}
