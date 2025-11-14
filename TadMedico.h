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

TpMedico *NovoMed(int id){
    TpMedico *med = new TpMedico;
    med->prox = NULL;
    med->ant = NULL;
    med->pac = NULL;
    med->id = id;
    med->ocupado = 0;
    med->tempomed = 0;
    med->total = 0;
    
    return med;
}



#endif
