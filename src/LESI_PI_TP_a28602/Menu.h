/**

	@file      Menu.h

	@brief	   Ficheiro de cabeçalho para funcionalidades do menu.

	@details   Este ficheiro contém declarações para funcionalidades
			   relacionadas ao menu do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date	   Modificado: 28.12.2023

	@copyright © Enrique George Rodrigues, 2023. All right reserved.

**/
#ifndef MENU_H
#define MENU_H

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
void ApresentarMenu();

/**
	@brief  Lê uma string do utilizador para a data.
	@param  data - A variável onde se quer guardar a data.
	@param  proposito - O objetivo da leitura (p. ex., "inicial" ou "final").
	@retval      - Verdadeiro se correu sem erros, Falso se correu com erros.
**/
bool LerData(char* data, const char* proposito);

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
int PacientesUltrapassaramCalorias(Dieta* dietas, int numDietas, int numPacientes);

/**
	@brief		Método que executa a funcionalidade 3 - apresentar pacientes com dietas fora do seu plano.
	@param pacientes - O array de pacientes.
	@param dietas    - O array de dietas.
	@param planos    - O array de planos.
	@retval          - 0 se correr com sucesso.
	@retval          - 20 se houver um erro com a leitura de datas.
**/
int PacientesForaPlano(Paciente* pacientes, Dieta* dietas, Plano* planos);

/**
	@brief  Lista os planos nutricionais de um paciente para determinada refeição ao longo de um determinado período.
	@param  planos    - O array de planos nutricionais.
	@param  numPlanos - O número de planos nutricionais no array.
	@retval           - 0 se correr com sucesso.
	@retval           - 20 se houver um erro com a leitura de datas (ERRO_LEITURA_DATA).
	@retval           - 22 se não for possível ler o ID do paciente (ERRO_LEITURA_ID_PACIENTE).
	@retval           - 23 se não for possível ler o tipo de refeição (ERRO_LEITURA_TIPO_REFEICAO).
**/
int ListarPlanosNutricionais(Plano planos[], int numPlanos);

/**
	@brief  Lista médias de calorias por refeição para um intervalo de datas específico.
	@param  pacientes   - O array de pacientes.
	@param  dietas      - O array de todas as dietas.
	@retval				- 0 se correr com sucesso.
	@retval				- 20 se houver um erro com a leitura de datas.
**/
int ListarMediasCaloriasPorRefeicao(Paciente pacientes[], Dieta dietas[]);

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
int GerarTabelaRefeicoes(Paciente pacientes[], int numPacientes, Plano planos[], int numPlanos, Dieta dietas[], int numDietas);

#endif
