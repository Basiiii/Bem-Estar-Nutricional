/**

	@file      Menu.c

	@brief     Implementação das funções relacionadas ao menu de opções do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date      Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constantes.h"
#include "Utils.h"

/**
   @brief  Apresenta o menu de opções para interação com o programa.

   @details   Esta função imprime no ecrã as opções disponíveis para interação com o programa.
			  O utilizador é solicitado a escolher uma das opções apresentadas.

   @note      As opções incluem carregar dados, verificar pacientes com calorias ultrapassadas,
			  verificar pacientes com calorias fora do intervalo, obter o plano nutricional de um
			  paciente para uma refeição específica, calcular médias de calorias consumidas por
			  refeição por cada paciente, e apresentar uma tabela das refeições planeadas e realizadas
			  para todos os pacientes. As opções 'q' e 'f' fecham o programa.

   @warning   A função não lida com a leitura da escolha do utilizador e não verifica a validade
			  da escolha inserida. Apenas apresenta o menu no stdout.
**/
void ApresentarMenu()
{
	LimparEcra();

	EscreverComCor(ANSI_TITULO, "\n\tPROGRAMA BEM - ESTAR \n\n");

	EscreverComCor(ANSI_TITULO, "Por favor escolha uma das seguintes opcoes:\n\n");
	printf("1. Carregar dados\n");
	printf("2. Pacientes que ultrapassaram determinada quantidade de calorias\n");
	printf("3. Pacientes com dietas fora do plano dentro de um intervalo\n");
	printf("4. Planos nutricionais de um paciente para determinada refeicao num determinado intervalo\n");
	printf("5. Medias das calorias consumidas por refeicao por cada paciente\n");
	printf("6. Tabela das refeicoes planeadas e realizadas para todos os pacientes\n");
	EscreverComCor(ANSI_COR_AMARELO, "\nq." ANSI_RESET " Fechar programa");
	EscreverComCor(ANSI_COR_VERMELHO, "\nf." ANSI_RESET " Fechar programa sem guardar dados\n\n");

	EscreverComCor(ANSI_TITULO, "Introduza a sua escolha: ");
}

/**
	@brief  Lê uma string do utilizador para a data.
	@param  data - A variável onde se quer guardar a data.
	@param  proposito - O objetivo da leitura (p. ex., "inicial" ou "final").
	@retval      - Verdadeiro se correu sem erros, Falso se correu com erros.
**/
bool LerData(char* data, const char* proposito)
{
	printf("%sPor favor introduza a data %s no formato DD-MM-AAAA.\n", ANSI_COR_BRANCO, proposito);
	printf("%sPor exemplo:\n01-01-2023\n\n%s", ANSI_INFO, ANSI_RESET);

	if (scanf("%10s", data) != 1 || !ValidarFormatoData(data))
	{
		return false;
	}
	return true;
}

/**
	@brief  Lê datas de inicio e fim para as funcionalidades do menu.
	@param  dataInicial - A data inicial.
	@param  dataFinal   - A data final.
	@retval             - 0 se correr com sucesso (SUCESSO).
	@retval             - 20 se houver um erro na leitura das datas (ERRO_LEITURA_DATA).
**/
static int InputDatasIniciaisFinais(char dataInicial[], char dataFinal[])
{
	if (!LerData(dataInicial, "inicial") || !LerData(dataFinal, "final"))
		return ERRO_LEITURA_DATA;

	LimparEcra();
	return SUCESSO;
}

/**
	@brief  Obter um input do utilizador para um limite de calorias.
	@param  limiteCalorias - Apontador do tipo inteiro para o limite de calorias.
	@retval             - 0 se correr com sucesso (SUCESSO).
	@retval             - 21 se houver um erro na leitura do limite de calorias (ERRO_LEITURA_LIMITE_CALORIAS).
**/
static int InputLimiteCalorias(int* limiteCalorias) {
	printf("Por favor introduza o limite de calorias.\n");

	if (scanf("%d", limiteCalorias) != 1 || *limiteCalorias < 0 || *limiteCalorias > LIMITE_MAX_CALORIAS)
	{
		return ERRO_LEITURA_LIMITE_CALORIAS;
	}

	LimparEcra();

	return SUCESSO;
}

/**
	@brief  Permite o utilizador dar input de um ID de um paciente.
	@param  idPaciente - O apontador do ID paciente.
	@retval            - 0 se correr com sucesso (SUCESSO).
	@retval            - 22 se não for possível ler o ID do paciente (ERRO_LEITURA_ID_PACIENTE).
**/
static int LerIDPaciente(int* idPaciente)
{
	printf("Por favor introduza o ID do paciente.\n");

	if (scanf("%d", idPaciente) != 1 || *idPaciente > LIMITE_MAX_INPUT_ID_PACIENTE)
		return ERRO_LEITURA_ID_PACIENTE;

	LimparEcra();
	return SUCESSO;
}

/**
	@brief  Permite o utilizador dar input de um tipo de refeição.
	@param  tipoRefeicao - O apontador do tipo de refeição.
	@retval            - 0 se correr com sucesso (SUCESSO).
	@retval            - 23 se não for possível ler o tipo de refeição (ERRO_LEITURA_TIPO_REFEICAO).
**/
static int LerTipoRefeicao(int* tipoRefeicao)
{
	printf("Por favor selecione o tipo de refeicao:\n");
	printf("Pequeno almoco:1\nAlmoco:2\nJantar:3\n\n");

	if (scanf("%d", tipoRefeicao) != 1 || *tipoRefeicao < LIMITE_MIN_INPUT_TIPOS_REFEICAO || *tipoRefeicao > LIMITE_MAX_INPUT_TIPOS_REFEICAO)
		return ERRO_LEITURA_TIPO_REFEICAO;

	LimparEcra();
	return SUCESSO;
}

#pragma region FUNCIONALIDADE_2

/**
	@brief  Calcula o valor total de calorias de cada paciente.
	@param  dietas       - O array de Dietas da memória.
	@param  numDietas    - O número de Dietas em memória.
	@param  numPacientes - O número de Pacientes em memória.
	@param  dataInicio   - A data inicial (objeto datetime).
	@param  dataFinal    - A data final (objeto datetime).
	@retval              - NULL se não for possível alocar memória do array de pacientes.
	@retval              - O total de calorias de cada paciente.
**/
static int* CalcularTotalCaloriasPorPaciente(Dieta* dietas, int numDietas, int numPacientes, time_t dataInicio, time_t dataFinal)
{
	if (numPacientes <= 0)
		return NULL;

	int* totalCaloriasPorPaciente = malloc(numPacientes * sizeof(int));
	if (totalCaloriasPorPaciente == NULL)
		return NULL;

	// Inicializar o array com 0's
	for (int i = 0; i < numPacientes; i++)
	{
		totalCaloriasPorPaciente[i] = 0;
	}

	// Iterar pelo array de dietas para calcular o total de calorias
	int pacienteAtual = 0; // indice do paciente atual
	for (int i = 0; i < numDietas; i++)
	{
		// se for o proximo paciente
		if (i > 0 && dietas[i].idPaciente != dietas[i - 1].idPaciente)
			pacienteAtual++;

		// se a data estiver entre a faixa de datas, atualizar total calorias
		if (dietas[i].data >= dataInicio && dietas[i].data <= dataFinal)
			totalCaloriasPorPaciente[pacienteAtual] += dietas[i].calorias;
	}

	return totalCaloriasPorPaciente;
}

/**
	@brief  Conta o número total de pacientes que ultrapassam um limite de calorias.
	@param  totalCaloriasPorPaciente - O array de calorias totais de cada paciente.
	@param  numPacientes             - O número total de pacientes.
	@param  limiteCalorias           - O limite de calorias.
	@retval                          - O contador.
**/
static int ContarPacientesUltrapassaramCalorias(int* totalCaloriasPorPaciente, int numPacientes, int limiteCalorias)
{
	int contador = 0;
	for (int i = 0; i < numPacientes; i++)
	{
		if (totalCaloriasPorPaciente[i] > limiteCalorias)
			contador++;
	}
	return contador;
}

/**
	@brief Função para executar a funcionalidade 2 - Pacientes que ultrapassam um dado limite de calorias entre determinadas datas.
	@param dietas       - O array de dietas.
	@param numDietas    - O número de dietas.
	@param numPacientes - O número de pacientes.
	@retval				- 0 se o programa correu sem erros (SUCESSO).
	@retval				- 6 se houve um erro na alocação de memória (ERRO_ALOCAR_MEMORIA).
	@retval				- 20 se houve erro na leitura da data (ERRO_LEITURA_DATA).
	@retval				- 21 se houve erro na leitura do limite de calorias (ERRO_LEITURA_LIMITE_CALORIAS).
**/
int PacientesUltrapassaramCalorias(Dieta* dietas, int numDietas, int numPacientes)
{
	char dataInicial[TAMANHO_DATA_TEXTO];
	char dataFinal[TAMANHO_DATA_TEXTO];
	int limiteCalorias = 0;

	// INPUT DATAS
	int resultadoData = InputDatasIniciaisFinais(dataInicial, dataFinal);
	if (resultadoData != SUCESSO)
		return resultadoData;

	// INPUT DO LIMITE DE CALORIAS
	int resultadoLimiteCalorias = InputLimiteCalorias(&limiteCalorias);
	if (resultadoLimiteCalorias != SUCESSO)
		return resultadoLimiteCalorias;

	// CONVERTER STRINGS PARA TIME_T
	time_t dataInicialTime = ConverterStringParaDatetime(dataInicial);
	time_t dataFinalTime = ConverterStringParaDatetime(dataFinal);

	// CALCULAR TOTAL DE CALORIAS POR PACIENTE
	int* totalCaloriasPorPaciente =
		CalcularTotalCaloriasPorPaciente(dietas, numDietas, numPacientes, dataInicialTime, dataFinalTime);

	// VERIFICAR SE O CALCULO CORREU SEM ERROS
	if (totalCaloriasPorPaciente == NULL)
		return ERRO_ALOCAR_MEMORIA;

	// CALCULAR NUMERO TOTAL DE PACIENTES QUE ULTRAPASSAM LIMITE
	int numPacientesUltrapassam =
		ContarPacientesUltrapassaramCalorias(totalCaloriasPorPaciente, numPacientes, limiteCalorias);

	// APRESENTAR RESULTADO
	printf("Numero de pacientes que ultrapassaram o limite de calorias: %d\n\n", numPacientesUltrapassam);

	free(totalCaloriasPorPaciente);

	return SUCESSO;
}

#pragma endregion

#pragma region FUNCIONALIDADE_3

/**
	@brief  Verifica se uma dieta está dentro do intervalo especificado para processamento.
	@param  d           - A dieta a ser verificada.
	@param  dataInicial - A data inicial do intervalo.
	@param  dataFinal   - A data final do intervalo.
	@retval             - Retorna 1 se a dieta está dentro do intervalo, 0 caso contrário.
**/
static int DentroDoIntervalo(Dieta d, time_t dataInicial, time_t dataFinal)
{
	return (d.data >= dataInicial && d.data <= dataFinal);
}

/**
	@brief Processa as dietas de um paciente num determinado intervalo de datas, comparando-as com os planos.
	@param p             - O paciente a ser processado.
	@param dietas        - O array de dietas.
	@param planos        - O array de planos.
	@param dataInicial   - A data inicial do intervalo.
	@param dataFinal     - A data final do intervalo.
	@param resultados    - O array que armazenará os resultados do processamento.
	@param numResultados - O apontador para o número de resultados armazenados no array.
	@retval              - 0 se correr com sucesso.
	@retval              - 18 se houver um erro de processamento.
**/
static int ProcessarPaciente(Paciente p, Dieta dietas[], Plano planos[], time_t dataInicial, time_t dataFinal,
	ResultadoProcessamentoFunc3 resultados[], int* numResultados)
{
	// Verificar se há espaço suficiente no array
	if (*numResultados >= TAMANHO_MAX_ARRAY)
	{
		return ERRO_PROCESSAMENTO;
	}

	// Array para controlar as dietas já processadas
	int dietasProcessadas[TAMANHO_MAX_ARRAY] = { 0 };

	for (int j = 0; j < TAMANHO_MAX_ARRAY; j++)
	{
		Dieta d = dietas[j];

		// Verificar se dieta foi processada, se esta dentro do intervalo e se o id paciente é a do dieta
		if (!dietasProcessadas[j] && DentroDoIntervalo(d, dataInicial, dataFinal) && d.idPaciente == p.id)
		{
			int totalCalorias = 0;

			for (int k = 0; k < TAMANHO_MAX_ARRAY; k++)
			{
				Dieta d2 = dietas[k];

				// Verificar se a proxima dieta no array tem a mesma data, mesma refeicao e pertence ao mesmo paciente
				if (DentroDoIntervalo(d2, dataInicial, dataFinal) && d2.idPaciente == p.id &&
					d2.data == d.data && d2.refeicao == d.refeicao)
				{
					// Adicionar calorias ao total
					totalCalorias += d2.calorias;
					// Marcar a dieta como processada
					dietasProcessadas[k] = 1;
				}
			}

			for (int k = 0; k < TAMANHO_MAX_ARRAY; k++)
			{
				Plano pl = planos[k];

				// Verifica se o paciente tem um plano para a mesma data/refeicao e se o total de calorias esta fora do plano
				if (pl.idPaciente == p.id && pl.data == d.data && pl.refeicao == d.refeicao &&
					(totalCalorias < pl.calorias[0] || totalCalorias > pl.calorias[1]))
				{
					// Guardar o resultado no array
					ResultadoProcessamentoFunc3 resultado;
					resultado.idPaciente = p.id;
					strcpy(resultado.nome, p.nome);
					strcpy(resultado.refeicao, ConverterRefeicaoParaTexto(pl.refeicao));
					resultado.totalCalorias = totalCalorias;
					resultado.caloriasMin = pl.calorias[0];
					resultado.caloriasMax = pl.calorias[1];
					strcpy(resultado.data, ConverterDatetimeParaString(pl.data));

					resultados[*numResultados] = resultado;
					(*numResultados)++;
					break;
				}
			}
		}
	}

	return SUCESSO;
}

/**
	@brief Bubble sort para ordenar array por ID de ordem decrescente.
	@param arr - O array.
	@param n   - O tamanho do array.
**/
static void OrdernarFunc3(ResultadoProcessamentoFunc3 arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			// Comparar elementos adjacentes e trocar se for preciso
			if (arr[j].idPaciente < arr[j + 1].idPaciente) {
				ResultadoProcessamentoFunc3 temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/**
	@brief Lista os pacientes com dietas fora do plano num intervalo de datas.
	@param pacientes   - Array de pacientes.
	@param dietas      - Array de dietas.
	@param planos      - Array de planos.
	@param dataInicial - Data inicial do intervalo.
	@param dataFinal   - Data final do intervalo.
**/
static void ListarPacientesForaPlano(Paciente pacientes[], Dieta dietas[], Plano planos[],
	time_t dataInicial, time_t dataFinal)
{
	printf("+-----------------+-----------------+-------------------+----------------------+---------------+------------+\n");
	printf("| %-15s | %-15s | %-17s | %-20s | %-13s | %-10s |\n",
		"ID PACIENTE", "NOME", "REFEICAO", "CALORIAS CONSUMIDAS", "INTERVALO", "DATA");
	printf("+-----------------+-----------------+-------------------+----------------------+---------------+------------+\n");

	// Criar um array que vai conter os resultados
	ResultadoProcessamentoFunc3 resultados[TAMANHO_MAX_ARRAY];
	int numResultados = 0;

	for (int i = 0; i < TAMANHO_MAX_ARRAY; i++)
	{
		ProcessarPaciente(pacientes[i], dietas, planos, dataInicial, dataFinal, resultados, &numResultados);
	}

	// Ordenar o array para ordem decrescente do número de paciente
	OrdernarFunc3(resultados, numResultados);

	// Apresentar resultados
	for (int i = 0; i < numResultados; i++)
	{
		printf("| %-15d | %-15s | %-17s | %-20d | %-5d - %-5d | %-10s |\n",
			resultados[i].idPaciente, resultados[i].nome, resultados[i].refeicao,
			resultados[i].totalCalorias, resultados[i].caloriasMin, resultados[i].caloriasMax, resultados[i].data);
	}

	printf("+-----------------+-----------------+-------------------+----------------------+---------------+------------+\n");
}

/**
	@brief      Função que executa a funcionalidade 3 - apresentar pacientes com dietas fora do seu plano.
	@param[in]  pacientes - O array de pacientes.
	@param[in]  dietas    - O array de dietas.
	@param[in]  planos    - O array de planos.
	@retval     0 se correr com sucesso.
	@retval     20 se houver um erro com a leitura de datas (ERRO_LEITURA_DATA).
**/
int PacientesForaPlano(Paciente* pacientes, Dieta* dietas, Plano* planos)
{
	char dataInicial[TAMANHO_DATA_TEXTO];
	char dataFinal[TAMANHO_DATA_TEXTO];

	// INPUT DATAS
	int resultadoData = InputDatasIniciaisFinais(dataInicial, dataFinal);
	if (resultadoData != SUCESSO)
		return resultadoData;

	LimparEcra();

	// APRESENTAR RESULTADO
	ListarPacientesForaPlano(
		pacientes, dietas, planos,
		ConverterStringParaDatetime(dataInicial),
		ConverterStringParaDatetime(dataFinal)
	);

	return SUCESSO;
}

#pragma endregion

#pragma region FUNCIONALIDADE_4

/**
	@brief Preenche o array de resultados com base nos planos fornecidos.
	@param planos          - O array de planos a serem considerados.
	@param numPlanos       - O número de planos no array.
	@param idPaciente      - O ID do paciente a ser considerado.
	@param tipoRefeicao    - O tipo de refeição a ser considerado.
	@param dataInicialTime - A data inicial a ser considerada (em formato time_t).
	@param dataFinalTime   - A data final a ser considerada (em formato time_t).
	@param resultados      - O array de resultados a ser preenchido.
	@param numResultados   - O número de resultados no array.
**/
static void PreencherResultados(Plano planos[], int numPlanos, int idPaciente, int tipoRefeicao,
	time_t dataInicialTime, time_t dataFinalTime, ResultadoProcessamentoFunc4 resultados[],
	int* numResultados)
{
	for (int i = 0; i < numPlanos; i++)
	{
		Plano plano = planos[i];

		if (plano.idPaciente == idPaciente && plano.refeicao == tipoRefeicao &&
			plano.data >= dataInicialTime && plano.data <= dataFinalTime) {

			// Guarda resultado
			ResultadoProcessamentoFunc4 resultado;
			resultado.idPaciente = idPaciente;
			strcpy(resultado.tipoRefeicao, ConverterRefeicaoParaTexto(plano.refeicao));
			strcpy(resultado.data, ConverterDatetimeParaString(plano.data));
			resultado.caloriasMin = plano.calorias[0];
			resultado.caloriasMax = plano.calorias[1];

			// Guarda o resultado no array
			resultados[*numResultados] = resultado;
			(*numResultados)++;
		}
	}
}

/**
	@brief Apresenta os resultados da funcionalidade 4.
	@param resultados    - O array de resultados a ser apresentado.
	@param numResultados - O número de resultados no array.
**/
static void ApresentarResultados(ResultadoProcessamentoFunc4 resultados[], int numResultados)
{
	printf("+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
	printf("| %-15s | %-15s | %-15s | %-15s | %-15s |\n",
		"ID PACIENTE", "TIPO REFEICAO", "DATA", "CALORIAS MIN", "CALORIAS MAX");
	printf("+-----------------+-----------------+-----------------+-----------------+-----------------+\n");

	for (int i = 0; i < numResultados; i++)
	{
		ResultadoProcessamentoFunc4 resultado = resultados[i];

		printf("| %-15d | %-15s | %-15s | %-15d | %-15d |\n",
			resultado.idPaciente, resultado.tipoRefeicao,
			resultado.data, resultado.caloriasMin, resultado.caloriasMax);
	}

	printf("+-----------------+-----------------+-----------------+-----------------+-----------------+\n");
	printf("\n");
}

/**
	@brief  Lista os planos nutricionais de um paciente para determinada refeição ao longo de um determinado período.
	@param  planos    - O array de planos nutricionais.
	@param  numPlanos - O número de planos nutricionais no array.
	@retval           - 0 se correr com sucesso.
	@retval           - 20 se houver um erro com a leitura de datas (ERRO_LEITURA_DATA).
	@retval           - 22 se não for possível ler o ID do paciente (ERRO_LEITURA_ID_PACIENTE).
	@retval           - 23 se não for possível ler o tipo de refeição (ERRO_LEITURA_TIPO_REFEICAO).
**/
int ListarPlanosNutricionais(Plano planos[], int numPlanos)
{
	char dataInicial[TAMANHO_DATA_TEXTO];
	char dataFinal[TAMANHO_DATA_TEXTO];
	int idPaciente, tipoRefeicao;

	// INPUT DATAS
	int resultadoData = InputDatasIniciaisFinais(dataInicial, dataFinal);
	if (resultadoData != SUCESSO)
		return resultadoData;

	// CONVERTER STRINGS PARA TIME_H
	time_t dataInicialTime = ConverterStringParaDatetime(dataInicial);
	time_t dataFinalTime = ConverterStringParaDatetime(dataFinal);

	// INPUT ID PACIENTE
	int resultadoID = LerIDPaciente(&idPaciente);
	if (resultadoID != SUCESSO)
		return resultadoID;

	// INPUT TIPO REFEICAO
	int resultadoRefeicao = LerTipoRefeicao(&tipoRefeicao);
	if (resultadoRefeicao != SUCESSO)
		return resultadoRefeicao;

	// RESULTADO
	ResultadoProcessamentoFunc4 resultados[TAMANHO_MAX_ARRAY];
	int numResultados = 0;

	PreencherResultados(planos, numPlanos, idPaciente, tipoRefeicao, dataInicialTime, dataFinalTime, resultados, &numResultados);

	ApresentarResultados(resultados, numResultados);

	return SUCESSO;
}

#pragma endregion

#pragma region FUNCIONALIDADE_5

/**
	@brief	Calcula o total de refeições e o total de calorias para um dado paciente.
	@param  dietas      - O array de todas as dietas.
	@param  pacienteID  - O identificador do paciente.
	@param  refeicaoID  - O identificador da refeição.
	@param  dataInicial - A data inicial do intervalo.
	@param  dataFinal   - A data final do intervalo.
	@param  totalCalorias - O total de calorias consumidas durante o período.
	@param  numRefeicoes   - O número total de refeições durante o período.
**/
static void ContaRefeicoesECalorias(Dieta dietas[], int pacienteID, int refeicaoID,
	time_t dataInicial, time_t dataFinal, int* totalCalorias, int* numRefeicoes)
{
	*totalCalorias = 0;
	*numRefeicoes = 0;

	// Guarda os registos com as datas únicas de uma dada refeição
	// O nosso array de dietas pode conter vários registos para um único dia, mas não podemos assumir que cada
	// registo é um dia diferente. Logo, é preciso guardar as datas dos dias contados, para contar corretamente o número
	// de dias e não os registos.
	time_t datasUnicas[TAMANHO_MAX_ARRAY] = { 0 };

	// Iterar pelo array de dietas
	for (int j = 0; j < TAMANHO_MAX_ARRAY; j++)
	{
		// Guardar a dieta atual
		Dieta d = dietas[j];

		// Se for o mesmo paciente e refeicao, e estiver dentro da faixa de datas
		if (d.idPaciente == pacienteID && d.refeicao == refeicaoID && d.data >= dataInicial && d.data <= dataFinal)
		{
			// Verifica se a data já foi processada para a refeição atual
			int dataExiste = 0;
			for (int k = 0; k < *numRefeicoes; k++)
			{
				if (datasUnicas[k] == d.data)
				{
					dataExiste = 1;
					break;
				}
			}

			if (!dataExiste)
			{
				// Atualizar datas unicas e adicionar o total de calorias
				datasUnicas[*numRefeicoes] = d.data;
				(*numRefeicoes)++;
			}

			// Adicionar calorias do registo atual ao total
			*totalCalorias += d.calorias;
		}
	}
}

/**
	@brief Itera sobre pacientes e refeições, calcula médias de calorias e armazena os resultados em um array.
	@param pacientes   - O array de pacientes.
	@param dietas      - O array de todas as dietas.
	@param resultados  - O array de resultados.
	@param numResultados - O número de resultados.
	@param dataInicialTime - A data inicial do intervalo.
	@param dataFinalTime   - A data final do intervalo.
**/
static void IterarPacientesRefeicoes(Paciente pacientes[], Dieta dietas[], ResultadoProcessamentoFunc5 resultados[],
	int* numResultados, time_t dataInicialTime, time_t dataFinalTime)
{
	for (int i = 0; i < TAMANHO_MAX_ARRAY; i++)
	{
		// Paciente atual
		Paciente p = pacientes[i];

		// Iterar por todos os tipos de refeicoes do paciente atual
		for (int refeicao = PEQUENO_ALMOCO_ID; refeicao <= JANTAR_ID; refeicao++)
		{
			const char* descricaoRefeicao = ConverterRefeicaoParaTexto(refeicao);

			int totalCalorias, numeroRefeicoes;
			ContaRefeicoesECalorias(dietas, p.id, refeicao, dataInicialTime, dataFinalTime, &totalCalorias, &numeroRefeicoes);

			if (numeroRefeicoes > 0)
			{
				// Guardar resultado
				ResultadoProcessamentoFunc5 resultado;
				resultado.idPaciente = p.id;
				strcpy(resultado.nomePaciente, p.nome);
				strcpy(resultado.descricaoRefeicao, descricaoRefeicao);
				resultado.totalCalorias = totalCalorias;
				resultado.numRefeicoes = numeroRefeicoes;

				// Calculo da media de calorias
				resultado.mediaCalorias = (double)totalCalorias / numeroRefeicoes;

				// Adicionar resultado ao array
				resultados[*numResultados] = resultado;
				(*numResultados)++;
			}
		}
	}
}

/**
	@brief  Lista médias de calorias por refeição para um intervalo de datas específico.
	@param  pacientes   - O array de pacientes.
	@param  dietas      - O array de todas as dietas.
	@param  resultados  - O array de resultados.
	@param  numResultados - O número de resultados.
	@retval				- 0 se correr com sucesso.
	@retval				- 20 se houver um erro com a leitura de datas.
**/
int ListarMediasCaloriasPorRefeicao(Paciente pacientes[], Dieta dietas[])
{
	// Definir array de resultados
	ResultadoProcessamentoFunc5 resultados[TAMANHO_MAX_ARRAY];

	// Inicializa o número de resultados
	int numResultados = 0;

	// Inicialia datas
	char dataInicial[TAMANHO_DATA_TEXTO];
	char dataFinal[TAMANHO_DATA_TEXTO];

	// INPUT DATAS
	int resultadoData = InputDatasIniciaisFinais(dataInicial, dataFinal);
	if (resultadoData != SUCESSO)
		return resultadoData;

	// CONVERTER STRINGS PARA TIME_H
	time_t dataInicialTime = ConverterStringParaDatetime(dataInicial);
	time_t dataFinalTime = ConverterStringParaDatetime(dataFinal);

	// APRESENTAR CABECALHO
	printf("+-----------------+----------------------+-----------------+-----------------+-----------------+----------------+\n");
	printf("| %-15s | %-20s | %-15s | %-15s | %-15s | %-10s |\n",
		"ID PACIENTE", "NOME PACIENTE", "REFEICAO", "TOTAL CALORIAS", "NUM REFEICOES", "MEDIA CALORIAS");
	printf("+-----------------+----------------------+-----------------+-----------------+-----------------+----------------+\n");

	// Chama outra função para iterar e calcular médias
	IterarPacientesRefeicoes(pacientes, dietas, resultados, &numResultados, dataInicialTime, dataFinalTime);

	// Iterar pelo array de resultados e fazer print
	for (int i = 0; i < numResultados; i++)
	{
		printf("| %-15d | %-20s | %-15s | %-15d | %-15d | %-14.2f |\n",
			resultados[i].idPaciente, resultados[i].nomePaciente, resultados[i].descricaoRefeicao,
			resultados[i].totalCalorias, resultados[i].numRefeicoes, resultados[i].mediaCalorias);
	}

	printf("+-----------------+----------------------+-----------------+-----------------+-----------------+----------------+\n");
	printf("\n");

	return SUCESSO;
}

#pragma endregion

#pragma region FUNCIONALIDADE_6

/**
	@brief  Encontra um paciente num array pelo seu ID.
	@param  pacientes    - Array de pacientes.
	@param  numPacientes - Número total de pacientes no array.
	@param  pacienteID   - ID do paciente a ser procurado.
	@retval              - Apontador para o paciente encontrado ou NULL se não encontrado.
**/
static Paciente* EncontrarPacientePorID(Paciente pacientes[], int numPacientes, int pacienteID)
{
	for (int i = 0; i < numPacientes; i++)
	{
		if (pacientes[i].id == pacienteID)
		{
			return &pacientes[i];
		}
	}
	return NULL;
}

/**
	@brief  Calcula o total de calorias consumidas para um plano.
	@param  dietas        - Array de dietas.
	@param  numDietas     - Número de dietas.
	@param  idPaciente    - ID do paciente.
	@param  refeicao      - Tipo de refeição.
	@param  data          - Data do plano.
	@retval               - O total de calorias consumidas.
**/
static int CalcularTotalCaloriasConsumidas(Dieta dietas[], int numDietas, int idPaciente, int refeicao, time_t data)
{
	int totalCalorias = 0;

	// Iterar pelo array dietas
	for (int i = 0; i < numDietas; i++)
	{
		// Guardar dieta atual
		Dieta d = dietas[i];

		// Se for o mesmo paciente, refeicao e data, soma o total de calorias
		if (d.idPaciente == idPaciente && d.refeicao == refeicao && d.data == data)
		{
			totalCalorias += d.calorias;
		}
	}

	return totalCalorias;
}

/**
	@brief  Imprime informações do plano.
	@param  paciente      - Apontador para o paciente.
	@param  plano         - Apontador para o plano.
	@param  totalCalorias - O total de calorias consumidas.
**/
static void ApresentarInformacaoPlano(Paciente* paciente, Plano* plano, int totalCalorias)
{
	// Se total calorias está entre o limite min e max do plano
	if (totalCalorias > plano->calorias[0] && totalCalorias < plano->calorias[1])
	{
		printf("| %-5d | %-15s | %-15s | %-15s | %-15s | %-8d | %-8d | %-8d |\n",
			paciente->id, paciente->nome, ConverterRefeicaoParaTexto(plano->refeicao),
			ConverterDatetimeParaString(plano->data),
			ConverterDatetimeParaString(plano->data),
			plano->calorias[0], plano->calorias[1], totalCalorias);
	}
}

/**
	@brief  Gera a tabela de refeições.
	@param  pacientes     - Array de pacientes.
	@param  numPacientes  - Número de pacientes.
	@param  planos        - Array de planos.
	@param  numPlanos     - Número de planos.
	@param  dietas        - Array de dietas.
	@param  numDietas     - Número de dietas.
	@retval				  - 0 se correr com sucesso.
	@retval               - 26 se não foi possível encontrar um paciente.
**/
int GerarTabelaRefeicoes(Paciente pacientes[], int numPacientes, Plano planos[], int numPlanos, Dieta dietas[], int numDietas)
{
	printf("+-------+-----------------+-----------------+-----------------+-----------------+----------+----------+----------+\n");
	printf("| %-5s | %-15s | %-15s | %-15s | %-15s | %-8s | %-8s | %-8s |\n",
		"NP", "Nome", "Tipo Refeicao", "Data de Inicio", "Data de Fim", "Cal Min", "Cal Max", "Consumo");
	printf("+-------+-----------------+-----------------+-----------------+-----------------+----------+----------+----------+\n");

	// Iterar pelo array de planos
	for (int i = 0; i < numPlanos; i++)
	{
		// Guardar plano atual
		Plano pl = planos[i];

		// Encontrar o paciente do plano com o ID
		Paciente* p = EncontrarPacientePorID(pacientes, numPacientes, pl.idPaciente);
		if (p == NULL) // não foi encontrado ou houve erro
			return ERRO_VALOR_NULLO;

		// Calcular o total de calorias consumidas
		int totalCalorias = CalcularTotalCaloriasConsumidas(dietas, numDietas, p->id, pl.refeicao, pl.data);

		// Apresentar informação
		ApresentarInformacaoPlano(p, &pl, totalCalorias);
	}

	printf("+-------+-----------------+-----------------+-----------------+-----------------+----------+----------+----------+\n");

	return SUCESSO;
}

#pragma endregion
