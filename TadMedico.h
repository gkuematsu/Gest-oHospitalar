#ifndef TADMEDICO_H
#define TADMEDICO_H

#include <stdio.h>
#include <string.h>

#include "TadPaciente.h"

struct TpMedico{
	int id,ocupado;
	int tempomed;
    int total;
	TpMedico *prox,*ant;
	TpPaciente *pac;
};

void InicializarMed(TpMedico *med){
    med->ant = med->prox = NULL;
}

TpMedico *NovoMed(){
    TpMedico *med = new TpMedico;
    med->prox = NULL;
    med->ant = NULL;
    med->pac = NULL;
    med->id = 0;
    med->ocupado = 0;
    med->tempomed = 0;
    med->total = 0;
    
 
    return med;
}

TpMedico *InserirMedico(TpMedico *med){
    TpMedico *no = NovoMed();
    TpMedico *flag = med;
    int aux=1;
    while(flag != NULL){
        aux++;
        flag = flag->prox;
    }
    no->id = aux;
    if(med == NULL){
        med = no;
    }else{
        TpMedico *p = med;
        while(p->prox != NULL) //busca ultimo elemento
            p= p->prox;
        if(p->prox == NULL){
            no->ant = p;
            p->prox = no;
        }
    }
    return med;
}

void ReorganizaID(TpMedico *med){
    int aux = 1;
    TpMedico *p = med;
    while(p != NULL){
        p->id = aux++;
        p = p->prox;
    }
}

int MedicoOcupado(TpMedico *med, int id){
    TpMedico *lista = med;
    while(lista != NULL){
        if(lista->id == id){
            return lista->ocupado;
        }
        lista = lista->prox;
    }
    return 0;
}

TpMedico *RemoverMedico(TpMedico *med, int id){
    if(med->id == id){
        TpMedico *aux = med;
        med= med->prox;
        delete(aux);
    }else{
        TpMedico *p = med->prox;
        while(p != NULL && p->id != id)
            p=p->prox;

        if(p != NULL){
            if(p->prox == NULL){
                p->ant->prox = NULL;
                delete(p);
            }
            else{
            p->prox->ant = p->ant;
            p->ant->prox = p->prox;
            delete(p);
            }
        }
    }
    ReorganizaID(med);
    return med;
}

void ExibirMedicos(TpMedico *inicio){
    if(inicio == NULL){
        printf("Lista vazia.\n");
        return;
    }

    TpMedico *p = inicio;
    printf("Medicos na lista:\n");

    while(p != NULL){
        printf("ID: %d | Ocupado: %d \n", p->id, p->ocupado);
        p = p->prox;
    }

    printf("\n");
}

#endif
