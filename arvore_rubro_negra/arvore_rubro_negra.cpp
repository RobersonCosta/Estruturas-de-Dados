# include <stdio.h>
# include <queue>
using namespace std;
class No {
  private:
	int valor;
   No *direito, *esquerdo, *pai;
   int cor; //1 -> preto 0->vermelho

  public:
	No () {
	    direito = NULL;
		esquerdo = NULL;
		pai = NULL;
		cor = 0;
	}
	No(int nvalor) {
	    valor = nvalor;
	    direito = NULL;
		esquerdo = NULL;
		pai = NULL;
		cor = 0;
	}

	No(int nvalor,No *npai) {
		valor = nvalor;
		direito = NULL;
		esquerdo = NULL;
		pai = npai;
		cor = 0;
	}

	int getValor() {
		return valor;
	}

	No *getDireito() {
		return direito;
	}

	No *getEsquerdo() {
		return esquerdo;
	}

	void setDireito(No* No) {
		direito = No;
	}

	void setEsquerdo(No* No) {
		esquerdo = No;
	}

	No *getPai() {
		return pai;
	}

	void setPai(No* No) {
		pai = No;
	}

	No *getAvo() {
		return pai->pai;
	}

	int ehPreto() {
		return cor;
	}

	int ehVermelho() {
		return !cor;
	}

	void setVermelho() {
		cor = 0;
	}

	void setPreto() {
		cor = 1;
	}

	void mostra() {
		printf("%d",valor);
		if (esquerdo != NULL) {
			if (esquerdo->ehPreto()) {
				if (direito == NULL)
					printf("<ul><li class=\"preto_last\">");
				else
					printf("<ul><li class=\"preto\">");
			}
			else {
				if (direito == NULL)
					printf("<ul><li class=\"vermelho_last\">");
				else
					printf("<ul><li class=\"vermelho\">");
			}
			esquerdo->mostra();
			printf("</li></ul>");

		}
		else {
			printf("<ul><li class=\"preto\">+</li></ul>");

		}
		if (direito != NULL) {
			if (direito->ehPreto())
				printf("<ul><li class=\"preto_last\">");
			else
				printf("<ul><li class=\"vermelho_last\">");
			direito->mostra();
			printf("</li></ul>");
		}
		else {
			printf("<ul><li class=\"preto_last\">+</li></ul>");

		}
	}
};

class RubroNegra {
private:
	No *raiz;

public:

	RubroNegra(int valor) {
		raiz = new No(valor);
		raiz->setPreto();

	}


	void mostra() {
		printf("<style>ul.tree, ul.tree ul { list-style-type: none; background: url(vline.png) repeat-y; margin: 0; padding: 0; } ul.tree ul{ margin-left: 10px; } ul.tree li { margin: 0; padding: 0 12px; line-height: 20px; background: url(node.png) no-repeat; color: #369; font-weight: bold; } ul.tree li.preto {color: #000;} ul.tree li.preto_last {color: #000; background: #fff url(lastnode.png) no-repeat; } ul.tree li.vermelho {color: #f00;} ul.tree li.vermelho_last {color: #f00; background: #fff url(lastnode.png) no-repeat; }</style>");

		printf("<UL class=\"tree\" id=\"tree\"><li class=\"preto_last\">");
		raiz->mostra();
		printf("</UL>");
	}

	int add(No *atual,int valor) {
		if (atual->getValor() == valor) {
			printf("valor ja existe\n\n");
			return 0;
		}
		if (valor > atual->getValor()) {
			if (atual->getDireito() == NULL) {
				atual->setDireito(new No(valor,atual));
				Balanceia(atual->getDireito());
				return 1;
			}
			else {
				return add(atual->getDireito(),valor);
			}
		}
		else {
			if (atual->getEsquerdo() == NULL) {
				atual->setEsquerdo(new No(valor,atual));
				Balanceia(atual->getEsquerdo());
				return 1;
			}
			else {
				return add(atual->getEsquerdo(),valor);
			}
		}
	}

	int insere(int valor) {
		return add(raiz,valor);
	}

	void Balanceia(No *atual) {
		//criar um ponteiro temporário pra guardar o tio
		No *tio;
		//verificar se o nó atual é o raiz. Se sim, setar pra preto e terminar
		if (atual==raiz){
			atual->setPreto();
			return;
		}

		while(atual->getPai()!=NULL && atual->getPai()->ehVermelho()) {
			//Casos 1 e 2: verifica se o pai do atual vem pela esquerda
			if(atual->getAvo()->getEsquerdo() == atual->getPai()) {
				//Caso 1: tem tio na direita
				if(atual->getAvo()->getDireito()!=NULL) {
					tio=atual->getAvo()->getDireito();
					if(tio->ehVermelho()) {
						atual->getPai()->setPreto();
						tio->setPreto();
						atual->getAvo()->setVermelho();
						atual=atual->getAvo();
					}
				}
				else {
				//Caso 2: não tem tio na direita
					//Caso 2a: verifica se o atual � o filho da direita
					if (atual->getPai()->getDireito()==atual) {
						//atual passa ser o pai
						atual=atual->getPai();
						//rotaciona pra esquerda pelo atual
						rotaciona_esquerda(atual);
					}
					//seta o pai do atual como preto
					atual->getPai()->setPreto();
					//seta o av� como vermelho
					atual->getAvo()->setVermelho();
					//rotaciona pra direita pelo av�
					rotaciona_direita(atual->getAvo());
				}
			} else {
			//Casos 3 e 4: verifica se o pai do atual vem pela direita
				//Caso 3: tem tio na esquerda
				if(atual->getAvo()->getEsquerdo()!=NULL) {
					tio=atual->getAvo()->getEsquerdo();
					if(tio->ehVermelho()) {
						atual->getPai()->setPreto();
						tio->setPreto();
						atual->getAvo()->setVermelho();
						atual=atual->getAvo();
					}
				}
				else {
				//Caso 4: não tem tio na esquerda
					//Caso 4a: verifica se o atual � o filho da esquerda
					if (atual->getPai()->getEsquerdo()==atual) {
						//atual passa ser o pai
						atual=atual->getPai();
						//rotaciona pra direito pelo atual
						rotaciona_direita(atual);
					}
					//seta o pai do atual como preto
					atual->getPai()->setPreto();
					//seta o av� como vermelho
					atual->getAvo()->setVermelho();
					//rotaciona pra esquerda pelo av�
					rotaciona_esquerda(atual->getAvo());
				}
			}
			//Seta raiz pra preto
			raiz->setPreto();

		} // Fim do Loop
	} //Fim do Balanceia

	void rotaciona_direita(No *p) {
		//verifica se não tem filho a esquerda
		if (p->getEsquerdo()==NULL)
			//se nao tem -> nada a fazer, termina
			return;
		//senao
		else {
			//salva o filho esquerdo temporariamente (y)
			No *y = p->getEsquerdo();
			//verifica se y tem filho a direita
			if (y->getDireito()!=NULL){
				//esquerda de p recebe direita de y
				p->setEsquerdo(y->getDireito());
				//pai da direita de y recebe p
				y->getDireito()->setPai(p);
			//senao
			} else {
				//esquerda de p recebe nulo
				p->setEsquerdo(NULL);
			}
			//verifica se p não é raiz, ou seja, se tem pai
			if (p->getPai()!=NULL)
				//pai do y passa a ser o antigo pai de p
				y->setPai(p->getPai());
			//se p n�o tem pai
			if (p->getPai()==NULL)
				//a raiz passa ser o y
				raiz = y;
			//senao (ajustar pai)
			else {
				//se p veio pela esquerda
				if (p->getPai()->getEsquerdo()==p)
					//ajusta o filho da esquerda do pai pra y
					p->getPai()->setEsquerdo(y);
				//senao
				else
					//ajusta o filho da direita do pai pra y
					p->getPai()->setDireito(y);
			}
			//filho da direita de y recebe o p
			y->setDireito(p);
			//ajusta o pai de p como o y
			p->setPai(y);
		}
	}

	void rotaciona_esquerda(No *p) {
		//verifica se não tem filho a direita
		if (p->getDireito()==NULL)
			//se nao tem -> nada a fazer, termina
			return;
		//senao
		else {
			//salva o filho direito temporariamente (y)
			No *y = p->getDireito();
			//verifica se y tem filho a esquerda
			if (y->getEsquerdo()!=NULL){
				//direita de p recebe esquerda de y
				p->setDireito(y->getEsquerdo());
				//pai da esquerda de y recebe p
				y->getEsquerdo()->setPai(p);
			//senao
			} else {
				//direita de p recebe nulo
				p->setDireito(NULL);
			}
			//verifica se p n�o � raiz, ou seja, se tem pai
			if (p->getPai()!=NULL)
				//pai do y passa a ser o antigo pai de p
				y->setPai(p->getPai());
			//se p n�o tem pai
			if (p->getPai()==NULL)
				//a raiz passa ser o y
				raiz = y;
			//senao (ajustar pai)
			else {
				//se p veio pela esquerda
				if (p->getPai()->getEsquerdo()==p)
					//ajusta o filho da esquerda do pai pra y
					p->getPai()->setEsquerdo(y);
				//senao
				else
					//ajusta o filho da direita do pai pra y
					p->getPai()->setDireito(y);
			}
			//filho da esquerda de y recebe o p
			y->setEsquerdo(p);
			//ajusta o pai de p como o y
			p->setPai(y);
		}
	}



};

int main() {
	RubroNegra x(10);

//	int tam = 9;
//	int insercao[] = {5,20,30,40,8,9,7,1,2};
	int tam = 7;
	int insercao[] = {5,20,30,40,8,9,7};


	for (int i=0;i<tam;i++)
		x.insere(insercao[i]);

	x.mostra();

}
