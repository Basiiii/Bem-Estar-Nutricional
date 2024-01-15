/**

	@file      IODadosAPI.h
	@brief     Funções de importar e exportar dados dos ficheiros ``ImportarDados.c`` e ``ExportarDados.c``.
	@details   ~
	@author    Enrique George Rodrigues
	@date      23.12.2023
	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef IO_DADOS_API_H
#define IO_DADOS_API_H

#include "../LESI_PI_TP_a28602/Constantes.h"
#include "../LESI_PI_TP_a28602/EstruturaDados.h"
#include "../LESI_PI_TP_a28602/Utils.h"

// Verificar se está a ser compilado no Windows
#ifdef _WIN32
	// Definir anotações de importar e exportar
#ifdef IO_DADOS_EXPORTS
#define IO_DADOS_API __declspec(dllexport)
#else
#define IO_DADOS_API __declspec(dllimport)
#endif
// Se não for Windows (Linux)
#else
#define IO_DADOS_API // Definir macro como macro vazio
#endif

/**
	@brief  Exporta os dados para o ficheiro binário.

	@param  nomeFicheiro - O nome do ficheiro binário.
	@param  dados        - Os dados na memória.
	@param  tamanho      - O número de elementos na memória.
	@param  tamanhoElemento - O tamanho de cada elemento no array.

	@retval 0 - Sucesso na execução (SUCESSO).
	@retval 12 - Erro ao abrir ficheiro (ERRO_ABRIR_FICHEIRO).
**/
IO_DADOS_API int ExportarDadosFichBinario(const char* nomeFicheiro, void* dados, int tamanho, size_t tamanhoElemento);

/**
	@brief  Importa os dados a partir do ficheiro binário.

	@param  nomeFicheiro - O nome do ficheiro binário.
	@param  dados        - O array de dados a ser importado.
	@param  tamanhoRegisto - O tamanho de cada registro em bytes.
	@param  numRegistos  - Um apontador para a variável que guarda o número de registros.

	@retval 0 - Sucesso na execução (SUCESSO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
	@retval 13 - Erro, tamanho máximo excedido. (ERRO_TAMANHO_EXCEDIDO).
 **/
IO_DADOS_API int ImportarDadosFichBinario(const char* nomeFicheiro, void* dados, size_t tamanhoRegisto, int* numRegistos);

/**
	@brief	Importa dados de pacientes de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso não tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param formato			- O formato dos dados do ficheiro de texto (FORMATO_PACIENTES_TXT ou FORMATO_PACIENTES_TAB).
	@param pacientes		- O array de pacientes.
	@param numPacientes		- Um apontador para a variável que guarda o número de pacientes.

	@note	Só é preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execução (SUCESSO).
	@retval 10 - Erro formato ficheiro (ERRO_FORMATO_INVALIDO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
 */
IO_DADOS_API int ImportarPacientesFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Paciente pacientes[TAMANHO_MAX_ARRAY], int* numPacientes);

/**
	@brief	Importa dados de dietas de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso não tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param formato			- O formato dos dados do ficheiro de texto (FORMATO_DIETAS_TXT ou FORMATO_DIETAS_TAB).
	@param dietas			- O array de dietas.
	@param numDietas		- Um apontador para a variável que guarda o número de dietas.

	@note	Só é preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execução (SUCESSO).
	@retval 10 - Erro formato ficheiro (ERRO_FORMATO_INVALIDO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
 */
IO_DADOS_API int ImportarDietasFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Dieta dietas[TAMANHO_MAX_ARRAY], int* numDietas);

/**
	@brief	Importa dados de planos de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso não tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param planos			- O array de planos.
	@param numPlanos		- Um apontador para a variável que guarda o número de planos.

	@note	Só é preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execução (SUCESSO).
	@retval 8 - Ficheiro vazio (ERRO_FICHEIRO_VAZIO).
	@retval 9 - Erro na leitura do ficheiro (ERRO_LEITURA_FICHEIRO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
	@retval 13 - Erro, tamanho máximo excedido. (ERRO_TAMANHO_EXCEDIDO).
 */
IO_DADOS_API int ImportarPlanosFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Plano planos[TAMANHO_MAX_ARRAY], int* numPlanos);

#endif // IO_DADOS_API_H
