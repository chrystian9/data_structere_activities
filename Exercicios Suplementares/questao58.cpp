#include <iostream>
using namespace std;

class noh{
	friend class arvore;
	private:
		unsigned dado;
		noh* direita;
		noh* esquerda;
		noh* pai;
		unsigned tamanho;
	public:
		noh(unsigned valor){
			dado = valor;
			tamanho = 0;
			direita = NULL;
			esquerda = NULL;
			pai = NULL;
		}
}

class arvore{
	private:
		noh* raiz;
	public:
		arvore(){
			raiz = NULL;
		}
		~arvore(){
			limpaArvore();
		}
		void limpaArvore(){
			while(raiz != NULL)	removeRecursivo(raiz->dado);
		}
		void insertRecursivo(const unsigned valor);
		noh* insertRecursivoAux(noh* raiz, const unsigned valor);
		noh* minimoAux(noh* umNoh);
		void transplanta(noh* antigo, noh* novo);
		void removeRecursivo(const unsigned valor);
		noh* removeRecursivoAux(noh* umNoh, const unsigned valor);
};
	
noh* arvore::minimoAux(noh* umNoh){
	while(umNoh->direita != NULL) umNoh = umNoh->direita;
	return umNoh;
}	
	
void arvore::insertRecursivo(const unsigned valor){
	raiz = insertRecursivoAux(raiz, valor);
	atualizaTamanho(raiz);
}

noh* arvore::insertRecursivoAux(noh* raiz, const unsigned valor){
	if(raiz == NULL){
		noh* novo = new noh(valor);
		return novo;
	}else{
		if(raiz->dado > valor){
			raiz->esquerda = insertRecursivoAux(raiz->esquerda, valor);
			raiz->esquerda->pai = raiz;
			raiz->esquerda->tamanho = raiz->tamanho;
			raiz->tamanho++;
		}else if(raiz->dado < valor){
			raiz->direita = insertRecursivoAux(raiz->direita, valor);
			raiz->direita->pai = raiz;
			raiz->direita->tamanho = raiz->tamanho;
			raiz->tamanho++;
		}
		return raiz;
	}
}

void arvore::transplanta(noh* antigo, noh* novo){
	if(raiz == antigo){
		raiz = novo;
	}else{
		if(antigo->pai->esquerdo == antigo) antigo->pai->esquerdo = novo;
		else antigo->pai->direito = novo;
	}
	if(novo != NULL) novo->pai = antigo->pai;
}

void arvore::removeRecursivo(const unsigned valor){
	raiz = removerRecursivoAux(raiz, valor);
	atualizaTamanho(raiz);
}

noh* arvore::removeRecursivoAux(noh* umNoh, const unsigned valor){
	if(umNoh == NULL){
		cout << "Nao encontrado" << endl;
		return umNoh;
	}else{
		noh* novaRaiz = umNoh;
		
		if(umNoh->dado > valor) umNoh->esquerda = removeRecursivoAux(umNoh->esquerda, valor);
		else if(umNoh->dado < valor) umNoh->direita = removeRecursivoAux(umNoh->direita, valor);
		else{
			if(umNoh->direita == NULL){
				novaRaiz = umNoh->esquerda;
				transplanta(umNoh, umNoh->esquerda);
			}else if(umNoh->esquerda == NULL){
				novaRaiz = umNoh->direita;
				transplanta(umNoh, umNoh->direita);
			}else{
				noh* sucessor = minimoAux(umNoh->direita);
				novaRaiz = sucessor;
				
				if(sucessor->pai != umNoh){
					transplanta(sucessor, sucessor->direita);
					sucessor->direita = umNoh->direita;
					sucessor->direita->pai = sucessor;
				}
				transplanta(umNoh, sucessor);
				sucessor->esquerda = umNoh->esquerda;
				sucessor->esquerda->pai = sucessor;
				
				delete umNoh;
			}
		}
		return novaRaiz;
	}		
}
	
	
	
			
			
			
	
	
	
	
	
	
	
	
	
