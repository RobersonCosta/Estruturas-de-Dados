#include <stdio.h>
#include <stdlib.h>

class Nodo {
	private:
		int x,y;
		Nodo *prox;
	public:
		Nodo(){
			x=0;
			y=0;
			prox=NULL;
		}
		Nodo(int vx,int vy){
			x=vx;
			y=vy;
			prox=NULL;
		}
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		Nodo* getProx(){
			return prox;
		}
		void setX(int vx){
			x=vx;
		}
		void setY(int vy){
			y=vy;
		}
		void setProx(Nodo *P){
			prox=P;
		}
		void mostra(){
			printf("%d - %d\n",x,y);
		}
};

class Lista {
	private:
		Nodo* Ini;
		int tam;
	public:
		Lista() {
			Ini=NULL;
			tam=0;
		}

		int insere(int posicao,Nodo *novo_valor) {
			//A posicao é invalida?
			if (posicao<1 || posicao>tam+1){
				printf("Posicao invalida!\n");
				return 0;
			}
			//A lista está vazia?
			if (Ini==NULL){
				Ini=novo_valor;
				tam++;
				return 1;
			}
			//na primeira posicao?
			if (posicao==1){
				novo_valor-> setProx(Ini);
				Ini=novo_valor;
				tam++;
				return 1;
			}
			//insere no meio
			Nodo* temp=Ini;
			for (int cont=1;cont<posicao-1;cont++){
				temp=temp->getProx();
			}
			novo_valor->setProx(temp->getProx());
			temp->setProx(novo_valor);
			tam++;
			return 1;
		}

		int remove(int posicao){
			//lista Vazia?
			if (Ini==NULL){
				printf("A lista esta vazia!\n");
				return 0;
			}
			//Estou em uma posicao invalida?
			if (posicao<1 || posicao>tam){
				printf("Posicao invalida!\n");
				return 0;
			}
			//Estou removendo do inicio?
			if (posicao==1){
				Ini=Ini->getProx();
				tam--;
				return 1;
			}
			//Remover do meio
			Nodo *temp;
			temp=Ini;
			for (int cont=1;cont<posicao-1;cont++){
				temp=temp->getProx();
			}
			temp->setProx(temp->getProx()->getProx());
			tam--;
			return 1;
		}

		Nodo *consulta(int posicao) {
			Nodo *temp;
			temp=Ini;
			for (int cont=1;cont<posicao;cont++){
				temp=temp->getProx();
			}
			return temp;
		}

		void mostra(){
			Nodo* temp=Ini;
			for (int cont=0;cont<tam;cont++){
				temp->mostra();
				temp=temp->getProx();
			}
		}
};

int main(){
	Nodo N1(1,1);
	Nodo N2(4,4);
	Nodo N3(2,2);

	Lista Minha_Lista;
	Minha_Lista.insere(1,&N1);
	Minha_Lista.insere(1,&N2);
	Minha_Lista.insere(2,&N3);
//	Minha_Lista.remove(3);
	Minha_Lista.mostra();
	printf("Consulta:\n");
	Minha_Lista.consulta(3)->mostra();
	return 1;
}
