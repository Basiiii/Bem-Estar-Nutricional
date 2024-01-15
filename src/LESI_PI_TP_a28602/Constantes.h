/**

	@file      Constantes.h

	@brief     Ficheiro de cabeçalho contendo definições de constantes para o programa.

	@details   Este ficheiro define várias constantes utilizadas ao longo do programa,
			   incluindo nomes de ficheiros, códigos de cor ANSI e mensagens de erro.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef CONSTANTES_H
#define CONSTANTES_H

// Modo Debug
#define MODO_DEBUG 1

// Tamanhos pré-defenidos
#define TAMANHO_NOME_PACIENTE				50 // Tamanho máximo de um nome de paciente
#define TAMANHO_NOME_REFEICAO				50 // Tamanho máximo de um nome de uma refeição
#define TAMANHO_MAX_ARRAY					20 // Tamanho máximo de arrays de pacientes/dietas/planos
#define TAMANHO_DATA_TEXTO					11 // Tamanho de uma data no formato ``DD-MM-AAAA`` com '\0' no fim.
#define TAMANHO_REFEICAO					20 // Tamanho máximo de uma refeição
#define LIMITE_MAX_CALORIAS					99999 // Limite máximo de calorias
#define LIMITE_MAX_INPUT_ID_PACIENTE		9999 // Número máximo do input possível para o ID paciente
#define LIMITE_MIN_INPUT_TIPOS_REFEICAO		1 // A primeira refeição começa com o valor de 1
#define LIMITE_MAX_INPUT_TIPOS_REFEICAO		3 // Só temos 3 tipos de refeiçoes
#define LIMITE_MIN_INPUT_TIPOS_FICHEIRO		1 // O ficheiro de tipo pacientes tem o valor de 1, logo não pode ser inferior a 1
#define LIMITE_MAX_INPUT_TIPOS_FICHEIRO		6 // 3 tipos de ficheiros (pacientes, dietas, planos) e dois formatos para cada (txt ou tab)
#define NUMERO_CALORIAS						2 // Calorias mínimas e máximas, array de tamanho 2
#define TAMANHO_MAX_BUFFER_INPUT			1000 // Tamanho máximo para o buffer de input de uma linha quando importamos do stdin
#define TAMANHO_MAX_BUFFER_FICHEIRO			5000 // Tamanho máximo do buffer para o ficheiro todo quando importamos do stdin

// Nomes de ficheiros binários
#define FICHEIRO_BIN_PACIENTES			"pacientes.dat"
#define FICHEIRO_BIN_DIETAS				"dietas_pacientes.dat"
#define FICHEIRO_BIN_PLANOS				"planos_pacientes.dat"

// Códigos de cor ANSI
#define ANSI_COR_PRETO					"\x1b[30m"
#define ANSI_COR_VERMELHO				"\x1b[31m"
#define ANSI_COR_VERMELHO_MAIS			"\033[1;37;41m"
#define ANSI_COR_VERDE					"\x1b[32m"
#define ANSI_COR_AMARELO				"\x1b[33m"
#define ANSI_COR_AZUL					"\x1b[34m"
#define ANSI_COR_MAGENTA				"\x1b[35m"
#define ANSI_COR_CYAN					"\x1b[36m"
#define ANSI_COR_BRANCO					"\x1b[37m"

// Respostas de confirmação
#define CONFIRMAR_SIM					'y'
#define CONFIRMAR_NAO					'n'

// Tipos de mensagens
#define ANSI_INFO						ANSI_COR_AZUL
#define ANSI_ERRO						ANSI_COR_VERMELHO
#define ANSI_SUCESSO					ANSI_COR_VERDE
#define ANSI_ALERTA						ANSI_COR_AMARELO
#define ANSI_DEBUG						ANSI_COR_MAGENTA
#define ANSI_RESET						"\x1b[0m"
#define ANSI_TITULO						"\033[4;1m"

// Tipos de ficheiros
#define TIPO_FICHEIRO_TXT				1
#define TIPO_FICHEIRO_BIN				2
#define TIPO_FICHEIRO_TAB				3

// Tipos de Dados de ficheiros
#define TIPO_DADOS_PACIENTES			1
#define TIPO_DADOS_DIETAS				2
#define TIPO_DADOS_PLANOS				3

// Leitura do stdin
#define FICHEIRO_PACIENTES_TXT					1
#define FICHEIRO_PACIENTES_TAB					2
#define FICHEIRO_DIETAS_TXT						3
#define FICHEIRO_DIETAS_TAB						4
#define FICHEIRO_PLANOS_TXT						5
#define FICHEIRO_PLANOS_TAB						6

// Tipos de refeicoes
#define ERRO_REFEICAO_ID				-1
#define PEQUENO_ALMOCO_ID				1
#define ALMOCO_ID						2
#define JANTAR_ID						3

// Nomes de refeicoes
#define PEQUENO_ALMOCO					"pequeno almoco"
#define ALMOCO							"almoco"
#define JANTAR							"jantar"

// Código de sucesso
#define SUCESSO							0

// Códigos de existência de ficheiros
#define FICHEIRO_EXISTE					1
#define FICHEIRO_NAO_EXISTE				0

// Erros de Operações de Ficheiros
#define ERRO_NAO_EXISTEM_FICHEIROS_BIN			1
#define ERRO_CRIAR_FICHEIRO						2
#define ERRO_IMPORTAR_DADOS_TEXTO				3
#define ERRO_IMPORTAR_DADOS_BIN					4
#define ERRO_APAGAR_FICHEIROS_BIN				5
#define ERRO_FICHEIRO_NAO_ENCONTRADO			7
#define ERRO_FICHEIRO_VAZIO						8
#define ERRO_LEITURA_FICHEIRO					9

// Erros de Gestão de Memória
#define ERRO_ALOCAR_MEMORIA						6

// Erros de Formato de Ficheiro e Análise
#define ERRO_FORMATO_INVALIDO					10

// Erros Gerais
#define ERRO_NAO_DEFINIDO						11
#define ERRO_ABRIR_FICHEIRO						12
#define ERRO_FICHEIRO_NULLO						24
#define ERRO_UTILIZADOR_NAO_DEU_PERMISSAO		25
#define ERRO_VALOR_NULLO						26

// Erros de Tamanho e Limites
#define ERRO_TAMANHO_EXCEDIDO					13

// Erros de Conversão de Dados
#define ERRO_CONVERSAO_TEXTO_DATETIME			14

// Erros de Processamento de Dados
#define ERRO_ARRAY_DADOS_NULL					15
#define ERRO_OPCAO_UTILIZADOR_DESCONHECIDA		16
#define ERRO_APAGAR_BASE_DADOS					17
#define ERRO_PROCESSAMENTO						18
#define ERRO_IMPORTAR_DADOS						19

// Erros de Manipulação de Inputs
#define ERRO_LEITURA_DATA						20
#define ERRO_LEITURA_LIMITE_CALORIAS			21
#define ERRO_LEITURA_ID_PACIENTE				22
#define ERRO_LEITURA_TIPO_REFEICAO				23
#define ERRO_LEITURA_TIPO_FICHEIRO				27

// Formato dos ficheiros de texto
#define FORMATO_PACIENTES_TXT					"%d;%49[^;];%ld"
#define FORMATO_PACIENTES_TAB					"%d\t%49[^\t]\t%ld"
#define FORMATO_DIETAS_TXT						"%d; %10[^;]; %19[^;]; %49[^;]; %d cal"
#define FORMATO_DIETAS_TAB						"%d\t %10[^\t]\t %19[^\t]\t %49[^\t]\t %d cal"
#define FORMATO_PLANOS_TXT						"%d; %10[^;]; %19[^;]; %d Cal, %d Cal"
#define FORMATO_PLANOS_TAB						"%d\t %10[^\t]\t %19[^\t]\t %d Cal, %d Cal"

// Constantes de formato de output
#define OUTPUT_FORMATO_DEBUG_PACIENTES_MEMORIA			"PID: %d, Nome: %s, Tel: %ld\n"
#define OUTPUT_FORMATO_DEBUG_DIETAS_MEMORIA_WIN			"PID: %d, Data: %s (%lld), Refeicao: %s (tipo: %d), Comida: %s, Calorias: %d\n"
#define OUTPUT_FORMATO_DEBUG_DIETAS_MEMORIA_LINUX		"PID: %d, Data: %s (%ld), Refeicao: %s (tipo: %d), Comida: %s, Calorias: %d\n"
#define OUTPUT_FORMATO_DEBUG_PLANOS_MEMORIA_WIN			"PID: %d, Data: %s (%lld), Refeicao: %s (tipo: %d), Calorias entre: %d e %d\n"
#define OUTPUT_FORMATO_DEBUG_PLANOS_MEMORIA_LINUX		"PID: %d, Data: %s (%ld), Refeicao: %s (tipo: %d), Calorias entre: %d e %d\n"

#endif // CONSTANTES_H
