/**
**
**===========================================================================
**  @file    TP01_-_Multi_Display_-_Gabriel_K._e_Pedro_L.,_Turma_4312.c
**  @author  Pedro L. Lima
**  @author  Gabriel C. Kopper
**  @group   4312
**  @date    nov / 2020
**  @version 1.0
**  @brief   Trabalho 1: Painel de displays que exibem mensagens de texto
**===========================================================================
**

Este programa realiza a exibição de uma mensagem, configurável por funções e por
macros, através de um número pré-definido de displays de 7 segmentos. O programa
realiza isso através da multiplexação dos catodos de cada display. A frequência
de multiplexação utilizada neste programa é de 1 kHz, podendo-se utilizar, assim
até 40 displays para exibir mensagens. As mensagens são exibidas com os caracteres
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

				   	PC8  -> Catodo Comum 1;
				   	PC9  -> Catodo Comum 2;
				   	PC10 -> Catodo Comum 3;
				   	PC11 -> Catodo Comum 4;

Tabela de caracteres para o display de 7 segmentos:

CARACTERE			BINÁRIO (Pinos de P a A do display)				HEXADECIMAL
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
(espaço)			0 0 0 0 0 0 0 0									0x00
.					1 0 0 0 0 0 0 0									0x80
;					1 0 0 0 0 0 1 0									0x82
!					1 0 0 0 0 1 1 0									0x83
-					0 1 0 0 0 0 0 0									0x40
_					0 0 0 0 1 0 0 0									0x04
‘					0 0 1 0 0 0 0 0									0x20
“					0 0 1 0 0 0 1 0									0x22


Dimensionamento dos componentes externos:

Transistores BC547	 -> Com Vcemáx de 45 V, Pcmáx de 500 mW, Icmáx de 100 mA,
						hfemin de 110 e ainda fmáx de 300 MHz, é o transistor
						ideal em termos de preço e funcionalidade para amplificar
						a corrente no catodo dos displays, bem como inverter o
						sinal de controle para conseguir fazer o respectivo display
						funcionar com sinal alto.

Resistores de 4700 R -> A corrente nos coletores dos transistors, considerando que,
						em cada segmento pode ter 5,56 mA (devido ao resistor de 270 R),
						é de no máximo 44,44 mA. Com isso, considerando o valor mínimo
						de hfe do transistor (110), tem-se, no máximo, 0,40404 mA assim,
						considerando Vbe como 0,7 V, o máximo valor de Rb é de
						(3,3 V - 0,7 V) / 0,40404 mA = 6435 R. Assim, resistores de 4k7
						são mais que suficientes.

Resistores de 270 R ->  Como os LEDs vermelhos drenam 1,8 V (por tabela online),
					    tem-se 3,3 V - 1,8 V nos resistores (1,5 V). Estabeleceu-se
					    uma corrente próxima de 5 mA para cada LED e, assim, 1,5 V
					    divididos por 5 mA resulta em 300 R, portanto, resistores
					    de 270 R são suficientes.

**/

/* Includes */
#include "stm32f4xx.h"

/* Variáveis Globais */
uint8_t bp = 0; // Variável que representa se o botão foi pressionado

/* Corpo das Funções de Interrupção */
void TIM1_TRG_COM_TIM11_IRQHandler (void) // Quando o bit UIF de TIM11 virar 1
{
	/* Variáveis Locais */
	static uint8_t bb; // Variável local, que preserva o valor na próxima chamada da função, responsável por guardar o estado do botão nos últimos 25 ms
	static uint8_t count = 0; // Variável local, que preserva o valor na próxima chamada da função, responsável por guardar o tempo passado
	static uint8_t lbp = 0; // Variável local, que preserva o valor na próxima chamada da função, responsável por iniciar a contagem de tempo ligado para o LED Verde

	TIM11 -> SR &= ~TIM_SR_UIF; // Zerando o UIF quando a contagem for concluída

	/* Debouncing */
	if (GPIOC -> IDR & GPIO_IDR_IDR_0) bb = 1; // Se o botão não for pressionado, armazena o estado do botão (0)
	else if (bb) // Caso contrário, o botão foi apertado e se o estado anterior era 1 (detector de subida de pulso)
	{
		bb = 0; // Agora o estado do botão é de pressionado

		if (!bp) // Se o ciclo do LED Azul anterior tiver sido finalizado
		{
			bp = 1; // Inicia um novo ciclo do LED Azul
			TIM10 -> CNT = 0; // Reinicia a contagem de 0,5 s
		}

		if (!lbp) // Se não foi iniciado um ciclo para o LED Verde
		{
			GPIOC -> ODR |= GPIO_ODR_ODR_2; // Liga o LED Verde
			lbp = 1; // Inicia um novo ciclo do LED Verde
			TIM11 -> CNT = 0; // Reinicia a contagem de 25 ms
		}
	}

	if (lbp) // Ciclo de tempo para desligar o LED Verde
	{
		count++; // Conta 25 ms (exceto na primeira vez)
		if (count == 4) // Se passaram 75 ms
		{
			GPIOC -> ODR &= ~GPIO_ODR_ODR_2; // Desliga o LED Verde
			count = 0; // Zera o contador
			lbp = 0; // Termina o ciclo do LED Verde
		}
	}
}

void TIM1_UP_TIM10_IRQHandler (void) // Quando o bit UIF de TIM10 virar 1
{
	/* Variáveis Locais */
	static uint8_t count = 0; // Variável local, que preserva o valor na próxima chamada da função, responsável por contar quantas vezes se passaram 500 ms

	TIM10 -> SR &= ~TIM_SR_UIF; // Zerando o UIF quando a contagem for concluída

	if (bp) // Se o botão for pressionado, inicia-se um novo ciclo para o LED Azul
	{
		count++; // Incrementa a variável count

		switch (count) // Tomada de ações a cada múltiplo de 0,5 s
		{
			case 2: // Caso passar 1 s
				GPIOC -> ODR |= GPIO_ODR_ODR_1; // Liga o LED Azul
				break;

			case 3: // Caso passar 1,5 s
				GPIOC -> ODR &= ~GPIO_ODR_ODR_1; // Desliga o LED Azul
				bp = 0; // Indica que acabou o ciclo do LED Azul
				count = 0; // Volta count para o início do ciclo
				break;

			default: // Outro caso
				GPIOC -> ODR &= ~GPIO_ODR_ODR_1; // Desliga o LED Azul
				break;
		}
	}
}

/* Programa Principal */
int main (void)
{
	/* Configuração dos pinos e periféricos */
	RCC -> AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN); // Ativando apenas o clock das GPIOA e GPIOC
	RCC -> APB2ENR |= (RCC_APB2ENR_TIM10EN | RCC_APB2ENR_TIM11EN); // Habilitando o Timer 10 e o Timer 11

	GPIOA -> MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1); // Configurando PA13 e PA14 como função alternativa (para debug)

	GPIOC -> MODER |= 0x555555; // Configurando PC0 até PC11 como saídas digitais

	TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrupções através do update do TIM10
	TIM10 -> PSC = 1999; // Colocando o Pre-scaller de TIM10 para dividir CK_INT (16 MHz) por 2000 (como delay inicialmente)
	TIM10 -> ARR = 3999; // Auto-reload reiniciando o contador após contar até 3999
	TIM10 -> CR1 |= TIM_CR1_CEN; // Habilitando contagem de TIM10
	/* Tem-se, assim, uma contagem para TIM10 que leva 500 ms para ser concluída */

	TIM11 -> DIER |= TIM_DIER_UIE; // Habilitando interrupções através do update do TIM11
	TIM11 -> PSC = 3999; // Colocando o Pre-scaller de TIM11 para dividir CK_INT (16 MHz) por 4000
	TIM11 -> ARR = 249; // Auto-reload reiniciando o contador após contar até 250
	TIM11 -> CR1 |= TIM_CR1_CEN; // Habilita contagem de TIM11
	/* Tem-se, assim, uma contagem para TIM11 que leva 25 ms para ser concluída */

	NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); // Habilitando a interrupção por hardware através do TIM10
	NVIC_EnableIRQ (TIM1_TRG_COM_TIM11_IRQn); // Habilitando a interrupção por hardware através do TIM11
	NVIC_SetPriority (TIM1_UP_TIM10_IRQn, 1); // Colocando a prioridade da interrupção de TIM10 como segunda prioridade
	NVIC_SetPriority (TIM1_TRG_COM_TIM11_IRQn, 0); // Colocando a prioridade da interrupção de TIM11 como máxima

	/* Laço de repetição */
	while (1); // Não faz nada no loop
}
