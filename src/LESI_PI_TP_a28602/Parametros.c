/**

	@file      Parametros.c

	@brief     Funções que controlam e lidam com os parâmetros opcionais do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 27.12.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constantes.h"
#include "Utils.h"
#include "OperacoesFicheiros.h"

/**
	@brief Lida com o parâmetro de apresentar o menu de ajuda.
	@param argc - Contador de argumentos.
	@param argv - Vetor de arumentos.
**/
static void ManipularMenuAjuda(int argc, char* argv[])
{
	if (argc > 1 && (strcmp(argv[1], "-ajuda") == 0))
	{
		if (argc > 2 && strcmp(argv[2], "erros") == 0)
			ApresentarErros();
		else
			ApresentarAjuda();

		exit(SUCESSO);
	}
}

/**
	@brief Lida com o parâmetro de apagar a base de dados.
	@param argc - Contador de argumentos.
	@param argv - Vetor de arumentos.
**/
static void ManipularApagarBd(int argc, char* argv[])
{
	if (argc > 1 && strcmp(argv[1], "-apagarbd") == 0)
		ApagarBaseDados();
}

/**
	@brief Verifica o tipo de ficheiro e muda o valor da variável ``*tipoFicheiro`` para o tipo do ficheiro.
	@param nomeFicheiro - O nome do ficheiro dado pelo utilizador.
	@param ficheiro     - Apontador para a string do nome do ficheiro.
	@param tipoFicheiro - Apontador para a variável do tipo do ficheiro.
	@param argv         - ``argv`` recebido no main().
	@param i            - Índice do parâmetro no array de argv.
	@param argc         - ``argc`` recebido no main().
**/
static void ManipularFicheiro(char* nomeFicheiro, char** ficheiro, int* tipoFicheiro, char* argv[], int i, int argc)
{
	*ficheiro = nomeFicheiro;
	if (i + 2 < argc)
	{
		if (strcmp(argv[i + 2], "-tab") == 0)
		{
			*tipoFicheiro = TIPO_FICHEIRO_TAB;
		}
		else if (strcmp(argv[i + 2], "-bin") == 0)
		{
			*tipoFicheiro = TIPO_FICHEIRO_BIN;
		}
	}
}

/**
	@brief Manipula os parâmetros opcionais.
	@param argc                  - Número de argumentos da linha de comandos.
	@param argv                  - Vetor de argumentos da linha de comandos.
	@param ficheiroPacientes     - Apontador para o nome do ficheiro de pacientes.
	@param ficheiroDietas        - Apontador para o nome do ficheiro de dietas.
	@param ficheiroPlanos        - Apontador para o nome do ficheiro de planos.
	@param tipoFicheiroPacientes - Apontador para o tipo de ficheiro de pacientes.
	@param tipoFicheiroDietas    - Apontador para o tipo de ficheiro de dietas.
	@param tipoFicheiroPlanos    - Apontador para o tipo de ficheiro de planos.
**/
void ManipularParametrosOpcionais(int argc, char* argv[], char** ficheiroPacientes, char** ficheiroDietas, char** ficheiroPlanos,
	int* tipoFicheiroPacientes, int* tipoFicheiroDietas, int* tipoFicheiroPlanos)
{
	ManipularMenuAjuda(argc, argv);
	ManipularApagarBd(argc, argv);

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'p':
				ManipularFicheiro(argv[i + 1], ficheiroPacientes, tipoFicheiroPacientes, argv, i, argc);
				break;
			case 'd':
				ManipularFicheiro(argv[i + 1], ficheiroDietas, tipoFicheiroDietas, argv, i, argc);
				break;
			case 'l':
				ManipularFicheiro(argv[i + 1], ficheiroPlanos, tipoFicheiroPlanos, argv, i, argc);
				break;
			}
		}
	}
}
