/**

	@file      OperacoesFicheiros.h

	@brief     Fun��es para opera��es relacionadas a ficheiros.

	@details   Este ficheiro cont�m declara��es de fun��es que realizam opera��es diversas
			   relacionadas a ficheiros.

	@author    Enrique George Rodrigues

	@date      Criado: 28.11.2023
	@date      Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#ifndef OPERACOES_FICHEIROS_H
#define OPERACOES_FICHEIROS_H

#include <stdbool.h>

// TODO: move to library?

/**
	@brief  Verifica se existe um dado ficheiro bin�rio atrav�s do nome do ficheiro.
	@param  nomeFicheiro - O nome do ficheiro bin�rio
	@retval				 - true (ficheiro existe)
	@retval              - false (ficheiro n�o existe)
**/
bool ExisteFicheiroBinario(const char* nomeFicheiro);

/**
	@brief  Fun��o que verifica se exite um ficheiro bin�rio. Se n�o existir, pergunta ao
			utilizador se quer cri�-lo.

	@param  nomeFicheiro - O nome do ficheiro bin�rio.

	@note Esta fun��o est� a ser utilizada nas verifica��es iniciais do programa para garantir
		  que todos os ficheiros bin�rios necess�rios existem antes de executar o programa.

	@retval 0  - Ficheiro criado com sucesso.
	@retval 1  - Ficheiro existe (FICHEIRO_EXISTE).
	@retval 2  - Erro criar ficheiro (ERRO_CRIAR_FICHEIRO).
	@retval 25 - Utilizador n�o deu permiss�o para criar o ficheiro. (ERRO_UTILIZADOR_NAO_DEU_PERMISSAO).
*/
int VerificarEAtualizarFicheiroBinario(const char* nomeFicheiro);

/**
	@brief Lida com o pedido de apagar a base de dados.
**/
void ApagarBaseDados();

/**
	@brief Importa os dados de um ficheiro espec�fico da base de dados (ficheiro .dat).

	@param caminhoFicheiro		- Caminho do arquivo bin�rio a ser importado.
	@param dados				- Array de estruturas para guardar os dados importados.
	@param tamDados				- Tamanho de cada elemento do array de dados.
	@param numDados				- O tamanho do array.
	@param tipoDados			- Nome do tipo de dados sendo importado (para a mensagem de log).
 */
void ImportarDadosBaseDados(const char* caminhoFicheiro, void* dados, size_t tamDados, int* numDados, const char* tipoDados);

#endif
