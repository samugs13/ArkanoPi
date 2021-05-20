
#include "ledDisplay.h"

tipo_pantalla pantalla_inicial = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,1,0},
	{0,0,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0},
	}
};

tipo_pantalla pantalla_final = {
	.matriz = {
	{0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0},
	{0,1,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0},
	}
};

// Maquina de estados: lista de transiciones
// {EstadoOrigen, CondicionDeDisparo, EstadoFinal, AccionesSiTransicion }
fsm_trans_t fsm_trans_excitacion_display[] = {
	{ DISPLAY_ESPERA_COLUMNA, CompruebaTimeoutColumnaDisplay, DISPLAY_ESPERA_COLUMNA, ActualizaExcitacionDisplay },
	{-1, NULL, -1, NULL },
};

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaLedDisplay (TipoLedDisplay *led_display) {

		pinMode (GPIO_LED_DISPLAY_COL_1, OUTPUT); //Se declara puerto de salida
		digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

		pinMode (GPIO_LED_DISPLAY_COL_2, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);

		pinMode (GPIO_LED_DISPLAY_COL_3, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);

		pinMode (GPIO_LED_DISPLAY_ROW_1, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_1, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_2, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_2, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_3, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_3, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_4, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_4, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_5, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_5, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_6, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_6, HIGH);

		pinMode (GPIO_LED_DISPLAY_ROW_7, OUTPUT);
		digitalWrite (GPIO_LED_DISPLAY_ROW_7, HIGH);

		tmr_startms((tmr_t*)(led_display->tmr_refresco_display),TIMEOUT_COLUMNA_DISPLAY);

		printf("\nLa pantalla se ha inicializado correctamente. Pulsa 2 para empezar una partida.\n");
		fflush(stdout);

		printf("\n\033[7;35mCONTROLES:\n");
		fflush(stdout);

		printf("\033[0;36mA - MOVER PALA HACIA LA IZQUIERDA\n");
		fflush(stdout);

		printf("\033[0;36mD - MOVER PALA HACIA LA DERECHA\n");
		fflush(stdout);

		printf("\033[0;36m3 - PAUSA-PLAY\n");
		fflush(stdout);

		printf("\033[0;36m1 - GUARDAR PUNTOS\n");
		fflush(stdout);
}

//------------------------------------------------------
// OTROS PROCEDIMIENTOS PROPIOS DE LA LIBRERIA
//------------------------------------------------------

void ApagaFilas (TipoLedDisplay *led_display){

	digitalWrite(GPIO_LED_DISPLAY_ROW_1, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_2, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_3, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_4, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_5, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_6, HIGH);
	digitalWrite(GPIO_LED_DISPLAY_ROW_7, HIGH);

}

void ExcitaColumnas(int columna) {

	switch(columna) {

		case 0:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);

		break;

		case 1:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);
		break;

		case 2:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);
		break;

		case 3:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);
		break;

		case 4:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);
		break;

		case 5:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, LOW);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);
		break;

		case 6:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, LOW);
		break;

		case 7:
			digitalWrite (GPIO_LED_DISPLAY_COL_3, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_2, HIGH);
			digitalWrite (GPIO_LED_DISPLAY_COL_1, HIGH);
		break;

		default:
		break;
	}
}

void ActualizaLedDisplay (TipoLedDisplay *led_display) {

	piLock(MATRIX_KEY);
	ApagaFilas(led_display);

	led_display->p_columna = led_display->p_columna + 1;

		if(led_display->p_columna > 7){
			led_display->p_columna = 0;
		}

	//Llamada a ExcitacionColumnas con columna a activar como argumento
	ExcitaColumnas(led_display->p_columna);

	for(int i = 0; i< NUM_FILAS_DISPLAY; i++){
		if(led_display->pantalla.matriz[i][led_display->p_columna]){

							digitalWrite(led_display->filas[i], LOW);
					}else{
							digitalWrite(led_display->filas[i], HIGH);

		}
	}

	piUnlock(MATRIX_KEY);

	/*for(int i = 0; i< NUM_FILAS_DISPLAY; i++){
		if(led_display->pantalla.matriz[i][led_display->p_columna]){
			digitalWrite(led_display->filas[i], LOW);
		}
	*/

}

/*void PintaPantallaPorTerminal (tipo_pantalla *p_pantalla) {
	int i=0, j=0;

	printf("\n[PANTALLA]\n");
	fflush(stdout);
	for(i=0;i<NUM_FILAS_DISPLAY;i++) {
		for(j=0;j<NUM_COLUMNAS_DISPLAY;j++) {
			printf("%d", p_pantalla->matriz[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}
	fflush(stdout);
}*/

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaTimeoutColumnaDisplay (fsm_t* this) {
	int result = 0;
	TipoLedDisplay *p_ledDisplay;
	p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	piLock(MATRIX_KEY);
	result = (p_ledDisplay->flags & FLAG_TIMEOUT_COLUMNA_DISPLAY);
	piUnlock(MATRIX_KEY);

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

void ActualizaExcitacionDisplay (fsm_t* this) {
	TipoLedDisplay *p_ledDisplay;
	p_ledDisplay = (TipoLedDisplay*)(this->user_data);

	piLock(MATRIX_KEY);
	led_display.flags &= (~FLAG_TIMEOUT_COLUMNA_DISPLAY);
	piUnlock(MATRIX_KEY);

	ActualizaLedDisplay(p_ledDisplay);

	tmr_startms((tmr_t*)(led_display.tmr_refresco_display),TIMEOUT_COLUMNA_DISPLAY);

}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_refresco_display_isr (union sigval value) {
	piLock(MATRIX_KEY);
	led_display.flags |= FLAG_TIMEOUT_COLUMNA_DISPLAY;
	piUnlock(MATRIX_KEY);

}
