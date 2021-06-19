#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore {
	char info;
	struct arvore *esq;
	struct arvore *dir;
} Arvore;

Arvore *cria_arv_vazia(void);
Arvore *arv_constroi(char c, Arvore *e, Arvore *d);
bool verifica_arv_vazia(Arvore *a);
Arvore *arv_libera(Arvore *a);
void arv_imprime(Arvore *a);
bool eh_espelho(Arvore *arv_a, Arvore *arv_b);
Arvore *cria_espelho(Arvore *a);

Arvore *cria_arv_vazia(void){
	return NULL;
}

Arvore *arv_constroi (char c, Arvore *e, Arvore *d){
	Arvore *a = (Arvore*) malloc(sizeof(Arvore));
	a->info=c;
	a->esq=e;
	a->dir=d;
	return a;
}

bool verifica_arv_vazia(Arvore *a){
	return (a == NULL);
}

Arvore *arv_libera(Arvore *a){
	if(!verifica_arv_vazia(a)){
		arv_libera(a->esq);
		arv_libera(a->dir);
		free(a);
	}
	return NULL;
}

void arv_imprime(Arvore *a){
	if(!a) return;

	printf("%c", a->info);
	arv_imprime(a->esq);
	arv_imprime(a->dir);
}

bool eh_espelho(Arvore *a, Arvore *b){
	if(!a || !b) return 0;

//	printf("a:%c b:%c \n", a->info, b->info );
	return !(a->info != b->info ||eh_espelho(a->esq, b->dir) || eh_espelho(a->dir, b->esq));
}

Arvore *cria_espelho(Arvore *a){
	Arvore *e, *d;
	if(!a) return (cria_arv_vazia());
	e = cria_espelho(a->dir);
	d = cria_espelho(a->esq);

	return (arv_constroi(a->info,e,d));
}
void main(){
	Arvore *a, *a1, *a2, *a3, *a4, *a5,
	       *b, *b1, *b2, *b3, *b4, *b5,
	       *c;
	
	//a1 = arv_constroi('j',cria_arv_vazia(),cria_arv_vazia());
	a1 = arv_constroi('d',cria_arv_vazia(),cria_arv_vazia());
	a2 = arv_constroi('b',cria_arv_vazia(),a1);
	a3 = arv_constroi('e',cria_arv_vazia(),cria_arv_vazia());
	a4 = arv_constroi('f',cria_arv_vazia(),cria_arv_vazia());
	a5 = arv_constroi('c',a3,a4);
	a  = arv_constroi('a',a2,a5);
	
	b1 = arv_constroi('d', cria_arv_vazia(),cria_arv_vazia());
	b2 = arv_constroi('b', b1,cria_arv_vazia());
	b3 = arv_constroi('e', cria_arv_vazia(),cria_arv_vazia());
	b4 = arv_constroi('f', cria_arv_vazia(),cria_arv_vazia());
	b5 = arv_constroi('c', b4,b3);
	b = arv_constroi('a', b5, b2);

	arv_imprime(a);
	printf("\n");
	arv_imprime(b);
	printf("\n");
	c = cria_espelho(a);
	arv_imprime(c);
	
	printf("\neh espelho? %d\n", eh_espelho(a,b));

	a = arv_libera(a);
	b = arv_libera(b);
	c = arv_libera(c);
}
