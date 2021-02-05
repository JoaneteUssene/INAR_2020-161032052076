
//-----------------------------------------------bibliotecas----------------

#include<stdlib.h>
#include<stdio.h>
#include<time.h>


//------------------------------------------criasao d metodos e variaveis...

typedef struct node{
    int tabela[9];
    int activo, eap;
    struct node * esquerdo, * direito, * cima, * baixo, * pai;
} node;

void mover_tabela(node *, node *, int, int);
int minimo_node(node *, node *, node *, node *);
void calcular_filho(node *);
void eap_distancia(node *);
void verificar_pais(node *);
int umpatane(node *, node *);
node * move(node *);
void print_tabela(node *);

//-----------------------------------------------criasao da estrutura logica...

int umpatane(node * n1, node * n2){
    int i;
    for(i=0; i<9; i++){
        if(n1->tabela[i] != n2->tabela[i]){
            return 0;
        }
    }
    return 1;
}

void calcular_filho(node * posicao){
    int i, localizacao_do_zero;
    
    for(i=0; i<9; i++){
        if(posicao->tabela[i] == 0){
            localizacao_do_zero = i;
            break;
        }
    }

    posicao->esquerdo = (node *)malloc(sizeof(node));
    posicao->cima = (node *)malloc(sizeof(node));
    posicao->direito = (node *)malloc(sizeof(node));
    posicao->baixo = (node *)malloc(sizeof(node));

    posicao->esquerdo->pai = posicao;
    posicao->cima->pai = posicao;
    posicao->direito->pai = posicao;
    posicao->baixo->pai = posicao; 

    posicao->esquerdo->activo = 1;
    posicao->cima->activo = 1;
    posicao->direito->activo = 1;
    posicao->baixo->activo = 1;

    mover_tabela(posicao, posicao->esquerdo, 1, localizacao_do_zero);
    mover_tabela(posicao, posicao->cima, 2, localizacao_do_zero);
    mover_tabela(posicao, posicao->direito, 3, localizacao_do_zero);
    mover_tabela(posicao, posicao->baixo, 4, localizacao_do_zero);

    verificar_pais(posicao->esquerdo);
    verificar_pais(posicao->cima);
    verificar_pais(posicao->direito);
    verificar_pais(posicao->baixo);

    eap_distancia(posicao->esquerdo);
    eap_distancia(posicao->cima);
    eap_distancia(posicao->direito);
    eap_distancia(posicao->baixo);

}

node * move(node * posicao){
    print_tabela(posicao);
    if(posicao->eap == 0){
        return posicao;
    }
    else{
        int minimo = minimo_node(posicao->esquerdo, posicao->cima, posicao->direito, posicao->baixo);
        switch(minimo){
            case 1:
                return posicao->esquerdo;
                break;
            case 2:
                return posicao->cima;
                break;
            case 3:
                return posicao->direito;
                break;
            case 4:
                return posicao->baixo;
                break;
        }
    }
}


void print_tabela(node * pos){

    printf("\n %d %d %d\n %d %d %d\n %d %d %d\n", pos->tabela[0], pos->tabela[1], 
    	pos->tabela[2], pos->tabela[3], pos->tabela[4], pos->tabela[5], pos->tabela[6], 
        	pos->tabela[7], pos->tabela[8]);
}


void verificar_pais(node * posicao){
    node * pai = posicao->pai;
    while(pai != NULL){
        if(umpatane(posicao, pai)){
            posicao->activo = 0;
            return;
        }
        pai = pai->pai;
    }
}

void eap_distancia(node * posicao){
    
    if(posicao->activo == 0){
        posicao->eap = 1000;
        return;
    }else if(posicao->activo == 2){
        posicao->eap = 5000;
        return;
    }
    
    int eap = 0;
    int i;
    for(i=0; i<9; i++){
        eap += abs((posicao->tabela[i]%3)-(i%3)) + abs((posicao->tabela[i]/3)-(i/3)); 
    }
    posicao->eap = eap;
}

void mover_tabela(node * actual, node * filho, int direcao, int localizacao_do_zero){
    
    int mover_localizacao;
    
    switch(localizacao_do_zero){
        case 0:
            if(direcao == 1 || direcao == 2){
                filho->activo = 2;
                return;
            }
            break;
        case 1:
        if(direcao == 2){
                filho->activo = 2;
                return;
            }
            break;
        case 2:
        if(direcao == 2 || direcao == 3){
                filho->activo = 2;
                return;
            }
            break;
        case 3:
        if(direcao == 1){
                filho->activo = 2;
                return;
            }
            break;
        case 4:
            break;
        case 5:
        if(direcao == 3){
                filho->activo = 2;
                return;
            }
            break;
        case 6:
        if(direcao == 1 || direcao == 4){
                filho->activo = 2;
                return;
            }
            break;
        case 7:
        if(direcao == 4){
                filho->activo = 2;
                return;
            }
            break;
        case 8:
            if(direcao == 3 || direcao == 4){
                filho->activo = 2;
                return;
            }
            break;
    }

    switch(direcao){
        case 1:
            mover_localizacao = localizacao_do_zero - 1;
            break;
        case 2:
            mover_localizacao = localizacao_do_zero - 3;
            break;
        case 3:
            mover_localizacao = localizacao_do_zero + 1;
            break;
        case 4:
            mover_localizacao = localizacao_do_zero + 3;
            break;
    }
     
   
    int i;
    for(i=0; i<9; i++){
        if(i == localizacao_do_zero){
            filho->tabela[i] = actual->tabela[mover_localizacao];
        }else if(i == mover_localizacao){
            filho->tabela[i] = 0;
        }else{
            filho->tabela[i] = actual->tabela[i];
        }
    }
    return;
}

int minimo2(int a, int b){
    if(a<b)
        return a;
    return b;
}

int minimo4(int a, int b, int c, int d){
    int x = minimo2(a, b);
    int y = minimo2(c, d);
    return minimo2(x, y);
}

int minimo_node(node * c1, node * c2, node * c3, node * c4){
    int minimo = minimo4(c1->eap, c2->eap, c3->eap, c4->eap);
    int minimos = 0;
    int selecao_aleatoria = rand();
    if(minimo == c1->eap){
        minimos += 1;
    }
    if(minimo == c2->eap){
        minimos += 2;
    }
    if(minimo == c3->eap){
        minimos += 4;
    }
    if(minimo == c4->eap){
        minimos += 8;
    }
    switch(minimos){
    	case 1:
    		return 1;
    		break;
    	case 2:
    		return 2;
    		break;
		case 3:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 1;
			}
			return 2;
			break;
		case 4:
			return 3;
			break;
		case 5:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 1;
			}
			return 3;
			break;
		case 6:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 3;
			}
			return 2;
			break;
		case 7:
			selecao_aleatoria = selecao_aleatoria % 3;
			if(selecao_aleatoria == 0){
				return 1;
			}else if(selecao_aleatoria == 1){
				return 2;
			}
			return 3;
			break;
		case 8:
			return 4;
			break;
		case 9:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 1;
			}
			return 4;
			break;
		case 10:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 4;
			}
			return 2;
			break;
		case 11:
			selecao_aleatoria = selecao_aleatoria % 3;
			if(selecao_aleatoria == 0){
				return 1;
			}else if(selecao_aleatoria == 1){
				return 2;
			}
			return 4;
			break;
		case 12:
			selecao_aleatoria = selecao_aleatoria % 2;
			if(selecao_aleatoria == 0){
				return 4;
			}
			return 3;
			break;
		case 13:
			selecao_aleatoria = selecao_aleatoria % 3;
			if(selecao_aleatoria == 0){
				return 1;
			}else if(selecao_aleatoria == 1){
				return 4;
			}
			return 3;
			break;
		case 14:
			selecao_aleatoria = selecao_aleatoria % 3;
			if(selecao_aleatoria == 0){
				return 4;
			}else if(selecao_aleatoria == 1){
				return 2;
			}
			return 3;
			break;
		case 15:
			selecao_aleatoria = selecao_aleatoria % 4;
			if(selecao_aleatoria == 0){
				return 1;
			}else if(selecao_aleatoria == 1){
				return 2;
			}else if(selecao_aleatoria == 2){
				return 4;
			}
			return 3;
			break;		
	}
}

void write_tabela(FILE * f, node * n){
    int i, j;
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            fprintf(f, "%d ", n->tabela[3*i+j]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

int main(){

    int tabela[9] = {3,4,6,2,8,5,1,7,0};
    int i, count = 0;
    FILE * output;
    output = fopen("ussene.txt","w");

    node * actual_node;
    actual_node = (node *)malloc(sizeof(node));
    actual_node->pai = NULL;
    actual_node->activo = 1;

    int t = time(NULL);

    for(i=0; i<9; i++){
        actual_node->tabela[i] = tabela[i];
    }

    calcular_filho(actual_node);
    eap_distancia(actual_node);

    while(actual_node->eap != 0){
        count++;
        actual_node = move(actual_node);
        calcular_filho(actual_node);
        write_tabela(output, actual_node);
        if(count % 50 == 0){
            fprintf(output, "%d\n\n", count);
        }
    }
    fprintf(output, "O PUZZLE foi resolvido em %d etapas, na durasao de %d seg.\n", count, time(NULL)-t);
    fclose(output);
}
