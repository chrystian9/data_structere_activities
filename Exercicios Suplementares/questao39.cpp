#include <iostream>
using namespace std;

class Hash{
	private:
		int quantDados;
		int capacidade;
		int* Dados;
		inline int esquerdo(int i){
			return (2*i)+1;
		}
		inline int direito(int i){
			return (2*i)+2;
		}
		void alocaVetor(){
			int numParents = 1;
			
			cout << "Digite a quantidade de Dados: ";
			cin >> quantDados;
			
			while(numParents < quantDados) numParents = numParents * 2;
			capacidade = (numParents - 1) + quantDados;
			
			Dados = new int[capacidade];
		}
		void addDados(){
			cout << "Digite os Dados: ";
			
			for(int c=(capacidade-quantDados); c<capacidade; c++) cin >> Dados[c];
		}
		void arruma(){
			for(int c=(capacidade-quantDados-1); c>=0; c--) copiaMaior(c);
		}
		void copiaMaior(int i){
			int esq = esquerdo(i);
			int dir = direito(i);
			int maior;
			
			if(esq < capacidade){
				if(dir < capacidade and Dados[dir] > Dados[esq]) maior = dir;
				else maior = esq;
				Dados[i] = Dados[maior];
			}else Dados[i] = -1;    // invalido
		}
			
	public:
		Hash(){
			quantDados = 0;
			capacidade = 0;
			Dados = NULL;
			alocaVetor();
			addDados();
			arruma();
		}
		~Hash(){
			delete Dados;
		}
		void retiraVencedor(){
			for(int c=1; c<capacidade; c++) if(Dados[c] == Dados[0]) Dados[c] = -1;
			Dados[0] = -1;
			
			cout << "Vetor antes de organizar: ";
			imprime();
			cout << endl;
			arruma();
		}
		int vencedor(){
			return Dados[0];
		}
		void imprime(){
			for(int c=0; c<capacidade; c++) cout << Dados[c] << " ";
			cout << endl;
		}
};

int main(){
	Hash torneio;
	
	cout << endl << "O primeiro lugar e: " << torneio.vencedor() << endl << endl;
	
	cout << "Vetor: ";
	torneio.imprime();
	cout << endl;
	
	while(torneio.vencedor() >= 0){
		cout << "------------------------------------------" << endl << endl;
		cout << "Retirando o primeiro e organizando torneio" << endl << endl;
		torneio.retiraVencedor();
		
		cout << "O primeiro lugar e: " << torneio.vencedor() << endl;
		
		cout << "Vetor: ";
		torneio.imprime();
		cout << endl;
	}
	return 0;
}
