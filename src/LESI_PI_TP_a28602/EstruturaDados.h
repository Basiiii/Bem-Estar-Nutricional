/**

	@file      EstruturaDados.h

	@brief     Definição das estruturas de dados para pacientes, dietas e planos.

	@details   Este ficheiro contém as definições das estruturas de dados utilizadas no programa
			   para representar informações sobre pacientes, dietas e planos. As estruturas incluem
			   detalhes como identificação, nome, telefone, data, refeição, comida e calorias.

	@author    Enrique George Rodrigues

	@date      Criado: 29.11.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef ESTRUTURA_DADOS_H
#define ESTRUTURA_DADOS_H

#include <time.h>

#include "Constantes.h"

// Estrutura dos pacientes
typedef struct {
	int id; // Identificação única do paciente
	char nome[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	long tel; // Número de telefone do paciente
} Paciente;

// Estrutura das dietas
typedef struct {
	int idPaciente; // Identificação única do paciente
	time_t data; // Data em formato timestamp
	int refeicao; // Tipo de refeição (PEQUENO_ALMOCO, ALMOCO, JANTAR)
	char comida[TAMANHO_NOME_REFEICAO]; // Nome da comida
	int calorias; // Quantidade de calorias da comida
} Dieta;

// Estrutura dos planos
typedef struct {
	int idPaciente; // Identificação única do paciente
	time_t data; // Data em formato timestamp
	int refeicao; // Tipo de refeição (PEQUENO_ALMOCO, ALMOCO, JANTAR)
	int calorias[NUMERO_CALORIAS]; // Intervalo de calorias. Índice 0 = cal mínimas, índice 1 = cal máximas
} Plano;

// Utilizado na funcionalidade 3
typedef struct {
	int idPaciente; // Identificação única do paciente
	char nome[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	char refeicao[TAMANHO_NOME_REFEICAO]; // Nome da refeição
	int totalCalorias; // Valor total das calorias
	int caloriasMin; // Valor mínimo das calorias
	int caloriasMax; // Valor máximo das calorias
	char data[TAMANHO_DATA_TEXTO]; // Data em texto
} ResultadoProcessamentoFunc3;

// Utilizado na funcionalidade 4
typedef struct {
	int idPaciente; // Identificação única do paciente
	char tipoRefeicao[TAMANHO_REFEICAO]; // Tipo de refeição
	char data[TAMANHO_DATA_TEXTO]; // Data em texto
	int caloriasMin; // Calorias mínimas
	int caloriasMax; // Calorias máximas
} ResultadoProcessamentoFunc4;

// Utilizado na funcionalidade 5
typedef struct {
	int idPaciente; // Identificação única do paciente
	char nomePaciente[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	char descricaoRefeicao[TAMANHO_NOME_REFEICAO]; // Refeição em texto
	int totalCalorias; // Total calorias
	int numRefeicoes; // Número de refeições
	double mediaCalorias; // Média das calorias em relação ao número de refeições
} ResultadoProcessamentoFunc5;

#endif