/**

	@file      ImportarDados.c

	@brief     Funções para importar dados a partir de ficheiros (binários e de texto).

	@details   Este ficheiro contém implementações de funções para importar dados de pacientes, dietas
			   e planos a partir de ficheiros binários e de texto. As funções são projetadas para adicionar
			   novos dados aos dados já existentes, ignorando registros duplicados quando adequado.

	@author    Enrique George Rodrigues

	@date      Created: 28.11.2023
	@date      Last modified: 18.12.2023

	@copyright © Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IODadosAPI.h"
#include "../LESI_PI_TP_a28602/Constantes.h"
#include "../LESI_PI_TP_a28602/EstruturaDados.h"
#include "../LESI_PI_TP_a28602/Utils.h"

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
int ImportarDadosFichBinario(const char* nomeFicheiro, void* dados, size_t tamanhoRegisto, int* numRegistos)
{
	FILE* file = fopen(nomeFicheiro, "rb");
	if (file == NULL)
		return ERRO_ABRIR_FICHEIRO;

	// Determinar o número de registros no ficheiro bin
	fseek(file, 0, SEEK_END);
	size_t tamanhoFicheiro = ftell(file);
	int numRegistosFicheiro = (int)tamanhoFicheiro / tamanhoRegisto;

	// Verificar se o número de registros é superior ao limite de registros
	if (*numRegistos + numRegistosFicheiro > TAMANHO_MAX_ARRAY)
	{
		fclose(file);
		return ERRO_TAMANHO_EXCEDIDO;
	}

	// Atualizar número de registros
	*numRegistos = *numRegistos + numRegistosFicheiro;

	// Voltar ao início do ficheiro e ler dados de bin para o array
	fseek(file, 0, SEEK_SET);
	fread(dados, tamanhoRegisto, numRegistosFicheiro, file);

	fclose(file);
	return SUCESSO;
}

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
int ImportarPacientesFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Paciente pacientes[TAMANHO_MAX_ARRAY], int* numPacientes)
{
	if (file != NULL) // se receber apenas o nome do ficheiro e não o apontador do FILE*
	{
		rewind(file);
	}
	else // como o apontador é NULLO vamos tentar abrir o ficheiro com o nome
	{
		file = fopen(nomeFicheiro, "r");
		if (file == NULL)
		{
			return ERRO_ABRIR_FICHEIRO;
		}
	}

	if (strcmp(formatoFicheiro, "") == 0)
		return ERRO_FORMATO_INVALIDO;

	Paciente tempPaciente;

	while (*numPacientes < TAMANHO_MAX_ARRAY && fscanf(file, formatoFicheiro,
		&tempPaciente.id,
		tempPaciente.nome,
		&tempPaciente.tel) == 3)
	{
		// Verifica se é um registo duplicado
		int isDuplicate = 0;
		for (int j = 0; j < *numPacientes; j++)
		{
			if (tempPaciente.id == pacientes[j].id)
			{
				isDuplicate = 1;
				break;  // Paramos se encontrarmos um registo duplicado
			}
		}

		// Se não é um registo duplicado, adicionar ao array principal
		if (!isDuplicate)
		{
			pacientes[*numPacientes] = tempPaciente;
			(*numPacientes)++;
		}
	}

	fclose(file);

	return SUCESSO;
}

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
int ImportarDietasFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Dieta dietas[TAMANHO_MAX_ARRAY], int* numDietas)
{
	if (file != NULL) // se receber apenas o nome do ficheiro e não o apontador do FILE*
	{
		rewind(file);
	}
	else // como o apontador é NULLO vamos tentar abrir o ficheiro com o nome
	{
		file = fopen(nomeFicheiro, "r");
		if (file == NULL)
		{
			return ERRO_ABRIR_FICHEIRO;
		}
	}

	if (strcmp(formatoFicheiro, "") == 0)
		return ERRO_FORMATO_INVALIDO;

	Dieta tempDieta;
	char tempData[TAMANHO_DATA_TEXTO];
	char tempRefeicao[TAMANHO_REFEICAO] = "\0";

	while (*numDietas < TAMANHO_MAX_ARRAY && fscanf(file, formatoFicheiro,
		&tempDieta.idPaciente,
		tempData,
		tempRefeicao,
		tempDieta.comida,
		&tempDieta.calorias) == 5)
	{
		tempDieta.data = ConverterStringParaDatetime(tempData);

		tempDieta.refeicao = ConverterRefeicaoParaId(tempRefeicao);

		dietas[*numDietas] = tempDieta;
		(*numDietas)++;
	}

	if (ferror(file))
	{
		fclose(file);
		return ERRO_LEITURA_FICHEIRO;
	}

	fclose(file);

	return SUCESSO;
}

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
int ImportarPlanosFichTexto(FILE* file, const char* nomeFicheiro, char* formatoFicheiro, Plano planos[TAMANHO_MAX_ARRAY], int* numPlanos)
{
	if (file != NULL) // se receber apenas o nome do ficheiro e não o apontador do FILE*
	{
		rewind(file);
	}
	else // como o apontador é NULLO vamos tentar abrir o ficheiro com o nome
	{
		file = fopen(nomeFicheiro, "r");
		if (file == NULL)
		{
			return ERRO_ABRIR_FICHEIRO;
		}
	}

	if (strcmp(formatoFicheiro, "") == 0)
		return ERRO_FORMATO_INVALIDO;

	Plano tempPlano;
	char tempData[TAMANHO_DATA_TEXTO];
	char tempRefeicao[TAMANHO_REFEICAO] = "\0";

	while (*numPlanos < TAMANHO_MAX_ARRAY && fscanf(file, formatoFicheiro,
		&tempPlano.idPaciente,
		tempData,
		tempRefeicao,
		&tempPlano.calorias[0],
		&tempPlano.calorias[1]) == 5)
	{
		// Converter data de texto para time_t
		tempPlano.data = ConverterStringParaDatetime(tempData);

		// Converter refeição de texto para ID
		tempPlano.refeicao = ConverterRefeicaoParaId(tempRefeicao);

		// Verificar se existem registos duplicados
		int isDuplicate = 0;
		for (int j = 0; j < *numPlanos; j++)
		{
			if (tempPlano.idPaciente == planos[j].idPaciente &&
				tempPlano.data == planos[j].data &&
				tempPlano.refeicao == planos[j].refeicao)
			{
				// Se as calorias são diferentes, atualizar as calorias
				if (tempPlano.calorias[0] != planos[j].calorias[0] ||
					tempPlano.calorias[1] != planos[j].calorias[1])
				{
					planos[j].calorias[0] = tempPlano.calorias[0];
					planos[j].calorias[1] = tempPlano.calorias[1];
				}
				isDuplicate = 1;
				break;  // Parar se encontrarmos um registo duplicado
			}
		}

		// Se não for um registo duplicado, adicionar ao array principal
		if (!isDuplicate)
		{
			planos[*numPlanos] = tempPlano;
			(*numPlanos)++;
		}
	}

	if (ferror(file))
	{
		fclose(file);
		return ERRO_LEITURA_FICHEIRO;
	}

	fclose(file);

	return SUCESSO;
}
