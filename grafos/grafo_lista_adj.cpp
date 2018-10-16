// Grafos - Lista de adjacência
#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;

class Grafo
{
	int V; // número de vértices
	list<int> *adj; // ponteiro para um array contendo as listas de adjacências

public:
	Grafo(int Valor){
		V = Valor; // atribui o número de vértices
		adj = new list<int>[V]; // cria as listas
	}

	int nro_nos(){
		return V;
	}

	void adicionarAresta(int v1, int v2){
		// adiciona vértice v2 à lista de vértices adjacentes de v1
		adj[v1].push_back(v2);
	}

	void removeAresta(int v1, int v2){
		// adiciona vértice v2 à lista de vértices adjacentes de v1
		adj[v1].remove(v2);
	}

	int obterGrauDeSaida(int v){
		// basta retornar o tamanho da lista que é a quantidade de vizinhos
		return adj[v].size();
	}

	void mostra(){
		int i,j;
		for (i=0;i<V;i++){
			printf("%d -> ",i);
			for (list<int>::iterator it=adj[i].begin(); it != adj[i].end(); it++){
				 cout << ' ' << *it;
			}
			printf("\n");
		}
	}



	void DFS(int no,int *visitado) {
		visitado[no] = 1;
		printf("%d\n",no);
		for (list<int>::iterator it=adj[no].begin(); it != adj[no].end(); it++){
			if(!visitado[*it]){
			   DFS(*it,visitado);
			}
		}
	}

	void BFS(int no_inicial) {
		int fila[V],visitado[V], ini, fim;
		for(int i=0; i<V; i++)
		  visitado[i] = 0;
		visitado[no_inicial] = 1;
		ini = fim = 0;
		fila[fim++] = no_inicial;

		while(ini != fim) {
			int no = fila[ini++];
			printf("%d\n",no);
			for (list<int>::iterator it=adj[no].begin(); it != adj[no].end(); it++){
				int viz = *it;
				if(!visitado[viz]) {
				fila[fim++] = viz;
				visitado[viz] = 1;
				}
			}
		}
	}


};

int main()
{
	// criando um grafo de 4 vértices
	Grafo grafo(6);

	// adicionando as arestas
	grafo.adicionarAresta(1, 0);
	grafo.adicionarAresta(0, 4);
	grafo.adicionarAresta(0, 5);
	grafo.adicionarAresta(4, 2);
	grafo.adicionarAresta(4, 3);
	grafo.adicionarAresta(5, 3);

	// mostrando os graus de saída
	cout << "Grau de saida do vertice 1: " << grafo.obterGrauDeSaida(1);
	cout << "\nGrau de saida do vertice 3: " << grafo.obterGrauDeSaida(3)<<"\n";

	// mostrando grafo
	grafo.mostra();

	int visitado[grafo.nro_nos()];
	for (int x=0;x<grafo.nro_nos();x++)
		visitado[x]=0;

	printf("\nDFS\n");
	grafo.DFS(1,visitado);

	printf("\nBFS\n");
	grafo.BFS(1);

	return 0;
}
