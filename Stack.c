#include <stdio.h>
#include <stdlib.h>

typedef struct fila Fila;
typedef struct elemento Elem;
typedef struct dados Dado;

struct fila{
	struct elemento* inicio;
	struct elemento* final;
};

struct dados{
	char chr;
};

struct elemento{
	Dado info;
	struct elemento *prox;
};

Fila* cria_fila(){
	Fila* fi = (Fila*) malloc(sizeof(Fila));
	if(fi != NULL){
		fi->inicio = NULL;
		fi->final = NULL;
	}
	return fi;
}

void libera_fila(Fila* fi){
	if(fi != NULL){
		Elem *no;
		while(fi->inicio != NULL){
			no = fi->inicio;
			printf("%c ", no->info.chr); /*Os primeiros elementos inseridos foram os ultimos retirados, ou seja, uma fila*/
			fi->inicio = no->prox;
			free(no);
		}
		printf("\n");
		free(fi);
	}
}

void insere_fila(Fila* fi, Dado* info){
	if(fi == NULL) return;
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) return;
	no->info = *info;
	no->prox = NULL;
	if (fi->final == NULL){
		fi->inicio = no;
	} else {
		fi->final->prox = no;
	}
	fi->final = no;
}

void remove_fila(Fila* fi){
	if ((fi == NULL) || (fi->inicio == NULL)) return;
	Elem *no = fi->inicio;
	fi->inicio = fi->inicio->prox;
	if (fi->inicio == NULL) fi->final = NULL;
	free(no);
}

void consulta_fila(Fila* fi, Dado *info){
	if ((fi == NULL) || (fi->inicio == NULL)) return;
	*info = fi->inicio->info;
}

void transfere_fila(int *n, Dado *info, Fila* fi1, Fila* fi2){
	consulta_fila(fi1, info);
	insere_fila(fi2, info);
	remove_fila(fi1);
	(*n)++;
}

void devolve_fila(int *n, Dado *info, Fila* fi1, Fila* fi2){
	int i;
	for (i=0;i<(*n);i++){
		 	consulta_fila(fi2, info);
		 	insere_fila(fi1, info);
			remove_fila(fi2);
		}
	(*n)=0;
}

int main(){

	Fila *fi1,*fi2;
	Dado info, scan, busca;
	int n=0,pos=-1;
	
	fi1 = cria_fila();
 	fi2 = cria_fila();
 	
 	printf("Type a chain of characteres:\n");
 	
 	/*Insere pilha*/
 	while(1){
	 	scanf("%c", &scan.chr);
	 	if(scan.chr == '\n') break;
	 	while(fi1->inicio != NULL){
	 		transfere_fila(&n, &info, fi1, fi2);
	 	}
	 	insere_fila(fi1, &scan);
	 	devolve_fila(&n, &info, fi1, fi2);
 	}
 	
 	/*Busca pilha por conteúdo*/
 	printf("Which element are you looking for?\n");
 	scanf("%c", &busca.chr);
	while((fi1->inicio != NULL)){
		transfere_fila(&n, &info, fi1, fi2);
	 	if(busca.chr == info.chr) pos = n;
	 }
	 if(pos == -1){
		printf("The element doesn't exist\n");
	} else {
		printf("The last position found is %d\n", pos);
	}
	devolve_fila(&n, &info, fi1, fi2);
	
	/*Busca pilha por posição*/
	printf("Which position are you looking for?\n");
	scanf("%d", &pos);
	if(pos == 1){
		consulta_fila(fi1, &info);
		printf("The element is %c\n", info.chr);
	} else {
		while(fi1->inicio != NULL){
	 		transfere_fila(&n, &info, fi1, fi2);
	 		if (n == pos) busca.chr = info.chr;
	 	}
	 	if((n < pos) || (pos <= 0)){
			printf("The position doesn't exist\n");
		} else {
			printf("The element is %c\n", busca.chr);
		}
	 	devolve_fila(&n, &info, fi1, fi2);
	}
 	
 	printf("The order of the 'stack' is: ");
 	libera_fila(fi1);
 	libera_fila(fi2);

	return 0;
}



