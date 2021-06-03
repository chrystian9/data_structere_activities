#include <iostream>
using namespace std;

class noh{
	friend class arvoreAVL;
	private:
		int dado;
		int tamanho;
		noh* pai;
		noh* direita;
		noh* esquerda;
	public:
		noh(int valor){
			dado = valor;
			tamanho = 1;
			pai = NULL;
			esquerda = NULL;
			direita = NULL;
		}		
};

class arvoreAVL{
	private:
		noh* raiz;
		inline int max(int num1, int num2);
		inline int infoSize(noh* umNoh);
		noh* rotacaoEsquerda(noh* umNoh);
		noh* rotacaoDireita(noh* umNoh);
	public:
		arvoreAVL(){
			raiz = NULL;
		}
		~arvoreAVL(){
			limpaArvore();
		}
		void showRoot();
		void limpaArvore();
		void percorreEmOrdem();
		void percorreEmOrdemAux(noh *umNoh);
		void getTamanho();
		void atualizaSize(noh* umNoh);
		int fatorB(noh* umNoh);
		noh* reajusta(noh* umNoh);
		void insert(const int valor);
		noh* insertAux(noh* umNoh, const int valor);
		noh* minimoAux(noh* umNoh);
		void transfere(noh* antigo, noh* novo);
		void remove(const int valor);
		noh* removeAux(noh* umNoh, const int valor);
		noh* buscaNoh(int valor);
		void busca(int valor);
};

//FUNÇÕES DA CLASSE ARVORE_AVL

inline int arvoreAVL::max(int num1, int num2){
	if(num1 > num2) return num1;
	else return num2;
}
		
inline int arvoreAVL::infoSize(noh* umNoh){
	if(umNoh != NULL) return umNoh->tamanho;
	else return 0;
}

noh* arvoreAVL::rotacaoEsquerda(noh* umNoh){
	noh* auxNoh = umNoh->direita;
	umNoh->direita = auxNoh->esquerda;
	auxNoh->esquerda = umNoh;
	if(umNoh->direita != NULL) umNoh->direita->pai = umNoh;
	auxNoh->pai = umNoh->pai;
			
	if(umNoh == raiz) raiz = auxNoh;
	else if(umNoh == umNoh->pai->esquerda) umNoh->pai->esquerda = auxNoh;
	else umNoh->pai->direita = auxNoh;
	umNoh->pai = auxNoh;
			
	atualizaSize(umNoh);
	atualizaSize(auxNoh);
	
	return auxNoh;
}

noh* arvoreAVL::rotacaoDireita(noh* umNoh){
	noh* auxNoh = umNoh->esquerda;
	umNoh->esquerda = auxNoh->direita;
	auxNoh->direita = umNoh;
	if(umNoh->esquerda != NULL) umNoh->esquerda->pai = umNoh;
	auxNoh->pai = umNoh->pai;
			
	if(umNoh == raiz) raiz = auxNoh;
	else if(umNoh == umNoh->pai->esquerda) umNoh->pai->esquerda = auxNoh;
	else umNoh->pai->direita = auxNoh;		
	umNoh->pai = auxNoh;
			
	atualizaSize(umNoh);
	atualizaSize(auxNoh);
			
	return auxNoh;
}

void arvoreAVL::showRoot(){
	cout << raiz->dado << endl;
}

void arvoreAVL::limpaArvore(){
	while(raiz != NULL) remove(raiz->dado);
	cout << ":)" << endl;
}

void arvoreAVL::percorreEmOrdem(){
	percorreEmOrdemAux(raiz);
}
				
void arvoreAVL::percorreEmOrdemAux(noh *umNoh){
	if(umNoh != NULL){
		percorreEmOrdemAux(umNoh->esquerda);
		cout << umNoh->dado << " ";
		percorreEmOrdemAux(umNoh->direita);
	}
}

void arvoreAVL::getTamanho(){
	cout << infoSize(raiz) << endl;
}
		
void arvoreAVL::atualizaSize(noh* umNoh){
	int altDireita = infoSize(umNoh->direita);
	int altEsquerda = infoSize(umNoh->esquerda);
	umNoh->tamanho = 1 + max(altDireita, altEsquerda);
}
		
int arvoreAVL::fatorB(noh* umNoh){
	int sizeDireita = infoSize(umNoh->direita);
	int sizeEsquerda = infoSize(umNoh->esquerda);
	int fator = sizeEsquerda - sizeDireita;
	return fator;
}
		
noh* arvoreAVL::reajusta(noh* umNoh){
	atualizaSize(umNoh);
	int fB = fatorB(umNoh);
	if(fB >= -1 and fB <= 1) return umNoh;
	
	if((fB > 1) and fatorB(umNoh->esquerda) >= 0) return rotacaoDireita(umNoh);
	else if(fB > 1 and fatorB(umNoh->esquerda) < 0){
		umNoh->esquerda = rotacaoEsquerda(umNoh->esquerda);
		return rotacaoDireita(umNoh);
	}else if(fB < -1 and fatorB(umNoh->direita) <= 0) return rotacaoEsquerda(umNoh);
	else if(fB < -1 and fatorB(umNoh->direita) > 0){
		umNoh->direita = rotacaoDireita(umNoh->direita);
		return rotacaoEsquerda(umNoh);
	}
}
		
void arvoreAVL::insert(const int valor){
	raiz = insertAux(raiz , valor);
}
		
noh* arvoreAVL::insertAux(noh* umNoh, const int valor){
	if(umNoh == NULL){
		noh* novo = new noh(valor);
		return novo;
	}else{
		if(umNoh->dado > valor){
			umNoh->esquerda = insertAux(umNoh->esquerda, valor);
			umNoh->esquerda->pai = umNoh;
		}
		if(umNoh->dado < valor){
			umNoh->direita = insertAux(umNoh->direita, valor);
			umNoh->direita->pai = umNoh;
		}
	}
	return reajusta(umNoh);
}

noh* arvoreAVL::minimoAux(noh* umNoh){
	while(umNoh->esquerda != NULL) umNoh = umNoh->esquerda;
	return umNoh;
}
		
void arvoreAVL::transfere(noh* antigo, noh* novo){
	if(antigo == raiz) raiz = novo;
	else if(antigo == antigo->pai->esquerda) antigo->pai->esquerda = novo;
	else antigo->pai->direita = novo;
	if(novo != NULL) novo->pai = antigo->pai;
}
		
void arvoreAVL::remove(const int valor){
	raiz = removeAux(raiz, valor);
}
		
noh* arvoreAVL::removeAux(noh* umNoh, const int valor){
	if(umNoh == NULL){
		cout << "Valor nao encontrado" << endl;
		return umNoh;
	}else{
		noh* novaRaiz = umNoh;
				
		if(umNoh->dado > valor){
			umNoh->esquerda = removeAux(umNoh->esquerda, valor);
		}else if(umNoh->dado < valor){
			umNoh->direita = removeAux(umNoh->direita, valor);
		}else{
			if(umNoh->direita == NULL){
				novaRaiz = umNoh->esquerda;
				transfere(umNoh, umNoh->esquerda);
			}else if(umNoh->esquerda == NULL){
				novaRaiz = umNoh->direita;
				transfere(umNoh, umNoh->direita);
			}else{
				novaRaiz = minimoAux(umNoh->direita);
						
				if(novaRaiz->pai != umNoh){
					transfere(novaRaiz, novaRaiz->direita);
													
					noh* aux = novaRaiz->pai;
					while(aux != umNoh->direita){
						atualizaSize(aux);
						aux = aux->pai;
					}
					novaRaiz->direita = reajusta(umNoh->direita);
					novaRaiz->direita->pai = novaRaiz;
				}
				transfere(umNoh, novaRaiz);
				novaRaiz->esquerda = umNoh->esquerda;
				novaRaiz->esquerda->pai = novaRaiz;
			}
			delete umNoh;
		}
		if(novaRaiz == NULL) return NULL;
		else return reajusta(novaRaiz);
	}
}

noh* arvoreAVL::buscaNoh(int valor){
	noh *aux = raiz;
	
	while(aux != NULL){
		if(aux->dado > valor) aux = aux->esquerda;
		else if(aux->dado < valor) aux = aux->direita;
		else if(aux->dado == valor) return aux;
	}
	return aux;
}

void arvoreAVL::busca(int valor){
	noh *aux = buscaNoh(valor);
		
	if(aux == NULL) cout << "nao encontrado" << endl;
	else cout << "encontrado" << endl;
}
		
int main(){
	arvoreAVL Arvore;
	int *vetor;
	
	cout << "Inserindo 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, na arvore" << endl;
	vetor = new int[16] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	
	for(int c=0; c<16; c++) Arvore.insert(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout << endl << "Exibindo tamanho: ";
	Arvore.getTamanho();
	cout << endl;
	
	cout << endl << "Removendo 9, 10, 11, 12, 1, 2, 3, da arvore" << endl;
	vetor = new int[7] {9, 10, 11, 12, 1, 2, 3};
	
	for(int c=0; c<7; c++) Arvore.remove(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout << endl << "Inserindo 11, 17, 18, 19, 20, 1, na arvore" << endl;
	vetor = new int[6] {11, 17, 18, 19, 20, 1};
	
	for(int c=0; c<6; c++) Arvore.insert(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout <<  endl << "Buscando  1, 2, 3, 18, 19, 20, na arvore" << endl;
	vetor = new int[6] { 1, 2, 3, 18, 19, 20};
	
	for(int c=0; c<6; c++){
		cout << endl << "Buscando " << vetor[c] << endl;
		Arvore.busca(vetor[c]);
	}
	delete[] vetor;
	
	cout << endl << "--------Limpando Arvore--------" << endl;
	Arvore.limpaArvore();
	
	cout << "Inserindo 15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16, na arvore" << endl;
	vetor = new int[16] {15, 14, 13, 1, 2, 3, 12, 11, 10, 4, 5, 6, 9, 8, 7, 16};
	
	for(int c=0; c<16; c++) Arvore.insert(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout << endl << "Exibindo tamanho: ";
	Arvore.getTamanho();
	cout << endl;
	
	cout << endl << "Removendo 9, 10, 11, 12, 1, 2, 3, da arvore" << endl;
	vetor = new int[7] {9, 10, 11, 12, 1, 2, 3};
	
	for(int c=0; c<7; c++) Arvore.remove(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout << endl << "Inserindo 11, 17, 18, 19, 20, 1, na arvore" << endl;
	vetor = new int[7] {11, 17, 18, 19, 20, 1, 20};
	
	for(int c=0; c<7; c++) Arvore.insert(vetor[c]);
	delete[] vetor;
	
	cout << endl << "Exibindo em ordem: ";
	Arvore.percorreEmOrdem();
	cout << endl;
	
	cout << endl << "Exibindo raiz: ";
	Arvore.showRoot();
	cout << endl;
	
	cout <<  endl << "Buscando  1, 2, 3, 18, 19, 20, na arvore" << endl;
	vetor = new int[6] { 1, 2, 3, 18, 19, 20};
	
	for(int c=0; c<6; c++){
		cout << endl << "Buscando " << vetor[c] << endl;
		Arvore.busca(vetor[c]);
	}
	delete[] vetor;
	
	cout << endl << "--------Limpando Arvore--------" << endl;
	Arvore.limpaArvore();
	
	return 0;
}
