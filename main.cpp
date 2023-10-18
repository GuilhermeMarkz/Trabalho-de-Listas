#include <iostream>
#include <locale.h>

#define TAM_MAX 512

using namespace std;

typedef struct{
    char nome[81], descricao[TAM_MAX];

}Times;

void inserirPal(Times* times);

int main(){
    setlocale(LC_ALL,"");
    int a = 0;
    char op;
    Times times[2];

    do{
        system("cls");
        printf("Dicionário de Frutas");
        printf("\n[1]Inserir palavra\n[2]Editar palavra\n[3]Excluir palavra\n[4]Pesquisar palavra\n[5]Palavras ordenandas\n[6]Lista de palavras\n[7]Sair\n:");
        scanf("%c", &op);

        switch(op){
        case '1':
            inserirPal(times); //Não funcional
            break;

        case '2':
            break;

        case '3':
            break;

        case '4':
            break;

        case '5':
            break;

        case '6':
            break;

        case '7':
            a = 1;
            break;
        default:
            system("cls");
            continue;
        }
    }while(a<1);

    return 0;
}

void inserirPal(Times* times){ //Inutil por enquanto
    system("cls");

    int a=0;

    do{
        a = 1;
        system("pause");
    }while(a<1);
}
