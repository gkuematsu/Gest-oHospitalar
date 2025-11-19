#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "TadMedico.h"
#include "TadPaciente.h"

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

void LimpaPausa(){
    gotoxy(13, 20);printf("           ");
    gotoxy(13, 22);printf("               ");
    gotoxy(13, 23);printf("               ");
    gotoxy(13, 24);printf("               ");
}
int ContaMedicos(TpMedico *lista){
    int qtd = 0;
    while(lista != NULL){
        qtd++;
        lista= lista->prox;
    }
    return qtd;
}
TpMedico *Pausar(TpMedico *lista){
    char op;
    do{
        textcolor(1); gotoxy(13, 20);printf("-PAUSE-");
        textcolor(2); gotoxy(13, 22);printf("[A]- Adicionar");
        textcolor(12); gotoxy(13, 23);printf("[B]- Remover");
        textcolor(14); gotoxy(13, 24);printf("[C]- Continuar");
        fflush(stdin);
        op = toupper(getch());
            switch(op){
                case 'A':
                    if(ContaMedicos(lista) >= 15){
                        textcolor(4);gotoxy(66,13);printf("Nao e possivel adicionar mais!(max 15)");
                        Sleep(100);
                    }else{
                        lista = InserirMedico(lista);
                        textcolor(10); gotoxy(85, 13);printf("Medico adicionado...");
                        Sleep(100);
                    }
                    break;
                case 'B':
                    int codremove;
                    textcolor(4); gotoxy(79, 13);
                    printf("Digite o id para remocao: ");
                    scanf("%d",&codremove);
                    textcolor(4); gotoxy(66, 24);
                    if(MedicoOcupado(lista,codremove))
                        printf("Medico %d atendendo,nao e possivel remover",codremove);
                    else{
                        textcolor(10); gotoxy(66, 26);
                        printf("Removido com sucesso!");
                        lista = RemoverMedico(lista,codremove);
                        Sleep(100);
                    }
                    break;
                case 'C':
                    LimpaPausa();

            }
        
    }while(op != 'C');
    return lista;
}

float Calculo(float soma, int qtd){
    if(qtd == 0) 
        return 0.0;
    return soma / qtd;
}

void GerarRelatorio(TpMedico *lista,TpDesc d, TpEstatisticas est){
    system("cls");
    Moldura(20, 5, 100, 30, 15);
    int x = 22;int y = 7;
    gotoxy(x, y); textcolor(1); printf("========= RELATORIO FINAL =========");

    y += 2;
    gotoxy(x, y); textcolor(15); printf("1) Pacientes tratados por classificacao:");
    y++;
    gotoxy(x, y); textcolor(4);  printf(" - Vermelho: %d", est.contverm);
    y++;
    gotoxy(x, y); textcolor(14); printf(" - Amarelo : %d", est.contamar);
    y++;
    gotoxy(x, y); textcolor(10); printf(" - Verde   : %d", est.contverde);
    y += 2;
    gotoxy(x, y); textcolor(15); printf("2) Tempo medio de espera:");
    y++;
    gotoxy(x, y); textcolor(4);  printf(" - Vermelho: %.2f", Calculo(est.somaverm, est.qtdverm));
    y++;
    gotoxy(x, y); textcolor(14); printf(" - Amarelo : %.2f", Calculo(est.somaamar, est.qtdamar));
    y++;
    gotoxy(x, y); textcolor(10); printf(" - Verde   : %.2f", Calculo(est.somaverde, est.qtdverde));

    y += 2;
    gotoxy(x, y); textcolor(15); printf("3) Pacientes NAO tratados:");
    y++;
    gotoxy(x, y); textcolor(4);  printf(" - Vermelho: %d", d.qtdverm);
    y++;
    gotoxy(x, y); textcolor(14); printf(" - Amarelo : %d", d.qtdamar);
    y++;
    gotoxy(x, y); textcolor(10); printf(" - Verde   : %d", d.qtdverde);
    Sleep(3000);
    system("cls");
    Moldura(20, 5, 100, 30, 15);
    x = 22; y = 7;
    gotoxy(x, y); textcolor(15); printf("4) Status dos medicos:");
    TpMedico *m = lista;
    while (m != NULL) {
        y++;
        gotoxy(x, y); textcolor(11);
        printf(" Médico %d - ", m->id);
        if (m->ocupado)
            printf("OCUPADO");
        else
            printf("LIVRE");
        printf(" | Tratou %d pacientes.\n", m->total);
        m = m->prox;
    }
}

void ExibirPainel(int tempo, TpDesc d){
    textcolor(1); gotoxy(13, 10);
    printf("Tempo: %d", tempo);

    gotoxy(13, 12); textcolor(15);
    printf("Filas:");

    gotoxy(13, 14); textcolor(4);
    printf("Vermelha: %d", d.qtdverm);

    gotoxy(13, 15); textcolor(14);
    printf("Amarela : %d", d.qtdamar);

    gotoxy(13, 16); textcolor(10);
    printf("Verde   : %d", d.qtdverde);

    textcolor(7);
}

void LimpaTela() {
    for (int i = 10; i < 28; i++) {
        gotoxy(32, i);
        printf("                                                                             ");
    }
}

void Simular(int tempomax, int qtd, char arquivo[30]){
    TpDesc d;
    TpEstatisticas est;
    TpMedico *lista = NULL;
    InicializarDesc(d);
    InicializarEst(est);
    
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
            getch();
            lista = Pausar(lista);
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
                int sorteio = rand() % 2; // sim ou nao somente 
                if(sorteio == 1){
                    TpPaciente *pac = NovoPaciente(reg);
                    if(strcmp(reg.classificacao, "Vermelho") == 0)
                        VermelhoFim(d, pac);
                    else if(strcmp(reg.classificacao, "Amarelo") == 0)
                        AmareloFim(d, pac);
                    else
                        VerdeFim(d, pac);
                    
                    pac->tempochego = tempo;
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
                    int espera = tempo - pac->tempochego;
                    if(strcmp(pac->classificacao,"Vermelho") == 0){
                        est.somaverm += espera;
                        est.qtdverm++;
                    }else if(strcmp(pac->classificacao,"Amarelo") == 0){
                        est.somaamar += espera;
                        est.qtdamar++;
                    }else{
                        est.somaverde += espera;
                        est.qtdverde++;
                    }
                }
            } else { 
                m->tempomed--;
                if(m->tempomed <= 0){ 
                    if(strcmp(m->pac->classificacao,"Vermelho") == 0)
                        est.contverm++;
                    else if(strcmp(m->pac->classificacao,"Amarelo") == 0)
                        est.contamar++;
                    else
                        est.contverde++;

                    m->total++;
                    m->ocupado = 0;
                    delete(m->pac);
                    m->pac = NULL;
                }
            }
            m = m->prox;
        }

        // impressao
        LimpaTela();
        gotoxy(63,27); textcolor(9);
        printf("Para pausar, pressione qualquer tecla");
        ExibirPainel(tempo,d);
        ExibirMedicos(lista);
        printf("\n");

        Sleep(1000);
        tempo++;
    }

    fclose(arq);
    GerarRelatorio(lista,d,est);
}


int main(void){
    FormPrincipal();
    gotoxy(50,18); textcolor(2);
    printf("GABRIEL KENJI UEMATSU - 262320290");
    Sleep(1000);
    int qtd,tempo;
	TpDesc d;
    TpMedico *lista = NULL;
    FormPrincipal();
    char arquivo[30] = "Arquivo.txt";
    gotoxy(33,10); textcolor(2);
    printf("Digite a quantidade de medicos (1 a 15): ");
    scanf("%d",&qtd);
    while(qtd <= 0 || qtd > 15){
        gotoxy(33,13); textcolor(4);
        printf("Quantidade Invalida, tente novamente!");
        Sleep(1000);
        FormPrincipal();
        gotoxy(33,10); textcolor(2);
        printf("Digite a quantidade de medicos (1 a 15): ");
        scanf("%d",&qtd);
    }

    FormPrincipal();
    gotoxy(33,10); textcolor(14);
    printf("Digite o tempo em segundos: ");
    scanf("%d",&tempo);
    while(tempo <= 0){
        gotoxy(33,13); textcolor(4);
        printf("Quantidade Invalida, tente novamente!");
        Sleep(1000);
        FormPrincipal();
        gotoxy(33,10); textcolor(14);
        printf("Digite o tempo em segundos: ");
        scanf("%d",&tempo);
    }
    system("cls");
    FormPrincipal();
    Simular(tempo,qtd,arquivo); 
    getche();
    return 0;
}


