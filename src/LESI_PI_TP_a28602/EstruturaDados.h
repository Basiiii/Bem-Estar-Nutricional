/**

	@file      EstruturaDados.h

	@brief     Defini��o das estruturas de dados para pacientes, dietas e planos.

	@details   Este ficheiro cont�m as defini��es das estruturas de dados utilizadas no programa
			   para representar informa��es sobre pacientes, dietas e planos. As estruturas incluem
			   detalhes como identifica��o, nome, telefone, data, refei��o, comida e calorias.

	@author    Enrique George Rodrigues

	@date      Criado: 29.11.2023
	@date	   Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef ESTRUTURA_DADOS_H
#define ESTRUTURA_DADOS_H

#include <time.h>

#include "Constantes.h"

// Estrutura dos pacientes
typedef struct {
	int id; // Identifica��o �nica do paciente
	char nome[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	long tel; // N�mero de telefone do paciente
} Paciente;

// Estrutura das dietas
typedef struct {
	int idPaciente; // Identifica��o �nica do paciente
	time_t data; // Data em formato timestamp
	int refeicao; // Tipo de refei��o (PEQUENO_ALMOCO, ALMOCO, JANTAR)
	char comida[TAMANHO_NOME_REFEICAO]; // Nome da comida
	int calorias; // Quantidade de calorias da comida
} Dieta;

// Estrutura dos planos
typedef struct {
	int idPaciente; // Identifica��o �nica do paciente
	time_t data; // Data em formato timestamp
	int refeicao; // Tipo de refei��o (PEQUENO_ALMOCO, ALMOCO, JANTAR)
	int calorias[NUMERO_CALORIAS]; // Intervalo de calorias. �ndice 0 = cal m�nimas, �ndice 1 = cal m�ximas
} Plano;

// Utilizado na funcionalidade 3
typedef struct {
	int idPaciente; // Identifica��o �nica do paciente
	char nome[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	char refeicao[TAMANHO_NOME_REFEICAO]; // Nome da refei��o
	int totalCalorias; // Valor total das calorias
	int caloriasMin; // Valor m�nimo das calorias
	int caloriasMax; // Valor m�ximo das calorias
	char data[TAMANHO_DATA_TEXTO]; // Data em texto
} ResultadoProcessamentoFunc3;

// Utilizado na funcionalidade 4
typedef struct {
	int idPaciente; // Identifica��o �nica do paciente
	char tipoRefeicao[TAMANHO_REFEICAO]; // Tipo de refei��o
	char data[TAMANHO_DATA_TEXTO]; // Data em texto
	int caloriasMin; // Calorias m�nimas
	int caloriasMax; // Calorias m�ximas
} ResultadoProcessamentoFunc4;

// Utilizado na funcionalidade 5
typedef struct {
	int idPaciente; // Identifica��o �nica do paciente
	char nomePaciente[TAMANHO_NOME_PACIENTE]; // Nome do paciente
	char descricaoRefeicao[TAMANHO_NOME_REFEICAO]; // Refei��o em texto
	int totalCalorias; // Total calorias
	int numRefeicoes; // N�mero de refei��es
	double mediaCalorias; // M�dia das calorias em rela��o ao n�mero de refei��es
} ResultadoProcessamentoFunc5;

#endif