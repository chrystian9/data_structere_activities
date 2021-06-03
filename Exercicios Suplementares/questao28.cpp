/* teste:
5
5 4 3 2 1
5
10 9 8 7 6
0
5
5
2
4
5
*/

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
		lista(const lista& umaLista);
		lista(const int* vet, int tam);
		~lista(){ limpaLista(); }
		
		bool empty(){ return (begin == NULL); } 
		void insertEnd(const int &valor);
		void insertBegin(const int &valor);
		void printInOrder();
		void printOutOrder();
		void insertMiddle(const int valor);
		void retiraNoFim();
		void retiraNoInicio();
		void retiraNaPosicao();
		void limpaLista();
		noh* acessaPosicao();
		noh* acessaPosicao(unsigned pos);
		void trocaPosicao(unsigned pos1, unsigned pos2);
		unsigned busca(int dado);
		lista& operator=(const lista& umaLista);
		lista operator+(const lista& umaLista);
		lista operator-(const lista& umaLista);
};

void lista::insertEnd(const int &valor){
	noh* newNoh = new noh(valor);
	if(empty()) begin = newNoh;
	else{
		end->next = newNoh;
		newNoh->previous = end;
	}
	end = newNoh;
	size++;
}
		
void lista::insertBegin(const int &valor){
	noh* newNoh = new noh(valor);
	if(empty()) end = newNoh;
	else{
		begin->previous = newNoh;
		newNoh->next = begin;
	}
	begin = newNoh;
	size++;
}
		
void lista::printInOrder(){
	noh* aux = begin;
	unsigned cont=1;
	
	while(aux != NULL){
		cout << cont << ": " << aux->getData() << endl;
		aux = aux->next;
		cont++;
	}
}
		
void lista::printOutOrder(){
	noh* aux = end;
	unsigned cont=size;
	while(aux != NULL){
		cout << cont << ": " << aux->getData() << endl;
		aux = aux->previous;
		cont--;
	}
}
		
void lista::insertMiddle(const int valor){
	noh* auxPtr = acessaPosicao();
	noh* newNoh = new noh(valor);
			
	if(auxPtr != NULL){
		newNoh->previous = auxPtr;
		newNoh->next = auxPtr->next;
		auxPtr->next = newNoh;
		size++;
	}else cout << "Posição não encontrada" << endl;
			
}
		
void lista::retiraNoFim(){
	noh* aux;
	
	aux = end;
	if(end == begin) end = begin = NULL;
	else{
		end = end->previous;
		end->next = NULL;
	}
			
	// pode ser feito alguma função com o valor retirado > aux->valor

	delete aux;
	size--;
}
		
void lista::retiraNoInicio(){
	noh* aux;
	
	aux = begin;
	if(begin == end) begin = end = NULL;
	else{
		begin = begin->next;
		begin->previous = NULL;
	}
		
	// pode ser feito alguma função com o valor retirado > aux->valor
	delete aux;			
	size--;
}
		
void lista::retiraNaPosicao(){
	noh *retirado = acessaPosicao(); 
	noh *auxPtr;
	
	if(begin != end){		
		auxPtr = retirado->previous;
		auxPtr->next = retirado->next;
		auxPtr = retirado->next;
		auxPtr->previous = retirado->previous;
		
		size--;
		delete retirado;
	}else retiraNoFim();
}

void lista::limpaLista(){
	while(empty() != true) retiraNoFim();
}
	
noh* lista::acessaPosicao(){
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

noh* lista::acessaPosicao(unsigned pos){
	noh* auxPtr = begin;
	unsigned aux=0;
			
	while(aux != pos-1){
		auxPtr = auxPtr->next;
		aux++;
	}
	
	return auxPtr;
}
		
unsigned lista::busca(int dado){
	noh* auxPtr = begin;
	unsigned aux=0;
			
	while(auxPtr->valor != dado){
		auxPtr = auxPtr->next;
		aux++;
	}
					
	return aux+1;
}

lista::lista(const lista& umaLista){    // construtor de copia
	begin = NULL;
	end = NULL;
	size = 0;
	
	noh* temp = umaLista.begin;
	while(temp != NULL){
		insertBegin(temp->valor);
		temp = temp->next;
	}
}

lista::lista(const int* vet, int tam){
	begin = NULL;
	end = NULL;
	size = 0;
	
	for(int c=0; c<tam; c++) insertBegin(vet[c]);
}	

lista& lista::operator=(const lista& umaLista){
	this->limpaLista();
	
	noh* temp = umaLista.begin;
	while(temp != NULL){
		this->insertBegin(temp->valor);
		temp = temp->next;
	}
	
	return *this;
}

void lista::trocaPosicao(unsigned pos1, unsigned pos2){
	noh* noh1 = acessaPosicao(pos1);
	noh* noh2 = acessaPosicao(pos2);
	noh* next1 = noh1->next;
	noh* previous1 = noh1->previous;
	noh* next2 = noh2->next;
	noh* previous2 = noh2->previous;
	
	if(next1 == noh2){
		noh1->next = noh2->next;
		noh2->next = noh1;
		noh2->previous = noh1->previous;
		noh1->previous = noh2;
	}else if(next2 == noh1){
		noh2->next = noh1->next;
		noh1->next = noh2;
		noh1->previous = noh2->previous;
		noh2->previous = noh1;
	}else{
		next1->previous = noh2;
		previous1->next = noh2;
		
		next2->previous = noh1;
		previous2->next = noh1;
		
		noh1->next = next2;
		noh1->previous = previous2;
		
		noh2->next = next1;
		noh2->previous = previous1;
	}
}

lista lista::operator+(const lista& umaLista){
	lista tempLista;
	noh *aux1 = this->begin;
	noh *aux2 = umaLista.begin;
	
	while(aux1 != NULL){
		tempLista.insertBegin(aux1->valor);
		aux1 = aux1->next;
	}
	while(aux2 != NULL){
		tempLista.insertBegin(aux2->valor);
		aux2 = aux2->next;
	}
	
	return tempLista;
}

lista lista::operator-(const lista& umaLista){
	lista tempLista;
	noh *aux1 = this->begin;
	noh *aux2 = umaLista.begin;
	bool control = false;
	
	while(aux1 != NULL){
		while(aux2 != NULL){
			if(aux2->valor == aux1->valor) control = true;
			aux2 = aux2->next;
		}
		if(!control) tempLista.insertBegin(aux1->valor);
		aux1 = aux1->next;
		aux2 = umaLista.begin;
		control = false;
	}
	
	return tempLista;
}
	
int main(){
	lista list;
	unsigned aux2=0;
	unsigned aux=0;
	
	cout << "Digite a quantidade de elementos (Insercao pelo comeco): ";
	cin >> aux2;
	
	cout << endl << "Digite os elementos: ";

	for(unsigned c=0; c<aux2; c++){
		cin >> aux;
		list.insertBegin(aux);
	}
	
	cout << endl << "Digite a quantidade de elementos (Insercao pelo fim): ";
	cin >> aux2;
	
	cout << endl << "Digite os elementos: ";

	for(unsigned c=0; c<aux2; c++){
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
	if(list.empty()) cout << "Lista vazia" << endl;
	else cout << endl << "elemento na posicao " << list.busca(aux) << endl;
	
	cout << endl << "Criando nova lista com o construtor de copia" << endl;
	
	lista list2(list);
	cout << endl << "Exibindo list2:" << endl;
	cout << "Em ordem" << endl;
	list2.printInOrder();
	cout << endl;
	
	cout << "Limpando list2" << endl; 
	list2.limpaLista();
	
	cout << endl << "Criando nova lista com atribuicao" << endl;
	
	int vet[5] = {0};
	lista list3(vet, 5);
	
	cout << "Exibindo list3 antes da atribuicao:" << endl;
	cout << "Em ordem" << endl;
	list3.printInOrder();
	cout << endl;
	
	list3 = list;
	
	cout << "Exibindo list3 depois da atribuicao:" << endl;
	cout << "Em ordem" << endl;
	list3.printInOrder();
	
	cout << endl << "Trocando posicao na list3" << endl;
	cout << "Qual posicao ira trocar: ";
	cin >> aux;
	cout << "Com qual posicao ira trocar: ";
	cin >> aux2;
	
	list3.trocaPosicao(aux, aux2);
	
	cout << endl << "Exibindo list3:" << endl;
	cout << "Em ordem" << endl;
	list3.printInOrder();
	
	cout << endl << "Concatenando list com list3, na list2" << endl;
	list2 = list + list3;
	
	cout << endl << "Exibindo list2:" << endl;
	cout << "Em ordem" << endl;
	list2.printInOrder();
	
	cout << endl << "list2 = list2 - list3" << endl;
	list2 = list2 - list3;
	
	cout << endl << "Exibindo list2:" << endl;
	cout << "Em ordem" << endl;
	list2.printInOrder();
	
	return 0;
}
