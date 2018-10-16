/*
 * Implementação de grafos não dirigidos utilizando uma
 * matriz de adjacências (apenas o triângulo inferior).
 */

#include <stdio.h>

class Grafo {
private:
  int n;      /* Número de nós */
  int **mat;  /* Matriz (a ser alocada dinamicamente) */
public:
	Grafo(int nos)  {
	  int i,j;
	  n = nos;
	  mat = new int*[n];

	  for (i = 0; i < n; i++){
			mat[i]=new int[n];
			for (j = 0; j < n; j++)
				mat[i][j]=0;
		}
	}

	void adiciona_aresta(int v1, int v2) {
		if (v1 > v2)
		 mat[v1-1][v2-1] = 1;
	  else
		 mat[v2-1][v1-1] = 1;
	}

	int existe_aresta(int v1, int v2) {
	  return v1 > v2 ? mat[v1-1][v2-1] : mat[v2-1][v1-1];
	}

	void remove_aresta(int v1, int v2) {
	  if (v1 > v2)
		 mat[v1-1][v2-1] = 0;
	  else
		 mat[v2-1][v1-1] = 0;
	}

	void mostra() {
		int i,j;
	  for (i = 0; i < n; i++){
		  for (j = 0; j < n; j++)
				printf("%d ",mat[i][j]);
			printf("\n");
		}
	}

};

int main() {
  	Grafo g(6);

  	g.adiciona_aresta(1,2);
  	g.adiciona_aresta(2,3);
  	g.adiciona_aresta(4,2);
  	g.adiciona_aresta(5,1);
  	g.adiciona_aresta(5,3);
  	g.adiciona_aresta(5,4);
	g.adiciona_aresta(6,4);
  	g.remove_aresta(5,3);
	g.mostra();
  return 0;
}
