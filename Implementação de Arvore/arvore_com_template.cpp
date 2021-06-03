#include <iostream>
using namespace std;

template<typename Dado>class Arvore;

template<typename Dado>
class noh{
	friend class Arvore<Dado>;
	private:
		Dado valor;
		noh<Dado> **filhos;
	public:
		noh(const Dado &valorNovo){
			valor = valorNovo;
			filhos = new noh*[2];
			filhos[0] = NULL;
			filhos[1] = NULL;
		}
		~noh(){ delete[] filhos;}
};

template<typename Dado>
class Arvore{
	private:
		noh<Dado> *raiz;
		unsigned profundidade;
		void insert(noh<Dado> **ptr, const Dado &valor, unsigned *prof);
		void preOrdem(noh<Dado> *ptr);
		void naOrdem(noh<Dado> *ptr);
		void posOrdem(noh<Dado> *ptr);
		bool buscaValor(noh<Dado> *ptr, Dado valor, int caminho[], int &c);
	public:
		Arvore(){
			raiz = NULL;
			profundidade = 0;
		}
		~Arvore(){
			delete raiz;
		}
		void insere(const Dado &valor);
		void imprime();
		void buscar(const Dado &valor);
};

template<typename Dado>
void Arvore<Dado>::insert(noh<Dado> **ptr, const Dado &valor, unsigned *prof){    //o ponteiro tem o endereço do noh raiz da sub-arvores
	if(*ptr == NULL){    // Quando encontrado uma folha, ou a raiz da arvore, com valor NULL, dizendo que ali podera ser alocado um novo noh
		*ptr = new noh<Dado>(valor);
	}else{
		if(valor < (*ptr)->valor){    // Quando o valor for menor do que o valor da raiz, ele vai para esquerda da sub-arvore
			*prof = *prof +1;
			insert(&((*ptr)->filhos[0]), valor, prof);
		}else if (valor > (*ptr)->valor){    // Quando o valor for menor do que o valor da raiz, ele vai para direita da sub-arvore
			*prof = *prof +1;
			insert(&((*ptr)->filhos[1]), valor, prof);
		}else cout << "valor repetido" << endl;
	}
}

template<typename Dado>
void Arvore<Dado>::preOrdem(noh<Dado> *ptr){
	if(ptr != NULL){
		cout << ptr->valor << " ";
		preOrdem(ptr->filhos[0]); 
		preOrdem(ptr->filhos[1]);
	}
}

template<typename Dado>
void Arvore<Dado>::naOrdem(noh<Dado> *ptr){
	if(ptr != NULL){
		preOrdem(ptr->filhos[0]);
		cout << ptr->valor << " ";
		preOrdem(ptr->filhos[1]);
	}
}

template<typename Dado>
void Arvore<Dado>::posOrdem(noh<Dado> *ptr){
	if(ptr != NULL){
		preOrdem(ptr->filhos[0]); 
		preOrdem(ptr->filhos[1]);
		cout << ptr->valor << " ";
	}
}

template<typename Dado>
bool Arvore<Dado>::buscaValor(noh<Dado> *ptr, Dado valor, int caminho[], int &c){
	bool result;
	caminho[c++] = ptr->valor;
	if(ptr == NULL){
		cout << "Valor não encontrado" << endl;
		result = false;
	}else{
		if(valor < ptr->valor) result = buscaValor(ptr->filhos[0], valor, caminho, c);
		else if(valor > ptr->valor) result = buscaValor(ptr->filhos[1], valor, caminho, c);
		else{
			cout << "Valor encontrado" << endl;
			result = true;
		}
	}
	return result;
}

template<typename Dado>
void Arvore<Dado>::insere(const Dado &valor){
	unsigned *prof = new unsigned;
	*prof = 0;
	insert(&raiz, valor, prof);
	if(*prof > profundidade) profundidade = *prof;
	delete prof;
}

template<typename Dado>
void Arvore<Dado>::imprime(){
	cout << "Em pre ordem: ";
	preOrdem(raiz);
	cout << "Em ordem: ";
	naOrdem(raiz);
	cout << "Em pos ordem: ";
	posOrdem(raiz);
	cout << endl;
}

template<typename Dado>
void Arvore<Dado>::buscar(const Dado &valor){
	int c=0;
	int *caminho = new int[profundidade];
	if(buscaValor(raiz, valor, caminho, c)){
		cout << "Caminho:";
		for(int i=0; i<c; i++) cout << " -> " << caminho[i];
		cout << endl;
	}
	delete[] caminho;
}



int main (){
	// Arvore com Ints
	Arvore<int> tree;
	int quant=0, aux=0;
	
	cout << "Digite o numero de elementos do tipo inteiro, na arvore: ";
	cin >> quant;
	cout << endl << "Digite os elementos do tipo inteiro: ";
	for(int c=0; c<quant; c++){
		cin >> aux;
		tree.insere(aux);
	}
	
	cout << endl << "Exibindo os dados" << endl << endl;
	tree.imprime();
	
	cout << endl << "Digite um valor a ser buscado: ";
	cin >> aux;
	tree.buscar(aux);
	
	tree.~Arvore();
	cout << endl << "Criando outra arvore" << endl << endl;
	
	//Arvore com floats
	Arvore<float> tree2;
	float quant2=0;
	float aux2=0;
	
	cout << "Digite o numero de elementos do tipo flutuante, na arvore: ";
	cin >> quant;
	cout << endl << "Digite os elementos do tipo flutuante: ";
	for(int c=0; c<quant2; c++){
		cin >> aux2;
		tree2.insere(aux2);
	}
	
	cout << endl << "Exibindo os dados" << endl << endl;
	tree2.imprime();
	
	cout << endl << "Digite um valor a ser buscado: ";
	cin >> aux2;
	tree2.buscar(aux);
	
	return 0;
	
}
