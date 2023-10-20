#include <iostream>
#include <locale.h>

#define TAM_MAX 512

int VariConEquipe = 0;

using namespace std;

typedef struct{
    char nome[81], descricao[TAM_MAX];

}Equipe;

void inserirPal(Equipe* equipe);
void pesquisarPal(Equipe* equipe);
void excluirPal(Equipe* equipe);
void editarPal(Equipe* equipe);

int main(){
    setlocale(LC_ALL,"");
    int a = 0;
    char op;
    Equipe equipe[2];

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
            editarPal(equipe);
            break;

        case '3':
            excluirPal(equipe);
            break;

        case '4':
            pesquisarPal(times);
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

void inserirPal(Equipe* equipe){ //Inutil por enquanto
    system("cls");

    int a=0;

    //Nessa parte insere na Lista

    do{
        a = 1;
        system("pause");
    }while(a<1);
}
void pesquisarPal(Equipe* equipe){
    int a = 0;
    char equipeEntrada[TAM_MAX];

    system("cls");

    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", equipeEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}

void excluirPal(Equipe* equipe){
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", equipeEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}

void editarPal(Equipe* equipe){
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", equipeEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}
