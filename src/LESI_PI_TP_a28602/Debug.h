/**

	@file      Debug.h

	@brief	   Funções que apresentam informações durante o modo debug.

	@details   ~

	@author    Enrique George Rodrigues

	@date      Criado: 17.12.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#include "Constantes.h"
#include "EstruturaDados.h"
#include "Utils.h"

/**
	@brief Apresenta os nomes e tipos de ficheiros que o utilizador deseja importar.
	@param ficheiroPacientes - O nome do ficheiro de pacientes.
	@param ficheiroDietas    - O nome do ficheiro de dietas.
	@param ficheiroPlanos    - O nome do ficheiro de planos.
	@param pacientesTipo     - O tipo do ficheiro de pacientes (txt, bin, tab).
	@param dietasTipo        - O tipo do ficheiro de dietas (txt, bin, tab).
	@param planosTipo        - O tipo do ficheiro de planos (txt, bin, tab).
**/
void DebugMostrarFicheirosUtilizador(char* ficheiroPacientes,
	char* ficheiroDietas, char* ficheiroPlanos, int pacientesTipo, int dietasTipo, int planosTipo);

/**
	@brief Apresenta os dados dos pacientes na memória para debugging.
	@param pacientes Array de pacientes.
	@param numPacientes Número de pacientes.
 */
void DebugMostrarPacientes(Paciente pacientes[TAMANHO_MAX_ARRAY], int numPacientes);

/**
	@brief Apresenta os dados das dietas na memória para debugging.
	@param dietas		- Array de dietas.
	@param numDietas	- Número de dietas.
 */
void DebugMostrarDietas(Dieta dietas[TAMANHO_MAX_ARRAY], int numDietas);

/**
	@brief Apresenta os dados dos planos na memória para debugging.
	@param planos		- Array de planos.
	@param numPlanos	- Número de planos.
 */
void DebugMostrarPlanos(Plano planos[TAMANHO_MAX_ARRAY], int numPlanos);

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
	Plano planos[TAMANHO_MAX_ARRAY], int numPlanos);

#endif
