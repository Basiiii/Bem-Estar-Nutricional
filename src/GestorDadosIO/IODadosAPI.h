/**

	@file      IODadosAPI.h
	@brief     Fun��es de importar e exportar dados dos ficheiros ``ImportarDados.c`` e ``ExportarDados.c``.
	@details   ~
	@author    Enrique George Rodrigues
	@date      23.12.2023
	@copyright � Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef IO_DADOS_API_H
#define IO_DADOS_API_H

#include "../LESI_PI_TP_a28602/Constantes.h"
#include "../LESI_PI_TP_a28602/EstruturaDados.h"
#include "../LESI_PI_TP_a28602/Utils.h"

// Verificar se est� a ser compilado no Windows
#ifdef _WIN32
	// Definir anota��es de importar e exportar
#ifdef IO_DADOS_EXPORTS
#define IO_DADOS_API __declspec(dllexport)
#else
#define IO_DADOS_API __declspec(dllimport)
#endif
// Se n�o for Windows (Linux)
#else
#define IO_DADOS_API // Definir macro como macro vazio
#endif

/**
	@brief  Exporta os dados para o ficheiro bin�rio.

	@param  nomeFicheiro - O nome do ficheiro bin�rio.
	@param  dados        - Os dados na mem�ria.
	@param  tamanho      - O n�mero de elementos na mem�ria.
	@param  tamanhoElemento - O tamanho de cada elemento no array.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 12 - Erro ao abrir ficheiro (ERRO_ABRIR_FICHEIRO).
**/
IO_DADOS_API int ExportarDadosFichBinario(const char* nomeFicheiro, void* dados, int tamanho, size_t tamanhoElemento);

/**
	@brief  Importa os dados a partir do ficheiro bin�rio.

	@param  nomeFicheiro - O nome do ficheiro bin�rio.
	@param  dados        - O array de dados a ser importado.
	@param  tamanhoRegisto - O tamanho de cada registro em bytes.
	@param  numRegistos  - Um apontador para a vari�vel que guarda o n�mero de registros.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
	@retval 13 - Erro, tamanho m�ximo excedido. (ERRO_TAMANHO_EXCEDIDO).
 **/
IO_DADOS_API int ImportarDadosFichBinario(const char* nomeFicheiro, void* dados, size_t tamanhoRegisto, int* numRegistos);

/**
	@brief	Importa dados de pacientes de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso n�o tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param formato			- O formato dos dados do ficheiro de texto (FORMATO_PACIENTES_TXT ou FORMATO_PACIENTES_TAB).
	@param pacientes		- O array de pacientes.
	@param numPacientes		- Um apontador para a vari�vel que guarda o n�mero de pacientes.

	@note	S� � preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 10 - Erro formato ficheiro (ERRO_FORMATO_INVALIDO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
 */
IO_DADOS_API int ImportarPacientesFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Paciente pacientes[TAMANHO_MAX_ARRAY], int* numPacientes);

/**
	@brief	Importa dados de dietas de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso n�o tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param formato			- O formato dos dados do ficheiro de texto (FORMATO_DIETAS_TXT ou FORMATO_DIETAS_TAB).
	@param dietas			- O array de dietas.
	@param numDietas		- Um apontador para a vari�vel que guarda o n�mero de dietas.

	@note	S� � preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 10 - Erro formato ficheiro (ERRO_FORMATO_INVALIDO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
 */
IO_DADOS_API int ImportarDietasFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Dieta dietas[TAMANHO_MAX_ARRAY], int* numDietas);

/**
	@brief	Importa dados de planos de um ficheiro de texto e adiciona-os aos dados guardados,
			ignorando os recordes duplicados.

	@param file				- Apontador do tipo FILE* do ficheiro. Caso n�o tenha, pode mandar NULL.
	@param nomeFicheiro		- O nome do ficheiro de texto.
	@param planos			- O array de planos.
	@param numPlanos		- Um apontador para a vari�vel que guarda o n�mero de planos.

	@note	S� � preciso mandar o nome do ficheiro ou o apontador FILE*.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 8 - Ficheiro vazio (ERRO_FICHEIRO_VAZIO).
	@retval 9 - Erro na leitura do ficheiro (ERRO_LEITURA_FICHEIRO).
	@retval 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
	@retval 13 - Erro, tamanho m�ximo excedido. (ERRO_TAMANHO_EXCEDIDO).
 */
IO_DADOS_API int ImportarPlanosFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Plano planos[TAMANHO_MAX_ARRAY], int* numPlanos);

#endif // IO_DADOS_API_H
