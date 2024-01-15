/**

	@file      Parametros.h

	@brief     Funções que controlam e lidam com os parâmetros opcionais do programa.

	@details   ~

	@author    Enrique George Rodrigues

	@date      Criado: 27.12.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef PARAMETROS_H
#define PARAMETROS_H

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
	int* tipoFicheiroPacientes, int* tipoFicheiroDietas, int* tipoFicheiroPlanos);

#endif
