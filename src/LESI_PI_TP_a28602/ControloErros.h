/**

	@file      ControloErros.h

	@brief	   Fun��es que lidam com erros.

	@details   ~

	@author    Enrique George Rodrigues

	@date      Criado: 27.12.2023
	@date	   Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef CONTROLO_ERROS_H
#define CONTROLO_ERROS_H

/**
	@brief Lida com os erros da importa��o de dados.
	@param codigoErro - O c�digo do erro.
**/
void LidarErrosImportacaoDados(int codigoErro);

/**
	@brief Lida com erros na verifica��o da exist�ncia dos ficheiros da base de dados.
	@param codigoErro - O c�digo do erro.
**/
void LidarErroVerificacaoFicheiroBinario(int codigoErro);

/**
	@brief Lida com os erros da funcionalidade 2.
	@param codigoErro - O c�digo do erro.
**/
void LidarErroPacientesUltrapassamCalorias(int codigoErro);

/**
	@brief Lida com os erros da funcionalidade 3.
	@param codigoErro - O c�digo de erro.
**/
void LidarErroPacientesForaPlano(int codigoErro);

/**
	@brief Lida com os erros da funcionalidade 4.
	@param codigoErro - O c�digo de erro.
**/
void LidarErroListarPlanoNutricional(int codigoErro);

/**
	@brief Lida com os erros da funcionalidade 5.
	@param codigoErro - O c�digo de erro.
**/
void LidarErroListarMediasCaloriasPorRefeicao(int codigoErro);

/**
	@brief Lida com os erros da funcionalidade 6.
	@param codigoErro - O c�digo de erro.
**/
void LidarErroGerarTabelaRefeicoes(int codigoErro);

/**
	@brief Lida com os erros ao guardar dados.
	@param codigoErro - O c�digo de erro.
**/
void LidarErroGuardarDados(int codigoErro);

#endif
