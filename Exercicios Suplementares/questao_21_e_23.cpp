#include <iostream>
using namespace std;

class noh{
	friend class lista;
	private:
		int valor;
		noh* previous;
		noh* next;
	public:
		noh(const int &newValor){
			valor = newValor;
			previous = NULL;
			next = NULL;
		}
		int getData(){ return valor; }
};

class lista{
	private:
		noh* begin;
		noh* end;
		unsigned size;
	public:
		lista(){
			begin = NULL;
			end = NULL;
			size = 0;
		}
		~lista(){
			while(empty()) retiraNoFim();
		}
		bool empty(){ return begin == NULL; } 
		void insertEnd(const int &valor){
			noh* newNoh = new noh(valor);
			if(empty()) begin = newNoh;
			else{
				end->next = newNoh;
				newNoh->previous = end;
			}
			end = newNoh;
			size++;
		}
		void insertBegin(const int &valor){
			noh* newNoh = new noh(valor);
			if(empty()) end = newNoh;
			else{
				begin->previous = newNoh;
				newNoh->next = begin;
			}
			begin = newNoh;
			size++;
		}
		void printInOrder(){
			noh* aux = begin;
			unsigned cont=1;
			while(aux != NULL){
				cout << cont << ": " << aux->getData() << endl;
				aux = aux->next;
				cont++;
			}
		}
		void printOutOrder(){
			noh* aux = end;
			unsigned cont=size;
			while(aux != NULL){
				cout << cont << ": " << aux->getData() << endl;
				aux = aux->previous;
				cont--;
			}
		}
		void insertMiddle(const int valor){
			noh* auxPtr = acessaPosicao();
			noh* newNoh = new noh(valor);
			
			if(auxPtr != NULL){
				newNoh->previous = auxPtr;
				newNoh->next = auxPtr->next;
				auxPtr->next = newNoh;
				size++;
			}else cout << "Posição não encontrada" << endl;
			
		}
		void retiraNoFim(){
			noh* aux;
			
			if(end == begin) begin = NULL;
			
			aux = end;
			end = aux->previous;
			end->next = NULL;
			
			// pode ser feito alguma função com o valor retirado > aux->valor
			
			delete aux;
			
			size--;
		}
		void retiraNoInicio(){
			noh* aux;
			
			if(end == begin) end = NULL;
			
			aux = begin;
			begin = aux->next;
			begin->previous = NULL;
			
			// pode ser feito alguma função com o valor retirado > aux->valor
			
			delete aux;
			
			size--;
		}
		void retiraNaPosicao(){
			noh *retirado = acessaPosicao(); 
			noh *auxPtr;
			
			auxPtr = retirado->previous;
			auxPtr->next = retirado->next;
			auxPtr = retirado->next;
			auxPtr->previous = retirado->previous;
			size--;
			
			delete retirado;
		}
		noh* acessaPosicao(){
			noh* auxPtr = begin;
			unsigned aux=0, pos=0;
			cout << "Digite a posicao desejada: ";
			cin >> pos;
			
			while(aux != pos-1){
				auxPtr = auxPtr->next;
				aux++;
			}
		
			return auxPtr;
		}
		unsigned busca(int dado){
			noh* auxPtr = begin;
			unsigned aux=0;
			
			while(auxPtr->valor != dado){
				auxPtr = auxPtr->next;
				aux++;
			}
			
			return aux+1;
		}
};
		
int main(){
	lista list;
	unsigned quant=0;
	unsigned aux=0;
	
	cout << "Digite a quantidade de elementos (Insercao pelo comeco): ";
	cin >> quant;
	
	cout << endl << "Digite os elementos: ";

	for(unsigned c=0; c<quant; c++){
		cin >> aux;
		list.insertBegin(aux);
	}
	
	cout << endl << "Digite a quantidade de elementos (Insercao pelo fim): ";
	cin >> quant;
	
	cout << endl << "Digite os elementos: ";

	for(unsigned c=0; c<quant; c++){
		cin >> aux;
		list.insertBegin(aux);
	}
	
	cout << endl << "Exibindo a lista" << endl;
	
	cout << "Em ordem" << endl;;
	list.printInOrder();
	cout << endl;
	cout << "Em ordem contraria" << endl;
	list.printOutOrder();
	cout << endl;
	
	cout << "Digite um valor para inserir no meio: ";
	cin >> aux;
	
	list.insertMiddle(aux);
	
	cout << endl << "Exibindo a lista" << endl;
	
	cout << "Em ordem" << endl;
	list.printInOrder();
	cout << endl;
	
	cout << "Retirando no fim" << endl;
	list.retiraNoFim();
	
	cout << "Em ordem" << endl;
	list.printInOrder();
	cout << endl;
	
	cout << "Retirando no inicio" << endl;
	list.retiraNoInicio();
	
	cout << "Em ordem" << endl;
	list.printInOrder();
	cout << endl;
	
	cout << "Retirando em posicao" << endl;
	list.retiraNaPosicao();
	
	cout << "Em ordem" << endl;
	list.printInOrder();
	cout << endl;
	
	cout << "Busca elemento" << endl << "Digite o elemento: ";
	cin >> aux;
	cout << endl << "elemento na posicao " << list.busca(aux) << endl;
	
	return 0;
}
