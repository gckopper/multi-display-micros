/**
**
**===========================================================================
**  @file    Interrupções (6) - Pedro L. Lima, Turma 4312.c
**  @author  Pedro L. Lima
**  @group   4312
**  @date    nov / 2020
**  @version 1.0
**  @brief   Exercício 6: Sinal monostável com delay, usando botão, LED e ISRs
**===========================================================================
**

Este programa transmite um sinal monostável (temporizado) que dura 0,5 s para um
LED (conectado à PC1) ao passar 1 s após o botão (conectado à PC0) ter sido
pressionado. Se o botão for pressionado durante o período em que o LED está ligado,
nada acontece, esse só liga o LED enquanto ele estiver desligado, não estendendo o
tempo de ativação do LED. Ao apertar-se o botão, independentemente do momento, um LED
verde (conectado à PC2) é ligado por 75 ms.

Pinagem:

Botão -> PC0
LED Azul -> PC1
LED Verde -> PC2

Dimensionamento dos componentes externos:

Resistor de 150 R ->   Como o LED azul drena 2,5 V (medido pelo voltímetro),
					   tem-se 3,3 V - 2,5 V no resistor (0,8 V). Estabeleceu-se
					   uma corrente próxima de 5 mA para o LED e, assim, 0,8 V
					   divididos por 5 mA resulta em 160 R, portanto, um resistor
					   de 150 R é suficiente.

Resistor de 270 R ->   Como o LED verde tem em torno de 1,8 V (medido pelo
				       voltímetro) sobr ele, tem-se 3,3 V - 1,8 V no
				       resistor (1,5 V). Estabeleceu-se uma corrente
				       próxima de 5 mA para o LED e, assim, 1,5 V
				       dividido por 5 mA resulta em 300 R, portanto, um
				       resistor de 270 R é próximo o suficiente.

Abaixo, o raciocínio para se configurar o TIM11 que é responsável pelo
debouncing do botão:

O debouncing, neste programa, funciona a cada passagem de tempo determinada, ou seja,
a cada contagem de um timer, o programa checa o estado do botão e compara com o estado
registrado no final da contagem anterior. Portanto, quanto menor for o tempo do timer,
mais rápido pode ser detectado o pressionamento do botão. Por isso, optou-se por um
período de 25 ms (até 40 pressionamentos por segundo) entre cada passagem de tempo. Com
isso, PSC foi escolhido como 3999 e ARR como 99.

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

	GPIOC -> MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0); // Configurando PC1 e PC2 como saídas digitais
	GPIOC -> PUPDR |= GPIO_PUPDR_PUPDR0_0; // Ativando resistor de pull-ip para PC0

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
