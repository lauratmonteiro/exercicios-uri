#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int c;
    struct lista* prox;
}Lista;

typedef struct tabela_hash{
    Lista** tabela; //array de ponteiros p lista
}Tabela_hash;

int hash(int c, int m){
    return c % m;
}

Lista* insere_chave(Lista *l, int chave){
    Lista *aux = l;
    Lista *ant = l;

    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->c = chave;
    novo->prox = NULL;

    if(l == NULL){
        l = novo;
        return l;
    }

    while(1){
        ant = aux;
        aux = aux->prox;

        if(aux == NULL){
            ant->prox = novo;
            break;
        }
    }

    return l;

}

void imprime_lista(Lista* l){
    Lista *aux = l;

    while(aux != NULL){
        printf("%d -> ", aux->c);
        aux = aux->prox;
    }
    printf("\\");
}

void imprime_tabela(Tabela_hash* t, int m){
    for(int i = 0; i<m; i++){
        printf("%d -> ", i);
        imprime_lista(t->tabela[i]);
    }
    printf("\n");
}

void insere_hash(Tabela_hash* t, int chave, int m){
    int h = hash(chave, m);
    
    t->tabela[h] = insere_chave(t->tabela[h], chave);

}

void free_lista(Lista* l){
    if(l == NULL) return;

    free_lista(l->prox);
    free(l);

}

void free_tabela(Tabela_hash* t, int m){
    for(int i = 0; i<m; i++){
        free_lista(t->tabela[i]);
    }
    free(t->tabela);
    free(t);
}

int main(){
    int casos;
    scanf(" %d", &casos);

    int m, c;
    int chave;

    for(int i = 0; i<casos; i++){
        scanf(" %d %d", &m, &c);

        Tabela_hash* t = (Tabela_hash*)malloc(sizeof(Tabela_hash));
        t->tabela = (Lista**)malloc(sizeof(Lista*)*m);

        for(int j = 0; j<m; j++){
            t->tabela[j] = NULL;
        }

        for(int j = 0; j<c; j++){
            scanf(" %d", &chave);
            insere_hash(t, chave, m);
        }
        imprime_tabela(t, m);

        if(i+1 != casos){
            printf("\n");
        }

        free_tabela(t, m);
    }


}