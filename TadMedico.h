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

struct TpEstatisticas{
    int contverm, contamar, contverde;
    int somaverm, somaamar, somaverde;
    int qtdverm, qtdamar, qtdverde;
};

void InicializarMed(TpMedico *med){
    med->ant = med->prox = NULL;
}

void InicializarEst(TpEstatisticas est){
    est.contverm = est.contamar = est.contverde = 0;
    est.somaverm = est.somaamar = est.somaverde = 0;
    est.qtdverm = est.qtdamar = est.qtdverde = 0;
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
    int i = 10;
    if(inicio == NULL){
        gotoxy(33,i); textcolor(13); printf("Lista vazia.\n");
        return;
    }

    TpMedico *p = inicio;
    gotoxy(33,i++);textcolor(9);printf("Medicos na lista:\n");
    gotoxy(33, i++);textcolor(11); printf("ID  |   STATUS   | PACIENTE\n");
    while(p != NULL){
     
        gotoxy(33,i++); textcolor(13); printf("%-3d |", p->id);
        if (p->ocupado == 1)
            printf("%-9s | ", "OCUPADO");
        else
            printf("%-9s | ", "LIVRE");
        if (p->ocupado == 1 && p->pac != NULL)
            printf("%s", p->pac->nome);
        else
            printf("Nenhum");

        p = p->prox;
    }

}

#endif
