/**

	@file      ControloErros.c

	@brief	   Funções que lidam com erros.

	@author    Enrique George Rodrigues

	@date      Criado: 27.12.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#include <stdio.h>
#include "Constantes.h"
#include "Utils.h"

/**
	@brief Lida com os erros da importação de dados.
	@param codigoErro - O código do erro.
**/
void LidarErrosImportacaoDados(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_TAMANHO_EXCEDIDO:
		EscreverComCor(ANSI_ERRO, "ERRO: Tamanho maximo permitido foi excedido.\n");
		TerminarProgramaComErro(ERRO_TAMANHO_EXCEDIDO);
		break;

	case ERRO_IMPORTAR_DADOS:
		EscreverComCor(ANSI_ERRO, "ERRO: Erro ao importar os dados do ficheiro.\n");
		TerminarProgramaComErro(ERRO_IMPORTAR_DADOS);
		break;
	}
}

/**
	@brief Lida com erros na verificação da existência dos ficheiros da base de dados.
	@param codigoErro - O código do erro.
**/
void LidarErroVerificacaoFicheiroBinario(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_UTILIZADOR_NAO_DEU_PERMISSAO:
		EscreverComCor(ANSI_ERRO, "O utilizador nao deu permissao para criar o ficheiro.\n");
		TerminarProgramaComErro(ERRO_UTILIZADOR_NAO_DEU_PERMISSAO);
		break;

	case ERRO_CRIAR_FICHEIRO:
		EscreverComCor(ANSI_ERRO, "Houve um erro na criacao do ficheiro.\n");
		TerminarProgramaComErro(ERRO_CRIAR_FICHEIRO);
		break;
	}
}

/**
	@brief Lida com os erros da funcionalidade 2.
	@param codigoErro - O código do erro.
**/
void LidarErroPacientesUltrapassamCalorias(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_ALOCAR_MEMORIA:
		EscreverComCor(ANSI_ERRO, "Erro ao alocar memoria. Por favor tente de novo.\n");
		break;

	case ERRO_LEITURA_DATA:
		EscreverComCor(ANSI_ERRO, "Erro ao ler a data. Por favor, insira a data com o formato correto.\n");
		break;

	case ERRO_LEITURA_LIMITE_CALORIAS:
		EscreverComCor(ANSI_ERRO, "Erro ao ler o limite de calorias. Por favor insira um valor valido.\n");
		break;
	}
}

/**
	@brief Lida com os erros da funcionalidade 3.
	@param codigoErro - O código de erro.
**/
void LidarErroPacientesForaPlano(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_LEITURA_DATA:
		EscreverComCor(ANSI_ERRO, "Erro na leitura da data. Por favor tente de novo.\n");
		break;
	}
}

/**
	@brief Lida com os erros da funcionalidade 4.
	@param codigoErro - O código de erro.
**/
void LidarErroListarPlanoNutricional(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_LEITURA_DATA:
		EscreverComCor(ANSI_ERRO, "Erro na leitura da data. Por favor tente de novo.\n");
		break;

	case ERRO_LEITURA_ID_PACIENTE:
		EscreverComCor(ANSI_ERRO, "Erro na leitura do ID paciente. Por favor tente de novo.\n");
		break;

	case ERRO_LEITURA_TIPO_REFEICAO:
		EscreverComCor(ANSI_ERRO, "Erro na leitura do tipo de refeicao. Por favor tente de novo.\n");
		break;
	}
}

/**
	@brief Lida com os erros da funcionalidade 5.
	@param codigoErro - O código de erro.
**/
void LidarErroListarMediasCaloriasPorRefeicao(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_LEITURA_DATA:
		EscreverComCor(ANSI_ERRO, "Erro na leitura da data. Por favor tente de novo.\n");
		break;
	}
}

/**
	@brief Lida com os erros da funcionalidade 6.
	@param codigoErro - O código de erro.
**/
void LidarErroGerarTabelaRefeicoes(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_VALOR_NULLO:
		EscreverComCor(ANSI_ERRO, "Houve um erro na execucao da funcao. Por favor tente de novo.\n");
		break;
	}
}

/**
	@brief Lida com os erros ao guardar dados.
	@param codigoErro - O código de erro.
**/
void LidarErroGuardarDados(int codigoErro)
{
	switch (codigoErro)
	{
	case ERRO_ABRIR_FICHEIRO:
		EscreverComCor(ANSI_ERRO, "Erro ao tentar abrir a base de dados. Por favor tente de novo.\n");
		break;

	default:
		printf("\n");
		EscreverComCor(ANSI_ERRO, "Nao foi possivel guardar todos os dados. Por favor tente novamente.\n");
		break;
	}

	printf("Carregue numa tecla para voltar ao menu.\n");
	LerTecla();
}
