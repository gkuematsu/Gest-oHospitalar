#ifndef TADPACIENTE_H
#define TADPACIENTE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>


struct TpPaciente{
	char classificacao[50],nome[50],queixa[50],data[30]; 
	int tempo;
    int tempochego;
	TpPaciente *prox;
};

struct TpDesc{
	int qtdverm,qtdamar,qtdverde,totalpacientes;
	TpPaciente *inicioverm,*fimverm;
	TpPaciente *inicioamar,*fimamar;
	TpPaciente *inicioverde,*fimverde;
};

void InicializarDesc(TpDesc &d){
    d.qtdverm = d.qtdamar = d.qtdverde = d.totalpacientes = 0;
    d.inicioverm = d.fimverm = NULL;
    d.inicioamar = d.fimamar = NULL;
    d.inicioverde = d.fimverde = NULL;
}

char VermelhoVazia(TpDesc &d){
    return d.fimverm == NULL;
}

char AmareloVazia(TpDesc &d){
    return d.fimamar == NULL;
}

char VerdeVazia(TpDesc &d){
    return d.fimverde == NULL;
}

TpPaciente *NovoPaciente(TpPaciente pac){
    TpPaciente *no = new TpPaciente;
    no->prox = NULL;
    strcpy(no->classificacao,pac.classificacao);
    no->tempo = pac.tempo;
    strcpy(no->nome,pac.nome);
    strcpy(no->queixa,pac.queixa);
    strcpy(no->data,pac.data);
    no->tempochego = pac.tempochego;

    return no;
}

void VermelhoFim(TpDesc &d,TpPaciente *pac){
    if(d.inicioverm == NULL){
        d.inicioverm = pac;
        d.fimverm = pac;
    }else{
        d.fimverm ->prox = pac;
        d.fimverm = pac;
    }
    d.qtdverm++;
    d.totalpacientes++;
}

void AmareloFim(TpDesc &d,TpPaciente *pac){
    if(d.inicioamar == NULL){
        d.inicioamar = d.fimamar = pac;
    }else{
        d.fimamar->prox = pac;
        d.fimamar = pac;
    }
    d.qtdamar++;
    d.totalpacientes++;
}

void VerdeFim(TpDesc &d,TpPaciente *pac){
    if(d.inicioverde == NULL){
        d.inicioverde = d.fimverde = pac;
    }else{
        d.fimverde-> prox = pac;
        d.fimverde = pac;
    }
    d.qtdverde++;
    d.totalpacientes++;
}

TpPaciente *RetirarVerm(TpDesc &d){
    TpPaciente *aux;
    if(!VermelhoVazia(d)){
        aux = d.inicioverm;
        d.inicioverm = aux->prox;
        if(d.inicioverm == NULL)
            d.fimverm = NULL;
        d.qtdverm--;
    }else
        printf("Nenhum elemento pra retirar.");

    return aux;
}

TpPaciente *RetirarAmar(TpDesc &d){
    TpPaciente *aux;
    if(!AmareloVazia(d)){
        aux = d.inicioamar;
        d.inicioamar= aux->prox;
        if(d.inicioamar == NULL)
            d.fimamar = NULL;
        d.qtdamar--;
    }else{
        printf("Nenhum elemento para retirar.\n");
    }
    return aux;
}


TpPaciente *RetirarVerde(TpDesc &d){
    TpPaciente *aux;
    if(!VerdeVazia(d)){
        aux = d.inicioverde;
        d.inicioverde= aux->prox;
        if(d.inicioverde == NULL)
            d.fimverde = NULL;
        d.qtdverde--;
    }else{
        printf("Nenhum elemento para retirar.\n");
    }
    return aux;
}

void ExibirFila(TpPaciente *inicio){
    TpPaciente *p = inicio;
    while(p != NULL){
        printf("Classificação: %s | Nome: %s | Tempo: %d | Queixa: %s | Data: %s\n",
               p->classificacao, p->nome, p->tempo, p->queixa, p->data);
        p = p->prox;
    }
}

#endif