/*Vetor Expansivel - Estrutura de Dados
 * by Chrystian A. Amaral - 2020
*/
 
#include <iostream>
using namespace std;

class Packet{
    private:
        int* vetor;
        unsigned capacidade;
        Packet* proximoPacket;
        unsigned tamanho;
    public:
        Packet(unsigned cap){
            capacidade = cap;
            vetor = new int[capacidade];
            proximoPacket = NULL;
            tamanho = 0;
        }
        ~Packet(){
            delete[] vetor;
        }
        void ordena(){
            int aux;
            
            for(unsigned c=0; c<tamanho; c++){
                for(unsigned d=c+1; d<tamanho; d++){
                    if(vetor[c] > vetor[d]){
                        aux = vetor[c];
                        vetor[c] = vetor[d];
                        vetor[d] = aux;
                    }
                }
            }
        }
        void insere(int valor){
            if(!cheio()){
                vetor[tamanho++] = valor;
                ordena();
            }
        }
        bool vazio(){ return tamanho == 0; }
        bool cheio(){ return tamanho == capacidade; }
        void remove(int valor){
            unsigned pos = 0;
            
            while(pos < tamanho){
                if(vetor[pos] == valor){
                    tamanho--;
                    ordena();
                }
                pos++;
            }
        }
        int ultimo(){ return vetor[tamanho]; }
        Packet* proximo(){ return proximoPacket; }
        void setProximo(Packet* novo){ proximoPacket = novo; }
        bool busca(int valor){
            unsigned pos = 0;
            
            while(pos < tamanho){
                if(vetor[pos] == valor) return true;
                pos++;
            }
            return false;
        }
        int elementoPos(unsigned pos){ return vetor[pos]; }
        void imprime(){
            for(unsigned c=0; c<tamanho; c++){
                cout << " | " << vetor[c] << " | ";
            }
        }
            
};

class vetorExpansivel{
    private:
        Packet* inicio;
        Packet* fim;
        unsigned quantPacket;
        unsigned tamanhoTotal;
        unsigned capacidadePacket;
    public:
        vetorExpansivel(unsigned cap){
            inicio = fim = NULL;
            quantPacket = 0;
            tamanhoTotal = 0;
            capacidadePacket = cap;
        }
        ~vetorExpansivel(){
            Packet* removido; 
            while(inicio != NULL){
                removido = inicio->proximo();
                if(removido == NULL){
                    delete inicio;
                    inicio = fim = NULL;
                }else{
                    inicio->setProximo(removido->proximo());
                    delete removido;
                }
            }
        }
        void insere(int valor){
            if(inicio == NULL) insereNoInicio(valor);
            else{
                bool verificacao = false;
                Packet* packetPos = buscaPos(valor, &verificacao);
                
                if(verificacao == true) cout << "Valor ja no vetor" << endl;
                else if(packetPos == NULL) insereNoFim(valor);
                else{
                    if(packetPos->cheio()){
                        dividePackets(packetPos, valor);
                        quantPacket++;
                        if(packetPos == fim) fim = fim->proximo();
                    }else packetPos->insere(valor);
                    tamanhoTotal++;
                }
            }
        }
        void insereNoInicio(int valor){
            Packet* newPacket = new Packet(capacidadePacket);
            newPacket->insere(valor);
            quantPacket++;
            inicio = fim = newPacket;
            tamanhoTotal++;
        }
        void insereNoFim(int valor){
            if(fim->cheio() == true){
                dividePackets(fim, valor);
                fim = fim->proximo();
            }else fim->insere(valor);
            tamanhoTotal++;
        }
        Packet* buscaPos(int valor, bool* verificacao){
            Packet* aux = inicio;
            while(aux != NULL and aux->ultimo() < valor) aux = aux->proximo();
            
            if(aux != NULL) *verificacao = aux->busca(valor);
            
            return aux;
        }
        void dividePackets(Packet* packet1, int valor){
            Packet* packet2 = new Packet(capacidadePacket);
            unsigned meio = (capacidadePacket-1)/2;

            packet2->setProximo(packet1->proximo());
            packet1->setProximo(packet2);

            for(unsigned c=meio+1; c<capacidadePacket; c++){
                packet2->insere(packet1->elementoPos(c));
            }
            for(unsigned c=capacidadePacket-1; c>meio; c--){
                packet1->remove(packet1->elementoPos(c));
            }
            
            if(packet1->ultimo() > valor) packet1->insere(valor);
            else packet2->insere(valor);
            quantPacket++;
        }
        void remove(int valor){
            bool verificacao = false;
            Packet* packetPos = buscaPos(valor, &verificacao);
            
            if(verificacao == false) cout << "Valor nao encontrado" << endl;
            else{
                packetPos->remove(valor);
                tamanhoTotal--;
                
                if(packetPos->vazio()) removePacket();
            }
        }
        void removePacket(){
            Packet* aux = inicio;
            Packet* aux2;
            
            while(aux != NULL){
                if(aux->proximo() != NULL){
                    aux2 = aux->proximo();
                    if(aux2->vazio()){ 
                        aux->setProximo(aux2->proximo());
                        delete aux2;
                        quantPacket--;
                    }
                }
                aux = aux->proximo();
            }
        }
        void imprimeVetor(){
            Packet* aux = inicio;
            unsigned cont = 1;
            
            while(aux != NULL){
                cout << endl << "Packet " << cont << " : ";
                aux->imprime();
                cout << endl;
                cont++;
                aux = aux->proximo();
            }
            cout << endl;
        }
        bool busca(int valor){
            Packet* aux = inicio;
            
            while(aux != NULL and aux->ultimo() < valor ) aux = aux->proximo();
            
            if(aux != NULL) return aux->busca(valor);
            else return false;
        }
};

int main(){
    int control;
    
    cout << "Qual o tamanho de cada packet?: ";
    cin >> control;
    vetorExpansivel Vector(control);
    
    cout << "Digite quantos numeros inteiros deseja inserir: ";
    cin >> control;
    cout << "Digite os numeros inteiros: ";
    for(unsigned c=control; c>0; c--){
        cin >> control;
        Vector.insere(control);
    }
    
    Vector.imprimeVetor();
    
    cout << "Digite um numero a ser buscado: ";
    cin >> control;
    if(Vector.busca(control)) cout << "encontrado" << endl;
    else cout << "nao encontrado" << endl;
    
    return 0;
}
