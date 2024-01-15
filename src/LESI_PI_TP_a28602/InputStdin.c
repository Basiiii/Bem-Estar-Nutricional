/**

	@file      InputStdin.c
	@brief
	@author    Enrique George Rodrigues
	@date      29.12.2023
	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constantes.h"
#include "Utils.h"

#include "Debug.h"

#include "../GestorDadosIO/IODadosAPI.h"

#ifdef _WIN32
#include <io.h>
#define fseeko _fseeki64
#define ftello _ftelli64
#else
#include <unistd.h>
#endif

/**
	@brief  Permite o utilizador dar input do tipo de ficheiro a ser importado.
	@param  tipoFicheiro - Apontador para a variável int com o tipo de ficheiro.
	@retval              - 0 se correr sem erros.
	@retval              - 27 se houver um erro na leitura do tipo de ficheiro.
**/
static int LerTipoFicheiro(int* tipoFicheiro)
{
	printf("Por favor escolha o tipo de ficheiro que deseja importar:\n");
	printf("Pacientes CSV: 1\nPacientes TAB: 2\n");
	printf("Dietas CSV: 3\nDietas TAB: 4\n");
	printf("Planos CSV: 5\nPlanos TAB: 6\n");

	if (scanf("%d%*c", tipoFicheiro) != 1 || *tipoFicheiro < LIMITE_MIN_INPUT_TIPOS_FICHEIRO || *tipoFicheiro > LIMITE_MAX_INPUT_TIPOS_FICHEIRO)
		return ERRO_LEITURA_TIPO_FICHEIRO;

	LimparEcra();
	return SUCESSO;
}

/**
	@brief  Cria um ficheiro temporário na memória.
	@param  dadosInput - Os dados para serem colocados no ficheiro.
	@retval            - O ficheiro criado.
**/
static FILE* CriarFicheiroTempMemoria(const char* dadosInput)
{
#ifdef _WIN32
	FILE* tempFile = tmpfile();
	if (tempFile != NULL)
	{
		fwrite(dadosInput, 1, strlen(dadosInput), tempFile);
		fseeko(tempFile, 0, SEEK_SET);  // Ir ao início do ficheiro
	}
#else

	FILE* tempFile = fmemopen((void*)dadosInput, strlen(dadosInput), "r");
#endif
	return tempFile;
}

/**
	@brief  Permite o utilizador introduzir dados através do stdin.
	@retval  - O ficheiro com os dados introduzidos pelo utilizador.
**/
static FILE* InputStdin()
{
	EscreverComCor(ANSI_TITULO, "Por favor introduza os dados do ficheiro.\n");
	printf("Carregue no enter numa linha vazia para terminar.\n\n");

	char inputBuffer[TAMANHO_MAX_BUFFER_INPUT];
	char dadosTemp[TAMANHO_MAX_BUFFER_FICHEIRO] = "";

	// Ciclo infinito até ter uma linha vazia
	while (1)
	{
		if (scanf("%999[^\n]%*c", inputBuffer) != 1 || inputBuffer[0] == '\0')
		{
			break;  // Sair se for linha vazia
		}

		strcat(dadosTemp, inputBuffer);
		strcat(dadosTemp, "\n");
	}

	return CriarFicheiroTempMemoria(dadosTemp);
}

int ImportarDadosStdin(Paciente pacientes[TAMANHO_MAX_ARRAY], int* numPacientes,
	Dieta dietas[TAMANHO_MAX_ARRAY], int* numDietas, Plano planos[TAMANHO_MAX_ARRAY], int* numPlanos)
{
	int tipoFicheiro = 0;

	// INPUT DO TIPO DE FICHEIRO
	int resultadoTipoFicheiro = LerTipoFicheiro(&tipoFicheiro);
	if (resultadoTipoFicheiro != SUCESSO)
		return resultadoTipoFicheiro;

	// INPUT DOS DADOS DO FICHEIRO
	FILE* ficheiroTemp = InputStdin();
	rewind(ficheiroTemp);

	// DEBUG para verificar conteudo do ficheiro
	if (MODO_DEBUG)
	{
		EscreverComCor(ANSI_DEBUG, "DEBUG OPCAO ESCOLHIDA:\n");
		printf("%d\n\n", tipoFicheiro);

		EscreverComCor(ANSI_DEBUG, "DEBUG CONTEUDO FICHEIRO:\n");
		printf(ANSI_DEBUG);
		int c;
		while ((c = fgetc(ficheiroTemp)) != EOF)
		{
			putchar(c);
		}
		printf(ANSI_RESET);

		LerTecla();
	}

	// IMPORTAR DADOS PARA O ARRAY
	int resultadoImportacao = 0;
	switch (tipoFicheiro)
	{
	case FICHEIRO_PACIENTES_TXT:
		resultadoImportacao = ImportarPacientesFichTexto(ficheiroTemp, "", FORMATO_PACIENTES_TXT, pacientes, numPacientes);
		break;

	case FICHEIRO_PACIENTES_TAB:
		resultadoImportacao = ImportarPacientesFichTexto(ficheiroTemp, "", FORMATO_PACIENTES_TAB, pacientes, numPacientes);
		break;

	case FICHEIRO_DIETAS_TXT:
		resultadoImportacao = ImportarDietasFichTexto(ficheiroTemp, "", FORMATO_DIETAS_TXT, dietas, numDietas);
		break;

	case FICHEIRO_DIETAS_TAB:
		resultadoImportacao = ImportarDietasFichTexto(ficheiroTemp, "", FORMATO_DIETAS_TAB, dietas, numDietas);
		break;

	case FICHEIRO_PLANOS_TXT:
		resultadoImportacao = ImportarPlanosFichTexto(ficheiroTemp, "", FORMATO_PLANOS_TXT, planos, numPlanos);
		break;

	case FICHEIRO_PLANOS_TAB:
		resultadoImportacao = ImportarPlanosFichTexto(ficheiroTemp, "", FORMATO_PLANOS_TAB, planos, numPlanos);
		break;
	}

	// fclose(ficheiroTemp);

	return resultadoImportacao;
}
