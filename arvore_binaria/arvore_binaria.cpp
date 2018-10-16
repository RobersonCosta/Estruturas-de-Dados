# include <iostream>
# include <stdio.h>
using namespace std;
class No {
private:
	int valor;
	No *Esquerda;
	No *Direita;

public:
	No(){
		valor=0;
		Esquerda=NULL;
		Direita=NULL;
	}
	No(int v){
		valor=v;
		Esquerda=NULL;
		Direita=NULL;
	}
	int getValor(){
		return valor;
	}
	void setValor(int v){
		valor=v;
	}
	No* getEsquerda(){
		return Esquerda;
	}
	No* getDireita(){
		return Direita;
	}
	void setEsquerda(No *p){
		Esquerda=p;
	}
	void setDireita(No *p){
		Direita=p;
	}

};

class ArvoreBinaria {
private:
	No *raiz;
public:
	ArvoreBinaria(){
		raiz = NULL;
	}
	void PreOrdem (No *atual) {
		//visita o proprio
		//visita da esquerda
		//visita o da direita
		if (atual != NULL){
			printf("%d\n",atual->getValor());
			PreOrdem(atual->getEsquerda());
			PreOrdem(atual->getDireita());
		}

	}

	void PreOrdem () {
		PreOrdem(raiz);
	}
	void EmOrdem () {
		EmOrdem(raiz);
	}
	void PosOrdem () {
		PosOrdem(raiz);
	}

	void EmOrdem (No *atual) {
		//visita da esquerda
		//visita o proprio
		//visita o da direita
		if (atual != NULL){
			EmOrdem(atual->getEsquerda());
			printf("%d\n",atual->getValor());
			EmOrdem(atual->getDireita());
		}
	}
	void PosOrdem (No *atual) {
		//visita da esquerda
		//visita o da direita
		//visita o proprio
		if (atual != NULL){
			EmOrdem(atual->getEsquerda());
			EmOrdem(atual->getDireita());
			printf("%d\n",atual->getValor());
		}
	}
	void insere (int valor) {
		if (raiz == NULL){
			raiz = new No(valor);
		} else {
			No *temp,*ant;
			temp=raiz;
			while (temp!=NULL){
				ant=temp;
				if (valor<temp->getValor()){
					temp=temp->getEsquerda();
				} else {
					temp=temp->getDireita();
				}
			}
			if (valor<ant->getValor()){
				ant->setEsquerda(new No(valor));
			} else {
				ant->setDireita(new No(valor));
			}
		}
	}

	No* noMaior(No *raiz2){
	    No *temp=NULL;
	    temp = raiz2;
	    if(temp->getDireita()== NULL){
			//raiz2 = raiz2->getEsquerda();
			printf("maior=%d\n",temp->getValor());
			return temp;
		} else
		return noMaior(raiz2->getDireita());
	}


};

int main()
{
	ArvoreBinaria arvore;
	arvore.insere(5);
	arvore.insere(2);
	arvore.insere(1);
	arvore.insere(4);
	arvore.insere(8);
	arvore.insere(6);
	arvore.insere(12);
	arvore.insere(9);
	arvore.insere(7);


	arvore.EmOrdem();
	printf("-------------------------\n");
	arvore.PreOrdem();



}
