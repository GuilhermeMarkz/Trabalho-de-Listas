#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

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
	Palavra PalavraInicio, *PalavraAux;
};

Letra LetraInicio, *LetraAux;

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
        if (Palavra->name[0] == p->letra)
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

	int i = 0;

	insert_Palavra ("Maria II");
	c1 = insert_Palavra ("Mariazinha");

	insert_Palavra ("Ziraldo");

	insert_Palavra ("Paulo");
	insert_Palavra ("Paulinho");

	insert_Palavra ("Karina");

	insert_Palavra ("Vinicius");

	insert_Palavra ("Olavo");

	insert_Palavra ("Alberto");

	insert_Palavra ("Joao II");
	c0 = insert_Palavra ("Joao III");
	insert_Palavra ("Joaozinho");

	printf("Palavra NOME: %s\n", retorna_Palavra_bynome("Joaozinho")->name);

	printf("\n===========POS INSERSAO============\n\n");

	i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		printf("%d - %c", i++, LetraAux->letra);
		LetraAux->PalavraAux = LetraAux->PalavraInicio.next;
		while (LetraAux->PalavraAux)
		{
			printf(" - %s", LetraAux->PalavraAux->name);
			LetraAux->PalavraAux = LetraAux->PalavraAux->next;
		}
		printf("\n");

		LetraAux = LetraAux->next;
	}

	ordenar_letras();

	printf("\n===========POS ORDENACAO============\n\n");

	i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		printf("%d - %c", i++, LetraAux->letra);
		LetraAux->PalavraAux = LetraAux->PalavraInicio.next;
		while (LetraAux->PalavraAux)
		{
			printf(" - %s", LetraAux->PalavraAux->name);
			LetraAux->PalavraAux = LetraAux->PalavraAux->next;
		}
		printf("\n");

		LetraAux = LetraAux->next;
	}

    printf("\n===========POS REMOCAO============\n\n");
	//Remove
	//remove_Letra_byindex(1);

	remove_Palavra(c0);
	remove_Palavra(c1);

	//List
    i = 0;
	LetraAux = LetraInicio.next;
	while (LetraAux)
	{
		printf("%d - %c", i++, LetraAux->letra);
		LetraAux->PalavraAux = LetraAux->PalavraInicio.next;
		while (LetraAux->PalavraAux)
		{
			printf(" - %s", LetraAux->PalavraAux->name);
			LetraAux->PalavraAux = LetraAux->PalavraAux->next;
		}
		printf("\n");

		LetraAux = LetraAux->next;
	}

	getch();

	return 0;
}

