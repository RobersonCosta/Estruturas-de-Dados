// Grafos - Lista de adjacência
#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;

const int MAX_INT=999999;

class No
{
private:
	int dest;
	int peso;
public:
	int getDest(){
		return dest;
	}
	int getPeso(){
		return peso;
	}
	void setDest(int d){
		dest=d;
	}
	int setPeso(int p){
		peso=p;
	}
};

class Grafo
{
	int V; // número de vértices
	list<No> *adj; // ponteiro para um array contendo as listas de adjacências

public:
	Grafo(int Valor){
		V = Valor; // atribui o número de vértices
		adj = new list<No>[V]; // cria as listas
	}

	int nro_nos(){
		return V;
	}

	void adicionarAresta(int v1, int v2,int peso){
		// adiciona vértice v2 à lista de vértices adjacentes de v1
		No temp;
		temp.setDest(v2);
		temp.setPeso(peso);
		adj[v1].push_back(temp);
	}

	void mostra(){
		int i,j;
		for (i=0;i<V;i++){
			printf("Orig: %d -> \n",i);
			for (list<No>::iterator it=adj[i].begin(); it != adj[i].end(); it++){
				 cout << "Dest: " << (*it).getDest() << "  -  Peso: " << (*it).getPeso()<<"\n";
			}
			printf("\n");
		}
	}


	int menor_dist(int **visitados,int *dist){
		int menor=MAX_INT,pos;
		for (int i=0;i<V;i++){
			if ((*visitados)[i]==0 && dist[i]<menor){
				menor=dist[i];
				pos=i;
			}
		}
		if (menor!=MAX_INT){
			(*visitados)[pos]=1;
			return pos;
		}else
			return -1;
	}
	void dijkstra(int source){
		int *visitados,*predecessores,*dist;
		visitados = new int[V];
		predecessores = new int[V];
		dist = new int[V];
		for (int i=0;i<V;i++){
			dist[i] = MAX_INT;
			predecessores[i]=-1;
			visitados[i]=0;
		}
		dist[source] = 0; 	// Distance from source to source
	 	int u = menor_dist(&visitados,dist);
	 	while (u!=-1){ 	// main loop
			for (list<No>::iterator it=adj[u].begin(); it != adj[u].end(); it++){
			 	int alt = dist[u] + (*it).getPeso();
			 	if (alt < dist[(*it).getDest()]){ 	// Relax (u,v)
				 	dist[(*it).getDest()] = alt;
				 	predecessores[(*it).getDest()] = u;
				}
			}
		 	u = menor_dist(&visitados,dist);
		}
		for (int i=0;i<V;i++){
			printf("Dist[%d]=%d	Predecessor[%d]=%d\n",i,dist[i],i,predecessores[i]);
		}
	}


};

int main()
{
	// criando um grafo de 4 vértices
	Grafo grafo(6);

	// adicionando as arestas
	grafo.adicionarAresta(0, 1,5);
	grafo.adicionarAresta(0, 4,2);
	grafo.adicionarAresta(0, 5,7);
	grafo.adicionarAresta(4, 2,3);
	grafo.adicionarAresta(4, 1,1);
	grafo.adicionarAresta(1, 3,2);
	grafo.adicionarAresta(1, 2,3);
	grafo.adicionarAresta(5, 3,2);
	grafo.adicionarAresta(1, 5,1);

	// mostrando grafo
	grafo.mostra();

	printf("Dijkstra:\n");
	grafo.dijkstra(0);

	return 0;
}
