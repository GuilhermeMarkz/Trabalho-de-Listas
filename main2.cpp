#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

/*
Lista de Letras que, por sua vez, possuem uma lista de seus filhos.
*/

#define TAM_DES_MAX 1024
#define TAM_PAL_MAX 128

int VariConPalavra = 0;

FILE* pont_arq;

using namespace std;

typedef struct Letra Letra;
typedef struct Palavra Palavra;
typedef struct Palavra_ptr Palavra_ptr;

struct Palavra_ptr
{
    short relevancia;
    Palavra *palavra;
    Palavra_ptr *next;
};

Palavra_ptr PPalInicio;

struct Palavra
{
	char nome[TAM_PAL_MAX], descricao[TAM_DES_MAX];
	Palavra *next;
};

struct Letra
{
	char letra;
	Letra *next, *prev;
	Palavra PalavraInicio, *palavraAux, *palavraAnt;
};

Letra letraInicio, *letraAux;

//Funções de Arquivos
void salvar_lista_arquivos(); // Salva as alterações do sistema na memória secundária
void carregar_lista_na_RAM();

//Funções de controle da lista de Letras
Letra* new_Letra(const char letra);
Letra* insert_Letra(const char letra);
void remove_Letra(Letra* Letra);

Letra* retorna_Letra_Palavra(Palavra* Palavra); // Retorna o ponteiro de uma letra conforme a primeira letra do nome de uma palavra
void ordenar_letras(); // Ordena a lista de letras por ordem alfabética

//Funções de controle da lista de Palavras
int num_substring_em_string(const char string[], const char substring[]); // Retorna o número de ocorrências de uma substring dentro de uma string
int compara_palavras( /*1*/Palavra* palAux, /*2*/Palavra* pPalavra);
Palavra* new_Palavra(const char nome[], const char descricao[]);

Palavra* retorna_Palavra_bynome(const char nome[]); // Retorna o ponteiro da palavra pela string de seu nome
Palavra* insert_Palavra(const char nome[], const char descricao[]); // Insere uma nova palavra na lista de uma letra
void ordenar_palavras(const char letra);  // Ordena todas as palavras de uma letra
void remove_Palavra(Palavra* Palavra); // Remove uma palavra da lista

//Funções extras
void listar_dicionario(); // Lista as palavras do dicionário na forma de índice remisso
void toupper_str(char* str); // Converte os chars de uma string para forma maiúscula
int strcont( /*1*/const char* string, /*2*/const char* substring); //Analisa se a string contém a substring

void gotoxy(unsigned short x, unsigned short y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){(SHORT)(x-1),(SHORT)(y-1)});
}

void inserirPal();
void pesquisarPal();
void excluirPal();
void editarPal();

void ordenarPal();
void pesquisaRelevancia();

int main(){
    setlocale(LC_ALL,"");
    int a = 0;
    char op;

    carregar_lista_na_RAM();

    do{
        system("cls");

        printf("*********************************************\n");
        printf("*******Dicionário de Times de Futebol********\n");
        printf("*******==============================********\n");
        printf("*\n*[1]Inserir palavra\n*[2]Editar palavra\n*[3]Excluir palavra\n*[4]Pesquisar palavra\n*[5]Ordenar dicionário\n*[6]Lista de palavras\n"
        "*[7]Pesquisa por Relevância\n*[8]Salvar e Sair\n*\n");
        printf("*******Resp:                         ********\n");
        printf("*********************************************\n");

        for (int i = 0; i < 10; i++)
        {
            gotoxy(45, 4+i);
            printf("*");
        }

        gotoxy(14,14);

        scanf("%c", &op);

        switch(op){
        case '1':
            fflush(stdin);
            inserirPal();
            break;

        case '2':
            fflush(stdin);
            editarPal();
            break;

        case '3':
            fflush(stdin);
            excluirPal();
            break;

        case '4':
            fflush(stdin);
            pesquisarPal();
            break;

        case '5':
            fflush(stdin);
            ordenarPal();
            break;

        case '6':
            fflush(stdin);
            listar_dicionario();
            break;

        case '7':
            fflush(stdin);
            pesquisaRelevancia();
            break;

        case '8':
            salvar_lista_arquivos();

            printf("> As alterações foram salvas!\n>> Sair do sistema? [0]Sim [Outra tecla]Não\n: ");
            fflush(stdin);
            scanf("%c", &op);

            if (op == '0')
            {
                a = 1;
            }


            break;
        default:
            fflush(stdin);
            continue;
        }
    }while(a<1);


    return 0;
}

void inserirPal(){
    system("cls");

    char nomePalavra[TAM_PAL_MAX], descPalavra[TAM_DES_MAX];

    int a=0;

    do{
    system("cls");
    printf("\n******************************INSERÇÃO******************************\n");
    printf("\n********************************************************************\n");
    printf(  "* > Digite o nome do time:                                         *\n");
    printf(  "********************* OBS: não use acentos! ************************\n");
    gotoxy(28, 5);
    fflush(stdin);
    scanf("%[^\n]", nomePalavra);
    fflush(stdin);
    if (nomePalavra[0] == '\0') ;
    gotoxy(1, 7);
    printf("\n > Descreva o time:");
    fflush(stdin);
    scanf("%[^\n]", descPalavra);
    fflush(stdin);

    nomePalavra[0] = toupper(nomePalavra[0]);
    insert_Palavra(nomePalavra, descPalavra);

    printf("\n\nRegistrar mais uma palavra? [1]Não [0]Sim\n->");
    scanf("%d", &a);

    }while(a<1);
    system("pause");
}

void pesquisarPal(){
    int a = 0;

    char PalavraEntrada[TAM_PAL_MAX];

    do{
        system("cls");
        printf("\n*******************************PESQUISA************/****************\n");
        printf("\n********************************************************************\n");
        printf(  "* > Digite o nome do time:                                         *\n");
        printf(  "********************************************************************\n");
        gotoxy(28, 5);
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);
        gotoxy(1, 7);

        Palavra* palavra;
        palavra = retorna_Palavra_bynome(PalavraEntrada);
        if(palavra == NULL){
            printf("\n\n > Palavra não encontrada!\n");

        }
        else{
            printf("Nome da palavra: %s\n", palavra->nome);
            printf("Descrição: %s\n", palavra->descricao);
        }


        printf("Continuar pesquisando? Sim[0] Não[1]\n->");
        scanf("%d", &a);

    }while(a<1);
}

void excluirPal(){
	int a = 0;
	char PalavraEntrada[TAM_PAL_MAX];
    do{
        system("cls");
        printf("\n***************************EXCLUSÃO*********************************\n");
        printf("\n********************************************************************\n");
        printf(  "* > Digite o nome do time:                                         *\n");
        printf(  "********************************************************************\n");
        gotoxy(28, 5);
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);
        gotoxy(1, 7);

        Palavra* palavra;
        palavra = retorna_Palavra_bynome(PalavraEntrada);
        if(palavra == NULL){
            printf("\n > Palavra não encontrada!\n");
        }
        else{
            printf("\n********************************************************************\n");
            printf(  "* >                                                                *\n");
            printf(  "*****************************DESCRIÇÃO******************************\n");
            gotoxy(5, 9);
            printf("Palavra: %s\n", palavra->nome);
            gotoxy(1, 11);
            printf("%s\n\n", palavra->descricao);
            printf("Remover time? Sim[0] Não[1]\n->");
            scanf("%d", &a);
            if(a==0){
                remove_Palavra(palavra);
            }
        }

        printf("Remover mais um time? Sim[0] Não[1]\n->");
        scanf("%d", &a);

    }while(a<1);
}

void editarPal(){

	int a = 0;
	char PalavraEntrada[TAM_PAL_MAX], tempDescricaoPalavra[TAM_DES_MAX];
    do{
        system("cls");
        printf("\n*****************************EDIÇÃO*********************************\n");
        printf("\n********************************************************************\n");
        printf(  "* > Digite o nome do time:                                         *\n");
        printf(  "********************************************************************\n");
        gotoxy(28, 5);
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        Palavra* palavra = retorna_Palavra_bynome(PalavraEntrada);
        if(palavra==NULL){
            printf("\n\n > Palavra não encontrada!\n");
        }else{
            printf("\n********************************************************************\n");
            printf(  "* >                                                                *\n");
            printf(  "*****************************DESCRIÇÃO******************************\n");
            gotoxy(5, 8);
            printf("Palavra: %s\n", palavra->nome);
            gotoxy(1, 10);
            printf("%s\n\n", palavra->descricao);
            printf("O que deseja editar: Nome[1]\tDescrição[2]\n:");
            scanf("%d", &a);
            switch(a){
                case 1:
                    printf("Digite o nome:");
                    fflush(stdin);
                    scanf("%[^\n]", PalavraEntrada);
                    fflush(stdin);

                    PalavraEntrada[0] = toupper(PalavraEntrada[0]);

                    if (palavra->nome[0] != PalavraEntrada[0])
                    {
                        strcpy(tempDescricaoPalavra, palavra->descricao);
                        remove_Palavra(palavra);
                        insert_Palavra(PalavraEntrada, tempDescricaoPalavra);
                    }
                    else
                    {
                        strcpy(palavra->nome, PalavraEntrada);
                    }


                    break;
                case 2:
                    printf("Digite a descrição:");
                    fflush(stdin);
                    scanf("%[^\n]", palavra->descricao);
                    fflush(stdin);
                    break;
                }
        }
        printf("Editar mais um time? Sim[0] Não[1]\n->");
        scanf("%d", &a);

    }while(a<1);
}

void ordenarPal()
{
    ordenar_letras();

    letraAux = letraInicio.next;
    while(letraAux)
    {
        ordenar_palavras(letraAux->letra);

        letraAux = letraAux->next;
    }

    printf("\n > As palavras e letras foram ordenadas!\n");

    system("pause");
}

void pesquisaRelevancia()
{
    system("cls");

    char substring[TAM_PAL_MAX];
    char ordena_palavra = 1;
    Palavra_ptr* pAux_ptr = PPalInicio.next;
    Palavra_ptr* pAnt_ptr = &PPalInicio;

    while(pAux_ptr)
    {
        pAnt_ptr = pAux_ptr;
        pAux_ptr = pAux_ptr->next;
        free(pAnt_ptr);
    }

    PPalInicio.next = NULL;
    pAux_ptr = PPalInicio.next;
    pAnt_ptr = &PPalInicio;

    printf("\n***********************PESQUISA POR RELEVÂNCIA**********************\n");
    printf("\n********************************************************************\n");
    printf(  "* > Digite a palavra a ser pesquisada (Não use espaços)            *\n");
    printf(  "* > :                                                              *\n");
    printf(  "********************************************************************\n");

    gotoxy(7, 6);
    fflush(stdin);
    scanf("%[^\n]", substring);
    fflush(stdin);

    letraAux = letraInicio.next;
    while (letraAux)
    {
        letraAux->palavraAux = letraAux->PalavraInicio.next;
        while(letraAux->palavraAux)
        {
            pAnt_ptr->next = (Palavra_ptr*) malloc(sizeof(Palavra_ptr));
            pAux_ptr = pAnt_ptr->next;
            pAux_ptr->palavra = letraAux->palavraAux;
            pAux_ptr->relevancia = num_substring_em_string(pAux_ptr->palavra->descricao, substring);

            if (pAux_ptr->relevancia < 1)
            {
                free(pAux_ptr);
                letraAux->palavraAux = letraAux->palavraAux->next;
                continue;
            }

            pAux_ptr = pAux_ptr->next;
            pAnt_ptr = pAnt_ptr->next;

            letraAux->palavraAux = letraAux->palavraAux->next;
        }

        letraAux = letraAux->next;
    }

    pAnt_ptr->next = NULL;

    while (ordena_palavra)
    {
        pAux_ptr = PPalInicio.next;
        pAnt_ptr = &PPalInicio;
        ordena_palavra = 0;

        while (pAux_ptr)
        {
            if (!pAux_ptr->next)
            {
                break;
            }

            if (pAux_ptr->relevancia < pAux_ptr->next->relevancia)
            {
                pAnt_ptr->next = pAux_ptr->next;
                pAux_ptr->next = pAux_ptr->next->next;
                pAnt_ptr = pAnt_ptr->next;
                pAnt_ptr->next = pAux_ptr;
            }

            pAux_ptr = pAux_ptr->next;
            pAnt_ptr = pAnt_ptr->next;
        }

        pAux_ptr = PPalInicio.next;
        while (pAux_ptr)
        {
            ordena_palavra = 0;

            if (!pAux_ptr->next)
            {
                break;
            }

            if (pAux_ptr->relevancia < pAux_ptr->next->relevancia)
            {
                ordena_palavra = 1;
                break;
            }

            pAux_ptr = pAux_ptr->next;
        }

    }

    printf(  "******************************RESULTADOS****************************\n");

    pAux_ptr = PPalInicio.next;
    int i = 0;
    while (pAux_ptr)
    {
        printf("[%d] : %s - %s\n\n", pAux_ptr->relevancia, pAux_ptr->palavra->nome, pAux_ptr->palavra->descricao);

        pAux_ptr = pAux_ptr->next;

        i++;
    }

    if (i == 0)
    {
        printf("\nA busca não obteve resultados!\n");
        printf("> A busca não funciona com espaços;\n> Verifique a ortografia;\n> A busca não é \"case sensitive\";\n> Não utilize acentos;\n\n");
    }

    system("pause");
}

/*===========================================================================================

CONTROLE DE LISTAS

=============================================================================================*/

Letra* retorna_Letra_bychar(char letra)
{
    int i = 0;
    letra = toupper(letra);
	letraAux = letraInicio.next;
	while (letraAux)
	{
		if (letra == letraAux->letra)
		{
			return letraAux;
		}
		letraAux = letraAux->next;
		i++;
	}

	return NULL;
}

void listar_dicionario()
{
    Letra* pLetra = letraInicio.next;
    system("cls");
    printf(  "\n***********************ÍNDICE REMISSIVO********************\n");
    int i = 0;

	while (pLetra)
	{
		printf("*\n* - %c -\n*", pLetra->letra);

		i+=2;

		Palavra* pPalavra = pLetra->PalavraInicio.next;
		int ii = 0;
		while (pPalavra)
		{
			printf(" [%d]...%s\n*", ++ii, pPalavra->nome);
			i++;
			pPalavra = pPalavra->next;
		}
		printf("\n");
		i++;

		pLetra = pLetra->next;
	}
    printf(  "***********************************************************\n");

    int j;
    for (j = 0; j < i; j++)
    {
            gotoxy(59, 3+j);
            printf("*");
    }

    gotoxy(1, 4+j);

    system("pause");
}

void toupper_str(char* str)
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

int strcont( /*1*/const char* string, /*2*/const char* substring)
{
    /*
    Parametros:
        1: String que pode conter a substring
        2: Substring a ser testada

    Retorna:
        int(0): A substring não está contida na string
        int(1): A substring está contida na string
    */

    char ustring[TAM_PAL_MAX], usubstring[TAM_PAL_MAX];

    strcpy(ustring, string);
    strcpy(usubstring, substring);

    toupper_str(ustring);
    toupper_str(usubstring);

    for (unsigned int i = 0; i < strlen(usubstring); i++)
    {
        if (ustring[i] != usubstring[i])
        {
            return 0;
        }
    }

    return 1;
}

int compara_palavras( /*1*/Palavra* palAux, /*2*/Palavra* pPalavra)
{
    /*
    Parametros:
        1: Ponteiro Auxiliar da Lista de Palavras
        2: Ponteiro Temporario do Loop

    Retorna:
        int(0): Palavras estao na ordem correta
        int(1): Palavras estao na ordem errada
    */

    int tam = strcmp(palAux->nome, pPalavra->nome);

    char str1[TAM_PAL_MAX], str2[TAM_PAL_MAX];

    strcpy(str1, palAux->nome);
    strcpy(str2, pPalavra->nome);

    toupper_str(str1);
    toupper_str(str2);

    switch(tam)
    {
    case 0:
        return 1;
    case 1:
        for (unsigned int i = 0; i < strlen(str2); i++)
        {
            if (str1[i] != str2[i])
            {
                if (str1[i] > str2[i])
                {
                    return 0;
                }
                else return 1;
            }
        }
        break;
    case -1:
        for (unsigned int i = 0; i < strlen(str1); i++)
        {
            if (str1[i] != str2[i])
            {
                if (str1[i] > str2[i])
                {
                    return 0;
                }
                else return 1;
            }

        }
        break;
    }

    return 1;
}

void ordenar_palavras(char letra)
{
    char ordena_palavra = 1;

    letra = toupper(letra);

	Letra* pLetra = retorna_Letra_bychar(letra);

	if (!pLetra)
    {
        printf("ERRO - Essa letra <\"%c\"> nao existe no dicionario!\n", letra);
        return;
    }

	pLetra->palavraAux = pLetra->PalavraInicio.next;
	pLetra->palavraAnt = &pLetra->PalavraInicio;

	while(pLetra->palavraAux)
	{
		Palavra* pPalavra = pLetra->PalavraInicio.next;
		char menor_palavra = 1;
		while (pPalavra)
		{
			menor_palavra = compara_palavras( pLetra->palavraAux, pPalavra );

			if (menor_palavra == 0)
                break;

			pPalavra = pPalavra->next;
		}

		if (menor_palavra)
		{
			pLetra->palavraAnt->next = pLetra->palavraAux->next;
			pLetra->palavraAux->next = pLetra->PalavraInicio.next;
			pLetra->PalavraInicio.next = pLetra->palavraAux;
			break;
		}

		pLetra->palavraAux = pLetra->palavraAux->next;
		pLetra->palavraAnt = pLetra->palavraAnt->next;
	}

	/*printf("\n===========DICIONARIO 1=============\n\n");

	listar_dicionario();

	printf("\n==================================\n\n");*/

	while (ordena_palavra != 0)
	{
		pLetra->palavraAux = pLetra->PalavraInicio.next;
        pLetra->palavraAnt = &pLetra->PalavraInicio;

		int i = 0;
		while(pLetra->palavraAux)
		{
			if (!pLetra->palavraAux->next)
				break;

			if ( !compara_palavras( pLetra->palavraAux, pLetra->palavraAux->next))
			{
			    pLetra->palavraAnt->next = pLetra->palavraAux->next;
                pLetra->palavraAux->next = pLetra->palavraAux->next->next;
                pLetra->palavraAnt = pLetra->palavraAnt->next;
                pLetra->palavraAnt->next = pLetra->palavraAux;
            }

			pLetra->palavraAux = pLetra->palavraAux->next;
			pLetra->palavraAnt = pLetra->palavraAnt->next;
			i++;
		}

        pLetra->palavraAux = pLetra->PalavraInicio.next;
		while(pLetra->palavraAux)
		{
			ordena_palavra = 0;

			if (!pLetra->palavraAux->next)
			{
				break;
			}

			if ( !compara_palavras( pLetra->palavraAux, pLetra->palavraAux->next) )
			{
				ordena_palavra++;
				break;
			}

			pLetra->palavraAux = pLetra->palavraAux->next;
		}
	}

}

void ordenar_palavras(const char* palavra)
{
	ordenar_palavras(toupper(palavra[0]));
}

void ordenar_letras()
{
	char ordena_Letra = 1;

	letraAux = letraInicio.next;

	while(letraAux)
	{
		Letra *p = letraInicio.next;
		char menor_letra = 1;
		while (p)
		{
			if (letraAux->letra > p->letra)
			{
				menor_letra = 0;
			}

			p = p->next;
		}

		if (menor_letra)
		{
			Letra* temp = NULL;
			if (letraAux->next)
				temp = letraAux->next;
			letraAux->prev->next = temp;
			letraAux->next = letraInicio.next;
			letraAux->prev = &letraInicio;
			letraInicio.next->prev = letraAux;
			letraInicio.next = letraAux;

			break;
		}

		letraAux = letraAux->next;
	}

	for( Letra* temp = letraInicio.next; temp; temp = temp->next )
	{
		if (temp->next)
			temp->next->prev = temp;
	}

	while (ordena_Letra != 0)
	{
		letraAux = letraInicio.next;
		int i = 0;
		while(letraAux)
		{
			if (!letraAux->next)
				break;

			if (letraAux->letra > letraAux->next->letra)
			{
				Letra* temp = letraAux->next->next;
				letraAux->next->prev = letraAux->prev;
				if (letraAux->next->next)
					letraAux->next->next->prev = letraAux;
				letraAux->prev = letraAux->next;
				letraAux->next = letraAux->prev->next;
				letraAux->prev->next = letraAux;
				letraAux->prev->prev->next = letraAux->prev;

				letraAux->next = temp;
			}

			letraAux = letraAux->next;
			i++;
		}

		letraAux = letraInicio.next;
		while(letraAux)
		{
			ordena_Letra = 0;

			if (!letraAux->next)
			{
				break;
			}

			if (letraAux->letra > letraAux->next->letra)
			{
				ordena_Letra++;
				break;
			}

			letraAux = letraAux->next;
		}
	}
}

void remove_Letra(Letra* Letra)
{
	if (!Letra)
	{
		printf("ERRO - Tentativa de remocao de ponteiro de Letra nulo\n");
		return;
	}

    if (Letra->next) Letra->next->prev = Letra->prev;
	Letra->prev->next = Letra->next;
	free(Letra);
}

Letra* new_Letra(const char letra)
{
	// 1 - Allocate
	Letra* p = (Letra*) malloc(sizeof(Letra));

	// 2 - Insert data
	p->letra = letra;

	// 3 - Lista Palavra
	p->palavraAux = &p->PalavraInicio;
	p->palavraAux->next = NULL;

	return p;
}

Letra* insert_Letra(const char letra)
{
	letraAux->next = new_Letra(letra);
	letraAux->next->prev = letraAux;
	letraAux = letraAux->next;
	letraAux->next = NULL;
	return letraAux;
}

Letra* retorna_Letra_Palavra(Palavra* Palavra)
{
    Letra* p = letraInicio.next;
	while (p)
	{
        if (Palavra->nome[0] == p->letra)
        {
            return p;
        }
        p = p->next;
	}
	return NULL;
}

Palavra* retorna_Palavra_bynome(const char nome[])
{
    char unome[TAM_PAL_MAX], upalavra[TAM_PAL_MAX];

    memset(unome, 0, sizeof(unome));
    memset(upalavra, 0, sizeof(upalavra));

    strcpy(unome, nome);

    toupper_str(unome);

	letraAux = retorna_Letra_bychar(unome[0]);
	if(letraAux)
	{
		int i = 0;
		letraAux->palavraAux = letraAux->PalavraInicio.next;
		while (letraAux->palavraAux)
		{
            strcpy(upalavra, letraAux->palavraAux->nome);
            toupper_str(upalavra);
			if (strcmp( unome, upalavra ) == 0)
			{
				return letraAux->palavraAux;
			}
			letraAux->palavraAux = letraAux->palavraAux->next;
			i++;
		}
	}
	return NULL;
}

void remove_Palavra(Palavra* Palavra)
{
	if (!Palavra)
    {
		printf("ERRO - Tentativa de remocao de ponteiro de Palavra nulo\n");
		return;
	}

    Letra* p = retorna_Letra_Palavra(Palavra);

    if (!p)
    {
        printf("ERRO - Essa letra <\"%c\"> nao existe no dicionario!\n", Palavra->nome[0]);
        return;
    }

    p->palavraAux = p->PalavraInicio.next;
    p->palavraAnt = &p->PalavraInicio;
    while (p->palavraAux)
    {
        if (p->palavraAux == Palavra)
        {
            p->palavraAnt->next = p->palavraAux->next;
            free(Palavra);
			break;
        }

        p->palavraAux = p->palavraAux->next;
        p->palavraAnt = p->palavraAnt->next;
    }

	if (p->PalavraInicio.next == NULL)
    {
        remove_Letra(p);
    }
}

Palavra* new_Palavra(const char nome[], const char descricao[])
{
	Palavra* c = (Palavra*) malloc(sizeof(Palavra));
	strcpy(c->nome, nome);
	strcpy(c->descricao, descricao);
	return c;
}

Palavra* insert_Palavra(const char nome[], const char descricao[])
{
    Palavra* palavra;
    palavra = new_Palavra(nome, descricao);

    letraAux = &letraInicio;
    while(letraAux->next)
    {
        letraAux = letraAux->next;
    }

    Letra* p = NULL;
    if (!(p = retorna_Letra_Palavra(palavra)))
    {
        p = insert_Letra(toupper(nome[0]));
    }

	p->palavraAux->next = palavra;
    p->palavraAux = p->palavraAux->next;
    p->palavraAux->next = NULL;
    return p->palavraAux;
}

int num_substring_em_string(const char string[], const char substring[])
{
    FILE* temp_buffer = fopen("temp", "w+"); //Arquivo de texto temporario

    char up_str[TAM_DES_MAX], up_substr[TAM_PAL_MAX]; //Strings temporarias, recebem o valor dos parametros
    char pal_str[TAM_PAL_MAX], des_str[TAM_DES_MAX];

    int num_substr = 0;

    memset(des_str, 0, sizeof(des_str));

    strcpy(up_str, string);
    strcpy(up_substr, substring);

    toupper_str(up_str);
    toupper_str(up_substr);

    fprintf(temp_buffer, "%s", up_str);

    int i = 0;
    int ii = 0;

    fseek(temp_buffer, 0, SEEK_SET);
    while ((des_str[i] = fgetc(temp_buffer)) != EOF )
    {
        //printf("%c", des_str[i]);
        if ((des_str[i] >= 48 && des_str[i] <= 57) || (des_str[i] >= 65 && des_str[i] <= 90) || (des_str[i] >= 97 && des_str[i] <= 122))
        {
            pal_str[ii] = des_str[i];
            //printf("Palavra: %s\n", pal_str);
            ii++;
        }
        else if (isspace(des_str[i]))
        {
            ii = 0;

            if (strcont(pal_str, up_substr))
            {
                num_substr++;
            }

            memset(pal_str, 0, sizeof(pal_str));
        }

        i++;
    }

    if (pal_str[0] != '\0')
    {
        ii = 0;

        //printf("Palavra: %s", pal_str);
        if (strcont(pal_str, up_substr))
        {
            num_substr++;
            //printf(" @");
        }

        //printf("\n");

        memset(pal_str, 0, sizeof(pal_str));
    }

    return num_substr;
}

void salvar_lista_arquivos()
{
    pont_arq = fopen("lista_arquivos.txt", "w+");

    if(pont_arq){

        ordenar_letras();
        Letra* pLetra = letraInicio.next;

        while (pLetra)
        {
            ordenar_palavras(pLetra->letra);

            Palavra* pPalavra = pLetra->PalavraInicio.next;
            while (pPalavra)
            {
                fprintf(pont_arq, "%c{Nome:\"%s\",Descrição:%s}\n", pLetra->letra, pPalavra->nome, pPalavra->descricao);
                pPalavra = pPalavra->next;
            }
            printf("\n");

            pLetra = pLetra->next;
        }
    }
    else{
        printf("\nERRO! Não foi possivel salvar.");
    }

    fclose(pont_arq);
}

void carregar_lista_na_RAM()
{
    pont_arq = fopen("lista_arquivos.txt", "r");

    char letra;
    char nome[TAM_PAL_MAX], descricao[TAM_DES_MAX];

    if(pont_arq){
        do{
            fscanf(pont_arq, "%c{Nome:\"%[^\"]\",Descrição:%[^}]}\n", &letra, nome, descricao);
            Palavra* p = insert_Palavra(nome, descricao);

        }while(!feof(pont_arq));
    }
    else{
        printf("Não exite arquivo!");
        getch();
    }

    fclose(pont_arq);
}
