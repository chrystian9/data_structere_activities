#include <iostream>
#include <string>
using namespace std;

typedef int Dado;

class noh{
    private:
        noh* pai;
        noh* fDireita;
        noh* fEsquerda;
        string cor;
        Dado dado;
    public:
        noh(noh* newPai, noh* NIL, Dado valor, string newCor){
            dado = valor;
            cor = newCor;
            fDireita = fEsquerda = NIL;
            pai = newPai;
        }
        noh(){ cor = nil; }
};

class ARN{
    private:
        folha* raiz;
        folha* NIL;
        unsigned size;
        unsigned quantNohs;
    public:
        ARN(){
            NIL = new noh();
            raiz = NULL;
            size = 0;
            quantNohs = 0;
        }
        ~ARN(){ while(raiz != NULL) removerRecAux(raiz); }
        void rotacaoDireita(noh* umNoh){
            noh* auxNoh = umNoh->fEsquerda;
            umNoh->fEsquerda = auxNoh->fDireita;
            auxNoh->fDireita = umNoh;
            if(umNoh->fEsquerda != NULL) umNoh->fEsquerda->pai = umNoh;
            auxNoh->pai = umNoh->pai;
            
            
            
            
    
