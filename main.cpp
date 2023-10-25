#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

/*
Lista de Letras que, por sua vez, possuem uma lista de seus filhos.
*/

#define TAM_MAX 512

int VariConPalavra = 0;

using namespace std;

typedef struct Letra Letra;
typedef struct Palavra Palavra;

struct Palavra
{
	char nome[30], descricao[TAM_MAX];
	Palavra *next;
};

struct Letra
{
	char letra;
	Letra *next, *prev;
	Palavra PalavraInicio, *PalavraAux;
};

Letra LetraInicio, *LetraAux;

Letra* new_Letra(const char letra);
Letra* insert_Letra(const char letra);
Letra* retorna_Letra_byindex(int index);
Letra* retorna_Letra_Palavra(Palavra* Palavra);
void ordenar_letras();
void remove_Letra(Letra* Letra);

Palavra* retorna_Palavra_bynome(char nome[]);
Palavra* new_Palavra(const char name[]);
Palavra* insert_Palavra(const char name[]);
void ordenar_palavras();
void remove_Palavra(Palavra* Palavra);

void inserirPal(Palavra* Palavra);
void pesquisarPal(Palavra* Palavra);
void excluirPal(Palavra* Palavra);
void editarPal(Palavra* Palavra);

int main(){
    setlocale(LC_ALL,"");
    int a = 0;
    char op;
    Palavra Palavra[2];

    do{
        system("cls");
        printf("Dicionário de Frutas");
        printf("\n[1]Inserir palavra\n[2]Editar palavra\n[3]Excluir palavra\n[4]Pesquisar palavra\n[5]Palavras ordenandas\n[6]Lista de palavras\n[7]Sair\n:");
        scanf("%c", &op);

        switch(op){
        case '1':
            //inserirPal(times); //Não funcional
            break;

        case '2':
            editarPal(Palavra);
            break;

        case '3':
            excluirPal(Palavra);
            break;

        case '4':
            //pesquisarPal(times);
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

void inserirPal(){ //Inutil por enquanto
    system("cls");

    int a=0;

    //Nessa parte insere na Lista

    do{
        a = 1;
        system("pause");
    }while(a<1);
}
void pesquisarPal(Palavra* Palavra){
    int a = 0;
    char PalavraEntrada[TAM_MAX];

    system("cls");

    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}

void excluirPal(Palavra* Palavra){
	int a = 0;
	char PalavraEntrada[TAM_MAX];
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}

void editarPal(Palavra* Palavra){
	int a = 0;
	char PalavraEntrada[TAM_MAX];
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        //Aqui tu faz a boa da rapazezda

    }while(a<1);
}

/*===========================================================================================

CONTROLE DE LISTAS

=============================================================================================*/

Letra* retorna_Letra_byindex(int index)
{
    int i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		if (i == index)
		{
			return LetraAux;
		}
		LetraAux = LetraAux->next;
		i++;
	}

	return NULL;
}

void ordenar_palavras()
{

}

void ordenar_letras()
{
	char ordena_Letra = 1;

	LetraAux = LetraInicio.next;

	while(LetraAux)
	{
		Letra *p = LetraInicio.next;
		char menor_letra = 1;
		while (p)
		{
			if (LetraAux->letra > p->letra)
			{
				menor_letra = 0;		
			}
			
			p = p->next;
		}

		if (menor_letra)
		{
			Letra* temp = NULL;
			if (LetraAux->next)
				temp = LetraAux->next;
			LetraAux->prev->next = temp;
			LetraAux->next = LetraInicio.next;
			LetraAux->prev = &LetraInicio;
			LetraInicio.next->prev = LetraAux;
			LetraInicio.next = LetraAux;

			break;
		}

		LetraAux = LetraAux->next;
	}

	for( Letra* temp = LetraInicio.next; temp; temp = temp->next )
	{
		if (temp->next)
			temp->next->prev = temp;
	}

	while (ordena_Letra != 0)
	{
		LetraAux = LetraInicio.next;
		int i = 0;
		while(LetraAux)
		{
			if (!LetraAux->next)
				break;

			if (LetraAux->letra > LetraAux->next->letra)
			{
				Letra* temp = LetraAux->next->next;
				LetraAux->next->prev = LetraAux->prev;
				if (LetraAux->next->next)
					LetraAux->next->next->prev = LetraAux;
				LetraAux->prev = LetraAux->next;
				LetraAux->next = LetraAux->prev->next;
				LetraAux->prev->next = LetraAux;
				LetraAux->prev->prev->next = LetraAux->prev;

				LetraAux->next = temp;
			}

			LetraAux = LetraAux->next;
			i++;
		}

		LetraAux = LetraInicio.next;
		while(LetraAux)
		{
			ordena_Letra = 0;
			if (!LetraAux->prev)
			{
				LetraInicio.next = LetraAux;
			}

			if (!LetraAux->next)
			{
				break;
			}
			
			if (LetraAux->letra > LetraAux->next->letra)
			{
				ordena_Letra++;
				break;
			}

			LetraAux = LetraAux->next;
		}
	}
}

void remove_Letra(Letra* Letra)
{
	Letra->next->prev = Letra->prev;
	Letra->prev->next = Letra->next;
	free(Letra);
}

void remove_Letra_byindex(int index)
{
    remove_Letra(retorna_Letra_byindex(index));
}

Letra* new_Letra(const char letra)
{
	// 1 - Allocate
	Letra* p = (Letra*) malloc(sizeof(Letra));

	// 2 - Insert data
	p->letra = letra;

	// 3 - Lista Palavra
	p->PalavraAux = &p->PalavraInicio;
	p->PalavraAux->next = NULL;

	return p;
}

Letra* insert_Letra(const char letra)
{
	LetraAux->next = new_Letra(letra);
	LetraAux->next->prev = LetraAux;
	LetraAux = LetraAux->next;
	LetraAux->next = NULL;
	return LetraAux;
}

Letra* retorna_Letra_Palavra(Palavra* Palavra)
{
    Letra* p = LetraInicio.next;
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

Palavra* retorna_Palavra_bynome(char nome[])
{
	LetraAux = LetraInicio.next;
	while(LetraAux)
	{
		int i = 0;
		if (LetraAux->letra == nome[0])
		{
			LetraAux->PalavraAux = LetraAux->PalavraInicio.next;
			while (LetraAux->PalavraAux)
			{
				if (strcmp( nome, LetraAux->PalavraAux->nome ) == 0)
				{
					return LetraAux->PalavraAux;
				}

				LetraAux->PalavraAux = LetraAux->PalavraAux->next;
				i++;
			}
		}
		LetraAux = LetraAux->next;
	}
	return NULL;
}

void remove_Palavra(Palavra* Palavra)
{
    Letra* p = retorna_Letra_Palavra(Palavra);
    p->PalavraAux = p->PalavraInicio.next;
    while (p->PalavraAux)
    {
        if (p->PalavraAux->next == Palavra)
            p->PalavraAux->next = Palavra->next;
        p->PalavraAux = p->PalavraAux->next;
    }

	free(Palavra);
}

Palavra* new_Palavra(const char name[])
{
	Palavra* c = (Palavra*) malloc(sizeof(Palavra));
	strcpy(c->nome, name);
	return c;
}

Palavra* insert_Palavra(const char name[])
{
    Palavra* Palavra = new_Palavra(name);

    if (LetraAux == NULL)
    {
        LetraAux = &LetraInicio;
        while(LetraAux->next)
        {
            LetraAux = LetraAux->next;
        }
    }

    Letra* p = NULL;
    if (!(p = retorna_Letra_Palavra(Palavra)))
    {
        p = insert_Letra(toupper(name[0]));
    }

	p->PalavraAux->next = Palavra;
    p->PalavraAux = p->PalavraAux->next;
    p->PalavraAux->next = NULL;
    return p->PalavraAux;
}

