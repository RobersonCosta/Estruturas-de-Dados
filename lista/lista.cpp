#include <stdio.h>
#include <stdlib.h>

class Nodo {
private:
	int x,y;
public:
	Nodo() {
		x = 0;
		y = 0;
	}
	Nodo(int a, int b) {
		x = a;
		y = b;
	}

	void setX(int novo) {
		x = novo;
	}
	void setY(int novo) {
		y = novo;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void mostra() {
		printf("(%d--%d)\n",x,y);
	}
};


class Lista {
private:
	int ini,fim;
	Nodo *array;
	int tam;

void desloca_direita(int pos){
	for (int cont=fim;cont>=pos;cont--){
		array[cont+1]=array[cont];
	}
	fim++;
}

void desloca_esquerda(int pos){
	for (int cont=ini;cont<=pos;cont++){
		array[cont-1]=array[cont];
	}
	ini--;
}

void desloca_direita_remove(int pos){
	for (int cont=pos;cont>=ini;cont--){
		array[cont+1]=array[cont];
	}
	ini++;
}

void desloca_esquerda_remove(int pos){
	for (int cont=pos;cont<=fim;cont++){
		array[cont-1]=array[cont];
	}
	fim--;
}

public:
	Lista() {
		tam=10;
		array = new Nodo[tam];
		ini=-1;
		fim=-1;
	}
	Lista(int tam_max) {
		tam=tam_max;
		array = new Nodo[tam];
		ini=-1;
		fim=-1;
	}
	int getTam(){
		if (ini==-1 && fim==-1)
			return 0;
		return (fim-ini+1);
	}

	int insere(int posicao,Nodo novo_valor) {
		if (ini==0 && fim==tam-1) { //lista cheia
			printf("Lista cheia!\n");
			return 0;
		}
		if (posicao<1 || posicao>getTam()+1) { //posicao invalida
			printf("Posicao invalida!\n");
			return 0;
		}
		if (ini==-1 && fim==-1) { //lista vazia
			ini=0;
		}
		int posicao_no_array=ini+posicao-1;
		if (ini==0){ //deslocar obrigatoriamente para direita
			desloca_direita(posicao_no_array);
		}	else {
			if (fim==tam-1){ //deslocar obrigatoriamente para esquerda
				posicao_no_array--;
				desloca_esquerda(posicao_no_array);
			} else {
				if (ini!=0 && fim!=tam-1){ //deslocar para qual lado?
					int dist_esq=posicao_no_array-ini;
					int dist_dir=fim-posicao_no_array;
					if (dist_esq<dist_dir){
						posicao_no_array--;
						desloca_esquerda(posicao_no_array);
					} else {
						desloca_direita(posicao_no_array);
					}
				}
			}
		}
		array[posicao_no_array]=novo_valor;
		return 1;
	}

	int remove(int posicao) {
		//lista Vazia?
		if (ini==-1 && fim==-1) {
			printf("Lista Vazia!\n");
			return 0;
		}

		//Estou em uma posicao invalida?
		if (posicao<1 || posicao>getTam()) {
			printf("Posicao Invalida\n");
			return 0;
		}
		//Estou removendo do inicio?
		if (posicao==1){
			//Quando exclui o unico elemento a lista fica vazia
			if (getTam()==1){
				ini=-1;
				fim=-1;
				return 1;
			}
			ini++;
			return 1;
		}
		//Estou removendo do fim?
		if (posicao==getTam()){ //posicao_array==fim
			fim--;
			return 1;
		}
		//Agora estou no caso do deslocamento
		int posicao_no_array=ini+posicao-1;
		int dist_esq=posicao_no_array-ini;
		int dist_dir=fim-posicao_no_array;
			//desloca direita
			if (dist_esq<dist_dir){
				desloca_direita_remove(posicao_no_array-1);
			} else {
			//desloca esquerda?
				desloca_esquerda_remove(posicao_no_array+1);
			}
	}

	Nodo consulta(int posicao) {
		if (posicao<1 || posicao>fim-ini+1 ) {
			printf("Posicao invalida para consulta.");
			Nodo tmp(0,0);
			return tmp;
		} else {
			return array[posicao+ini-1];
		}
	}

	void mostra() {
		if (ini==-1 && fim==-1){
			printf("Lista vazia.\n");
		} else {
			for (int cont=ini;cont<=fim;cont++){
				array[cont].mostra();
			}
		}
	}

};


int main() {
	Nodo N1(1,1);
	Nodo N2(2,2);
	Nodo N3(3,3);
	Nodo N4(4,4);
	Nodo N5(5,5);

	Lista L;

	L.mostra();
	L.insere(1,N1);
	L.insere(2,N2);
	L.insere(3,N3);
	L.insere(4,N4);
	L.insere(5,N5);
	L.mostra();
	printf("Consulta:\n");
	L.consulta(2).mostra();

	printf("Removendo...\n");
	L.remove(4);
	L.mostra();
}
