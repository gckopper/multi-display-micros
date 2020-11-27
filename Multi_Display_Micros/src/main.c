/**
**
**===========================================================================
**  @file    TP01_-_Multi_Display_-_Gabriel_K._e_Pedro_L.,_Turma_4312.c
**  @author  Pedro L. Lima
**  @author  Gabriel C. Kopper
**  @group   4312
**  @date    nov / 2020
**  @version 1.0
**  @brief   Trabalho 1: Painel de displays que exibe mensagens de texto
**===========================================================================
**

Este programa realiza a exibi��o de uma mensagem, configur�vel por fun��es e por
macros, atrav�s de um n�mero pr�-definido de displays de 7 segmentos. O programa
realiza isso atrav�s da multiplexa��o dos catodos de cada display. A frequ�ncia
de multiplexa��o utilizada neste programa � de 1 kHz, podendo-se utilizar, assim
at� 40 displays para exibir mensagens. As mensagens s�o exibidas com os caracteres
descritos na tabela abaixo.

Pinagem (para todos os displays com pinos comuns conectados):

				   Displays de 7 segmentos:

							  A
							-----
						  F| 	 |B
						   |  G  |
						    -----
						  E|	 |C
						   |	 |
						    -----
						      D    * P

				   	   PC0 -> A, PC1 -> B,
				   	   PC2 -> C, PC3 -> D,
				   	   PC4 -> E, PC5 -> F,
				   	   PC6 -> G, PC7 -> P;

				   	PC8  -> Base Transistor 1;
				   	PC9  -> Base Transistor 2;
				   	PC10 -> Base Transistor 3;
				   	PC11 -> Base Transistor 4;

Tabela de caracteres para o display de 7 segmentos:

CARACTERE			BIN�RIO (Pinos de P a A do display)				HEXADECIMAL
0					0 0 1 1 1 1 1 1									0x3F
1					0 0 0 0 0 1 1 0									0x6
2					0 1 0 1 1 0 1 1									0x5B
3					0 1 0 0 1 1 1 1									0x4F
4					0 1 1 0 0 1 1 0									0x66
5					0 1 1 0 1 1 0 1									0x6D
6					0 1 1 1 1 1 0 1									0x7D
7					0 0 0 0 0 1 1 1									0x7
8					0 1 1 1 1 1 1 1									0x7F
9					0 1 1 0 1 1 1 1									0x6F
A					0 1 1 1 0 1 1 1									0x77
B					0 1 1 1 1 1 0 0									0x7C
C					0 0 1 1 1 0 0 1									0x39
D					0 1 0 1 1 1 1 0									0x5E
E					0 1 1 1 1 0 0 1									0x79
F					0 1 1 1 0 0 0 1									0x71
G					0 0 1 1 1 1 0 1									0x3D
H					0 1 1 1 0 1 0 0									0x74
I					0 0 1 1 0 0 0 0									0x30
J					0 0 0 1 1 1 1 0									0x1E
K					0 1 1 1 0 1 0 1									0x75
L					0 0 1 1 1 0 0 0									0x38
M					0 0 0 1 0 1 0 1									0x15
N					0 0 1 1 0 1 1 1									0x37
O					0 1 0 1 1 1 0 0									0x5C
P					0 1 1 1 0 0 1 1									0x73
Q					0 1 1 0 0 1 1 1									0x67
R					0 0 1 1 0 0 1 1									0x33
S					0 1 1 0 1 0 0 1									0x69
T					0 1 1 1 1 0 0 0									0x78
U					0 0 1 1 1 1 1 0									0x3E
V					0 0 1 0 1 1 1 0									0x2E
W					0 0 1 0 1 0 1 0									0x2A
X					0 1 1 1 0 1 1 0									0x76
Y					0 1 1 0 1 1 1 0									0x6E
Z					0 1 0 0 1 0 1 1									0x4B
(espa�o)			0 0 0 0 0 0 0 0									0x00
.					1 0 0 0 0 0 0 0									0x80
;					1 0 0 0 0 0 1 0									0x82
!					1 0 0 0 0 1 1 0									0x83
-					0 1 0 0 0 0 0 0									0x40
_					0 0 0 0 1 0 0 0									0x04
�					0 0 1 0 0 0 0 0									0x20
�					0 0 1 0 0 0 1 0									0x22
,					0 0 0 0 0 1 0 0									0x04
(					0 0 1 1 1 0 0 1									0x39
)					0 0 0 0 1 1 1 1									0x0F
\					0 1 1 0 0 1 0 0									0x64
/					0 1 0 1 0 0 1 0									0x52
?					1 1 0 1 0 0 1 1									0xD3
:					1 1 0 0 0 0 1 0									0xC2
=					0 1 0 0 1 0 0 0									0x48
>					0 1 0 0 0 0 1 1									0x43
<					0 1 1 0 0 0 0 1									0x61

Dimensionamento dos componentes externos:

Transistores BC547	 -> Com Vcem�x de 45 V, Pcm�x de 500 mW, Icm�x de 100 mA,
						hfemin de 110 e ainda fm�x de 300 MHz, � o transistor
						ideal em termos de pre�o e funcionalidade para amplificar
						a corrente no catodo dos displays, bem como inverter o
						sinal de controle para conseguir fazer o respectivo display
						funcionar com sinal alto.

Resistores de 4700 R -> A corrente nos coletores dos transistors, considerando que,
						em cada segmento pode ter 5,56 mA (devido ao resistor de 270 R),
						� de no m�ximo 44,44 mA. Com isso, considerando o valor m�nimo
						de hfe do transistor (110), tem-se, no m�ximo, 0,40404 mA assim,
						considerando Vbe como 0,7 V, o m�ximo valor de Rb � de
						(3,3 V - 0,7 V) / 0,40404 mA = 6435 R. Assim, resistores de 4k7
						s�o mais que suficientes.

Resistores de 270 R ->  Como os LEDs vermelhos drenam 1,8 V (por tabela online),
					    tem-se 3,3 V - 1,8 V nos resistores (1,5 V). Estabeleceu-se
					    uma corrente pr�xima de 5 mA para cada LED e, assim, 1,5 V
					    divididos por 5 mA resulta em 300 R, portanto, resistores
					    de 270 R s�o suficientes.

**/

/* Includes */
#include "stm32f4xx.h"
#include <stdlib.h>

/* Vari�veis Globais */
uint8_t tascii [] = {0x00, 0x86, 0x22, 0xff, 0xff, 0xff, 0xff, 0x20, 0x39, 0x0f, // Tabela de convers�o de char para sa�da da GPIO
					 0xff, 0xff, 0x04, 0x40, 0x80, 0x52, 0x3f, 0x06, 0x5b, 0x4f, // baseada no valor num�rico dos caracterees na
					 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0xc2, 0x82, 0x61, 0x48, // tabela ASCII com um offset de 32 para excluir
					 0x43, 0xd3, 0xff, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, // caracteres sem representa��o gr�fica e economizar
					 0x74, 0x30, 0x1e, 0x75, 0x38, 0x15, 0x37, 0x5c, 0x73, 0x67, // mem�ria
					 0x33, 0x69, 0x78, 0x3e, 0x2e, 0x2a, 0x76, 0x6e, 0x4b, 0xff,
					 0x64, 0xff, 0xff, 0x08};

uint8_t* contrlDisp; // Ponteiro usado para manipular globalmente o ponteiro dPin

char* frase; // Ponteiro usado para percorrer o espa�o de mem�ria com a frase que ser� mostrada no display

uint8_t nDisplays = 0; // Vari�vel que armazena o numero de displays

int tamanho = 0; // Vari�vel representando o tamanho do espa�o (em bytes) que a frase que ser� mostrada no display ocupa

unsigned int lTempo; // Vari�vel usada para tornar global a vari�vel lTime da fun��o displayConf

char selModo; // Vari�vel usada para tornar global a vari�vel selectMode da fun��o displayConf

/* Corpo de Fun��es de Interrup��o */
void TIM1_UP_TIM10_IRQHandler (void) // Quando o bit UIF de TIM10 virar 1
{
	if (frase != NULL) { // Verifica se o vetor frase � n�o nulo, pois caso ele seja nulo, n�o haver� mensagem para ser mostrada

		// Vari�veis Locais
		static unsigned int count = 0; // Vari�vel local, que preserva o valor na pr�xima chamada da fun��o, respons�vel por contar quantas vezes passou 1 ms

		if (tamanho < 0) // Caso tamanho seja negativo, significa que seu valor foi multiplicado por '-1', assim:
		{
			count = 0; // O contador deve ser resetado
			tamanho *= -1; // E o tamanho multiplicado por '-1' novamente
		}

		if (*frase == '\0') // Caso o seja o �ltimo caractere do espa�o reservado para a frase
		{
			frase -= (tamanho - 1); // Retorna para o primeiro endere�o da frase usando o tamanho dela;
			count = 0; // Reseta o contador de interrup��es

			if (selModo == 'u') // Caso o modo selecionado como par�metro da fun��o displayConf seja igual a 'u'
			{
				TIM10 -> DIER &= ~TIM_DIER_UIE; // Desabilita interrup��es atrav�s do update do TIM10
			}

			return; // Finaliza a execu��o da interrup��o
		}

		if ((count % nDisplays == 0) && (count != 0)) // Quando o contador for um multiplo do n�mero de displays (excluindo o valor nulo)
		{
			frase -= nDisplays; // Retorna nDisplays endere�os no espa�o da frase (para ir para o caractere do primeiro display)

			if (count == lTempo) // Entra na condicional quando passaram lTempo vezes 1 ms
			{
				frase++; // Passa para a pr�xima letra da frase
				count = 0; // Zera o contador
			}
		}

		GPIOC -> ODR &= 0xfffff000; // Desligando todos os segmentos dos displays (PC0 a PC7)

		/* Ligando um display usando deslocamento de bits para a posi��o indicada pelo ponteiro que cont�m os pinos indicados pelo usu�rio */
		/* O endere�o usado � o modulo entre o contador de ciclos e o n�mero de displays, ciclando entre 0 e (nDisplays - 1)               */
		GPIOC -> ODR |= 1 << contrlDisp [count % nDisplays];

		/* � inserido na ODR um valor determinado pelo vetor tascii no endere�o determinado pelo valor num�rico do caractere no vetor (frase - 32) (offset da tabela) */
		GPIOC -> ODR |= tascii [(int)(*frase) - 32];

		frase++; // Passa para o pr�ximo caractere da frase
		count++; // Adiciona um ao contador de interrup��es

	}
	TIM10 -> SR &= ~TIM_SR_UIF; // Zerando o bit UIF quando a contagem for conclu�da
}

/* Corpo de Fun��es Customizadas */
void displayConf (const char* fEntra, uint8_t dEntra, uint8_t* dPin, unsigned int lTime, const char selectMode)
{
/*
   Par�metros da fun��o:

   fEntra guarda uma string para ser mostrada nos displays;

   dEntrada guarda a quantidade de displays em uso;

   dPin � um vetor com os valores dos pinos no GPIOC;

   lTime serve para definir o tempo de cada caractere no display (em ms).
*/
	/* Vari�veis Locais */
	int backupTamanho = tamanho; // Salvando uma copia do tamanho

	if (*fEntra == '\0' || *dPin == '\0' || dEntra == 0 || lTime == 0 || (selectMode != 'u' && selectMode != 'c')) // Caso n�o esteja bem configurada a fun��o
	{
		return; // Encerra a fun��o
	}

	TIM10 -> DIER &= ~TIM_DIER_UIE; // Desabilitando interrup��es atrav�s do update do TIM10

	selModo = selectMode; // Tornando o par�metro selectMode global em selModo

	lTempo = lTime; // Passando o tempo configurado para a vari�vel global

	nDisplays = dEntra; // Definindo o valor da vari�vel global que armazena o n�mero de displays

	static char* phFrase = NULL; // Definindo um placeholder para o ponteiro de forma est�tica para usar o free caso a fun��o seja executada novamente
	static uint8_t* phCtrlDisp = NULL; // Definindo um placeholder para o ponteiros de forma est�tica para usar o free caso a fun��o seja executada novamente

	if (frase == NULL) // Caso o ponteiro apontado para uma parte da frase tenha endere�o nulo, significa que � a primeira execu��o desta fun��o
	{
		TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrup��es atrav�s do update do TIM10
		TIM10 -> PSC = 159; // Colocando o Pre-scaller de TIM10 para dividir CK_INT (16 MHz) por 160
		TIM10 -> ARR = 99; // Auto-reload reiniciando o contador ap�s contar at� 99
		TIM10 -> CR1 |= TIM_CR1_CEN;
		/* Tem-se, assim, uma contagem para TIM10 que leva 1 ms para ser conclu�da */

		NVIC_SetPriority (TIM1_UP_TIM10_IRQn, 0); // Colocando a prioridade da interrup��o de TIM10 como prioridade m�xima
		NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); // Habilitando a interrup��o por hardware atrav�s do TIM10
	}

	tamanho = 0; // Zerando o tamanho da frase para trocar seu valor

	while (*fEntra != '\0') // Executa at� o fim da frase
	{
		fEntra++; // Passa para o pr�ximo endere�o da string par�metro
		tamanho++; // Contabiliza a letra no tamanho da frase
	}

	fEntra -= tamanho; // Retornando pro inicio da string

	tamanho++; // Contabilizando o caractere de fechamento da string

	frase = NULL;      // Deixando os ponteiros
	contrlDisp = NULL; // globais em endere�o nulo

	frase = malloc (tamanho + (dEntra * 2)); // Alocando mem�ria para a frase com espa�os extras para o padding
	contrlDisp = malloc (sizeof (uint8_t) * dEntra); // Alocando mem�ria para armazenar os pinos de controle

	if (frase == NULL || contrlDisp == NULL) // Se os ponteiros estiverem nulos, significa que o malloc falhou
	{
		if (phFrase != NULL && phCtrlDisp != NULL)
		{
			/* Caso os placeholders tenham algum valor, eles s�o usados juntamente do backupTamanho para retornar as vari�veis globais para seus valores      */
			/* originais antes da �ltima chamada da fun��o como forma de backup (o n�mero de entradas n�o foi alterado e portanto n�o precisa ser recuperado) */

			tamanho = backupTamanho; // )
			frase = phFrase;		 // } Execu��o do backup
			contrlDisp = phCtrlDisp; // )
		}
		return; // Encerra a fun��o
	}

	free (phFrase);    /* Caso seja a primeira vez que a fun��o � executada, os ponteiros ser�o nulos e nada acontecer�. Caso */
	free (phCtrlDisp); /* contr�rio, liberar� o espa�o usado para a frase anterior, bem como o espa�o dos pinos de controle   */

	phFrase = NULL;    /* Limpando os ponteiros placeholders */
	phCtrlDisp = NULL; /* para evitar problemas              */

	phFrase = frase; 		 /* Atualizando os */
	phCtrlDisp = contrlDisp; /* placeholders   */

	// Adicionando (dEntra - 1) espa�os no in�cio da frase (padding inicial)
	for (uint8_t i = 0; i < (dEntra - 1); i++) // Cicla por 0 at� (dEntra - 2)
	{
		*frase = ' '; // Adiciona um padding � frase
		frase++; // Passa para o pr�ximo endere�o dessa
		tamanho++; // Computa a altera��o no tamanho da string
	}

	// Colocando o primeiro argumento da fun��o no ponteiro global frase
	while (*fEntra != '\0') // Enquanto n�o alcan�ar o final da string fEntra
	{
		*frase = *fEntra; // Copia o valor da entrada atual para o a posi��o atual da frase (ap�s o padding inicial)

		if ((int)*frase > 96) // Quando o caractere for maior que 96 (letras min�sculas)
		{
			*frase -= 32; // Subtrai-se 32 para tornar a letra em seu correspondente mai�sculo
		}

		frase++; // Avan�a para o pr�ximo espa�o da frase
		fEntra++; // Avan�a para o pr�ximo caractere da entrada
	}

	// Incorporando dEntra espa�os no final da frase (padding final)
	for (uint8_t i = 0; i < dEntra; i++) // Coloca  no ponteiro global contrlDisp
	{
		*frase = ' '; // Adiciona um padding � frase
		*contrlDisp = *dPin; // Aproveita para copiar o conte�do do terceiro argumento da fun��o (as sa�das dos pinos de controle) para o conte�do do ponteiro global respons�vel
		contrlDisp++; // Avan�a o endere�o do espa�o reservado para os pinos de controle
		dPin++; // Avan�a o endere�o do espa�o reservado para os pinos de controle (vari�vel global)
		frase++; // Avan�a para o pr�ximo espa�o da frase
		tamanho++; // Computa a altera��o no tamanho da string
	}

	*frase = '\0'; // Adicionando um caractere de finaliza��o � string a ser mostrada

	frase = phFrase; 	     /* Retornando os ponteiros da frase */
	contrlDisp = phCtrlDisp; /* e de controle � posi��o inicial  */

	tamanho *= -1; // Negativando o valor do tamanho para indicar uma modifica��o nele

	TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrup��es atrav�s do update do TIM10
}

/* Programa Principal */
int main (void)
{
	/* Configura��o dos Pinos e Perif�ricos */
	RCC -> AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN); // Ativando apenas o clock das GPIOA e GPIOC
	RCC -> APB2ENR |= RCC_APB2ENR_TIM10EN; // Habilitando o Timer 10

	GPIOA -> MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1); // Configurando PA13 e PA14 como fun��o alternativa (para debug)

	GPIOC -> MODER |= 0x555555; // Configurando PC0 at� PC11 como sa�das digitais

	uint8_t pin [4] = {8, 9, 10, 11}; // Criando um vetor com os pinos de controle da GPIOC

	displayConf ("Hello world!", 4, pin, 300, 'u'); // Chamando a fun��o displayConf para apresentar a frase "Hello world!" em 4 displays, 300 s por display, por uma �nica vez

	while (*frase != '\0'); // Esperando a frase anterior terminar

	displayConf ("Ola mundo", 4, pin, 700, 'c'); // Chamando a fun��o displayConf para apresentar a frase "Ola mundo" em 4 displays, 700 ms por display, por uma �nica vez

	/* La�o de Repeti��o */
	while (1); // N�o faz nada no loop
}
