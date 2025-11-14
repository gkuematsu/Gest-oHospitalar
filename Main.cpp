#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "TadMedico.h"
#include "TadPaciente.h"

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
    
    printf("Inserindo 3 medicos...\n");
    lista = InserirMedico(lista);
    lista = InserirMedico(lista);
    lista = InserirMedico(lista);
    
    ExibirMedicos(lista);
    
    printf("Inserindo mais 2...\n");
    lista = InserirMedico(lista);
    lista = InserirMedico(lista);
    
    ExibirMedicos(lista);
    getche();
    return 0;
}


