#ifndef _SYSTEMLIB_H_
#define _SYSTEMLIB_H_

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
//#include <wiringPi.h>
#include "pseudoWiringPi.h"

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "fsm.h"
#include "tmr.h"

//#define __SIN_PSEUDOWIRINGPI__

#define CLK_MS 					1

// INTERVALO DE GUARDA ANTI-REBOTES
#define	DEBOUNCE_TIME			250
#define TIMEOUT_ACTUALIZA_JUEGO 2000

// A 'key' which we can lock and unlock - values are 0 through 3
//	This is interpreted internally as a pthread_mutex by wiringPi
//	which is hiding some of that to make life simple.

// CLAVES PARA MUTEX
#define	KEYBOARD_KEY		0
#define	SYSTEM_FLAGS_KEY	1
#define	MATRIX_KEY			2
#define	STD_IO_BUFFER_KEY	3

// Distribucion de pines GPIO empleada para el teclado y el display
#define GPIO_KEYBOARD_COL_1 	00
#define GPIO_KEYBOARD_COL_2 	01
#define GPIO_KEYBOARD_COL_3 	02
#define GPIO_KEYBOARD_COL_4 	03
#define GPIO_KEYBOARD_ROW_1 	05
#define GPIO_KEYBOARD_ROW_2 	06
#define GPIO_KEYBOARD_ROW_3 	14
#define GPIO_KEYBOARD_ROW_4 	15

#define GPIO_LED_DISPLAY_COL_1	13
#define GPIO_LED_DISPLAY_COL_2	16
#define GPIO_LED_DISPLAY_COL_3	21
#define GPIO_LED_DISPLAY_COL_4	22
#define GPIO_LED_DISPLAY_ROW_1	04
#define GPIO_LED_DISPLAY_ROW_2	07
#define GPIO_LED_DISPLAY_ROW_3	10
#define GPIO_LED_DISPLAY_ROW_4	12
#define GPIO_LED_DISPLAY_ROW_5	26
#define GPIO_LED_DISPLAY_ROW_6	27
#define GPIO_LED_DISPLAY_ROW_7	28

// FLAGS FSM CONTROL DE SERPIENTE Y GESTION JUEGO
#define FLAG_MOV_ARRIBA 	0x01
#define FLAG_MOV_ABAJO		0x02
#define FLAG_MOV_DERECHA 	0x04
#define FLAG_MOV_IZQUIERDA 	0x08
#define FLAG_TIMER_JUEGO	0x10
#define FLAG_BOTON 			0x20
#define FLAG_FIN_JUEGO		0x40
#define FLAG_PAUSA			0x80
#define FLAG_SCORE			0x100

enum fsm_state {
	WAIT_START,
	WAIT_PUSH,
	WAIT_END,
	WAIT_PAUSE,
	WAIT_SCORE,
	};

extern int flags;

#endif /* SYSTEMLIB_H_ */
