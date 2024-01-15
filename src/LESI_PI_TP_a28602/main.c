/**

	@file      main.c

	@brief     Ponto de entrada principal da aplicação que apoia o
			   bem-estar e cuidados nutricionais. Desenvolvido por Enrique
			   Rodrigues na unidade curricular de Programação Imperativa.

	@details   O programa visa apoiar o bem-estar e cuidados nutricionais, abordando o problema do
			   comportamento alimentar saudável. Funcionalidades incluem carregamento de dados de
			   pacientes, dietas e planos nutricionais, apresentação de estatísticas de calorias, listagem
			   de pacientes com comportamento fora do plano nutricional e análises diversas.
			   Desenvolvido com base em métodos rigorosos de análise de problemas e as melhores práticas de
			   programação imperativa em C.

	@author    Enrique George Rodrigues

	@date      Criado: 16.11.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Constantes.h"
#include "EstruturaDados.h"
#include "Utils.h"

#include "Menu.h"

#include "InputStdin.h"

#include "Parametros.h"

#include "ControloErros.h"

#include "OperacoesFicheiros.h"
#include "../GestorDadosIO/IODadosAPI.h"

#include "Debug.h"

/**
   @brief	  Função principal que controla a execução do programa.

   @details   Esta função inicia o programa e controla a execução de diferentes blocos
			  de código, incluindo o controlo dos parametros do utlizador, a verificação (e criação)
			  dos ficheiros binários, a importação dos dados para memória do sistema, a apresentação
			  de um menu para interação com o utilizador e a execução das opções escolhidas no menu.

   @warning   Esta função pode interagir com o utilizador para corrigir erros nos dados dos pacientes.
   @warning   O utilizador pode apagar todos os dados dos pacientes se chamar o programa com o parámetro "--apagarbd".
   @warning   O menu corre num ciclo infinito até ser escolhido 'q' (terminar e guardar dados) ou 'f' (terminar sem guardar).

   @param[in] argc O número de argumentos da linha de comandos.
   @param[in] argv Um array de strings representando os argumentos da linha de comandos.

   @return 0 - O programa correu sem erros (SUCESSO).
   @return 1 - Não existem os ficheiros binários (ERRO_NAO_EXISTEM_FICHEIROS_BIN).
   @return 2 - Erro ao criar o ficheiro (ERRO_CRIAR_FICHEIRO).
   @return 3 - Erro ao importar dados do texto (ERRO_IMPORTAR_DADOS_TEXTO).
   @return 4 - Erro ao importar dados binários (ERRO_IMPORTAR_DADOS_BIN).
   @return 5 - Erro ao apagar ficheiros binários (ERRO_APAGAR_FICHEIROS_BIN).
   @return 6 - Erro ao alocar memória (ERRO_ALOCAR_MEMORIA).
   @return 7 - Ficheiro não encontrado (ERRO_FICHEIRO_NAO_ENCONTRADO).
   @return 8 - Ficheiro vazio (ERRO_FICHEIRO_VAZIO).
   @return 9 - Erro durante a leitura do ficheiro (ERRO_LEITURA_FICHEIRO).
   @return 10 - Formato inválido (ERRO_FORMATO_INVALIDO).
   @return 11 - Erro não definido (ERRO_NAO_DEFINIDO).
   @return 12 - Erro ao abrir o ficheiro (ERRO_ABRIR_FICHEIRO).
   @return 13 - Erro tamanho array excedido (ERRO_TAMANHO_EXCEDIDO).
   @return 14 - Erro conversão data texto para objeto datetime (ERRO_CONVERSAO_TEXTO_DATETIME).
   @return 15 - Erro array de dados nullo (ERRO_ARRAY_DADOS_NULL).
   @return 16 - Erro opção introduzida pelo utilizador desconhecida (ERRO_OPCAO_UTILIZADOR_DESCONHECIDA).
   @return 17 - Erro apagar ficheiros da base de dados (.dat) (ERRO_APAGAR_BASE_DADOS).
   @return 18 - Erro processamento dos ficheiros (ERRO_PROCESSAMENTO).
   @return 19 - Erro importar dados dos ficheiros (ERRO_IMPORTAR_DADOS).
   @return 20 - Erro durante a leitura da data (ERRO_LEITURA_DATA).
   @return 21 - Erro durante a leitura do limite de calorias (ERRO_LEITURA_LIMITE_CALORIAS).
   @return 22 - Erro durante a leitura do ID do paciente (ERRO_LEITURA_ID_PACIENTE).
   @return 23 - Erro durante a leitura do tipo de refeição (ERRO_LEITURA_TIPO_REFEICAO).
   @return 24 - Erro ficheiro nulo (ERRO_FICHEIRO_NULLO).
   @return 25 - O utilizador não deu permissão (ERRO_UTILIZADOR_NAO_DEU_PERMISSAO).
   @return 26 - Valor nulo (ERRO_VALOR_NULLO).
   @return 27 - Erro durante a leitura do tipo de ficheiro (ERRO_LEITURA_TIPO_FICHEIRO).
**/
int main(int argc, char* argv[])
{
	// Configura a localização para português
	setlocale(LC_ALL, "pt_PT.UTF-8");

	// Limpa o ecra e inicia o programa
	LimparEcra();
	EscreverComCor(ANSI_TITULO, "\n\tPROGRAMA BEM ESTAR \n\n");

#pragma region VERIFICAR_PARAMETROS_UTILIZADOR

	char* ficheiroPacientes = NULL;
	char* ficheiroDietas = NULL;
	char* ficheiroPlanos = NULL;

	int tipoFicheiroPacientes = TIPO_FICHEIRO_TXT;
	int tipoFicheiroDietas = TIPO_FICHEIRO_TXT;
	int tipoFicheiroPlanos = TIPO_FICHEIRO_TXT;

	// Atualiza as variáveis dos parametros opcionais de acordo com os argumentos passados
	ManipularParametrosOpcionais(argc, argv, &ficheiroPacientes, &ficheiroDietas, &ficheiroPlanos,
		&tipoFicheiroPacientes, &tipoFicheiroDietas, &tipoFicheiroPlanos);

	// Apresenta os ficheiros e tipos de ficheiros passados para o programa
	if (MODO_DEBUG)
		DebugMostrarFicheirosUtilizador(ficheiroPacientes, ficheiroDietas, ficheiroPlanos,
			tipoFicheiroPacientes, tipoFicheiroDietas, tipoFicheiroPlanos);

#pragma endregion

#pragma region VERIFICAR_E_CRIAR_FICHEIROS_BINARIOS

	EscreverComCor(ANSI_TITULO, "\nA executar os testes iniciais...\n\n");

	int resultadoVerificacao = 0;

	resultadoVerificacao = VerificarEAtualizarFicheiroBinario(FICHEIRO_BIN_PACIENTES);
	if (resultadoVerificacao == FICHEIRO_EXISTE)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da base de dados dos pacientes existe...\n\n");
	else if (resultadoVerificacao == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da criado com sucesso.\n\n");
	else
		LidarErroVerificacaoFicheiroBinario(resultadoVerificacao);

	resultadoVerificacao = VerificarEAtualizarFicheiroBinario(FICHEIRO_BIN_DIETAS);
	if (resultadoVerificacao == FICHEIRO_EXISTE)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da base de dados das dietas existe...\n\n");
	else if (resultadoVerificacao == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da criado com sucesso.\n\n");
	else
		LidarErroVerificacaoFicheiroBinario(resultadoVerificacao);

	resultadoVerificacao = VerificarEAtualizarFicheiroBinario(FICHEIRO_BIN_PLANOS);
	if (resultadoVerificacao == FICHEIRO_EXISTE)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da base de dados dos planos existe...\n\n");
	else if (resultadoVerificacao == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Ficheiro binario da criado com sucesso.\n\n");
	else
		LidarErroVerificacaoFicheiroBinario(resultadoVerificacao);

#pragma endregion

#pragma region IMPORTAR_BASE_DADOS

	Paciente pacientes[TAMANHO_MAX_ARRAY] = { 0 };
	int numPacientes = 0;

	Dieta dietas[TAMANHO_MAX_ARRAY] = { 0 };
	int numDietas = 0;

	Plano planos[TAMANHO_MAX_ARRAY] = { 0 };
	int numPlanos = 0;

	// Importar dados da 'base de dados' (ficheiros .dat)
	ImportarDadosBaseDados(FICHEIRO_BIN_PACIENTES, pacientes, sizeof(Paciente), &numPacientes, "pacientes");
	ImportarDadosBaseDados(FICHEIRO_BIN_DIETAS, dietas, sizeof(Dieta), &numDietas, "dietas");
	ImportarDadosBaseDados(FICHEIRO_BIN_PLANOS, planos, sizeof(Plano), &numPlanos, "planos");

#pragma endregion

#pragma region IMPORTAR_DADOS_FICHEIROS_UTILIZADOR

	// Processa e importa os dados dos ficheiros dados pelo utilizador através dos 
	// parametros opcionais do programa
	int resultadoProcessamentoFicheiro = -1;

	// IMPORTAR PACIENTES
	resultadoProcessamentoFicheiro = ImportarEProcessarFicheiro(ficheiroPacientes, TIPO_DADOS_PACIENTES, tipoFicheiroPacientes,
		pacientes, sizeof(Paciente), &numPacientes);

	if (resultadoProcessamentoFicheiro == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Dados importados com sucesso.\n");

	// IMPORTAR DIETAS
	resultadoProcessamentoFicheiro = ImportarEProcessarFicheiro(ficheiroDietas, TIPO_DADOS_DIETAS, tipoFicheiroDietas,
		dietas, sizeof(Dieta), &numDietas);

	if (resultadoProcessamentoFicheiro == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Dados importados com sucesso.\n");

	// IMPORTAR PLANOS
	resultadoProcessamentoFicheiro = ImportarEProcessarFicheiro(ficheiroPlanos, TIPO_DADOS_PLANOS, tipoFicheiroPlanos,
		planos, sizeof(Plano), &numPlanos);

	if (resultadoProcessamentoFicheiro == SUCESSO)
		EscreverComCor(ANSI_SUCESSO, "Dados importados com sucesso.\n");

	// DEBUG - Apresenta os dados na memória
	if (MODO_DEBUG)
		DebugMostrarDadosMemoria(pacientes, numPacientes, dietas, numDietas, planos, numPlanos);

#pragma endregion

#pragma region ORGANIZAR_DADOS

	OrganizarDietasPorId(dietas, numDietas);

#pragma endregion

	printf("\nCarregue numa tecla para continuar...");
	LerTecla();

#pragma region "Menu do programa"

	char escolhaMenu = '\0';
	int resultado = -1;

	do {
		ApresentarMenu();
		escolhaMenu = LerTecla();

		switch (escolhaMenu)
		{
		case '1': // Carregar Dados
			LimparEcra();

			ImportarDadosStdin(pacientes, &numPacientes, dietas, &numDietas, planos, &numPlanos);

			if (MODO_DEBUG)
				DebugMostrarDadosMemoria(pacientes, numPacientes, dietas, numDietas, planos, numPlanos);

			printf("\n\nCarregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case '2': // Pacientes que ultrapassaram determinada quantidade de calorias
			LimparEcra();

			resultado = PacientesUltrapassaramCalorias(dietas, numDietas, numPacientes);
			if (resultado != SUCESSO)
				LidarErroPacientesUltrapassamCalorias(resultado);

			LimparInputBuffer();
			printf("Carregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case '3': // Pacientes com dietas fora do plano dentro de um intervalo
			LimparEcra();

			resultado = PacientesForaPlano(pacientes, dietas, planos);
			if (resultado != SUCESSO)
				LidarErroPacientesForaPlano(resultado);

			LimparInputBuffer();
			printf("\n\nCarregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case '4': // Planos nutricionais de um paciente para determinada refeicao
			LimparEcra();

			resultado = ListarPlanosNutricionais(planos, numPlanos);
			if (resultado != SUCESSO)
				LidarErroListarPlanoNutricional(resultado);

			LimparInputBuffer();
			printf("Carregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case '5': // Medias das calorias consumidas por refeicao por cada paciente
			LimparEcra();

			resultado = ListarMediasCaloriasPorRefeicao(pacientes, dietas);
			if (resultado != SUCESSO)
				LidarErroListarMediasCaloriasPorRefeicao(resultado);

			LimparInputBuffer();
			printf("Carregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case '6': // Tabela das refeicoes planeadas e realizadas para todos os pacientes
			LimparEcra();

			resultado = GerarTabelaRefeicoes(pacientes, numPacientes, planos, numPlanos, dietas, numDietas);
			if (resultado != SUCESSO)
				LidarErroGerarTabelaRefeicoes(resultado);

			LimparInputBuffer();
			printf("\nCarregue uma tecla para continuar...\n");
			LerTecla();
			break;

		case 'q': // Terminar e guardar dados
			LimparEcra();
			EscreverComCor(ANSI_INFO, "A guardar dados...");

			resultado = GuardarDados(pacientes, numPacientes, dietas, numDietas, planos, numPlanos);
			if (resultado == SUCESSO)
			{
				printf("\n");
				EscreverComCor(ANSI_SUCESSO, "Dados guardados com sucesso.\n");
				printf("\nA terminar o programa...\n");
				exit(0);
			}
			else
			{
				LidarErroGuardarDados(resultado);
			}
			break;

		case 'f': // Terminar sem guardar dados
			printf("\nA terminar o programa sem guardar dados...\n");
			exit(0);

		}
	} while (1);

#pragma endregion
}
