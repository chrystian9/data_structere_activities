/*----MENU----
 * i: seguido de um identificador de fila (a ou b), seguida de um número inteiro, insere a palavra na fila
 * e: seguido de um identificador de fila (a ou b), escreve o conteúdo da fila
 * a=b: copia a fila b para a fila a (note a ausência de espaços no comando)
 * b=a: copia a fila a para a fila b (note a ausência de espaços no comando)
 * s: soma (mescla) a fila a com a fila b numa fila temporária e escreve o seu conteúdo
 * t: termina a execução do programa
 */

#include <iostream>

using namespace std;

class fila;

class noh {
	friend class fila;
	friend ostream& operator<<(ostream&, const fila&);
	private:
		int dado; // poderia ser outro tipo de variável
		noh* prox;
	public:
		noh(){
			dado = 0;
			prox = NULL;
		}
		~noh(){
			prox = NULL;
		}
};

// pilha dinamicamente encadeada
class fila {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;

	public:
		fila();
		fila(const fila& umaFila);
		~fila();
		void insere(int d){ enfileira(d);}
		void enfileira(int d); // insere no final da fila 
		int desenfileira(); // retorna o primeiro elemento da fila
		int espia(); // espia o primeiro elemento da fila
		bool vazia();
		void imprime();
		fila operator+(const fila& umaFila) const;
        fila& operator=(const fila& umaFila);
        friend ostream& operator<<(ostream&, const fila&);
};

fila::fila() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

fila::~fila() { 
    while (primeiro != NULL) {
        desenfileira();
    }
}

void fila::enfileira(int d){
    // primeiro criamos o novo nó
    noh* temp = new noh;
    
    temp->dado = d;
    temp->prox = NULL;
    if (ultimo != NULL) {
        ultimo->prox = temp;
    }
    ultimo = temp;
    if(vazia()) primeiro = temp;    
    tamanho++;
}

int fila::desenfileira(){
    int removido;
    noh* temp;
    
    removido = primeiro->dado;
    temp = primeiro;
    primeiro = primeiro->prox;
    
    if(vazia()){
        ultimo = NULL;
    }
    
    temp->~noh();
    delete temp;
    
    tamanho--;
    return removido;    
}

int fila::espia(){
    return primeiro->dado;
}
    
bool fila::vazia(){
    return (primeiro == NULL);
}

void fila::imprime(){
    noh* temp = primeiro;
    while (temp != NULL) {
	cout << temp->dado << " ";
        temp = temp->prox;
    }
    cout << endl;
}

//mesclar filas
fila fila::operator+(const fila& umaLista) const {
	fila temp;
	noh *aux1 = this->primeiro;
	noh *aux2 = umaLista.primeiro;

	while (temp.tamanho != (this->tamanho + umaLista.tamanho)){
		if(aux1->dado < aux2->dado){
			temp.enfileira(aux1->dado);
			aux1 = aux1->prox;
		}else if(aux1->dado > aux2->dado){
			temp.enfileira(aux2->dado);
			aux2 = aux2->prox;
		}
		if(aux1 == NULL or aux2 == NULL){
			if(aux1 == NULL){
				while(aux2 != NULL){
					temp.enfileira(aux2->dado);
					aux2 = aux2->prox;
				}
			}else{
				while(aux1 != NULL){
					temp.enfileira(aux1->dado);
					aux1 = aux1->prox;
				}
			}
		}
    }
	return temp;
}

// sobrecarga do operador de atribuição
fila& fila::operator=(const fila& umaFila){
    noh* temp;
    while(!this->vazia()){
		temp = primeiro;
		primeiro = primeiro->prox;
		if(vazia()){ ultimo = NULL; }
		temp->~noh();    
		tamanho--;
	}
	
	temp = umaFila.primeiro;
    while (temp != NULL) {
		this->enfileira(temp->dado);
        temp = temp->prox;
    }

    delete temp;
	return *this;
}

// construtor de cópia
fila::fila(const fila& umaFila) {
	this->tamanho = 0;      // garante a iniciação correta do tamanho e dos ponteiros noh
    this->primeiro = NULL;
    this->ultimo = NULL;

	noh* temp = umaFila.primeiro;    // o ponteiro auxilio pega o endereço do topo da fila que vai ser copiada
    while (temp != NULL) {    // enquanto não chega ao fim da fila, realiza a copia de cada dado na nova fila
		this->enfileira(temp->dado);
        temp = temp->prox;
    }
    
    delete temp;
}

ostream& operator<<(ostream& saida, const fila& umaFila){
    noh* temp = umaFila.primeiro;
    while (temp != NULL) {
	cout << temp->dado << " ";
        temp = temp->prox;
    }
	
	delete temp;
	return saida;
}

int main() {
    fila filaA;
    fila filaB;
    string opcao;
    int dado;
    char idFila;
    do {
        cin >> opcao;
        if (opcao == "i") {
            cin >> idFila >> dado;
            if (idFila == 'a')
                filaA.enfileira(dado);
            else
                filaB.enfileira(dado);
        }
		else if (opcao == "a=b") {
            filaA = filaB;
        }
		else if (opcao == "b=a") {
            filaB = filaA;
        }
		else if (opcao == "s") {
            fila filaM = filaA + filaB;
            filaM.imprime();
        }
		else if (opcao == "e") {
            cin >> idFila;
            if (idFila == 'a')
                filaA.imprime();
            else
                filaB.imprime();
        }
    } while (opcao != "t");
    
    cout << "Fila A: " << filaA << endl << "Fila B: " << filaB << endl;
    return 0;
}
