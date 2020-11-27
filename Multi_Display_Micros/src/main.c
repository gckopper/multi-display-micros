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

// Tabela de convers�o de char para sa�da do GPIO baseado no valor num�rico dos caracteres na tabela ascii com um offset de 32 para excluir caracteres sem representa��o gr�fica e economizar mem�ria
uint8_t tascii[] = {               0x00, 0x86, 0x22, 0xff, 0xff, 0xff, 0xff, 0x20,
					   0x39, 0x0f, 0xff, 0xff, 0x04, 0x40, 0x80, 0x52, 0x3f, 0x06,
					   0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0xc2, 0x82,
					   0x61, 0x48, 0x43, 0xd3, 0xff, 0x77, 0x7c, 0x39, 0x5e, 0x79,
					   0x71, 0x3d, 0x74, 0x30, 0x1e, 0x75, 0x38, 0x15, 0x37, 0x5c,
					   0x73, 0x67, 0x33, 0x69, 0x78, 0x3e, 0x2e, 0x2a, 0x76, 0x6e,
					   0x4b, 0xff, 0x64, 0xff, 0xff, 0x08};

uint8_t* contrlDisp; //

char* frase; // Vetor que armazena a frase que ser� mostrada no display

uint8_t nDisplays = 0; // Variavel que armazena o numero de displays

int tamanho = 0; // Variavel do tamanho do vetor frase

unsigned int lTempo; // Variavel usada para definir o tempo de cada letra por display

uint8_t unicaVez;

void TIM1_UP_TIM10_IRQHandler (void) // Quando o bit UIF de TIM10 virar 1
{
	if (frase != NULL) { // Verifica se o vetor frase � n�o nulo, pois caso ele seja nulo n�o haver� mensagem para ser mostrada
		// Vari�veis Locais
		static unsigned int count = 0; // Vari�vel local, que preserva o valor na pr�xima chamada da fun��o, respons�vel por contar quantas vezes se passaram 5 ms

		if (tamanho < 0){ // Caso ele seja inveritido significa que seu valor foi alterado e portanto o contador deve ser resetado
			count = 0;
			tamanho *= -1;
		}

		if (*frase == '\0') // Caso o seja o ultimo caracter no vetor
		{
			frase -= (tamanho - 1); // Retorna para antes do primeiro endere�o do vetor usando o tamanho dele;
			count = 0; // Reseta o contador da interrup��o
			if (unicaVez){
				TIM10 -> DIER &= ~TIM_DIER_UIE;// Desabilitando interrup��es atrav�s do update do TIM10
			}
			return; // Finaliza a exe��o da interrup��o
		}

		if ((count % nDisplays == 0 && count != 0)) // Ativa quando o contador for um multiplo do n�mero de displays
		{
			frase -= nDisplays; // Retorna nDisplays endere�os no vetor (para ir para o caracter do primeiro display)
			if (count == lTempo) // Entra na condicional quando se passaram 200 vezes os 5 ms ou 1s
			{
				frase++; // Passa para a pr�xima letra do vetor
				count = 0; // Zera o contador
			}
		}

		GPIOC -> ODR &= 0xfffff000; // Desliga os displays e os segmentos
		/* Liga o display usando um deslocamento de bit para posi��o indicada pelo vetor que contem os pinos indicados pelo usu�rio
		 * O endere�o usado � o modulo entre o contador de ciclos e o n�mero de displays */
		GPIOC -> ODR |= 1 << contrlDisp[count % nDisplays];
		GPIOC -> ODR |= tascii[(int)(*frase)-32]; // � inserido no ODR um valor determinado pelo vetor tascii no endere�o determinado pelo valor num�rico do caracter no vetor frase -32 (offset da tabela)
		frase++; // Passa para o pr�ximo caracter do vetor
		count++; // Adiciona um ao contador de interrup��es

	}
	TIM10 -> SR &= ~TIM_SR_UIF; // Zerando o UIF quando a contagem for conclu�da
}

void displayConf(const char* fEntra, uint8_t dEntra, uint8_t* dPin, unsigned int lTime, uint8_t interUnicaVez) // fEntra guarda uma sequencia de caracteres para ser mostrada nos displays, dEntrada guarda a quantidade de displays em uso, dPin � um vetor com os valores dos pinos no GPIOC e lTime serve para definir o tempo de cada caracter no display (em ms)
{

	unicaVez = interUnicaVez;

	if (*fEntra == '\0' || *dPin == '\0' || dEntra == 0) { // Caso n�o esteja bem configurado ele retorna
		return;
	}

	TIM10 -> DIER &= ~TIM_DIER_UIE;// Desabilitando interrup��es atrav�s do update do TIM10

	static char* phFrase = NULL; // Define place holders para os ponteiros de forma est�tica para usar o free caso a fun��o seja executada novamente
	static uint8_t* phCtrlDisp = NULL; // Define place holders para os ponteiros de forma est�tica para usar o free caso a fun��o seja executada novamente


	if (frase == NULL) // Caso o vetor frase esteja nulo significa que � a primeira execu��o dessa fun��o nem a interrup��o nem os timers ainda foram configurados
	{
		TIM10 -> DIER |= TIM_DIER_UIE; ; // Habilitando interrup��es atrav�s do update do TIM10
		TIM10 -> PSC = 159; // Colocando o Pre-scaller de TIM10 para dividir CK_INT (16 MHz) por 160
		TIM10 -> ARR = 99; // Auto-reload reiniciando o contador ap�s contar at� 99
		TIM10 -> CR1 |= TIM_CR1_CEN;
		/* Tem-se, assim, uma contagem para TIM10 que leva 1 ms para ser conclu�da */

		NVIC_SetPriority (TIM1_UP_TIM10_IRQn, 0); // Colocando a prioridade da interrup��o de TIM10 como segunda prioridade
		NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); // Habilitando a interrup��o por hardware atrav�s do TIM10
	}

	lTempo = lTime; // Passando o tempo configurado para a vari�vel global
	int backupTamanho = tamanho; // Salva uma copia do tamanho
	tamanho = 0; // Zera o tamanho do vetor frase para trocar seu valor
	while (*fEntra != '\0') // Executa at� o fim do vetor
	{
		fEntra++; // Passa para o pr�ximo valor do vetor
		tamanho++; // Contabiliza a letra no tamanho do vetor
	}
	fEntra -= tamanho; // Retorna pro inicio do vetor

	tamanho++; // Contabiliza o caracter de fechamento da string

	frase = NULL; // Deixa os vetors globais nulos
	contrlDisp = NULL;

	frase = malloc(tamanho + dEntra * 2); // A mem�ria � alocada para os ponteiros com espa�os extras para o padding
	contrlDisp = malloc(sizeof(uint8_t) * dEntra); // A mem�ria � alocada para os ponteiros

	if (frase == NULL || contrlDisp == NULL) // Se os ponteiros estiverem nulos significa que o malloc falhou e por isso ele retorna
	{
		if (phFrase != NULL && phCtrlDisp != NULL)
		{
			/* Caso os placeholders tenham algum valor eles s�o usados, juntamente do backupTamanho, para retornar as variaveis globais para seus valores
			 * antes da ultima chamada da fun��o como forma de backup (o numero de entradas n�o foi alterado e portanto n�o precisa ser recuperado)*/
			tamanho = backupTamanho;
			frase = phFrase;
			contrlDisp = phCtrlDisp;
		}
		return;
	}

	free(phFrase); // Caso seja a primeira vez que a fun��o � executada os ponteiros ser�o nulos e nada acontecer�.
	free(phCtrlDisp);

	phFrase = NULL; // Os ponteiros ent�o s�o limpos para evitar problemas
	phCtrlDisp = NULL;

	phFrase = frase; // Atualiza os placeholders
	phCtrlDisp = contrlDisp;

	nDisplays = dEntra; // Define o valor da variavel global

	for (uint8_t i = 0; i < (dEntra - 1); i++) // Cicla pro dEntra - 2
	{
		*frase = ' '; // Adiciona um espa�o ao vetor
		frase++; // Passa par o pr�ximo valor
		tamanho++; // Computa a altera��o no tamanho do vetor
	}

	while (*fEntra != '\0') // Coloca o primeiro argumento no ponteiro global frase
	{
		*frase = *fEntra; // Copia o valor da entrada para o vetor frase
		if ((int)*frase > 96) // Quando o caracter for maior que 96 (letras minusculas) ele subtrai 32 para tornar a letra em seu correspondente maiusculo
		{
			*frase -= 32;
		}
		frase++; // Avan�a os vetores
		fEntra++; // Avan�a os vetores
	}

	for (uint8_t i = 0; i < dEntra; i++) // Coloca o terceiro argumento no ponteiro global contrlDisp
	{
		*frase = ' '; // Adiciona mais 'paddings' para frase
		*contrlDisp = *dPin; // Aproveita para copia a entrada dos pinos pro vetor global respons�vel
		contrlDisp++; // Avan�a os vetores
		dPin++; // Avan�a os vetores
		frase++; // Avan�a os vetores
		tamanho++; // Computa a altera��o no tamanho do vetor
	}

	*frase = '\0'; // Adiciona um caracter de finaliza��o ao ponteiro

	frase = phFrase; // Faz os ponteiros voltarem a posi��o inicial
	contrlDisp = phCtrlDisp;

	tamanho *= -1; // Inverte o valor do tamanho para indicar uma modifica��o nele

	TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrup��es atrav�s do update do TIM10

}

/* Programa Principal */
int main (void)
{
	/* Configura��o dos pinos e perif�ricos */
	RCC -> AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN); // Ativando apenas o clock das GPIOA e GPIOC
	RCC -> APB2ENR |= (RCC_APB2ENR_TIM10EN); // Habilitando o Timer 10 e o Timer 11

	GPIOA -> MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1); // Configurando PA13 e PA14 como fun��o alternativa (para debug)

	GPIOC -> MODER |= 0x555555; // Configurando PC0 at� PC11 como sa�das digitais

	uint8_t pin[4] = {8, 9, 10, 11}; // Cria um vetor com os pinos

	displayConf("Hello world!", 4, pin, 1000, 1); // Chama a fun��o displayConf para apresentar a frase "Hello world!"

	while (*frase != '\0'); // Espera a frase anterior terminar

	displayConf("Ola mundo", 4, pin, 500, 1); // Chama a fun��o displayConf para apresentar a frase "Ola mundo"

	// N�o faz nada no loop
	/* La�o de repeti��o */
	while (1);
}
