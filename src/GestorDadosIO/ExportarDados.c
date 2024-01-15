/**

	@file      ExportarDados.c

	@brief     Funções para exportar dados para ficheiros binários.

	@details   Este ficheiro contém implementações de funções para exportar dados de pacientes,
			   dietas e planos para ficheiros binários.

	@author    Enrique George Rodrigues

	@date      Created: 28.11.2023
	@date	   Last modified: 17.12.2023

	@copyright © Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "IODadosAPI.h"
#include "../LESI_PI_TP_a28602/Constantes.h"
#include "../LESI_PI_TP_a28602/EstruturaDados.h"

/**
	@brief  Exporta os dados para o ficheiro binário.

	@param  nomeFicheiro - O nome do ficheiro binário.
	@param  dados        - Os dados na memória.
	@param  tamanho      - O número de elementos na memória.
	@param  tamanhoElemento - O tamanho de cada elemento no array.

	@retval 0 - Sucesso na execução (SUCESSO).
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
