#include <iostream>
#include <queue>

typedef int TChave;

class Noh {
    friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
    friend class ArvoreB;
    public:
        // colocar aqui métodos públicos
        void Insere(TChave novaChave, Noh* nohAnterior, Noh* nohPosterior);
        Noh(int grau);
        ~Noh();
    private:
        bool mFolha;
        unsigned mNroChaves;
        TChave* mVetChaves; // até 2M-1 chaves
        Noh** mVetPtFilhos; // até 2M filhos
        Noh* mPai;
};

class ArvoreB {
    public:
        // colocar aqui métodos públicos
        ArvoreB(int grau);
        ~ArvoreB();
        void Inserir(TChave novaChave);
        Noh* BuscaNoNoh(Noh* nohAux, TChave novaChave);
        void DivideNoh(Noh* nohAntigo);
        void EscreverNivelANivel(std::ostream& saida);
    private:
        // colocar aqui métodos privados/auxiliares
        int mGrau;
        Noh* mPtRaiz;
};

using namespace std;

Noh::Noh(int grau){
    mPai = NULL;
    mFolha = true;
    mNroChaves = 0;
    mVetChaves = new TChave[grau*2-1];
    mVetPtFilhos = new Noh*[grau*2];
    for(int c=0; c<grau*2; c++)
        mVetPtFilhos[c] = NULL;
}

Noh::~Noh(){
    for(unsigned c=0; c<mNroChaves; c++){
        delete[] mVetChaves;
        delete mVetPtFilhos[c];
    }
    delete mVetPtFilhos[mNroChaves];
    delete[] mVetPtFilhos;
}

void Noh::Insere(TChave novaChave, Noh* nohAnterior, Noh* nohPosterior){
    unsigned pos = mNroChaves;
    
    for(unsigned c=0; c<mNroChaves; c++){
        if(mVetChaves[c] > novaChave){
            pos = c;
            c = mNroChaves;
        }
    }
    
    for(unsigned d=mNroChaves; d>pos; d--){
        mVetChaves[d] = mVetChaves[d-1];
        mVetPtFilhos[d+1] = mVetPtFilhos[d];
        mVetPtFilhos[d] = mVetPtFilhos[d-1];
    }
    
    mVetChaves[pos] = novaChave;
    mVetPtFilhos[pos] = nohAnterior;
    mVetPtFilhos[pos+1] = nohPosterior;
    mNroChaves++;
}

ArvoreB::ArvoreB(int grau){
    mGrau = grau;
    mPtRaiz = NULL;
}

ArvoreB::~ArvoreB(){
    delete mPtRaiz;
}

Noh* ArvoreB::BuscaNoNoh(Noh* nohAux, TChave novaChave){
    unsigned pos;
    pos = nohAux->mNroChaves;
    for(unsigned c=0; c<nohAux->mNroChaves; c++){
        if(nohAux->mVetChaves[c] > novaChave){
            pos = c;
            c = nohAux->mNroChaves;
        }
    }
    return nohAux->mVetPtFilhos[pos];
}

void ArvoreB::Inserir(TChave novaChave){
    if(mPtRaiz == NULL){
        mPtRaiz = new Noh(mGrau);
        mPtRaiz->Insere(novaChave, NULL, NULL);
    }else{
        if(mPtRaiz->mFolha){
            if(int(mPtRaiz->mNroChaves) == mGrau*2-1){
                DivideNoh(mPtRaiz);
                Inserir(novaChave);
            }else{
                mPtRaiz->Insere(novaChave, NULL, NULL);
            }
        }else{
            Noh* nohAux = mPtRaiz;
            
            while(!nohAux->mFolha){
                if(int(nohAux->mNroChaves) == mGrau*2-1){
                    DivideNoh(nohAux);
                    nohAux = nohAux->mPai;
                    nohAux = BuscaNoNoh(nohAux, novaChave);
                }else{
                    nohAux = BuscaNoNoh(nohAux, novaChave);
                }
            }
            if(int(nohAux->mNroChaves) == mGrau*2-1){
                DivideNoh(nohAux);
                nohAux = nohAux->mPai;
                nohAux = BuscaNoNoh(nohAux, novaChave);
            }
            nohAux->Insere(novaChave, NULL, NULL);
        }
    }
}

void ArvoreB::DivideNoh(Noh* nohAntigo){
    Noh* newNoh = new Noh(mGrau);
    
    for(int c=mGrau; c<(mGrau*2)-1; c++){
        newNoh->Insere(nohAntigo->mVetChaves[c], nohAntigo->mVetPtFilhos[c], nohAntigo->mVetPtFilhos[c+1]);
        nohAntigo->mNroChaves--;
    }
    if(nohAntigo->mFolha == false){
        newNoh->mFolha= false;
        for(unsigned c=0; c<newNoh->mNroChaves; c++){
            newNoh->mVetPtFilhos[c]->mPai = newNoh->mVetPtFilhos[c+1]->mPai = newNoh;
        }
    }
    if(nohAntigo == mPtRaiz){
        Noh* newRaiz = new Noh(mGrau);
        mPtRaiz = newRaiz;
        mPtRaiz->mFolha = false;
        nohAntigo->mPai = mPtRaiz;
    }
    newNoh->mPai = nohAntigo->mPai;
    
    nohAntigo->mPai->Insere(nohAntigo->mVetChaves[nohAntigo->mNroChaves-1], nohAntigo, newNoh);
    nohAntigo->mNroChaves--;
}

ostream& operator<<(ostream& saida, Noh* ptNoh) {
    saida << '[';
    if (ptNoh != NULL) {
        saida << ptNoh->mVetChaves[0];
        for (unsigned i = 1; i < ptNoh->mNroChaves; ++i)
            saida << ',' << ptNoh->mVetChaves[i];
    }
    saida << ']';
    return saida;
}

// Escreve a árvore nível a nível para facilitar a depuração.
void ArvoreB::EscreverNivelANivel(ostream& saida) {
    if (mPtRaiz == NULL)
        saida << "[]\n";
    else {
        queue<Noh*> filhos;
        filhos.push(mPtRaiz);
        while (not filhos.empty()) {
            unsigned nroNohsNesteNivel = unsigned(filhos.size());
            for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
                Noh* ptNoh = filhos.front();
                filhos.pop();
                saida << ptNoh << ' ';
                if (not ptNoh->mFolha)
                    for (unsigned i = 0; i <= ptNoh->mNroChaves; ++i)
                        filhos.push(ptNoh->mVetPtFilhos[i]);
            }
            saida << "\n";
        }
    }
}

int main() {
    int grau;
    cin >> grau;
    ArvoreB arvore(grau);
    char opcao;
    TChave chave;
    do {
        cin >> opcao;
        switch (opcao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.Inserir(chave);
                break;
            case 'e': // Escrever nós nível a nível
                arvore.EscreverNivelANivel(cout);
                break;
            case 'f': // Finalizar o programa
                // vai verificar depois
                break;
            default:
                cerr << "Opção inválida\n";
        }
    } while (opcao != 'f');
    return 0;
}
