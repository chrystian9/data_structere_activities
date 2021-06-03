/* MENU:
 * t - para terminar a execução do programa
 * e - para enfileirar um valor - seguido do valor (número inteiro)
 * d - para desenfileirar um valor
 * p - para escrever o próximo valor na fila (sem desenfileirar)
 * i - para escrever as informações da fila (atributos e conteúdo)
*/

#include <iostream>

typedef int Dado;

class Fila {
    public:
        Fila(unsigned cap = 80);
        ~Fila();
        Dado Desenfileira();
        bool Enfileirar(const Dado& valor);
        void EscreverConteudo(std::ostream& saida) const;
        void Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const;
        Dado Proximo() const;
        unsigned Tamanho() const { return mTamanho; }
        bool Vazia() const;
    protected:
        unsigned mCapacidade;
        Dado* mDados;
        unsigned mPosInicio; // indica a posicao do primeiro
        unsigned mPosFim;    // indica a posicao do ultimo
        unsigned mTamanho;
};

using namespace std;

Fila::Fila(unsigned cap) {
	mDados = new Dado[cap] {0};
	mPosInicio = cap+2;
	mPosFim = cap-1;
	mTamanho = 0;
	mCapacidade = cap;
}

Fila::~Fila() {
	delete mDados;
}

Dado Fila::Desenfileira() {
	unsigned aux = 0;
	if(mTamanho == 0) return false;
	
	aux = mDados[mPosInicio];
	if(mPosInicio == mPosFim){
		mPosInicio = mCapacidade+2;
		mPosFim = mCapacidade-1;
	}else mPosInicio = (mPosInicio+1) % mCapacidade;
	mTamanho--;
	
	return aux;
}

bool Fila::Enfileirar(const Dado& valor) {
	if(mTamanho == mCapacidade) return false;

	if(mPosInicio == mCapacidade+2) mPosInicio = 0;
	
	mPosFim = (mPosFim+1) % mCapacidade;
	mDados[mPosFim] = valor;
	mTamanho++;
		
	return true;
}

void Fila::EscreverConteudo(ostream& saida) const {
	for(unsigned c=0; c<mCapacidade; c++) saida << mDados[c] << " ";
	saida << endl; 
}

void Fila::Info(unsigned* ptTam, unsigned* ptCap, unsigned* ptIni, unsigned* ptFim) const {
	*ptTam = mTamanho;
	*ptCap = mCapacidade;
	if(mTamanho == 0){
		*ptIni = 0;
		*ptFim = 0;
	}else{
		*ptIni = mPosInicio;
		*ptFim = mPosFim;
	}	
}

Dado Fila::Proximo() const {
	return mDados[mPosInicio];
}

bool Fila::Vazia() const {
	return (mTamanho == 0);
}

int main() {
    unsigned tamanho, capacidade, inicio, fim;
    cin >> capacidade;
    
    Fila fila(capacidade);
    Dado valor;
    char comando;
    cin >> comando;
    
    while (comando != 't') {
        switch (comando) {
        case 'e': // enfileirar
            cin >> valor;
            if (not fila.Enfileirar(valor))
                cout << "FILA CHEIA!\n";
            break;
        case 'd': // desenfileirar
            if (fila.Vazia())
                cout << "ERRO\n";
            else {
                valor = fila.Desenfileira();
                cout << valor << endl;
            }
            break;
        case 'p': // proximo
            if (fila.Vazia())
                cout << "ERRO\n";
            else
                cout << fila.Proximo() << endl;
            break;
        case 'i': 
            fila.Info(&tamanho, &capacidade, &inicio, &fim);
            cout << "tamanho=" << tamanho << " capacidade=" << capacidade << " inicio=" << inicio
                 << " fim=" << fim << endl;
            fila.EscreverConteudo(cout);
            break;
        case 't':
            // vai testar novamente no while
            break;
        default:
            cout << "comando invÃ¡lido\n";
        }
        cin >> comando;
    }
    return 0;
}
