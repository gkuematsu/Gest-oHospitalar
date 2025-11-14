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

TpMedico *NovoMed(){
    int auxid = 1;
    TpMedico *med = new TpMedico;
    med->prox = NULL;
    med->ant = NULL;
    med->pac = NULL;
    med->id = auxid++;
    med->ocupado = 0;
    med->tempomed = 0;
    med->total = 0;
    
    return med;
}

TpMedico *InserirMedico(TpMedico *med){
    TpMedico *no = NovoMed();
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

void ExibirMedicos(TpMedico *inicio){
    if(inicio == NULL){
        printf("Lista vazia.\n");
        return;
    }

    TpMedico *p = inicio;
    printf("Medicos na lista:\n");

    while(p != NULL){
        printf("ID: %d | Ocupado: %d | Total Atendidos: %d\n",
                p->id, p->ocupado, p->total);
        p = p->prox;
    }

    printf("\n");
}

#endif
