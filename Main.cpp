#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "TadMedico.h"
#include "TadPaciente.h"


TpMedico *Pausar(TpMedico *lista){
    char op;
    do{
        printf("-=-=-=-PAUSE-=-=-=-\n");
        printf("[A]- Adicionar mais um medico\n");
        printf("[B]- Remover um médico\n");
        printf("[C]- Continuar simulação\n");
        fflush(stdin);
        op = toupper(getch());
            switch(op){
                case 'A':
                    lista = InserirMedico(lista);
                    printf("Medico adicionado...");
                    Sleep(100);
                    break;
                case 'B':
                    int codremove;
                    printf("Digite o id para remoção: ");
                    scanf("%d",&codremove);
                    if(MedicoOcupado(lista,codremove))
                        printf("Medico %d em atendimento, não é possivel remove-lo\n",codremove);
                    else{
                        lista = RemoverMedico(lista,codremove);
                    }
                    break;
            }
        
    }while(op != 'C');
    return lista;
}

void LimpaTela() {
    for (int i = 10; i < 28; i++) {
        gotoxy(32, i);
        printf("                                                                             ");
    }
}

void Simular(int tempomax, int qtd, char arquivo[30]){
    TpDesc d;
    TpMedico *lista = NULL;
    InicializarDesc(d);
    
    for(int i = 0; i < qtd; i++){
        lista = InserirMedico(lista);
    }

    FILE *arq = fopen(arquivo, "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo!\n");
    }

    TpPaciente reg;
    int flag = 0;       
    int tempo = 0;      
    int fimArquivo = 0; 

    while(tempo < tempomax){
        // PAUSE
        if(kbhit()){
            lista = Pausar(lista);
            fflush(stdin);
        }

        // ARQUIVO E INSERCAO
        if(!fimArquivo){
            if(flag == 0){
                if(fscanf(arq, "%[^;];%d;%[^;];%[^;];%s\n",
                          reg.classificacao, &reg.tempo, reg.nome, reg.queixa, reg.data) == EOF){
                    fimArquivo = 1; 
                } else {
                    flag = 1; 
                }
            }

            if(flag == 1){
                int sorteio = rand() % 2;
                if(sorteio == 1){
                    TpPaciente *pac = NovoPaciente(reg);
                    if(strcmp(reg.classificacao, "Vermelho") == 0)
                        VermelhoFim(d, pac);
                    else if(strcmp(reg.classificacao, "Amarelo") == 0)
                        AmareloFim(d, pac);
                    else
                        VerdeFim(d, pac);

                    flag = 0; 
                }
            }
        }

        // MEDICOS
        TpMedico *m = lista;
        while(m != NULL){
            if(m->ocupado == 0){ // medico livre
                TpPaciente *pac = NULL;
                if(!VermelhoVazia(d))
                    pac = RetirarVerm(d);
                else if(!AmareloVazia(d))
                    pac = RetirarAmar(d);
                else if(!VerdeVazia(d))
                    pac = RetirarVerde(d);

                if(pac != NULL){
                    m->pac = pac;
                    m->ocupado = 1;
                    m->tempomed = pac->tempo; 
                    pac->tempochego = tempo;   
                }
            } else { 
                m->tempomed--;
                if(m->tempomed <= 0){ 
                    m->ocupado = 0;
                    delete(m->pac);
                    m->pac = NULL;
                }
            }
            m = m->prox;
        }

        // impressao
        LimpaTela();
        printf("Tempo: %d\n", tempo);
        printf("Fila Vermelha: %d | Amarela: %d | Verde: %d\n", d.qtdverm, d.qtdamar, d.qtdverde);
        ExibirMedicos(lista);
        printf("\n");

        Sleep(1000);
        tempo++;
    }

    fclose(arq);
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
	TpDesc d;
    TpMedico *lista = NULL;
    char arquivo[30] = "Arquivo.txt";
    Simular(100,3,arquivo);
    getche();
    return 0;
}


