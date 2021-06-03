#include <iostream>
using namespace std;

void menu(){
	cout << "1. Inserir novo registro" << endl;
	cout << "2. Remover registro" << endl;
	cout << "3. Exibir Hash de registros" << endl;
	cout << "4. Exibir registro" << endl;
	cout << "0. Terminar" << endl;	
}

class Hash{
	private:
		struct registro{
			int id;
			string nome;
			string setor;
			string funcao;
		};
		unsigned size;
		registro **tabela;
	
	public:
		Hash(int tam);
		~Hash();
		int key(int id);
		int busca(int i, int id);
		void confStruct(int i, int id);
		void insert(int id);
		void remove(int id);
		void exibe();
		void exibeRegistro(int id);
};

//funções da Hash

Hash::Hash(int tam){
	size = (unsigned)tam;
	tabela = new registro*[tam] {NULL};
}
	
Hash::~Hash(){
	for(unsigned c=0; c<size; c++) delete tabela[c];
}
	
int Hash::key(int id){
	return id % size;
}

void Hash::confStruct(int i, int id){
	tabela[i] = new registro;
	
	tabela[i]->id = id;
	cin.ignore();
	cout << "Qual o nome?: ";
	getline(cin, tabela[i]->nome);
	cout << "Qual o setor?: ";
	getline(cin, tabela[i]->setor);
	cout << "Qual o funcao?: ";
	getline(cin, tabela[i]->funcao);
}

int Hash::busca(int i, int id){
	int posInicial = i;
	
	if(tabela[i] == NULL or tabela[i]->id == id) return i;
	else{
		i++;
		while(tabela[i] != NULL or tabela[i]->id != id){
			
			i++;
			if(i == (int)size) i = 0;
			if(i == posInicial){
				cout << "nao encontrado" << endl;
				return -1;
			}
		}
		return i;
	}
}	

void Hash::insert(int id){
	int i = key(id);
	
	i = busca(i, id);
	
	if(i != -1) confStruct(i, id);
}

void Hash::remove(int id){
	int i = key(id);
	
	i = busca(i, id);
	
	if(i != -1){
		delete tabela[i];
		tabela[i] = NULL;
	}
}

void Hash::exibe(){
	for(unsigned c=0; c<size; c++){
		cout << c << ": ";
		if(tabela[c] != NULL) cout << tabela[c]->id;
		cout << endl;
	}
}

void Hash::exibeRegistro(int id){
	int i = key(id);
	
	i = busca(i, id);
	
	if(i != 1){
		cout << tabela[i]->nome << endl;
		cout << tabela[i]->setor << endl;
		cout << tabela[i]->funcao << endl;
	}	
}

int main(){
	int aux;
	
	cout << "Digite o tamanho da tabela Hash: ";
	cin >> aux;
	
	Hash hash(aux);
	
	aux = 1;
	while(aux != 0){
		cout << endl;
		menu();
		cout << "Digite a funcao: ";
		cin >> aux;
	
		if(aux == 1){
			cout << "Digite o id a ser inserido: ";
			cin >> aux;
			hash.insert(aux);
			aux = 1;
		
		}else if(aux == 2){
			cout << "Digite o id a ser removido: ";
			cin >> aux;
			hash.remove(aux);
			aux = 2;
		
		}else if(aux == 3) hash.exibe();
		
		else if(aux == 4){
			cout << "Digite o id do registro: ";
			cin >> aux;
			hash.exibeRegistro(aux);
			aux = 4;
		}
	}
	
	return 0;
	
}
