#include <stdio.h>
#include <stdlib.h>

// ponteiro da sub-árvore, da direita e da à esquerda.
struct node{
	int valor;
	struct node *direito;                                                       
	struct node *esquerdo;                                                      
};

typedef struct node Arvore;

// cria uma árvore vazia representada por NULL.																				
Arvore *criar(){      

	return NULL;
}

// cria um nó raiz dadas a informação e as duas sub-árvores, a da esquerda e a da direita.
// libera memória alocada pela estrutura da árvore.
// as sub-árvores devem ser liberadas antes de se liberar o nó raiz.
// retorna uma árvore vazia, representada por NULL.

Arvore *inserir(Arvore *raiz, int x){

	if(raiz == NULL){
		Arvore *aux=(Arvore*)malloc(sizeof(Arvore));		
		aux->valor=x;
		aux->direito=NULL;
		aux->esquerdo=NULL;

		return aux;

	}else{
		if(x < raiz->valor){
			raiz->esquerdo = inserir(raiz->esquerdo, x);
			printf("\nO %d foi inserido a esquerda do %d\n", x, raiz->valor);
		
		}else if(x > raiz->valor){
			raiz->direito = inserir(raiz->direito, x);
			printf("\nO %d foi inserido a direita do %d\n", x, raiz->valor);
		
		}else{
			printf("\nO %d ja existe\n",x);                                        //Opcional
		}
	}
	
	return raiz;

}

// explora e busca a propriedade de ordenação da árvore.
Arvore *busca(Arvore *raiz, int x)
{
    if (raiz != NULL)
    {
        if (raiz->valor == x)
            return NULL;
        else
        {
            if (x > raiz->valor)
                return busca(raiz->direito, x);
            else
                return busca(raiz->esquerdo, x);
        }
    }
    return NULL;
}

// Impressão dos valores das sub-árvores seguindo a ordem e pós-ordem.
void imprimirNaOrdem(Arvore *raiz){
	if(raiz!=NULL){
		imprimirNaOrdem(raiz->esquerdo);
		imprimirNaOrdem(raiz->direito);
		printf(" %d ",raiz->valor);	
	}
}

void imprimirNaPosOrdem(Arvore *raiz){
	if(raiz !=NULL){
		imprimirNaPosOrdem(raiz->esquerdo);
		imprimirNaPosOrdem(raiz->direito);
		printf(" %d ", raiz->valor);		
	}
}

// Inserção dos valores (pares) da raiz nas sub-arvores. 
int main(){
	Arvore *raiz=criar();
	raiz=inserir(raiz,10);
	raiz=inserir(raiz,40);
	raiz=inserir(raiz,100);
	raiz=inserir(raiz,20);
	raiz=inserir(raiz,50);
    raiz=inserir(raiz,80);
	
	printf("\n");

	imprimirNaOrdem(raiz);
	
    printf("\n");
	
	return 0;
}
