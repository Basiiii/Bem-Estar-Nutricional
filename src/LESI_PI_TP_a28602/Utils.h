/**

	@file      Utils.h

	@brief     Ficheiro de cabe�alho para utilit�rios do programa.

	@details   Este ficheiro cont�m declara��es para fun��es utilit�rias do programa.

	@author    Enrique George Rodrigues

	@date      Criado: 18.11.2023
	@date      Modificado: 28.12.2023

	@copyright � Enrique George Rodrigues, 2023. Todos os direitos reservados.

**/
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "EstruturaDados.h"

/**
	@brief Uma fun��o que para o programa durante n segundos.

	@param segundos - O n�mero de segundos que o programa deve parar.

	@note - A fun��o usa o "Sleep()" para Windows e "sleep()" para sistemas Unix.
**/
void CustomSleep(int segundos);

/**
	@brief Uma fun��o que permite ler um carater.

	@note - A fun��o usa o "_getch()" para Windows e um processo especial para sistemas Unix.
**/
int LerTecla();

/**
   @brief	  Limpa o ecr� do terminal.

   @details   Esta fun��o utiliza a fun��o 'system()' para chamar o comando adequado para
			  limpar o ecr� do terminal. Suporta sistemas Windows e Unix.

   @note      A fun��o suporta sistemas Windows (utiliza "cls") e sistemas Unix
			  (utiliza "clear").
**/
void LimparEcra();

/**
   @brief  Termina o programa apresentando uma mensagem de erro e terminando com um c�digo de erro.

   @details   Esta fun��o imprime uma mensagem de erro no standard error (stderr) seguida pelo
			  c�digo de erro especificado. A seguir, termina o programa utilizando 'exit()'
			  com o c�digo de erro "codigoErro".

   @param  codigoErro - O c�digo de erro a ser apresentado e utilizado para encerrar o programa.
**/
void TerminarProgramaComErro(int erro);

/**
	@brief Uma fun��o que permite escrever no terminal numa cor definida por c�digos ANSI.

	@param cor     - O c�digo ANSI ou modo pr�-definido (ex. ANSI_INFO ou ANSI_ERROR).
	@param formato - O texto a ser apresentado no terminal com suporte para par�metros (ex. %d).
	@param ...	   - Os par�metros opcionais para apresentar valores de vari�veis (ex. %d).

	@note		   - Esta fun��o � uma fun��o vari�dica que suporta `n` par�metros adicionais para
					 escrever valores de vari�veis.

					 Exemplo de uso:
					 ```EscreverComCor(ANSI_INFO, "Isto e uma mensagem de info! %d, &variavelTipoInt);```
**/
void EscreverComCor(const char* cor, const char* formato, ...);

/**
   @brief	Apresenta o manual de ajuda ao utilizador.

   @details   Esta fun��o demonstra como utilizar o programa.
**/
void ApresentarAjuda();

/**
   @brief  Apresenta os poss�veis erros na execu��o do programa.
**/
void ApresentarErros();

/**
	@brief Pergunta ao utilizador se deseja iniciar o programa ou sair.
**/
void PerguntarUtilizadorIniciarPrograma();

/**
	@brief  Converte uma data no formato texto ``DD-MM-AAAA`` para um objeto datetime.
	@param  dateString - A data em formato texto.
	@retval            - O objeto datetime.
	@retval            - 14 - Erro na convers�o (ERRO_CONVERSAO_TEXTO_DATETIME).
**/
time_t ConverterStringParaDatetime(const char* dateString);

/**
	@brief  Converte um objeto datetime para uma data no formato texto ``DD-MM-AAAA``.
	@param  datetime - O objeto datetime.
	@retval          - A string formatada "DD-MM-AAAA".
**/
const char* ConverterDatetimeParaString(time_t datetime);

/**
	@brief Liberta toda a memoria alocada aos pacientes, dietas e planos.
	@param pacientes    - Array pacientes.
	@param numPacientes - Pointer para o n�mero de pacientes.
	@param dietas       - Array dietas.
	@param numDietas    - Pointer para o n�mero de dietas.
	@param planos       - Array planos.
	@param numPlanos    - Pointer para o n�mero de planos.
**/
void LibertarMemoria(Paciente** pacientes, int* numPacientes, Dieta** dietas, int* numDietas, Plano** planos, int* numPlanos);

/**
	@brief Compara dois elementos do tipo Paciente por ID.
	@param a - Apontador para o primeiro elemento Paciente.
	@param b - Apontador para o segundo elemento Paciente.
	@return Um n�mero negativo se o ID de 'a' � menor que o ID de 'b',
			um n�mero positivo se o ID de 'a' � maior que o ID de 'b' e
			0 se os IDs s�o iguais.
**/
int CompararPacientePorId(const void* a, const void* b);

/**
	@brief Organiza um array de Paciente por ID usando o algoritmo de ordena��o qsort.
	@param pacientes - Array de Paciente.
	@param tamanho   - N�mero de elementos no array.
**/
void OrganizarPacientesPorId(Paciente pacientes[], int tamanho);

/**
	@brief Compara dois elementos do tipo Dieta por ID do paciente associado.
	@param a - Apontador para o primeiro elemento Dieta.
	@param b - Apontador para o segundo elemento Dieta.
	@return Um n�mero negativo se o ID do paciente associado de 'a' � menor que o ID do paciente associado de 'b',
			um n�mero positivo se o ID do paciente associado de 'a' � maior que o ID do paciente associado de 'b'
			e 0 se os IDs do paciente associado s�o iguais.
**/
int CompararDietaPorId(const void* a, const void* b);

/**
	@brief  Compara dois elementos do tipo Dieta por data em ordem decrescente.
	@param  a - Um apontador para o primeiro elemento Dieta.
	@param  b - Um apontador para o segundo elemento Dieta.

	@retval Um n�mero negativo se a data de 'a' � mais recente que a data de 'b',
			um n�mero positivo se a data de 'a' � mais antiga que a data de 'b',
			e 0 se as datas s�o iguais.
**/
int CompararDietaPorData(const void* a, const void* b);

/**
	@brief Organiza um array de Dieta por ID do paciente associado usando o algoritmo de ordena��o qsort.
	@param dietas  - Array de Dieta.
	@param tamanho - N�mero de elementos no array.
**/
void OrganizarDietasPorId(Dieta dietas[], int tamanho);

/**
	@brief Compara dois elementos do tipo Plano por ID do paciente associado.
	@param a - Apontador para o primeiro elemento Plano.
	@param b - Apontador para o segundo elemento Plano.
	@return Um n�mero negativo se o ID do paciente associado de 'a' � menor que o ID do paciente associado de 'b',
			um n�mero positivo se o ID do paciente associado de 'a' � maior que o ID do paciente associado de 'b'
			e 0 se os IDs do paciente associado s�o iguais.
**/
int CompararPlanoPorId(const void* a, const void* b);

/**
	@brief Organiza um array de Plano por ID do paciente associado usando o algoritmo de ordena��o qsort.
	@param planos  - Array de Plano.
	@param tamanho - N�mero de elementos no array.
**/
void OrganizarPlanosPorId(Plano planos[], int tamanho);

/**
	@brief Verifica se uma string est� no formato de data DD-MM-AAAA.
	@param dataStr - String de data para verifica��o.
	@return true se estiver no formato correto, false caso contr�rio.
 **/
bool ValidarFormatoData(const char* dataStr);

/**
	@brief Processa um ficheiro, importando dados de acordo com o tipo de ficheiro e tipo de dados especificados.

	@param nomeFicheiro - O nome do ficheiro a ser processado.
	@param tipoDadosFicheiro - O tipo de dados a ser importado (TIPO_DADOS_PACIENTES, TIPO_DADOS_DIETAS, TIPO_DADOS_PLANOS).
	@param tipoFicheiro - O tipo de ficheiro a ser processado (TIPO_FICHEIRO_TXT, TIPO_FICHEIRO_BIN, TIPO_FICHEIRO_TAB).
	@param dados - Um apontador para a estrutura de dados onde os dados ser�o guardados.
	@param tamanhoRegisto - O tamanho de cada registo dos dados.
	@param numRegistos - Um apontador para a vari�vel que vai guardar o n�mero de registos importados.

	@note Esta fun��o � respons�vel por chamar fun��es espec�ficas de importa��o de acordo com os tipos especificados.

	@retval resultado - O c�digo de resultado da opera��o.
*/
int ProcessarFicheiro(const char* nomeFicheiro, int tipoDadosFicheiro, int tipoFicheiro,
	void* dados, size_t tamanhoRegisto, int* numRegistos);

/**
	@brief Importa e processa um ficheiro, apresentando informa��es e lidando com o resultado.

	@param ficheiro - O nome do ficheiro a ser importado.
	@param tipoDados - O tipo de dados a ser importado (TIPO_DADOS_PACIENTES, TIPO_DADOS_DIETAS, TIPO_DADOS_PLANOS).
	@param tipoFicheiro - O tipo de ficheiro a ser importado (TIPO_FICHEIRO_TXT, TIPO_FICHEIRO_BIN, TIPO_FICHEIRO_TAB).
	@param dados - Um apontador para a estrutura de dados onde os dados ser�o guardados.
	@param tamanhoRegisto - O tamanho de cada registo dos dados.
	@param numRegistos - Um apontador para a vari�vel que vai guardar o n�mero de registos importados.

	@note Esta fun��o � utilizada para simplificar o processo de importa��o, apresenta��o de informa��es e manipula��o do resultado.

	@retval                - 0 se o programa correu sem erros (SUCESSO).
	@retval                - 24 se o ficheiro introduzido � NULLO (ERRO_FICHEIRO_NULLO).
**/
int ImportarEProcessarFicheiro(const char* ficheiro, int tipoDados, int tipoFicheiro,
	void* dados, size_t tamanhoRegisto, int* numRegistos);

/**
	@brief  Converte uma string de refei��o para o ID (PEQUENO_ALMOCO_ID, ALMOCO_ID, JANTAR_ID).
	@param  refeicao - A string da refei��o.
	@retval          - O ID da refei��o.
**/
int ConverterRefeicaoParaId(char refeicao[TAMANHO_REFEICAO]);


/**
	@brief  Converte uma string de refei��o para o ID (PEQUENO_ALMOCO_ID, ALMOCO_ID, JANTAR_ID).
	@param  refeicao - O ID da refei��o.
	@retval          - A string da refei��o.
**/
const char* ConverterRefeicaoParaTexto(int refeicao);

/**
	@brief Guarda os dados para os ficheiros bin�rios.
	@param pacientes    Array de pacientes a serem guardados.
	@param numPacientes N�mero de elementos no array de pacientes.
	@param dietas       Array de dietas a serem guardadas.
	@param numDietas    N�mero de elementos no array de dietas.
	@param planos       Array de planos a serem guardados.
	@param numPlanos    N�mero de elementos no array de planos.
**/
int GuardarDados(Paciente pacientes[], int numPacientes, Dieta dietas[], int numDietas, Plano planos[], int numPlanos);

/**
	@brief Limpa o buffer input.
**/
void LimparInputBuffer();

#endif
