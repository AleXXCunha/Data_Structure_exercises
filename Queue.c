#include <stdio.h>
#include <stdlib.h>

typedef struct elemento* Pilha;
typedef struct elemento Elem;
typedef struct dados Dado;

struct dados{
	char chr;
};

struct elemento{
	Dado info;
	struct elemento *prox;
};

Pilha* cria_pilha() {
	Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
	if(pi != NULL)
		*pi = NULL;
	return pi;
}

void libera_pilha(Pilha *pi){
	if(pi != NULL){
		Elem* no;
		while((*pi) != NULL){
			no = *pi;
			printf("%c ", no->info.chr); /*Os primeiros elementos inseridos foram os primeiros retirados, ou seja, uma fila*/ 
			*pi = (*pi)->prox;			
			free(no);
		}
		printf("\n");
		free(pi);
	}
}

void insere_pilha(Pilha* pi, Dado *info){
	if(pi == NULL) return;
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return;
	no->info = *info;
	no->prox = (*pi);
	*pi = no;
}

void remove_pilha(Pilha* pi){
	if ((pi == NULL) || ((*pi) == NULL)) return;
	Elem *no = *pi;
	*pi = no->prox;
	free(no);
}

void consulta_pilha(Pilha* pi, Dado *info){
	if ((pi == NULL) || ((*pi) == NULL)) return;
	*info = (*pi)->info;
}

void devolve_pilha(int *n, Dado *info, Pilha* pi1, Pilha* pi2){
	int i;
	for (i=0;i<(*n);i++){
		 	consulta_pilha(pi2, info);
		 	insere_pilha(pi1, info);
			remove_pilha(pi2);
		}
	(*n)=0;
}

void transfere_pilha(int *n, Dado *info, Pilha* pi1, Pilha* pi2){
	consulta_pilha(pi1, info);
	insere_pilha(pi2, info);
	remove_pilha(pi1);
	(*n)++;
}

int main() {

	Pilha *pi1,*pi2;
	Dado info, scan, busca;
	int n=0,pos;

 	pi1 = cria_pilha();
 	pi2 = cria_pilha();
 	
 	printf("Type a chain of characteres:\n");
 	
 	/*Insere fila*/
 	while(1){
	 	scanf("%c", &scan.chr);
	 	if(scan.chr == '\n') break;
	 	while((*pi1) != NULL){
	 		transfere_pilha(&n, &info, pi1, pi2);
	 	}
	 	insere_pilha(pi1, &scan);
	 	devolve_pilha(&n, &info, pi1, pi2);
 	}
 	
 	/*Busca fila por conteúdo*/
 	printf("Which element are you looking for?\n");
 	scanf("%c", &busca.chr);
 	if(busca.chr == info.chr){
 		printf("The first position found is 1\n");
 	} else {
	 	while(((*pi1) != NULL) && busca.chr != info.chr){
	 		transfere_pilha(&n, &info, pi1, pi2);
	 	}
	 	if(busca.chr != info.chr){
			printf("The element doesn't exist\n");
		} else {
			printf("The first position found is %d\n", n);
		}
	 	devolve_pilha(&n, &info, pi1, pi2);
	}
	
	/*Busca fila por posição*/
	printf("Which position are you looking for?\n");
	scanf("%d", &pos);
	if(pos == 1){
		consulta_pilha(pi1, &info);
		printf("The element is %c\n", info.chr);
	} else {
		while(((*pi1) != NULL) && n != pos){
	 		transfere_pilha(&n, &info, pi1, pi2);
	 	}
	 	if((n != pos) || (n == 0)){
			printf("The position doesn't exist\n");
		} else {
			printf("The element is %c\n", info.chr);
		}
	 	devolve_pilha(&n, &info, pi1, pi2);
	}
 	
 	printf("The order of the 'queue' is: ");
 	libera_pilha(pi1);
 	libera_pilha(pi2);
	return 0;
}
