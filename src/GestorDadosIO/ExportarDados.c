/**

	@file      ExportarDados.c

	@brief     Fun��es para exportar dados para ficheiros bin�rios.

	@details   Este ficheiro cont�m implementa��es de fun��es para exportar dados de pacientes,
			   dietas e planos para ficheiros bin�rios.

	@author    Enrique George Rodrigues

	@date      Created: 28.11.2023
	@date	   Last modified: 17.12.2023

	@copyright � Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "IODadosAPI.h"
#include "../LESI_PI_TP_a28602/Constantes.h"
#include "../LESI_PI_TP_a28602/EstruturaDados.h"

/**
	@brief  Exporta os dados para o ficheiro bin�rio.

	@param  nomeFicheiro - O nome do ficheiro bin�rio.
	@param  dados        - Os dados na mem�ria.
	@param  tamanho      - O n�mero de elementos na mem�ria.
	@param  tamanhoElemento - O tamanho de cada elemento no array.

	@retval 0 - Sucesso na execu��o (SUCESSO).
	@retval 12 - Erro ao abrir ficheiro (ERRO_ABRIR_FICHEIRO).
**/
int ExportarDadosFichBinario(const char* nomeFicheiro, void* dados, int tamanho, size_t tamanhoElemento)
{
	FILE* file = fopen(nomeFicheiro, "wb");
	if (file == NULL)
		return ERRO_ABRIR_FICHEIRO;

	fwrite(dados, tamanhoElemento, tamanho, file);

	fclose(file);
	return SUCESSO;
}
