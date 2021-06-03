/* teste:
5
5 4 3 2 1
5
1 2 3 4 5
0
5
5
2
*/
/* teste:
5
5 4 3 2 1
5
1 2 3 4 5
0
5
5
2
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
		void insert(const int &valor);
		void printInOrder();
		void printOutOrder();
		void retiraNoFim();
		void retiraNoInicio();
		void retiraNaPosicao();
		void limpaLista();
		noh* acessaPosicao();
		noh* acessaPosicao(unsigned pos);
		void trocaPosicao(unsigned pos1, unsigned pos2);
		unsigned busca(int dado);
		lista& operator=(const lista& umaLista);
};

void lista::insert(const int &valor){
	noh* newNoh = new noh(valor);
	noh* auxPtr = begin;
	
	if(empty()) begin = newNoh;
	else{
		while(newNoh->valor > auxPtr->valor) auxPtr = auxPtr->next;
		if(auxPtr != NULL){
			newNoh->next = auxPtr;
			newNoh->previous = auxPtr->previous;
			auxPtr->previous = newNoh;
		}else{
			newNoh->next = auxPtr;
			newNoh->previous = end->previous;
			end = newNoh;
		}
		if(auxPtr == begin) begin = newNoh;
	}
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
	return buscaBinaria(dado, begin, end);
}

unsigned buscaBinaria(const int& dado, const unsigned& inicio, const unsigned& fim){
	unsigned* begin = &inicio;
	unsigned* end = &fim;
	unsigned* meio;
	unsigned aux=0;
	
	while
	
	
	
	
}	

lista::lista(const lista& umaLista){    // construtor de copia
	begin = NULL;
	end = NULL;
	size = 0;
	
	noh* temp = umaLista.begin;
	while(temp != NULL){
		insert(temp->valor);
		temp = temp->next;
	}
}

lista::lista(const int* vet, int tam){
	begin = NULL;
	end = NULL;
	size = 0;
	
	for(int c=0; c<tam; c++) insert(vet[c]);
}	

lista& lista::operator=(const lista& umaLista){
	this->limpaLista();
	
	noh* temp = umaLista.begin;
	while(temp != NULL){
		this->insert(temp->valor);
		temp = temp->next;
	}
	
	return *this;
}

int main(){
	lista list;
	unsigned aux2=0;
	unsigned aux=0;
	
	cout << "Digite a quantidade de elementos: ";
	cin >> aux2;
	
	cout << endl << "Digite os elementos: ";

	for(unsigned c=0; c<aux2; c++){
		cin >> aux;
		list.insert(aux);
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
	
	
	return 0;
}
