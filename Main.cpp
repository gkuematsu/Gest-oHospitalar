#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "TadMedico.h"
#include "TadPaciente.h"

void LerArquivo(TpDesc &d,char arquivo[30]){
    FILE *arq = fopen(arquivo,"r");
    if(arq == NULL)
        printf("Erro ao abrir arquivo\n");
   else{
        TpPaciente reg;
        fscanf(arq, "%[^;];%d;%[^;];%[^;];%s\n",reg.classificacao,&reg.tempo,reg.nome,reg.queixa,reg.data);
        while(!feof(arq)){
            int sorteio = rand() % 2;
            if(sorteio == 1){
                TpPaciente *pac = NovoPaciente(reg);
                if(strcmp(reg.classificacao,"Vermelho") == 0)
                    VermelhoFim(d,pac);
                else if(strcmp(reg.classificacao,"Amarelo") == 0)
                    AmareloFim(d,pac);
                    else
                    VerdeFim(d,pac);
                fscanf(arq, "%[^;];%d;%[^;];%[^;];%s\n",reg.classificacao,&reg.tempo,reg.nome,reg.queixa,reg.data);  
            }     
        }
   }   
    fclose(arq);
}

void Simular(TpDesc &d, TpMedico *lista, char arquivo[30], int tempomax){
    FILE *arq = fopen(arquivo,"r");
    if(arq == NULL)
        printf("Erro ao abrir arquivo\n");
    for(int tempo = 0; tempo < tempomax ; tempo++){
    }
}

void LimpaTela() {
    for (int i = 10; i < 28; i++) {
        gotoxy(32, i);
        printf("                                                                             ");
    }
}

void Moldura(int CI, int LI, int CF, int LF, int Frente) {
    textcolor(Frente);
    gotoxy(CI, LI); printf("%c", 201);
    gotoxy(CF, LI); printf("%c", 187);
    gotoxy(CI, LF); printf("%c", 200);
    gotoxy(CF, LF); printf("%c", 188);
    for (int a = CI + 1; a < CF; a++) {
        gotoxy(a, LI); printf("%c", 205);
        gotoxy(a, LF); printf("%c", 205);
    }
    for (int a = LI + 1; a < LF; a++) {
        gotoxy(CI, a); printf("%c", 186);
        gotoxy(CF, a); printf("%c", 186);
    }
    textcolor(7);
}
void FormPrincipal(void) {
    system("cls");
    Moldura(10, 5, 110, 29, 15);
    Moldura(11, 6, 109, 8, 4);
    gotoxy(48, 7);
    printf("### HOSPITAL DO LEANDRAO ###");
    Moldura(11, 9, 30, 28, 4);
    Moldura(31, 9, 109, 28, 4);
}

int main(void){
    TpMedico *lista = NULL;
    char arquivo[30] = "Arquivo.txt";
    TpDesc d;

    InicializarDesc(d); 

    printf("Lendo arquivo...\n\n");
    LerArquivo(d, arquivo);

    printf("\n=== RESULTADOS ===\n");
    printf("Total Vermelho: %d\n", d.qtdverm);
    printf("Total Amarelo : %d\n", d.qtdamar);
    printf("Total Verde   : %d\n", d.qtdverde);
    printf("Total geral   : %d\n\n", d.totalpacientes);

    printf("\n--- FILA VERMELHA ---\n");
    ExibirFila(d.inicioverm);

    printf("\n--- FILA AMARELA ---\n");
    ExibirFila(d.inicioamar);

    printf("\n--- FILA VERDE ---\n");
    ExibirFila(d.inicioverde);
    getche();
    return 0;
}


