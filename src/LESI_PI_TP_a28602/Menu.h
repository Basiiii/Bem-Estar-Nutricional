/**

	@file      Menu.h

	@brief	   Ficheiro de cabe�alho para funcionalidades do menu.

	@details   Este ficheiro cont�m declara��es para funcionalidades
			   relacionadas ao menu do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date	   Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef MENU_H
#define MENU_H

/**
   @brief  Apresenta o menu de op��es para intera��o com o programa.

   @details   Esta fun��o imprime no ecr� as op��es dispon�veis para intera��o com o programa.
			  O utilizador � solicitado a escolher uma das op��es apresentadas.

   @note      As op��es incluem carregar dados, verificar pacientes com calorias ultrapassadas,
			  verificar pacientes com calorias fora do intervalo, obter o plano nutricional de um
			  paciente para uma refei��o espec�fica, calcular m�dias de calorias consumidas por
			  refei��o por cada paciente, e apresentar uma tabela das refei��es planeadas e realizadas
			  para todos os pacientes. As op��es 'q' e 'f' fecham o programa.

   @warning   A fun��o n�o lida com a leitura da escolha do utilizador e n�o verifica a validade
			  da escolha inserida. Apenas apresenta o menu no stdout.
**/
void ApresentarMenu();

/**
	@brief  L� uma string do utilizador para a data.
	@param  data - A vari�vel onde se quer guardar a data.
	@param  proposito - O objetivo da leitura (p. ex., "inicial" ou "final").
	@retval      - Verdadeiro se correu sem erros, Falso se correu com erros.
**/
bool LerData(char* data, const char* proposito);

/**
	@brief Fun��o para executar a funcionalidade 2 - Pacientes que ultrapassam um dado limite de calorias entre determinadas datas.
	@param dietas       - O array de dietas.
	@param numDietas    - O n�mero de dietas.
	@param numPacientes - O n�mero de pacientes.
	@retval				- 0 se o programa correu sem erros (SUCESSO).
	@retval				- 6 se houve um erro na aloca��o de mem�ria (ERRO_ALOCAR_MEMORIA).
	@retval				- 20 se houve erro na leitura da data (ERRO_LEITURA_DATA).
	@retval				- 21 se houve erro na leitura do limite de calorias (ERRO_LEITURA_LIMITE_CALORIAS).
**/
int PacientesUltrapassaramCalorias(Dieta* dietas, int numDietas, int numPacientes);

/**
	@brief		M�todo que executa a funcionalidade 3 - apresentar pacientes com dietas fora do seu plano.
	@param pacientes - O array de pacientes.
	@param dietas    - O array de dietas.
	@param planos    - O array de planos.
	@retval          - 0 se correr com sucesso.
	@retval          - 20 se houver um erro com a leitura de datas.
**/
int PacientesForaPlano(Paciente* pacientes, Dieta* dietas, Plano* planos);

/**
	@brief  Lista os planos nutricionais de um paciente para determinada refei��o ao longo de um determinado per�odo.
	@param  planos    - O array de planos nutricionais.
	@param  numPlanos - O n�mero de planos nutricionais no array.
	@retval           - 0 se correr com sucesso.
	@retval           - 20 se houver um erro com a leitura de datas (ERRO_LEITURA_DATA).
	@retval           - 22 se n�o for poss�vel ler o ID do paciente (ERRO_LEITURA_ID_PACIENTE).
	@retval           - 23 se n�o for poss�vel ler o tipo de refei��o (ERRO_LEITURA_TIPO_REFEICAO).
**/
int ListarPlanosNutricionais(Plano planos[], int numPlanos);

/**
	@brief  Lista m�dias de calorias por refei��o para um intervalo de datas espec�fico.
	@param  pacientes   - O array de pacientes.
	@param  dietas      - O array de todas as dietas.
	@retval				- 0 se correr com sucesso.
	@retval				- 20 se houver um erro com a leitura de datas.
**/
int ListarMediasCaloriasPorRefeicao(Paciente pacientes[], Dieta dietas[]);

/**
	@brief  Gera a tabela de refei��es.
	@param  pacientes     - Array de pacientes.
	@param  numPacientes  - N�mero de pacientes.
	@param  planos        - Array de planos.
	@param  numPlanos     - N�mero de planos.
	@param  dietas        - Array de dietas.
	@param  numDietas     - N�mero de dietas.
	@retval				  - 0 se correr com sucesso.
	@retval               - 26 se n�o foi poss�vel encontrar um paciente.
**/
int GerarTabelaRefeicoes(Paciente pacientes[], int numPacientes, Plano planos[], int numPlanos, Dieta dietas[], int numDietas);

#endif
