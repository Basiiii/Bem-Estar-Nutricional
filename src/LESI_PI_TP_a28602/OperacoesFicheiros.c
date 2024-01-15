/**

	@file      OperacoesFicheiros.c

	@brief     Implementa��o das fun��es relacionadas �s opera��es em ficheiros.

	@details   Este ficheiro cont�m implementa��es das fun��es para verificar e controlar
			   ficheiros.

	@author    Enrique George Rodrigues

	@date      Criado: 28.11.2023
	@date      Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../GestorDadosIO/IODadosAPI.h"

#include "Constantes.h"
#include "Utils.h"

/**
	@brief  Verifica se existe um dado ficheiro bin�rio atrav�s do nome do ficheiro.
	@param  nomeFicheiro - O nome do ficheiro bin�rio
	@retval				 - true (ficheiro existe)
	@retval              - false (ficheiro n�o existe)
**/
bool ExisteFicheiroBinario(const char* nomeFicheiro)
{
	FILE* ficheiro = fopen(nomeFicheiro, "r");

	if (ficheiro == NULL)
	{
		return false; // Ficheiro n�o existe ou erro ao abrir
	}

	fclose(ficheiro);
	return true; // Ficheiro existe
}

/**
	@brief  Cria um ficheiro bin�rio com um dado nome.
	@param  nomeFicheiro - O nome do ficheiro bin�rio.
	@retval              - 0 se conseguir criar o ficheiro - (SUCESSO).
	@retval              - 2 se n�o conseguir criar o ficheiro - (ERRO_CRIAR_FICHEIRO).
**/
static int CriarFicheiroBinario(const char* nomeFicheiro)
{
	FILE* ficheiro = fopen(nomeFicheiro, "wb");

	if (ficheiro == NULL)
	{
		return ERRO_CRIAR_FICHEIRO;
	}

	fclose(ficheiro);
	return SUCESSO;
}

/**
	@brief  Apaga os ficheiros binarios que servem de base de dados da aplicacao.

	@details	Util quando se quer fazer um "reset" em caso de problemas. Esta a��o � irrevers�vel
				e deve ser utilizado com cuidado. Pergunte sempre ao utilizador para confirmar.

	@warning	Esta fun��o apaga TODOS os dados dos utilizadores. DEVE SER UTILIZADO COM CUIDADO!

	@retval  - 5 se houver erro ao apagar os ficheiros bin�rios - ERRO_APAGAR_FICHEIROS_BIN.
			   0 se correr com sucesso - SUCESSO.
**/
static int ApagarFicheirosBinarios()
{
	if (remove(FICHEIRO_BIN_PACIENTES) != 0)
		return ERRO_APAGAR_FICHEIROS_BIN;

	if (remove(FICHEIRO_BIN_DIETAS) != 0)
		return ERRO_APAGAR_FICHEIROS_BIN;

	if (remove(FICHEIRO_BIN_PLANOS) != 0)
		return ERRO_APAGAR_FICHEIROS_BIN;

	return SUCESSO;
}

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
int VerificarEAtualizarFicheiroBinario(const char* nomeFicheiro)
{
	if (ExisteFicheiroBinario(nomeFicheiro))
	{
		return FICHEIRO_EXISTE;
	}
	else
	{
		EscreverComCor(ANSI_ALERTA, "O ficheiro %s nao existe. Deseja criar? (Y/N)\n", nomeFicheiro);
		char escolha = LerTecla();

		if (escolha == CONFIRMAR_SIM)
		{
			if (CriarFicheiroBinario(nomeFicheiro) == SUCESSO)
				return SUCESSO;
			else
				return ERRO_CRIAR_FICHEIRO;
		}
		else
		{
			return ERRO_UTILIZADOR_NAO_DEU_PERMISSAO;
		}
	}
}

/**
	@brief Lida com o pedido de apagar a base de dados. Depois de terminar, seja com sucesso ou n�o, o programa termina.
**/
void ApagarBaseDados()
{
	EscreverComCor(ANSI_ALERTA, "ALERTA: Foi detetado um pedido para apagar a base de dados.\n");
	EscreverComCor(ANSI_ALERTA, "Deseja continuar e apagar tudo? (%c/%c)\n", CONFIRMAR_SIM, CONFIRMAR_NAO);
	EscreverComCor(ANSI_COR_VERMELHO, "AVISO: ESTA ACAO E IRREVERSIVEL!\n");

	// CONFIRMAR SE O UTILIZADOR DESEJA APAGAR
	char confirmar = LerTecla();
	if (confirmar != CONFIRMAR_SIM)
	{
		printf("\n\n");
		EscreverComCor(ANSI_ALERTA, "ALERTA: Operacao cancelada pelo utilizador.\n");
		printf("Os ficheiros NAO serao apagados...\n");
		exit(ERRO_APAGAR_BASE_DADOS);
	}

	// CONFIRMAR DE NOVO
	printf("\n");
	EscreverComCor(ANSI_COR_VERMELHO, "AVISO: Tem a certeza que deseja apagar todos os ficheiros dos dados dos pacientes? (%c/%c)\n", CONFIRMAR_SIM, CONFIRMAR_NAO);
	char confirmar2 = LerTecla();
	if (confirmar2 != CONFIRMAR_SIM)
	{
		printf("\n\n");
		EscreverComCor(ANSI_ALERTA, "ALERTA: Operacao cancelada pelo utilizador.\n");
		printf("Os ficheiros NAO serao apagados...\n");
		exit(ERRO_APAGAR_BASE_DADOS);
	}

	// APAGAR BASE DADOS
	if (ApagarFicheirosBinarios() == SUCESSO)
	{
		printf("\n");
		EscreverComCor(ANSI_SUCESSO, "Todos os ficheiros foram apagados com sucesso.\n");
		exit(SUCESSO);
	}
	else
	{
		EscreverComCor(ANSI_ERRO, "\nERRO: Falha ao apagar os ficheiros. ERRO NUMERO %d.\n", ERRO_APAGAR_FICHEIROS_BIN);
		exit(ERRO_APAGAR_BASE_DADOS);
	}
}

/**
	@brief Importa os dados de um ficheiro espec�fico da base de dados (ficheiro .dat).

	@param caminhoFicheiro		- Caminho do arquivo bin�rio a ser importado.
	@param dados				- Array de estruturas para guardar os dados importados.
	@param tamDados				- Tamanho de cada elemento do array de dados.
	@param numDados				- O tamanho do array.
	@param tipoDados			- Nome do tipo de dados sendo importado (para a mensagem de log).
 */
void ImportarDadosBaseDados(const char* caminhoFicheiro, void* dados, size_t tamDados, int* numDados, const char* tipoDados)
{
	EscreverComCor(ANSI_INFO, "A importar dados de %s da base de dados para memoria...\n", tipoDados);

	int resultado = ImportarDadosFichBinario(caminhoFicheiro, dados, tamDados, numDados);

	if (resultado == SUCESSO)
	{
		EscreverComCor(ANSI_SUCESSO, "Dados de %s importados com sucesso.\n", tipoDados);
	}
	else if (resultado == ERRO_TAMANHO_EXCEDIDO)
	{
		EscreverComCor(ANSI_ERRO, "ERRO: Tamanho m�ximo permitido foi excedido.\n");
		TerminarProgramaComErro(ERRO_TAMANHO_EXCEDIDO);
	}
	else
	{
		EscreverComCor(ANSI_ERRO, "ERRO: Erro ao importar os dados de %s.\n", tipoDados);
		TerminarProgramaComErro(ERRO_IMPORTAR_DADOS_BIN);
	}
}
