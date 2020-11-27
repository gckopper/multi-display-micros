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

				   	PC8  -> Base Transistor 1;
				   	PC9  -> Base Transistor 2;
				   	PC10 -> Base Transistor 3;
				   	PC11 -> Base Transistor 4;

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
#include <stdlib.h>

/* Variáveis Globais */
uint8_t tascii [] = {0x00, 0x86, 0x22, 0xff, 0xff, 0xff, 0xff, 0x20, 0x39, 0x0f, // Tabela de conversão de char para saída da GPIO
					 0xff, 0xff, 0x04, 0x40, 0x80, 0x52, 0x3f, 0x06, 0x5b, 0x4f, // baseada no valor numérico dos caracterees na
					 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0xc2, 0x82, 0x61, 0x48, // tabela ASCII com um offset de 32 para excluir
					 0x43, 0xd3, 0xff, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, // caracteres sem representação gráfica e economizar
					 0x74, 0x30, 0x1e, 0x75, 0x38, 0x15, 0x37, 0x5c, 0x73, 0x67, // memória
					 0x33, 0x69, 0x78, 0x3e, 0x2e, 0x2a, 0x76, 0x6e, 0x4b, 0xff,
					 0x64, 0xff, 0xff, 0x08};

uint8_t* contrlDisp; // Ponteiro usado para manipular globalmente o ponteiro dPin

char* frase; // Ponteiro usado para percorrer o espaço de memória com a frase que será mostrada no display

uint8_t nDisplays = 0; // Variável que armazena o numero de displays

int tamanho = 0; // Variável representando o tamanho do espaço (em bytes) que a frase que será mostrada no display ocupa

unsigned int lTempo; // Variável usada para tornar global a variável lTime da função displayConf

char selModo; // Variável usada para tornar global a variável selectMode da função displayConf

/* Corpo de Funções de Interrupção */
void TIM1_UP_TIM10_IRQHandler (void) // Quando o bit UIF de TIM10 virar 1
{
	if (frase != NULL) { // Verifica se o vetor frase é não nulo, pois caso ele seja nulo, não haverá mensagem para ser mostrada

		// Variáveis Locais
		static unsigned int count = 0; // Variável local, que preserva o valor na próxima chamada da função, responsável por contar quantas vezes passou 1 ms

		if (tamanho < 0) // Caso tamanho seja negativo, significa que seu valor foi multiplicado por '-1', assim:
		{
			count = 0; // O contador deve ser resetado
			tamanho *= -1; // E o tamanho multiplicado por '-1' novamente
		}

		if (frase[nDisplays - 1] == '\0') // Caso o seja o último caractere do espaço reservado para a frase
		{
			frase -= (tamanho - nDisplays); // Retorna para o primeiro endereço da frase usando o tamanho dela;
			count = 0; // Reseta o contador de interrupções

			if (selModo == 'u') // Caso o modo selecionado como parâmetro da função displayConf seja igual a 'u'
			{
				TIM10 -> DIER &= ~TIM_DIER_UIE; // Desabilita interrupções através do update do TIM10
			}

			return; // Finaliza a execução da interrupção
		}

		if ((count % nDisplays == 0) && (count != 0)) // Quando o contador for um multiplo do número de displays (excluindo o valor nulo)
		{

			if (count == lTempo) // Entra na condicional quando passaram lTempo vezes 1 ms
			{
				frase++; // Passa para a próxima letra da frase
				count = 0; // Zera o contador
			}
		}

		GPIOC -> ODR &= 0xfffff000; // Desligando todos os segmentos dos displays (PC0 a PC7)

		/* Ligando um display usando deslocamento de bits para a posição indicada pelo ponteiro que contém os pinos indicados pelo usuário */
		/* O endereço usado é o modulo entre o contador de ciclos e o número de displays, ciclando entre 0 e (nDisplays - 1)               */
		GPIOC -> ODR |= 1 << contrlDisp [count % nDisplays];

		/* É inserido na ODR um valor determinado pelo vetor tascii no endereço determinado pelo valor numérico do caractere no vetor (frase - 32) (offset da tabela) */
		GPIOC -> ODR |= tascii [(int)(frase[count % nDisplays]) - 32];

		count++; // Adiciona um ao contador de interrupções

	}
	TIM10 -> SR &= ~TIM_SR_UIF; // Zerando o bit UIF quando a contagem for concluída
}

/* Corpo de Funções Customizadas */
void displayConf (const char* fEntra, uint8_t dEntra, uint8_t* dPin, unsigned int lTime, const char selectMode)
{
/*
   Parâmetros da função:

   fEntra guarda uma string para ser mostrada nos displays;

   dEntrada guarda a quantidade de displays em uso;

   dPin é um vetor com os valores dos pinos no GPIOC;

   lTime serve para definir o tempo de cada caractere no display em milissegundos (precisa ser um múltiplo de dEntra);

   selectMode serve para selecionar o modo de operação do painel:

   	   Se for igual à 'u' -> Mostrará o texto apenas uma vez

   	   Se for igual à 'c' -> Mostrará o texto infinitas vezes
*/
	/* Variáveis Locais */
	int backupTamanho = tamanho; // Salvando uma copia do tamanho

	if (*fEntra == '\0' || dEntra == 0 || *dPin == '\0' || lTime == 0 || (selectMode != 'u' && selectMode != 'c')) // Caso não esteja bem configurada a função
	{
		return; // Encerra a função
	}

	TIM10 -> DIER &= ~TIM_DIER_UIE; // Desabilitando interrupções através do update do TIM10

	selModo = selectMode; // Tornando o parâmetro selectMode global em selModo

	lTempo = lTime - (lTime % dEntra); // Passando o tempo configurado para a variável global (arredondado para o menor mais próximo múltiplo de dEntra)

	static char* phFrase = NULL; // Definindo um placeholder para o ponteiro de forma estática para usar o free caso a função seja executada novamente
	static uint8_t* phCtrlDisp = NULL; // Definindo um placeholder para o ponteiros de forma estática para usar o free caso a função seja executada novamente

	if (frase == NULL) // Caso o ponteiro apontado para uma parte da frase tenha endereço nulo, significa que é a primeira execução desta função
	{
		TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrupções através do update do TIM10
		TIM10 -> PSC = 159; // Colocando o Pre-scaller de TIM10 para dividir CK_INT (16 MHz) por 160
		TIM10 -> ARR = 99; // Auto-reload reiniciando o contador após contar até 99
		TIM10 -> CR1 |= TIM_CR1_CEN;
		/* Tem-se, assim, uma contagem para TIM10 que leva 1 ms para ser concluída */

		NVIC_SetPriority (TIM1_UP_TIM10_IRQn, 0); // Colocando a prioridade da interrupção de TIM10 como prioridade máxima
		NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); // Habilitando a interrupção por hardware através do TIM10
	}

	tamanho = 0; // Zerando o tamanho da frase para trocar seu valor

	while (*fEntra != '\0') // Executa até o fim da frase
	{
		fEntra++; // Passa para o próximo endereço da string parâmetro
		tamanho++; // Contabiliza a letra no tamanho da frase
	}

	fEntra -= tamanho; // Retornando pro inicio da string

	frase = NULL;      // Deixando os ponteiros
	contrlDisp = NULL; // globais em endereço nulo

	frase = malloc (tamanho + (dEntra * 2)); // Alocando memória para a frase com espaços extras para o padding
	contrlDisp = malloc (sizeof (uint8_t) * dEntra); // Alocando memória para armazenar os pinos de controle

	if (frase == NULL || contrlDisp == NULL) // Se os ponteiros estiverem nulos, significa que o malloc falhou
	{
		if (phFrase != NULL && phCtrlDisp != NULL)
		{
			/* Caso os placeholders tenham algum valor, eles são usados juntamente do backupTamanho para retornar as variáveis globais para seus valores      */
			/* originais antes da última chamada da função como forma de backup (o número de entradas não foi alterado e portanto não precisa ser recuperado) */

			tamanho = backupTamanho; // )
			frase = phFrase;		 // } Execução do backup
			contrlDisp = phCtrlDisp; // )
		}
		return; // Encerra a função
	}

	nDisplays = dEntra; // Definindo o valor da variável global que armazena o número de displays

	free (phFrase);    /* Caso seja a primeira vez que a função é executada, os ponteiros serão nulos e nada acontecerá. Caso */
	free (phCtrlDisp); /* contrário, liberará o espaço usado para a frase anterior, bem como o espaço dos pinos de controle   */

	phFrase = NULL;    /* Limpando os ponteiros placeholders */
	phCtrlDisp = NULL; /* para evitar problemas              */

	phFrase = frase; 		 /* Atualizando os */
	phCtrlDisp = contrlDisp; /* placeholders   */

	// Adicionando (dEntra - 1) espaços no início da frase (padding inicial)
	for (uint8_t i = 0; i < (dEntra - 1); i++) // Cicla por 0 até (dEntra - 2)
	{
		*frase = ' '; // Adiciona um padding à frase
		frase++; // Passa para o próximo endereço dessa
		tamanho++; // Computa a alteração no tamanho da string
	}

	// Colocando o primeiro argumento da função no ponteiro global frase
	while (*fEntra != '\0') // Enquanto não alcançar o final da string fEntra
	{
		*frase = *fEntra; // Copia o valor da entrada atual para o a posição atual da frase (após o padding inicial)

		if ((int)*frase > 96) // Quando o caractere for maior que 96 (letras minúsculas)
		{
			*frase -= 32; // Subtrai-se 32 para tornar a letra em seu correspondente maiúsculo
		}

		frase++; // Avança para o próximo espaço da frase
		fEntra++; // Avança para o próximo caractere da entrada
	}

	// Incorporando dEntra espaços no final da frase (padding final)
	for (uint8_t i = 0; i < dEntra; i++) // Coloca  no ponteiro global contrlDisp
	{
		*frase = ' '; // Adiciona um padding à frase
		*contrlDisp = *dPin; // Aproveita para copiar o conteúdo do terceiro argumento da função (as saídas dos pinos de controle) para o conteúdo do ponteiro global responsável
		contrlDisp++; // Avança o endereço do espaço reservado para os pinos de controle
		dPin++; // Avança o endereço do espaço reservado para os pinos de controle (variável global)
		frase++; // Avança para o próximo espaço da frase
		tamanho++; // Computa a alteração no tamanho da string
	}

	*frase = '\0'; // Adicionando um caractere de finalização à string a ser mostrada

	tamanho++; // Contabilizando o caractere de fechamento da string

	frase = phFrase; 	     /* Retornando os ponteiros da frase */
	contrlDisp = phCtrlDisp; /* e de controle à posição inicial  */

	tamanho *= -1; // Negativando o valor do tamanho para indicar uma modificação nele

	TIM10 -> DIER |= TIM_DIER_UIE; // Habilitando interrupções através do update do TIM10
}

void esperaDisplay(void)
{
	/* Função que espera o texto terminar de passar
	 * Se a interrupção estiver ligada significa que ainda tem texto passando.
	 * Caso a interrupção esteja desligada significa que não existe texto nos displays e portando nada é feito*/
	if (TIM10 -> DIER & TIM_DIER_UIE)
	{
		while (!(frase[nDisplays + 1] == '\0')); // Espera o display terminar a última frase
	}
}

void updateDisplay(const char* fEntra, unsigned int lTime, uint8_t interUnicaVez) {
	/* Um 'wrapper' para facilitar a entrada do usuário ao alterar o texto, pois mantem os pinos e displays previamente definidos */
	if (nDisplays != 0 && contrlDisp != NULL) // Confirma que já houve uma configuração do display
	{
		displayConf(fEntra, nDisplays, contrlDisp, lTime, interUnicaVez);
	}
}

/* Programa Principal */
int main (void)
{
	/* Configuração dos Pinos e Periféricos */
	RCC -> AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN); // Ativando apenas o clock das GPIOA e GPIOC
	RCC -> APB2ENR |= RCC_APB2ENR_TIM10EN; // Habilitando o Timer 10

	GPIOA -> MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER14_1); // Configurando PA13 e PA14 como função alternativa (para debug)

	GPIOC -> MODER |= 0x555555; // Configurando PC0 até PC11 como saídas digitais

	uint8_t pin [4] = {8, 9, 10, 11}; // Criando um vetor com os pinos de controle da GPIOC

	displayConf ("Hello world!", 4, pin, 300, 'u'); // Chamando a função displayConf para apresentar a frase "Hello world!" em 4 displays, 300 s por display, por uma única vez

	esperaDisplay(); // Esperando a frase anterior terminar

	updateDisplay ("Ola mundo", 700, 'c'); // Chamando a função updateDisplay para apresentar a frase "Ola mundo" nos mesmos displays, 700 ms por display, por uma única vez

	/* Laço de Repetição */
	while (1); // Não faz nada no loop
}
