/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */



/** 
 ** Entrega realizada por:
 **  - Samuel Granato
 **  
 **	 - Link do vídeo
 **  - https://youtu.be/mprX58I_akY
 **/

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"




/************************************************************************/
/* defines                                                              */
/************************************************************************/

const int songspeed = 1; //Change to 2 for a slower version of the song, the bigger the number the slower the song
//*****************************************
#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5 988
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//led
#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        12                    // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

//botao
#define BUT_PIO           PIOA                  // periferico que controla o botao
#define BUT_PIO_ID        10                    // ID do periférico PIOA (controla botao)
#define BUT_PIO_IDX       11u                   // ID do botao no PIO
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)   // Mascara para CONTROLARMOS o botao

//buzzer
#define BUZ_PIO           PIOD                  // periferico que controla o botao
#define BUZ_PIO_ID        ID_PIOD                    // ID do periférico PIOA (controla botao)
#define BUZ_PIO_IDX       20u                   // ID do botao no PIO
#define BUZ_PIO_IDX_MASK (1u << BUZ_PIO_IDX)   // Mascara para CONTROLARMOS o botao


//botao vermelho
#define RED_BUT_PIO           PIOD                
#define RED_BUT_PIO_ID        ID_PIOD                  
#define RED_BUT_PIO_IDX       25u                 
#define RED_BUT_PIO_IDX_MASK (1u << RED_BUT_PIO_IDX)  

//botao verde

#define GREEN_BUT_PIO           PIOB
#define GREEN_BUT_PIO_ID        ID_PIOB
#define GREEN_BUT_PIO_IDX       0u
#define GREEN_BUT_PIO_IDX_MASK (1u << GREEN_BUT_PIO_IDX)
/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

int notes2[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int duration2[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

int notes[] = {       //Note of the song, 0 is a rest/pulse
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,

	NOTE_A4, NOTE_A4,
	//Repeat of first part
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,
	//End of Repeat

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,

	250, 125,
	//Rpeat of First Part
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,
	//End of Repeat
	
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 500,

	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 500
};

// Função de inicialização do uC
void init(void){
	// Initialize the board clock
	sysclk_init();
	
	
	// Disativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	
	//clock do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	//botão vermelho
	pmc_enable_periph_clk(RED_BUT_PIO_ID);
	pio_set_input(RED_BUT_PIO,RED_BUT_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(RED_BUT_PIO,RED_BUT_PIO_IDX_MASK,1);
	
	//botão verde
	pmc_enable_periph_clk(GREEN_BUT_PIO_ID);
	pio_set_input(GREEN_BUT_PIO,GREEN_BUT_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(GREEN_BUT_PIO,GREEN_BUT_PIO_IDX_MASK,1);
	
	
	//clock buzzer
	pmc_enable_periph_clk(BUZ_PIO_ID);

	//Inicializa PC8 como saída
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	pio_set_input(BUT_PIO,BUT_PIO_IDX_MASK,PIO_DEFAULT);
	
	//buzzer
	pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);
	
	
	pio_pull_up(BUT_PIO,BUT_PIO_IDX_MASK,1);
}


void pause(){
	while(1){
		if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
			return;
		}
		
		if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
			pause();
		}
		
	}
}

int play_music(int music, int k){
	while(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
		delay_ms(10);
	}
	
	if(!music){
		//PIRATAS DO CARIBE
		int cnt = sizeof(notes)/sizeof(notes[0]);
		
		int j = 0;
		for (int i=k;i<cnt;i++){              //203 is the total number of music notes in the song
			int wait = duration[i] * songspeed  ;
			//tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
			
			
			pio_clear(LED_PIO,LED_PIO_IDX_MASK);
			
			
			while(j < duration[i] * 2){
				if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
					return i;
				}
				pio_set(BUZ_PIO,BUZ_PIO_IDX_MASK);
				delay_us(70000/notes[i]);
				pio_clear(BUZ_PIO,BUZ_PIO_IDX_MASK);
				delay_us(70000/notes[i]);
				j++;
			}
			j = 0;
			if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
				return i;
			}
			pio_set(LED_PIO,LED_PIO_IDX_MASK);
			delay_ms(wait);
			
			// f = 1 / t
			// t = 1 / f
			
			
		}                        //delay is used so it doesn't go to the next loop before tone is finished playing
		pio_clear(LED_PIO,LED_PIO_IDX_MASK);
		delay_ms(50);
		return -1;
		
	}else{
		//MARIO
		
		int cnt2 = sizeof(notes2)/sizeof(notes2[0]);
		int j = 0;
		for (int i=k;i<cnt2;i++){              //203 is the total number of music notes in the song
			int wait = duration2[i] * songspeed * 10;
			//tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
			
			
			pio_clear(LED_PIO,LED_PIO_IDX_MASK);
			
			
			while(j < duration2[i] * 20){
				if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
					return i;
				}
				pio_set(BUZ_PIO,BUZ_PIO_IDX_MASK);
				
				delay_us(300000/notes2[i]);
				pio_clear(BUZ_PIO,BUZ_PIO_IDX_MASK);
				delay_us(300000/notes2[i]);
				j++;
			}
			
			j = 0;
			if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
				return i;
			}
			pio_set(LED_PIO,LED_PIO_IDX_MASK);
			delay_ms(wait);
			
			// f = 1 / t
			// t = 1 / f
			
			
		}                        //delay is used so it doesn't go to the next loop before tone is finished playing

		delay_ms(50);
		
		return -1;
	}
}



/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();
  
	
	int music = 0;
	int i = 0;
  
  

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	if(!pio_get(RED_BUT_PIO,PIO_INPUT,RED_BUT_PIO_IDX_MASK)){
		
		if(music == 1){
			music = 0;
		}else{
			i = 0;
			music++;
		}
		while(!pio_get(RED_BUT_PIO,PIO_INPUT,RED_BUT_PIO_IDX_MASK)){
			delay_ms(10);
		}
	}
	if(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
		
		i = play_music(music,i);
		if( i == -1){
			i = 0;
		}
		while(!pio_get(GREEN_BUT_PIO,PIO_INPUT,GREEN_BUT_PIO_IDX_MASK)){
			delay_ms(10);
		}
		
	}
  }
  return 0;
}
