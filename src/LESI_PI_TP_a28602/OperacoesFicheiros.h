/**

	@file      OperacoesFicheiros.h

	@brief     Funções para operações relacionadas a ficheiros.

	@details   Este ficheiro contém declarações de funções que realizam operações diversas
			   relacionadas a ficheiros.

	@author    Enrique George Rodrigues

	@date      Criado: 28.11.2023
	@date      Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#ifndef OPERACOES_FICHEIROS_H
#define OPERACOES_FICHEIROS_H

#include <stdbool.h>

// TODO: move to library?

/**
	@brief  Verifica se existe um dado ficheiro binário através do nome do ficheiro.
	@param  nomeFicheiro - O nome do ficheiro binário
	@retval				 - true (ficheiro existe)
	@retval              - false (ficheiro não existe)
**/
bool ExisteFicheiroBinario(const char* nomeFicheiro);

/**
	@brief  Função que verifica se exite um ficheiro binário. Se não existir, pergunta ao
			utilizador se quer criá-lo.

	@param  nomeFicheiro - O nome do ficheiro binário.

	@note Esta função está a ser utilizada nas verificações iniciais do programa para garantir
		  que todos os ficheiros binários necessários existem antes de executar o programa.

	@retval 0  - Ficheiro criado com sucesso.
	@retval 1  - Ficheiro existe (FICHEIRO_EXISTE).
	@retval 2  - Erro criar ficheiro (ERRO_CRIAR_FICHEIRO).
	@retval 25 - Utilizador não deu permissão para criar o ficheiro. (ERRO_UTILIZADOR_NAO_DEU_PERMISSAO).
*/
int VerificarEAtualizarFicheiroBinario(const char* nomeFicheiro);

/**
	@brief Lida com o pedido de apagar a base de dados.
**/
void ApagarBaseDados();

/**
	@brief Importa os dados de um ficheiro específico da base de dados (ficheiro .dat).

	@param caminhoFicheiro		- Caminho do arquivo binário a ser importado.
	@param dados				- Array de estruturas para guardar os dados importados.
	@param tamDados				- Tamanho de cada elemento do array de dados.
	@param numDados				- O tamanho do array.
	@param tipoDados			- Nome do tipo de dados sendo importado (para a mensagem de log).
 */
void ImportarDadosBaseDados(const char* caminhoFicheiro, void* dados, size_t tamDados, int* numDados, const char* tipoDados);

#endif
