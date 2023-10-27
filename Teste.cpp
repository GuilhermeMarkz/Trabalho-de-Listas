#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define TAM_MAX 256

/*
Lista de Letras que, por sua vez, possuem uma lista de seus filhos.
*/

typedef struct Letra Letra;
typedef struct Palavra Palavra;

struct Palavra
{
	char name[30];
	Palavra *next;
};

struct Letra
{
	char letra;
	Letra *next, *prev;
	Palavra PalavraInicio, *PalavraAux, *PalavraAnt;
};

Letra LetraInicio, *LetraAux;

Letra* retorna_Letra_bychar(char letra)
{
    int i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		if (letra == LetraAux->letra)
		{
			return LetraAux;
		}
		LetraAux = LetraAux->next;
		i++;
	}

	return NULL;
}

void listar_dicionario()
{
    int i = 0;

    Letra* pLetra = LetraInicio.next;

	while (pLetra)
	{
		printf("%d - %c", i++, pLetra->letra);

		Palavra* pPalavra = pLetra->PalavraInicio.next;
		while (pPalavra)
		{
			printf(" - %s", pPalavra->name);
			pPalavra = pPalavra->next;
		}
		printf("\n");

		pLetra = pLetra->next;
	}
}

void toupper_str(char* str)
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
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

    int tam = strcmp(palAux->name, pPalavra->name);

    char str1[TAM_MAX], str2[TAM_MAX];

    strcpy(str1, palAux->name);
    strcpy(str2, pPalavra->name);

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

	Letra* pLetra = retorna_Letra_bychar(letra);

	if (!pLetra)
    {
        printf("ERRO - Essa letra <\"%c\"> nao existe no dicionario!\n", letra);
        return;
    }

	pLetra->PalavraAux = pLetra->PalavraInicio.next;
	pLetra->PalavraAnt = &pLetra->PalavraInicio;

	while(pLetra->PalavraAux)
	{
		Palavra* pPalavra = pLetra->PalavraInicio.next;
		char menor_palavra = 1;
		while (pPalavra)
		{
			menor_palavra = compara_palavras( pLetra->PalavraAux, pPalavra );

			if (menor_palavra == 0)
                break;

			pPalavra = pPalavra->next;
		}

		if (menor_palavra)
		{
			pLetra->PalavraAnt->next = pLetra->PalavraAux->next;
			pLetra->PalavraAux->next = pLetra->PalavraInicio.next;
			pLetra->PalavraInicio.next = pLetra->PalavraAux;
			break;
		}

		pLetra->PalavraAux = pLetra->PalavraAux->next;
		pLetra->PalavraAnt = pLetra->PalavraAnt->next;
	}

	/*printf("\n===========DICIONARIO 1=============\n\n");

	listar_dicionario();

	printf("\n==================================\n\n");*/

	while (ordena_palavra != 0)
	{
		pLetra->PalavraAux = pLetra->PalavraInicio.next;
        pLetra->PalavraAnt = &pLetra->PalavraInicio;

		int i = 0;
		while(pLetra->PalavraAux)
		{
			if (!pLetra->PalavraAux->next)
				break;

			if ( !compara_palavras( pLetra->PalavraAux, pLetra->PalavraAux->next))
			{
			    pLetra->PalavraAnt->next = pLetra->PalavraAux->next;
                pLetra->PalavraAux->next = pLetra->PalavraAux->next->next;
                pLetra->PalavraAnt = pLetra->PalavraAnt->next;
                pLetra->PalavraAnt->next = pLetra->PalavraAux;
            }

			pLetra->PalavraAux = pLetra->PalavraAux->next;
			pLetra->PalavraAnt = pLetra->PalavraAnt->next;
			i++;
		}

		/*printf("\n===========DICIONARIO 2=============\n\n");

        listar_dicionario();

        printf("\n==================================\n\n");*/

        pLetra->PalavraAux = pLetra->PalavraInicio.next;
		while(pLetra->PalavraAux)
		{
			ordena_palavra = 0;

			if (!pLetra->PalavraAux->next)
			{
				break;
			}

			if ( !compara_palavras( pLetra->PalavraAux, pLetra->PalavraAux->next) )
			{
				ordena_palavra++;
				break;
			}

			pLetra->PalavraAux = pLetra->PalavraAux->next;
		}
	}

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
        if (Palavra->name[0] == p->letra)
        {
            return p;
        }
        p = p->next;
	}
	return NULL;
}

Palavra* retorna_Palavra_bynome(const char nome[])
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
				if (strcmp( nome, LetraAux->PalavraAux->name ) == 0)
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

    if (!p)
    {
        printf("ERRO - Essa letra <\"%c\"> nao existe no dicionario!\n", Palavra->name[0]);
        return;
    }

    p->PalavraAux = p->PalavraInicio.next;
    p->PalavraAnt = &p->PalavraInicio;
    while (p->PalavraAux)
    {
        if (p->PalavraAux == Palavra)
        {
            p->PalavraAnt->next = p->PalavraAux->next;
            p->PalavraAux->

            free(Palavra);
        }

        p->PalavraAux = p->PalavraAux->next;
        p->PalavraAnt = p->PalavraAnt->next;
    }

	free(Palavra);

	if (p->PalavraInicio.next == NULL)
    {
        remove_Letra(p);
    }
}

Palavra* new_Palavra(const char name[])
{
	Palavra* c = (Palavra*) malloc(sizeof(Palavra));
	strcpy(c->name, name);
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
    //printf("Inseriu %s em %c!\n", p->PalavraAux->name, p->letra);
    return p->PalavraAux;
}

int main()
{
    LetraInicio.next = NULL;

	Palavra *c0, *c1, *c2;

	insert_Palavra ("Maria");
	c1 = insert_Palavra ("Mariazinha");
	insert_Palavra ("Moises");
	insert_Palavra ("Mariel");
	insert_Palavra ("Muriel");
	insert_Palavra ("Mateus");
	insert_Palavra ("Messias");
	insert_Palavra ("Monica");
	insert_Palavra ("Miguel");
	insert_Palavra ("Melissa");
	insert_Palavra ("Mozart");
	insert_Palavra ("Max");

	c2 = insert_Palavra ("Ziraldo");

	insert_Palavra ("Paulo");
	insert_Palavra ("Paulinho");

	insert_Palavra ("Karina");

	insert_Palavra ("Vinicius");

	insert_Palavra ("Olavo");

	insert_Palavra ("Alberto");

	c0 = insert_Palavra ("Joao");
	insert_Palavra ("Jeremias");
	insert_Palavra ("Jailson");
	insert_Palavra ("Juan");
	insert_Palavra ("Jose");

	remove_Letra(retorna_Letra_bychar('J'));

	printf("Palavra NOME: %s\n", retorna_Palavra_bynome("Joaozinho")->name);

	printf("\n===========POS INSERSAO============\n\n");

	listar_dicionario();

	ordenar_letras();
	ordenar_palavras('J');
	ordenar_palavras('M');

	printf("\n===========POS ORDENACAO============\n\n");

	listar_dicionario();

    printf("\n===========POS REMOCAO============\n\n");
	//Remove
	//remove_Letra_byindex(1);

	//remove_Palavra(c0);
	//remove_Palavra(c1);
	remove_Palavra(c2);

	//List
    listar_dicionario();

	getch();

	return 0;
}
