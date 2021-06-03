#include <iostream>
using namespace std;

class noh{
	friend class arvore;
	private:
		int dado;
		unsigned profundidade;
		unsigned quant;
		noh* fDireita;
		noh* fEsquerda;
		noh* pai;
	public:
		noh(int valor){
			quant = 0;
			dado = valor;
			profundidade = 0;
			fDireita = NULL;
			fEsquerda = NULL;
			pai = NULL;
		}
};

class arvore{
	private:
		noh* raiz;
		unsigned tamanho;
		
	public:
		arvore();
		~arvore();
		void limpaArvore();
		noh* buscaNoh(int valor);
		void busca(int valor);
		void minimo();
		noh *minimoNoh(noh *aux);
		void maximo();
		noh *maximoNoh(noh *aux);
		void getTamanho();
		void percorreEmOrdem();
		void percorreEmOrdemAux(noh *raiz);
		void percorrePreOrdem();
		void percorrePreOrdemAux(noh *raiz);
		void percorrePosOrdem();
		void percorrePosOrdemAux(noh *raiz);
		void verificaTamanho(noh* raiz);
		void insertRecursivo(const int valor);
		noh* insertNewNoh(noh *raiz, const int valor);
		void transplanta(noh *antigo, noh *novo);
		void remove(const int valor);
		void removeRecursivo(const int valor);
		noh* removeRecAux(noh *umNoh, const int valor);
		void tipoDeArvore();
		string verificaTipoDeArvore(noh* raiz, string tipo);
		void profundidade(noh* umNoh, int pronf);
		void verificaNumNoh();
		unsigned verificaNumNohAux(noh* raiz, unsigned);
		void verificaNumNohFolha();
		unsigned verificaNumNohFolhaAux(noh* raiz, unsigned quant);
		void verificaSomaDosValores();
		unsigned verificaSomaDosValoresAux(noh* raiz, unsigned soma);
};	

arvore::arvore(){
	raiz = NULL;
	tamanho = 0;
}
		
arvore::~arvore(){
	limpaArvore();
}
		
void arvore::limpaArvore(){
	while(raiz != NULL) remove(raiz->dado);
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
		
void arvore::minimo(){
	if(raiz == NULL) cout << "arvore vazia" << endl;
	else{
		noh *nohMinimo = minimoNoh(raiz);
		cout << nohMinimo->dado << endl;
	}
}
		
noh* arvore::minimoNoh(noh *aux){
	while(aux->fEsquerda != NULL) aux = aux->fEsquerda;
	return aux;
}
		
void arvore::maximo(){
	if(raiz == NULL) cout << "arvore vazia" << endl;
	else{
		noh* nohMaximo = maximoNoh(raiz);
		cout << nohMaximo->dado << endl;
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
		for(unsigned c=0; c<raiz->quant; c++) cout << raiz->dado << " ";
		percorreEmOrdemAux(raiz->fDireita);
	}
}
		
void arvore::percorrePreOrdem(){
	percorrePreOrdemAux(raiz);
}
		
void arvore::percorrePreOrdemAux(noh *raiz){
	if(raiz != NULL){
		for(unsigned c=0; c<raiz->quant; c++) cout << raiz->dado << " ";
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
		for(unsigned c=0; c<raiz->quant; c++) cout << raiz->dado << " ";
	}
}

void arvore::getTamanho(){
	cout << tamanho << endl;
}

void arvore::verificaTamanho(noh* raiz){
	if(raiz != NULL){
		verificaTamanho(raiz->fEsquerda);
		if(raiz->profundidade >= tamanho) tamanho = raiz->profundidade + 1;
		verificaTamanho(raiz->fDireita);
	}
}
		
void arvore::insertRecursivo(const int valor){
	raiz = insertNewNoh(raiz, valor);
	verificaTamanho(raiz);
}
		
noh* arvore::insertNewNoh(noh *raiz, const int valor){
	if(raiz == NULL){
		noh *novo = new noh(valor);
		novo->quant++;
		return novo;
	}else{
		if(raiz->dado > valor){
			raiz->fEsquerda = insertNewNoh(raiz->fEsquerda, valor);
			raiz->fEsquerda->pai = raiz;
			raiz->fEsquerda->profundidade = raiz->profundidade + 1;
		}else if(raiz->dado < valor){
			raiz->fDireita = insertNewNoh(raiz->fDireita, valor);
			raiz->fDireita->pai = raiz;
			raiz->fDireita->profundidade = raiz->profundidade + 1;
		}else if(raiz->dado == valor) raiz->quant++;
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

void arvore::profundidade(noh* umNoh, int pronf){
	if(umNoh->fEsquerda != NULL){
		profundidade(umNoh->fEsquerda, pronf+1);
	}
	if(umNoh->fDireita != NULL){
		profundidade(umNoh->fDireita, pronf+1);
	}
	umNoh->profundidade = pronf;
}

void arvore::remove(const int valor){
	noh *removido = buscaNoh(valor);
	
	if(removido == NULL) cout << "nao encontrado" << endl;
	
	removido->quant--;
	if(removido->quant == 0){
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
	profundidade(raiz, 0);
	verificaTamanho(raiz);
}

void arvore::removeRecursivo(const int valor){
	raiz = removeRecAux(raiz, valor);
	profundidade(raiz, 0);
	verificaTamanho(raiz);
}

noh* arvore::removeRecAux(noh *umNoh, const int valor){
	if(umNoh == NULL){
		cout << "nao encontrado" << endl;
		return umNoh;
	}
	noh *novaRaiz = umNoh;
			
	if(umNoh->dado > valor) umNoh->fEsquerda = removeRecAux(umNoh->fEsquerda, valor);
	else if(umNoh->dado < valor) umNoh->fDireita = removeRecAux(umNoh->fDireita, valor);
	else{
		umNoh->quant--;
		if(umNoh->quant == 0){	
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
	}
	return novaRaiz; 
}

void arvore::tipoDeArvore(){
	cout << verificaTipoDeArvore(raiz, "Arvore Binaria Cheia") << endl;
}

string arvore::verificaTipoDeArvore(noh* raiz, string tipo){
	if(raiz != NULL and tipo != "Arvore Estritamente Binaria"){
		tipo = verificaTipoDeArvore(raiz->fEsquerda, tipo);
		if(raiz->fEsquerda == NULL or raiz->fDireita == NULL){
			if(raiz->profundidade == tamanho - 2) tipo = "Arvore Binaria Completa";
			else if(raiz->profundidade == tamanho - 1 and tipo != "Arvore Binaria Completa") tipo = "Arvore Binaria Cheia";
			else tipo = "Arvore Estritamente Binaria";
			
		}else tipo = "Arvore Binaria Cheia";
		tipo = verificaTipoDeArvore(raiz->fDireita, tipo);
	}
	return tipo;
}

void arvore::verificaNumNoh(){
	cout << verificaNumNohAux(raiz, 0) << endl;
}

unsigned arvore::verificaNumNohAux(noh* raiz, unsigned quant){
	if(raiz != NULL){
		quant = verificaNumNohAux(raiz->fEsquerda, quant);
		quant++;
		quant = verificaNumNohAux(raiz->fEsquerda, quant);
	}
	return quant;
}

void arvore::verificaNumNohFolha(){
	cout << verificaNumNohFolhaAux(raiz, 0) << endl;
}

unsigned arvore::verificaNumNohFolhaAux(noh* raiz, unsigned quant){
	if(raiz != NULL){
		quant = verificaNumNohFolhaAux(raiz->fEsquerda, quant);
		if(raiz->fEsquerda == NULL and raiz->fDireita == NULL) quant++;
		quant = verificaNumNohFolhaAux(raiz->fDireita, quant);
	}
	return quant;
}

void arvore::verificaSomaDosValores(){
	cout << verificaSomaDosValoresAux(raiz, 0) << endl;
}

unsigned arvore::verificaSomaDosValoresAux(noh* raiz, unsigned soma){
	if(raiz != NULL){
		soma = verificaSomaDosValoresAux(raiz->fEsquerda, soma);
		soma += raiz->dado;
		soma = verificaSomaDosValoresAux(raiz->fDireita, soma);
	}
	return soma;
}

int main(){
	arvore Arvore;
	int *vetor;
	
	cout << "Inserindo 4, 2, 3, 1, 6, 5, 7, na arvore" << endl;
	vetor = new int[7] {4, 2, 3, 1, 6, 5, 7};
	
	for(int c=0; c<7; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pre ordem: ";
	Arvore.percorrePreOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pos ordem: ";
	Arvore.percorrePosOrdem();
	cout << endl;
	
	cout << endl << "Exibindo minimo: ";
	Arvore.minimo();
	cout << endl;
	
	cout << endl << "Exibindo maximo: ";
	Arvore.maximo();
	cout << endl;
	
	cout << endl << "Exibindo tamanho: ";
	Arvore.getTamanho();
	cout << endl;
	
	cout << endl << "Exibindo tipo: ";
	Arvore.tipoDeArvore();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh: ";
	Arvore.verificaNumNoh();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh folha: ";
	Arvore.verificaNumNohFolha();
	cout << endl;
	
	cout << endl << "Exibindo soma dos valores: ";
	Arvore.verificaSomaDosValores();
	cout << endl;
	
	cout << endl << "--------Limpando Arvore--------" << endl;
	Arvore.limpaArvore();
	
	cout << "Inserindo 5, 2, 3, 1, 4, 7, 6, 8, 7, na arvore" << endl;
	vetor = new int[9] {5, 2, 3, 1, 4, 7, 6, 8, 7};
	
	for(int c=0; c<9; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pre ordem: ";
	Arvore.percorrePreOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pos ordem: ";
	Arvore.percorrePosOrdem();
	cout << endl;
	
	cout << endl << "Exibindo minimo: ";
	Arvore.minimo();
	cout << endl;
	
	cout << endl << "Exibindo maximo: ";
	Arvore.maximo();
	cout << endl;
	
	cout << endl << "Exibindo tamanho: ";
	Arvore.getTamanho();
	cout << endl;
	
	cout << endl << "Exibindo tipo: ";
	Arvore.tipoDeArvore();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh: ";
	Arvore.verificaNumNoh();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh folha: ";
	Arvore.verificaNumNohFolha();
	cout << endl;
	
	cout << endl << "Exibindo soma dos valores: ";
	Arvore.verificaSomaDosValores();
	cout << endl;
	
	cout << endl << "--------Limpando Arvore--------" << endl;
	Arvore.limpaArvore();
	
	cout << endl << "Inserindo 15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16, na arvore" << endl;
	vetor = new int[16] {15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16};
	
	for(int c=0; c<16; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pre ordem: ";
	Arvore.percorrePreOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pos ordem: ";
	Arvore.percorrePosOrdem();
	cout << endl;
	
	cout << endl << "Exibindo minimo: ";
	Arvore.minimo();
	cout << endl;
	
	cout << endl << "Exibindo maximo: ";
	Arvore.maximo();
	cout << endl;
	
	cout << endl << "Exibindo tamanho: ";
	Arvore.getTamanho();
	cout << endl;
	
	cout << endl << "Exibindo tipo: ";
	Arvore.tipoDeArvore();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh: ";
	Arvore.verificaNumNoh();
	cout << endl;	
	
	cout << endl << "Exibindo numero de noh folha: ";
	Arvore.verificaNumNohFolha();
	cout << endl;
	
	cout << endl << "Exibindo soma dos valores: ";
	Arvore.verificaSomaDosValores();
	cout << endl;
	
	cout << endl << "Removendo 9, 10, 11, 12, 1, 2, 3, da arvore" << endl;
	vetor = new int[7] {9, 10, 11, 12, 1, 2, 3};
	
	for(int c=0; c<7; c++) Arvore.removeRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pre ordem: ";
	Arvore.percorrePreOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pos ordem: ";
	Arvore.percorrePosOrdem();
	cout << endl;
	
	cout << endl << "Exibindo minimo: ";
	Arvore.minimo();
	cout << endl;
	
	cout << endl << "Exibindo maximo: ";
	Arvore.maximo();
	cout << endl;
	
	cout << endl << "Inserindo 11, 17, 18, 19, 20, 1, na arvore" << endl;
	vetor = new int[7] {11, 17, 18, 19, 20, 1, 20};
	
	for(int c=0; c<7; c++) Arvore.insertRecursivo(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pre ordem: ";
	Arvore.percorrePreOrdem();
	cout << endl;
	
	cout << endl << "Exibindo pos ordem: ";
	Arvore.percorrePosOrdem();
	cout << endl;
	
	cout << endl << "Exibindo minimo: ";
	Arvore.minimo();
	cout << endl;
	
	cout << endl << "Exibindo maximo: ";
	Arvore.maximo();
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
