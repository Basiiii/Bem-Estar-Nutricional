/**

	@file      Debug.c

	@brief     Funções que apresentam informações durante o modo debug.

	@author    Enrique George Rodrigues

	@date      Criado: 16.11.2023
	@date      Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#include <stdio.h>

#include "Constantes.h"
#include "EstruturaDados.h"
#include "Utils.h"

/**
	@brief Apresenta os nomes e tipos de ficheiros que o utilizador deseja importar.
	@param ficheiroPacientes - O nome do ficheiro de pacientes.
	@param ficheiroDietas    - O nome do ficheiro de dietas.
	@param ficheiroPlanos    - O nome do ficheiro de planos.
	@param tipoFicheiroPacientes     - O tipo do ficheiro de pacientes (txt, bin, tab).
	@param tipoFicheiroDietas        - O tipo do ficheiro de dietas (txt, bin, tab).
	@param tipoFicheiroPlanos        - O tipo do ficheiro de planos (txt, bin, tab).
**/
void DebugMostrarFicheirosUtilizador(char* ficheiroPacientes,
	char* ficheiroDietas, char* ficheiroPlanos, int pacientesTipo, int dietasTipo, int planosTipo)
{
	EscreverComCor(ANSI_DEBUG, "Ficheiros introduzidos nos parametros opcionais:\n\n");

	EscreverComCor(ANSI_DEBUG, "Ficheiro pacientes: %s (tipo:%d)\n", ficheiroPacientes, pacientesTipo);
	EscreverComCor(ANSI_DEBUG, "Ficheiro dietas: %s (tipo:%d)\n", ficheiroDietas, dietasTipo);
	EscreverComCor(ANSI_DEBUG, "Ficheiro planos: %s (tipo:%d)\n\n", ficheiroPlanos, planosTipo);
}

/**
	@brief Apresenta os dados dos pacientes na memória para debugging.
	@param pacientes Array de pacientes.
	@param numPacientes Número de pacientes.
 */
void DebugMostrarPacientes(Paciente pacientes[TAMANHO_MAX_ARRAY], int numPacientes)
{
	EscreverComCor(ANSI_DEBUG, "\nPACIENTES NA MEMORIA:");

	if (numPacientes != 0)
		printf("\n\n");

	for (int i = 0; i < numPacientes; ++i)
	{
		EscreverComCor(ANSI_DEBUG, OUTPUT_FORMATO_DEBUG_PACIENTES_MEMORIA,
			pacientes[i].id, pacientes[i].nome, pacientes[i].tel);
	}

	printf("\n");
}

/**
	@brief Apresenta os dados das dietas na memória para debugging.
	@param dietas		- Array de dietas.
	@param numDietas	- Número de dietas.
 */
void DebugMostrarDietas(Dieta dietas[TAMANHO_MAX_ARRAY], int numDietas)
{
	EscreverComCor(ANSI_DEBUG, "\nDIETAS NA MEMORIA:");

	if (numDietas != 0)
		printf("\n\n");

	for (int i = 0; i < numDietas; i++)
	{
#ifdef _WIN32
		EscreverComCor(ANSI_DEBUG, OUTPUT_FORMATO_DEBUG_DIETAS_MEMORIA_WIN,
			dietas[i].idPaciente, ConverterDatetimeParaString(dietas[i].data), dietas[i].data,
			ConverterRefeicaoParaTexto(dietas[i].refeicao), dietas[i].refeicao, dietas[i].comida, dietas[i].calorias);
#else
		EscreverComCor(ANSI_DEBUG, OUTPUT_FORMATO_DEBUG_DIETAS_MEMORIA_LINUX,
			dietas[i].idPaciente, ConverterDatetimeParaString(dietas[i].data), dietas[i].data,
			ConverterRefeicaoParaTexto(dietas[i].refeicao), dietas[i].refeicao, dietas[i].comida, dietas[i].calorias);
#endif
	}

	printf("\n");
}

/**
	@brief Apresenta os dados dos planos na memória para debugging.
	@param planos		- Array de planos.
	@param numPlanos	- Número de planos.
 */
void DebugMostrarPlanos(Plano planos[TAMANHO_MAX_ARRAY], int numPlanos)
{
	EscreverComCor(ANSI_DEBUG, "\nPLANOS NA MEMORIA : ");

	if (numPlanos != 0)
		printf("\n\n");

	for (int i = 0; i < numPlanos; i++)
	{
#ifdef _WIN32
		EscreverComCor(ANSI_DEBUG, OUTPUT_FORMATO_DEBUG_PLANOS_MEMORIA_WIN,
			planos[i].idPaciente, ConverterDatetimeParaString(planos[i].data), planos[i].data,
			ConverterRefeicaoParaTexto(planos[i].refeicao), planos[i].refeicao, planos[i].calorias[0], planos[i].calorias[1]);
#else
		EscreverComCor(ANSI_DEBUG, OUTPUT_FORMATO_DEBUG_PLANOS_MEMORIA_LINUX,
			planos[i].idPaciente, ConverterDatetimeParaString(planos[i].data), planos[i].data,
			ConverterRefeicaoParaTexto(planos[i].refeicao), planos[i].refeicao, planos[i].calorias[0], planos[i].calorias[1]);
#endif
	}

	printf("\n");
}

/**
	@brief Apresenta os dados na memória para debugging.
	@param pacientes	- Array de pacientes.
	@param numPacientes - Número de pacientes.
	@param dietas		- Array de dietas.
	@param numDietas	- Número de dietas.
	@param planos		- Array de planos.
	@param numPlanos	- Número de planos.
 */
void DebugMostrarDadosMemoria(Paciente pacientes[TAMANHO_MAX_ARRAY], int numPacientes,
	Dieta dietas[TAMANHO_MAX_ARRAY], int numDietas,
	Plano planos[TAMANHO_MAX_ARRAY], int numPlanos)
{
	printf(ANSI_DEBUG);

	DebugMostrarPacientes(pacientes, numPacientes);
	DebugMostrarDietas(dietas, numDietas);
	DebugMostrarPlanos(planos, numPlanos);

	printf(ANSI_RESET);
}
