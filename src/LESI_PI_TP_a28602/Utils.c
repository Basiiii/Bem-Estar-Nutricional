/**

	@file      Utils.c

	@brief     Funções utilitárias do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h> // Inclui o cabeçalho necessário para a função Sleep() 
#include <conio.h> // Inclui o cabeçalho necessário para a função _getch()
#else
#include <unistd.h> // Inclui o cabeçalho necessário para a função sleep() no Linux
#endif

#include "Constantes.h"
#include "EstruturaDados.h"
#include "ControloErros.h"
#include "../GestorDadosIO/IODadosAPI.h"

/**
	@brief Uma função que para o programa durante n segundos.

	@param segundos - O número de segundos que o programa deve parar.

	@note - A função usa o "Sleep()" para Windows e "sleep()" para sistemas Unix.
**/
void CustomSleep(int segundos)
{
#ifdef _WIN32
	Sleep(segundos * 1000);  // Função sleep em millisegundos para Windows
#else
	sleep(segundos);  // Função sleep em segundos para sistemas Unix
#endif
}

/**
	@brief Uma função que permite ler um carater.

	@note - A função usa o "_getch()" para Windows e um processo especial para sistemas Unix.
**/
int LerTecla()
{
#ifdef _WIN32
	return _getch();
#else
	// Verificar se existem caracteres no stdin
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(0, &readfds); // file descriptor 0 é o standard input
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if (select(1, &readfds, NULL, NULL, &timeout) > 0)
	{
		// Se existem caracteres no stdin, limpar o buffer
		int tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF);
	}

	// Desativar buffer input
	system("stty raw");

	// Ler apenas um char
	int ch = getchar();

	// Ativar buffer input
	system("stty cooked");

	return ch;
#endif
}

/**
   @brief	  Limpa o ecrã do terminal.

   @details   Esta função utiliza a função 'system()' para chamar o comando adequado para
			  limpar o ecrã do terminal. Suporta sistemas Windows e Unix.

   @note      A função suporta sistemas Windows (utiliza "cls") e sistemas Unix
			  (utiliza "clear").
**/
void LimparEcra()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/**
	@brief Uma função que permite escrever no terminal numa cor definida por códigos ANSI.

	@param cor     - O código ANSI ou modo pré-definido (ex. ANSI_INFO ou ANSI_ERROR).
	@param formato - O texto a ser apresentado no terminal com suporte para parâmetros (ex. %d).
	@param ...	   - Os parâmetros opcionais para apresentar valores de variáveis (ex. %d).

	@note		   - Esta função é uma função variádica que suporta `n` parâmetros adicionais para
					 escrever valores de variáveis.

					 Exemplo de uso:
					 ```EscreverComCor(ANSI_INFO, "Isto e uma mensagem de info! %d, &variavelTipoInt);```
**/
void EscreverComCor(const char* cor, const char* formato, ...)
{
	va_list args;
	va_start(args, formato);

	printf("%s", cor);

	vprintf(formato, args);

	printf(ANSI_RESET);

	va_end(args);
}

/**
   @brief	Apresenta o manual de ajuda ao utilizador.

   @details   Esta função demonstra como utilizar o programa.
**/
void ApresentarAjuda()
{
	EscreverComCor(ANSI_TITULO, "Importar dados com ficheiros:\n\n");

	EscreverComCor(ANSI_COR_CYAN, "-p <ficheiro.x>");
	printf("\t\tImportar dados de pacientes de um ficheiro de texto ou binario.\n");
	EscreverComCor(ANSI_COR_CYAN, "-d <ficheiro.x>");
	printf("\t\tImportar dados de dietas de um ficheiro de texto ou binario.\n");
	EscreverComCor(ANSI_COR_CYAN, "-l <ficheiro.x>");
	printf("\t\tImportar dados de planos de um ficheiro de texto ou binario.\n");
	EscreverComCor(ANSI_COR_CYAN, "-tab");
	printf("\t\t\tIndica que o ficheiro esta formatado com separacao por tabs.\n");
	EscreverComCor(ANSI_COR_CYAN, "-bin");
	printf("\t\t\tIndica que o ficheiro e do tipo binario.\n");


	EscreverComCor(ANSI_TITULO, "\nApagar dados guardados:\n\n");
	EscreverComCor(ANSI_COR_AMARELO, "-apagarbd");
	printf("\t\tApagar a base de dados (ficheiros binarios).\n");


	EscreverComCor(ANSI_TITULO, "\nVer possiveis erros do programa:\n\n");
	EscreverComCor(ANSI_COR_VERMELHO, "-ajuda erros");
	printf("\t\tMostra os erros possiveis do programa.\n");


	EscreverComCor(ANSI_TITULO, "\nExemplos de utilizacao:\n");
	printf("\nFicheiro pacientes de texto normal: \t\t" ANSI_COR_MAGENTA "./bemestar -p ex1.txt" ANSI_RESET);
	printf("\nFicheiro dietas com separacao por tab: \t\t" ANSI_COR_MAGENTA "./bemestar -d ex2.txt -tab" ANSI_RESET);
	printf("\nFicheiro planos do tipo binario: \t\t" ANSI_COR_MAGENTA "./bemestar -l ex3.bin -bin" ANSI_RESET);
	printf("\nApagar base de dados: \t\t\t\t" ANSI_COR_AMARELO "./bemestar -apagarbd" ANSI_RESET);
	printf("\nVer possiveis erros do programa: \t\t" ANSI_COR_VERMELHO "./bemestar -ajuda erros" ANSI_RESET);

	printf("\n\n");
}

/**
   @brief  Apresenta os possíveis erros na execução do programa.
**/
void ApresentarErros()
{
	EscreverComCor(ANSI_TITULO, "Possiveis erros durante a execucao do programa:\n\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 1 - ");
	printf("Nao existem ficheiros binarios.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 2 - ");
	printf("Nao e possivel criar um ficheiro.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 3 - ");
	printf("Nao e possivel importar dados dos ficheiros de texto.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 4 - ");
	printf("Nao e possivel importar dados dos ficheiros binarios.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 5 - ");
	printf("Nao e possivel apagar os ficheiros binarios.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 6 - ");
	printf("Erro ao alocar memoria.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 7 - ");
	printf("Ficheiro nao encontrado.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 8 - ");
	printf("Ficheiro vazio.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 9 - ");
	printf("Erro durante a leitura do ficheiro.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 10 - ");
	printf("Formato invalido.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 11 - ");
	printf("Erro nao definido.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 12 - ");
	printf("Erro ao abrir o ficheiro.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 13 - ");
	printf("Erro tamanho array excedido.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 14 - ");
	printf("Erro conversao texto para objeto datetime.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 15 - ");
	printf("Erro array de dados nullo.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 16 - ");
	printf("Erro, opcao introduzida pelo utilizador desconhecida.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 17 - ");
	printf("Erro apagar ficheiros da base de dados.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 18 - ");
	printf("Erro processamento dos ficheiros.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 19 - ");
	printf("Erro importar dados dos ficheiros.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 20 - ");
	printf("Erro durante a leitura da data.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 21 - ");
	printf("Erro durante a leitura do limite de calorias.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 22 - ");
	printf("Erro durante a leitura do ID do paciente.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 23 - ");
	printf("Erro durante a leitura do tipo de refeicao.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 24 - ");
	printf("Erro ficheiro nulo.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 25 - ");
	printf("O utilizador nao deu permissao.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 26 - ");
	printf("Valor nulo.\n");

	EscreverComCor(ANSI_COR_VERMELHO, "  ERRO 27 - ");
	printf("Erro durante a leitura do tipo de ficheiro.\n");

	printf("\n");
}

/**
   @brief  Termina o programa apresentando uma mensagem de erro e terminando com um código de erro.

   @details   Esta função imprime uma mensagem de erro no standard error (stderr) seguida pelo
			  código de erro especificado. A seguir, termina o programa utilizando 'exit()'
			  com o código de erro "codigoErro".

   @param  codigoErro - O código de erro a ser apresentado e utilizado para encerrar o programa.
**/
void TerminarProgramaComErro(int codigoErro)
{
	fprintf(stderr, ANSI_COR_VERMELHO "PROGRAMA TERMINADO COM ERRO %d\n" ANSI_RESET, codigoErro);
	exit(codigoErro);
}

/**
	@brief Pergunta ao utilizador se deseja iniciar o programa ou sair.
**/
void PerguntarUtilizadorIniciarPrograma()
{
	printf("\n\nDeseja iniciar o programa? (y/n)\n");

	char escolha = LerTecla();
	if (escolha == 'y')
		LimparEcra();
	else
		exit(SUCESSO);
}

/**
	@brief  Converte uma data no formato texto ``DD-MM-AAAA`` para um objeto datetime.
	@param  dateString - A data em formato texto.
	@retval            - O objeto datetime.
	@retval            - 14 - Erro na conversão (ERRO_CONVERSAO_TEXTO_DATETIME).
**/
time_t ConverterStringParaDatetime(const char* dateString)
{
	struct tm tm = { 0 }; // Inicializar todos campos a zero
	int dia, mes, ano;

	if (sscanf(dateString, "%d-%d-%d", &dia, &mes, &ano) != 3)
		return ERRO_CONVERSAO_TEXTO_DATETIME;

	tm.tm_year = ano - 1900; // Anos desde 1900
	tm.tm_mon = mes - 1;    // Meses deste Janeiro [0-11]
	tm.tm_mday = dia;		// Dia do mes [1-31]
	tm.tm_isdst = -1;		// Info. DST

	time_t time = mktime(&tm);

	if (time != -1)
		return time;

	return ERRO_CONVERSAO_TEXTO_DATETIME;
}

/**
	@brief  Converte um objeto datetime para uma data no formato texto ``DD-MM-AAAA``.
	@param  datetime - O objeto datetime.
	@retval          - A string formatada "DD-MM-AAAA".
**/
const char* ConverterDatetimeParaString(time_t datetime)
{
	static char dateString[11];

	struct tm* tm_info = localtime(&datetime);
	if (!tm_info)
		return NULL;

	strftime(dateString, sizeof(dateString), "%d-%m-%Y", tm_info);

	return dateString;
}

/**
	@brief Liberta toda a memoria alocada aos pacientes, dietas e planos.
	@param pacientes    - Array pacientes.
	@param numPacientes - Apontador para o número de pacientes.
	@param dietas       - Array dietas.
	@param numDietas    - Apontador para o número de dietas.
	@param planos       - Array planos.
	@param numPlanos    - Apontador para o número de planos.

	@note	- Esta função não está a ser utilizada neste momento devido à migração para arrays de
			  tamanho constante. Mas numa implentação futura, pode-se alocar a memória dinamicamente,
			  colocando os dados no heap em vez do stack.
**/
void LibertarMemoria(Paciente** pacientes, int* numPacientes, Dieta** dietas, int* numDietas, Plano** planos, int* numPlanos)
{
	// Libertar memoria pacientes
	free(*pacientes);
	*pacientes = NULL;
	*numPacientes = 0;

	// Libertar memoria dietas
	free(*dietas);
	*dietas = NULL;
	*numDietas = 0;

	// Libertar memoria planos
	free(*planos);
	*planos = NULL;
	*numPlanos = 0;
}

/**
	@brief Compara dois elementos do tipo Paciente por ID.
	@param a - Apontador para o primeiro elemento Paciente.
	@param b - Apontador para o segundo elemento Paciente.
	@return Um número negativo se o ID de 'a' é menor que o ID de 'b',
			um número positivo se o ID de 'a' é maior que o ID de 'b' e
			0 se os IDs são iguais.
**/
int CompararPacientePorId(const void* a, const void* b)
{
	int idA = ((Paciente*)a)->id;
	int idB = ((Paciente*)b)->id;

	if (idA < 0 || idB < 0)
	{
		// Se algum dos IDs não estiver inicializado ou for inválido, coloca 
		// o elemento com ID não inicializado no fim
		return (idA < 0) - (idB < 0);
	}

	return idB - idA;
}

/**
	@brief Organiza um array de Paciente por ID usando o algoritmo de ordenação qsort.
	@param pacientes - Array de Paciente.
	@param tamanho   - Número de elementos no array.
**/
void OrganizarPacientesPorId(Paciente pacientes[], int tamanho)
{
	qsort(pacientes, tamanho, sizeof(Paciente), CompararPacientePorId);
}

/**
	@brief Compara dois elementos do tipo Dieta por ID do paciente associado.
	@param a - Apontador para o primeiro elemento Dieta.
	@param b - Apontador para o segundo elemento Dieta.
	@return Um número negativo se o ID do paciente associado de 'a' é menor que o ID do paciente associado de 'b',
			um número positivo se o ID do paciente associado de 'a' é maior que o ID do paciente associado de 'b'
			e 0 se os IDs do paciente associado são iguais.
**/
int CompararDietaPorId(const void* a, const void* b)
{
	int idA = ((Dieta*)a)->idPaciente;
	int idB = ((Dieta*)b)->idPaciente;

	if (idA == 0 || idB == 0)
	{
		return (idA == 0) - (idB == 0);
	}

	return idA - idB;
}

/**
	@brief  Compara dois elementos do tipo Dieta por data em ordem decrescente.
	@param  a - Um apontador para o primeiro elemento Dieta.
	@param  b - Um apontador para o segundo elemento Dieta.

	@retval Um número negativo se a data de 'a' é mais recente que a data de 'b',
			um número positivo se a data de 'a' é mais antiga que a data de 'b',
			e 0 se as datas são iguais.
**/
int CompararDietaPorData(const void* a, const void* b)
{
	int idA = ((Dieta*)a)->idPaciente;
	int idB = ((Dieta*)b)->idPaciente;
	time_t dataA = ((Dieta*)a)->data;
	time_t dataB = ((Dieta*)b)->data;

	// Registos com ID 0 são considerados maiores do que qualquer ID válido
	if (idA == 0 || idB == 0) {
		return (idA == 0) - (idB == 0);
	}

	// Ordem descendente
	return (dataB - dataA);
}

/**
	@brief Organiza um array de Dieta por ID do paciente associado usando o algoritmo de ordenação qsort.
	@param dietas  - Array de Dieta.
	@param tamanho - Número de elementos no array.
**/
void OrganizarDietasPorId(Dieta dietas[], int tamanho)
{
	qsort(dietas, tamanho, sizeof(Dieta), CompararDietaPorId);
}

/**
	@brief Compara dois elementos do tipo Plano por ID do paciente associado.
	@param a - Apontador para o primeiro elemento Plano.
	@param b - Apontador para o segundo elemento Plano.
	@return Um número negativo se o ID do paciente associado de 'a' é menor que o ID do paciente associado de 'b',
			um número positivo se o ID do paciente associado de 'a' é maior que o ID do paciente associado de 'b'
			e 0 se os IDs do paciente associado são iguais.
**/
int CompararPlanoPorId(const void* a, const void* b)
{
	int idA = ((Plano*)a)->idPaciente;
	int idB = ((Plano*)b)->idPaciente;

	if (idA < 0 || idB < 0)
	{
		// Se algum dos IDs não estiver inicializado ou for inválido, coloca 
		// o elemento com ID não inicializado no fim
		return (idA < 0) - (idB < 0);
	}

	return idA - idB;
}

/**
	@brief Organiza um array de Plano por ID do paciente associado usando o algoritmo de ordenação qsort.
	@param planos  - Array de Plano.
	@param tamanho - Número de elementos no array.
**/
void OrganizarPlanosPorId(Plano planos[], int tamanho)
{
	qsort(planos, tamanho, sizeof(Plano), CompararPlanoPorId);
}

/**
	@brief Verifica se uma string está no formato de data DD-MM-AAAA.
	@param dataStr - String de data para verificação.
	@return true se estiver no formato correto, false caso contrário.
 **/
bool ValidarFormatoData(const char* dataStr)
{
	int dia, mes, ano;
	return sscanf(dataStr, "%2d-%2d-%4d", &dia, &mes, &ano) == 3;
}

/**
	@brief Processa um ficheiro, importando dados de acordo com o tipo de ficheiro e tipo de dados especificados.

	@param nomeFicheiro - O nome do ficheiro a ser processado.
	@param tipoDadosFicheiro - O tipo de dados a ser importado (TIPO_DADOS_PACIENTES, TIPO_DADOS_DIETAS, TIPO_DADOS_PLANOS).
	@param tipoFicheiro - O tipo de ficheiro a ser processado (TIPO_FICHEIRO_TXT, TIPO_FICHEIRO_BIN, TIPO_FICHEIRO_TAB).
	@param dados - Um apontador para a estrutura de dados onde os dados serão guardados.
	@param tamanhoRegisto - O tamanho de cada registo dos dados.
	@param numRegistos - Um apontador para a variável que vai guardar o número de registos importados.

	@note Esta função é responsável por chamar funções específicas de importação de acordo com os tipos especificados.

	@retval resultado - O código de resultado da operação.
*/
int ProcessarFicheiro(const char* nomeFicheiro, int tipoDadosFicheiro, int tipoFicheiro,
	void* dados, size_t tamanhoRegisto, int* numRegistos)
{
	int resultado = ERRO_PROCESSAMENTO;
	char* formatoFicheiro = "";

	// Ficheiro de texto
	if (tipoFicheiro == TIPO_FICHEIRO_TXT || tipoFicheiro == TIPO_FICHEIRO_TAB)
	{
		if (tipoDadosFicheiro == TIPO_DADOS_PACIENTES)
		{
			if (tipoFicheiro == TIPO_FICHEIRO_TAB)
				formatoFicheiro = FORMATO_PACIENTES_TAB;
			else if (tipoFicheiro == TIPO_FICHEIRO_TXT)
				formatoFicheiro = FORMATO_PACIENTES_TXT;

			resultado = ImportarPacientesFichTexto(NULL, nomeFicheiro, formatoFicheiro, dados, numRegistos);
		}

		else if (tipoDadosFicheiro == TIPO_DADOS_DIETAS)
		{
			if (tipoFicheiro == TIPO_FICHEIRO_TAB)
				formatoFicheiro = FORMATO_DIETAS_TAB;
			else if (tipoFicheiro == TIPO_FICHEIRO_TXT)
				formatoFicheiro = FORMATO_DIETAS_TXT;

			resultado = ImportarDietasFichTexto(NULL, nomeFicheiro, formatoFicheiro, dados, numRegistos);
		}

		else if (tipoDadosFicheiro == TIPO_DADOS_PLANOS)
		{
			if (tipoFicheiro == TIPO_FICHEIRO_TAB)
				formatoFicheiro = FORMATO_PLANOS_TAB;
			else if (tipoFicheiro == TIPO_FICHEIRO_TXT)
				formatoFicheiro = FORMATO_PLANOS_TXT;

			resultado = ImportarPlanosFichTexto(NULL, nomeFicheiro, formatoFicheiro, dados, numRegistos);
		}
	}
	else // Ficheiro binario
	{
		resultado = ImportarDadosFichBinario(nomeFicheiro, dados, tamanhoRegisto, numRegistos);
	}

	return resultado;
}

/**
	@brief Importa e processa um ficheiro, apresentando informações e lidando com o resultado.

	@param ficheiro - O nome do ficheiro a ser importado.
	@param tipoDados - O tipo de dados a ser importado (TIPO_DADOS_PACIENTES, TIPO_DADOS_DIETAS, TIPO_DADOS_PLANOS).
	@param tipoFicheiro - O tipo de ficheiro a ser importado (TIPO_FICHEIRO_TXT, TIPO_FICHEIRO_BIN, TIPO_FICHEIRO_TAB).
	@param dados - Um apontador para a estrutura de dados onde os dados serão guardados.
	@param tamanhoRegisto - O tamanho de cada registo dos dados.
	@param numRegistos - Um apontador para a variável que vai guardar o número de registos importados.

	@note Esta função é utilizada para simplificar o processo de importação, apresentação de informações e manipulação do resultado.

	@retval                - 0 se o programa correu sem erros (SUCESSO).
	@retval                - 24 se o ficheiro introduzido é NULLO (ERRO_FICHEIRO_NULLO).
**/
int ImportarEProcessarFicheiro(const char* ficheiro, int tipoDados, int tipoFicheiro,
	void* dados, size_t tamanhoRegisto, int* numRegistos)
{
	if (ficheiro == NULL)
		return ERRO_FICHEIRO_NULLO;

	EscreverComCor(ANSI_INFO, "A importar dados do ficheiro %s...\n", ficheiro);

	int resultado = ProcessarFicheiro(ficheiro, tipoDados, tipoFicheiro, dados, tamanhoRegisto, numRegistos);

	if (resultado != SUCESSO)
	{
		LidarErrosImportacaoDados(resultado);
	}

	return SUCESSO;
}

/**
	@brief  Converte uma string de refeição para o ID (PEQUENO_ALMOCO_ID, ALMOCO_ID, JANTAR_ID).
	@param  refeicao - A string da refeição.
	@retval          - O ID da refeição ou ERRO_REFEICAO_ID (-1) em caso de erro.
**/
int ConverterRefeicaoParaId(char refeicao[TAMANHO_REFEICAO])
{
	if (strcmp(refeicao, PEQUENO_ALMOCO) == 0)
		return PEQUENO_ALMOCO_ID;

	else if (strcmp(refeicao, ALMOCO) == 0)
		return ALMOCO_ID;

	else if (strcmp(refeicao, JANTAR) == 0)
		return JANTAR_ID;

	return ERRO_REFEICAO_ID;
}

/**
	@brief  Converte uma string de refeição para o ID (PEQUENO_ALMOCO_ID, ALMOCO_ID, JANTAR_ID).
	@param  refeicao - O ID da refeição.
	@retval          - A string da refeição.
**/
const char* ConverterRefeicaoParaTexto(int refeicao)
{
	if (refeicao == PEQUENO_ALMOCO_ID)
		return PEQUENO_ALMOCO;

	else if (refeicao == ALMOCO_ID)
		return ALMOCO;

	else if (refeicao == JANTAR_ID)
		return JANTAR;

	else if (refeicao == ERRO_REFEICAO_ID)
		return "DESCONHECIDO";

	return "DESCONHECIDO";
}

/**
	@brief Guarda os dados para os ficheiros binários.
	@param pacientes    Array de pacientes a serem guardados.
	@param numPacientes Número de elementos no array de pacientes.
	@param dietas       Array de dietas a serem guardadas.
	@param numDietas    Número de elementos no array de dietas.
	@param planos       Array de planos a serem guardados.
	@param numPlanos    Número de elementos no array de planos.
**/
int GuardarDados(Paciente pacientes[], int numPacientes, Dieta dietas[], int numDietas, Plano planos[], int numPlanos)
{
	LimparEcra();
	EscreverComCor(ANSI_INFO, "A guardar dados...");

	int resultado = (
		ExportarDadosFichBinario(FICHEIRO_BIN_PACIENTES, pacientes, numPacientes, sizeof(Paciente)) +
		ExportarDadosFichBinario(FICHEIRO_BIN_DIETAS, dietas, numDietas, sizeof(Dieta)) +
		ExportarDadosFichBinario(FICHEIRO_BIN_PLANOS, planos, numPlanos, sizeof(Plano))
		);

	return resultado;
}

/**
	@brief Limpa o buffer input.
**/
void LimparInputBuffer()
{
	int tmp;
	while ((tmp = getchar()) != '\n' && tmp != EOF);
}
