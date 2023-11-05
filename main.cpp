#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

/*
Lista de Letras que, por sua vez, possuem uma lista de seus filhos.
*/

#define TAM_DES_MAX 512
#define TAM_PAL_MAX 128

int VariConPalavra = 0;

using namespace std;

typedef struct Letra Letra;
typedef struct Palavra Palavra;

FILE* pont_arq;

struct Palavra
{
	char name[TAM_PAL_MAX], descricao[TAM_DES_MAX];
	Palavra *next;
};

struct Letra
{
	char letra;
	Letra *next, *prev;
	Palavra PalavraInicio, *PalavraAux, *PalavraAnt;
};

Letra LetraInicio, *LetraAux;

//Funções de Arquivos
void salvar_lista_arquivos();
void carregar_lista_na_RAM();

//Fun��es de controle da lista de Letras
Letra* new_Letra(const char letra);
Letra* insert_Letra(const char letra);
void remove_Letra(Letra* Letra);

Letra* retorna_Letra_Palavra(Palavra* Palavra);
void ordenar_letras();

//Fun��es de controle da lista de Palavras
int num_substring_em_string(const char string[], const char substring[]); //
Palavra* new_Palavra(const char name[], const char descricao[]); //

Palavra* retorna_Palavra_bynome(const char nome[]);
Palavra* insert_Palavra(const char name[], const char descricao[]);
void ordenar_palavras(const char letra);  // Ordena todas as palavras de uma letra
void remove_Palavra(Palavra* Palavra); // Remove uma palavra da lista

//Fun��es extras
void listar_dicionario();
void toupper_str(char* str);

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

        Palavra* palavra = retorna_Palavra_bynome("Botafogo");

        printf("N�mero de ocorr�ncias de \"Botafogo\" na descri��o da palavra \"Botafogo\": %d\n", num_substring_em_string(palavra->descricao, "Botafogo"));

        printf("Dicion�rio de Times de Futebol");
        printf("\n[1]Inserir palavra\n[2]Editar palavra\n[3]Excluir palavra\n[4]Pesquisar palavra\n[5]Palavras ordenandas\n[6]Lista de palavras\n[7]Sair\n:");
        scanf("%c", &op);

        switch(op){
        case '1':
            inserirPal();
            break;

        case '2':
            editarPal();
            break;

        case '3':
            excluirPal();
            break;

        case '4':
            pesquisarPal();
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

    salvar_lista_arquivos();

    return 0;
}

void inserirPal(){
    system("cls");

    char nomePalavra[TAM_PAL_MAX], descPalavra[TAM_DES_MAX];


    int a=0;


    do{
    printf("Nome do time:");
    fflush(stdin);
    scanf("%[^\n]", nomePalavra);
    fflush(stdin);
    printf("\nDescreva o time:");
    fflush(stdin);
    scanf("%[^\n]", descPalavra);
    fflush(stdin);
    insert_Palavra(nomePalavra, descPalavra);

    printf("\n\nRegistrar mais uma palavra? [1]N�o [0]Sim\n->");
    scanf("%d", &a);

    }while(a<1);
    system("pause");
}

void pesquisarPal(){
    int a = 0;

    char PalavraEntrada[TAM_PAL_MAX];

    system("cls");

    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        Palavra* palavra;
        palavra = retorna_Palavra_bynome(PalavraEntrada);
        if(palavra == NULL){
            printf("Palavra n�o existe\n");

        }
        else{
            printf("Nome da palavra: %s\n", palavra->name);
            printf("Descri��o: %s\n", palavra->descricao);
        }


        printf("Continuar pesquisando? Sim[0] N�o[1]\n->");
        scanf("%d", &a);

    }while(a<1);

    system("pause");
}

void excluirPal(){
	int a = 0;
	char PalavraEntrada[TAM_PAL_MAX];
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        Palavra* palavra;
        palavra = retorna_Palavra_bynome(PalavraEntrada);
        if(palavra == NULL){
            printf("Palavra n�o encontrada\n");
        }
        else{
            printf("Palavra:%s\n", palavra->name);
            printf("Descri��o:%s\n", palavra->descricao);
            printf("Remover time? Sim[0] N�o[1]\n->");
            scanf("%d", &a);
            if(a==0){
                remove_Palavra(palavra);
            }
        }

        printf("Remover mais um time? Sim[0] N�o[1]\n->");
        scanf("%d", &a);

    }while(a<1);
}

void editarPal(){

	int a = 0;
	char PalavraEntrada[TAM_PAL_MAX];
    do{
        printf("\nDigite o nome do time:");
        fflush(stdin);
        scanf("%[^\n]", PalavraEntrada);
        fflush(stdin);

        Palavra* palavra=retorna_Palavra_bynome(PalavraEntrada);
        if(palavra==NULL){
            printf("Palavra n�o encontrada:");
        }else{
            printf("Palavra:%s\n", palavra->name);
            printf("Descri��o:%s\n", palavra->descricao);
            printf("O que deseja editar: Nome[1]/tDescri��o[2]");
            scanf("%d", &a);
            switch(a){
                case 1:
                    printf("Digite o nome:");
                    fflush(stdin);
                    scanf("%[^\n]", palavra->name);
                    fflush(stdin);
                    break;
                case 2:
                    printf("Digite a descri��o:");
                    fflush(stdin);
                    scanf("%[^\n]", palavra->descricao);
                    fflush(stdin);
                    break;
                }
        }
        printf("Editar mais um time? Sim[0] N�o[1]\n->");
        scanf("%d", &a);

    }while(a<1);
}

void pesquisaRelevancia()
{

}

/*===========================================================================================

CONTROLE DE LISTAS

=============================================================================================*/

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

    char str1[TAM_PAL_MAX], str2[TAM_PAL_MAX];

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

    letra = toupper(letra);

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

void ordenar_palavras(const char* palavra)
{
	ordenar_palavras(toupper(palavra[0]));
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
	LetraAux = retorna_Letra_bychar(nome[0]);
	if(LetraAux)
	{
		int i = 0;
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
            free(Palavra);
			break;
        }

        p->PalavraAux = p->PalavraAux->next;
        p->PalavraAnt = p->PalavraAnt->next;
    }

	if (p->PalavraInicio.next == NULL)
    {
        remove_Letra(p);
    }
}

Palavra* new_Palavra(const char name[], const char descricao[])
{
	Palavra* c = (Palavra*) malloc(sizeof(Palavra));
	strcpy(c->name, name);
	strcpy(c->descricao, descricao);
	return c;
}

Palavra* insert_Palavra(const char name[], const char descricao[])
{
    Palavra* Palavra = new_Palavra(name, descricao);

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

            printf("Palavra: %s", pal_str);
            if (strcmp(pal_str, up_substr) == 0)
            {
                num_substr++;
                printf(" @");
            }

            printf("\n");

            memset(pal_str, 0, sizeof(pal_str));
        }

        i++;
    }

    if (pal_str[0] != '\0')
    {
        ii = 0;

        printf("Palavra: %s", pal_str);
        if (strcmp(pal_str, up_substr) == 0)
        {
            num_substr++;
            printf(" @");
        }

        printf("\n");

        memset(pal_str, 0, sizeof(pal_str));
    }

    system("pause");

    return num_substr;
}

void salvar_lista_arquivos()
{

    pont_arq = fopen("lista_arquivos.txt", "w+");

    if(pont_arq){

        Letra* pLetra = LetraInicio.next;

        ordenar_letras();

        while (pLetra)
        {

            ordenar_palavras(pLetra->letra);

            Palavra* pPalavra = pLetra->PalavraInicio.next;
            while (pPalavra)
            {
                fprintf(pont_arq, "%c{Nome:\"%s\",Descrição:%s.}\n", pLetra->letra, pPalavra->name, pPalavra->descricao);
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

void carregar_lista_na_RAM(){

    pont_arq = fopen("lista_arquivos.txt", "r+");

    char letra;
    char nome[81], descricao[512];

    do{

        fscanf(pont_arq, "%c{Nome:\"%[^\"]\",Descrição:%[^.]}", &letra, nome, descricao);
        insert_Palavra(nome, descricao);

    }while(!feof(pont_arq));

    printf("\n %c, %s, %s", letra, nome, descricao);
    fclose(pont_arq);
}


