#include <stdio.h>
#include <stdbool.h>
#include "dia_en_la_uni.h"

#define OLAF 'O'
#define STITCH 'S'
#define JASMIN 'J'
#define RAYO_MCQUEEN 'R'

const char TRINEO = 'T';
const char NAVE_ESPACIAL = 'N';
const char CAMION = 'C';
const char ALFOMBRA = 'A';
const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';
const int NOTA_MINIMA = 1;
const int NOTA_MAXIMA = 10;
const int PUNTOS_TRINEO_NAVE = 10;
const int PUNTOS_CAMION_ALFOMBRA = 20;
const int PUNTOS_BOLAS_DE_NIEVE = 3;
const int PUNTOS_PIUM_PIUM = 6;
const int PUNTOS_KUCHAU = 9;
const int PUNTOS_GENIO = 12;
const int LIMITE_HORAS = 24;
const float HORA_DE_PARCIAL = 15.30f;
const float LIMITE_MINUTOS = 0.60f;

// Funcion "es_transporte_valido"
// Pre condiciones: -
// Post condiciones: retorna un true/false segun la variable ingresada cumpla o no la condicion.

bool es_transporte_valido (char transporte) {

	return (transporte != TRINEO) && (transporte != NAVE_ESPACIAL) && (transporte != CAMION) && (transporte != ALFOMBRA);

}

// Funcion "es_medio_valido"
// Pre condiciones: -
// Post condiciones: retorna un true/false segun la variable ingresada cumpla o no la condicion.

bool es_medio_valido (char medio) { 

	return (medio != BOLAS_DE_NIEVE) && (medio != PIUM_PIUM) && (medio != KUCHAU) && (medio != GENIO);

}

// Funcion "es_hora_valido"
// Pre condiciones: -
// Post condiciones: retorna un true/false segun la variable ingresada cumpla o no la condicion.

bool es_hora_valida (int horas, float minutos) {  

	return ((horas < 0 || horas >= LIMITE_HORAS) || (minutos < 0 || minutos >= LIMITE_MINUTOS));

}

// Funcion "es_nota_valido"
// Pre condiciones: -
// Post condiciones: retorna un true/false segun la variable ingresada cumpla o no la condicion.

bool es_nota_valida (int nota) {

	return ((nota >= NOTA_MINIMA) && (nota <= NOTA_MAXIMA));

}	

// Procedimiento "elegir_transporte"
// Pre condiciones: -
// Post condiciones: el ingreso, guardado y verificacion del transporte elegido por el usuario.

void elegir_transporte (char* transporte) {

	printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes,\n"
	"¿Qué otro transporte elegís? (Podes elegir Trineo (T), Nave Espacial (N), Camión (C) o Alfombra (A)): ");
	scanf(" %c", transporte);

	while (es_transporte_valido(*transporte)) {

		printf("No! Elegi una de las opciones,\n"
		"¿Qué otro transporte elegís?(Podes elegir Trineo (T), Nave Espacial (N), Camión (C) o Alfombra (A)): ");
		scanf(" %c", transporte);

	}	
}

// Procedimiento "elegir_medio"
// Pre condiciones: -
// Post condiciones: el ingreso, guardado y verificacion del medio por el cual se deshacera de la manifestacion elegido por el usuario.

void elegir_medio (char* deshacer_manifestacion) {

	printf("En medio del camino te encontras con una manifestación,\n"
	"¿Que medio utilizas para deshacerte de ella? (Podes elegir Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G)): ");
	scanf(" %c", deshacer_manifestacion);

	while (es_medio_valido(*deshacer_manifestacion)) {

		printf("No! Elegi una de las opciones,\n¿Que medio utilizas para deshacerte de ella?"
		"(Podes elegir Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G)): ");
		scanf(" %c", deshacer_manifestacion);

	}
}

// Procedimiento "ingresar_hora"
// Pre condiciones: -
// Post condiciones: el ingreso, guardado y verificacion de la hora que el usuario llega a la facultad.

void ingresar_hora (float* hora_de_llegada) {

	printf("Lograste superar la manifestación,\n¿A qué hora conseguiste llegar a la universidad? (Ingresa hh:mm): ");
	scanf("%f", hora_de_llegada);

	int horas;
	float minutos;

	horas = (int)*hora_de_llegada;
	minutos = *hora_de_llegada - (float)horas;

	while (es_hora_valida(horas, minutos)) {

		printf("No! Ingresa una hora correcta: ");
		scanf("%f", hora_de_llegada);

		horas = (int)*hora_de_llegada;
		minutos = *hora_de_llegada - (float)horas;

	}
}

// Procedimiento "ingresar_nota"
// Pre condiciones: -
// Post condiciones: el ingreso, guardado y verificacion de la nota del parcial que obtuvo el usuario.

void ingresar_nota (int* nota_parcial) {

	printf("Por fin llegó la nota del parcial!\n¿Qué nota lograste sacarte? (Ingresa un numero del 1 al 10): ");
	scanf("%i", nota_parcial);

	while (!es_nota_valida(*nota_parcial)) {

		printf("No! Ingresa un numero del 1 al 10: ");
		scanf("%i", nota_parcial);

	}
}

// Funcion "puntos_transporte"
// Pre condiciones: haber elegido anteriormente el transporte dentro de las opciones.
// Post condiciones: retorna el puntaje segun el medio de transporte elegido.

int puntos_transporte (int eleccion_transporte) {

	int puntaje_transporte;

	if (eleccion_transporte == TRINEO || eleccion_transporte == NAVE_ESPACIAL) {

		puntaje_transporte = PUNTOS_TRINEO_NAVE;
		
	} else {

		puntaje_transporte = PUNTOS_CAMION_ALFOMBRA;
	
	}

	return puntaje_transporte;

	}

// Funcion "puntos_manifestacion"
// Pre condiciones: haber elegido anteriormente el medio para deshacerse de la manifestacion dentro de las opciones.
// Post condiciones: retorna el puntaje segun el medio elegido.		

int puntos_manifestacion (int eleccion_medio) {

	int puntaje_medios;

	if (eleccion_medio == BOLAS_DE_NIEVE) {

		puntaje_medios = PUNTOS_BOLAS_DE_NIEVE;
		
	} else if (eleccion_medio == PIUM_PIUM) {

		puntaje_medios = PUNTOS_PIUM_PIUM;

	} else if (eleccion_medio == KUCHAU) {

		puntaje_medios = PUNTOS_KUCHAU;

	} else {

		puntaje_medios = PUNTOS_GENIO;
	}

	return puntaje_medios;
}

// Funcion "multiplicador_segun_nota"
// Pre condiciones: haber ingresado anteriormente la nota de parcial obtenida dentro del intervalo correspondiente.
// Post condiciones: retorna el multiplicador segun la nota ingresada.

int multiplicador_segun_nota (int nota_de_parcial) {

	int multiplicador;

	if ((nota_de_parcial >= 1) && (nota_de_parcial <= 3)) {

		multiplicador = 1;
		
	} else if ((nota_de_parcial >= 4) && (nota_de_parcial <= 6)) {

		multiplicador = 2;

	} else if ((nota_de_parcial == 7) || (nota_de_parcial == 8)) {

		multiplicador = 3;

	} else {

		multiplicador = 4;
	}

	return multiplicador;
}

// Funcion "puntaje_final"
// Pre condiciones: 
// Post condiciones: define el personaje final, segun puntos totales y finalmente por hora de llegada a la facultad.

int puntaje_final (char transporte, char medio_manifestacion, int nota) {

	int ptos_transporte = puntos_transporte(transporte);
	int ptos_manifestacion = puntos_manifestacion(medio_manifestacion);
	int multiplicador_por_parcial = multiplicador_segun_nota(nota);

	int puntaje_final = ptos_transporte + (ptos_manifestacion * multiplicador_por_parcial);

	return puntaje_final;

}

// Procedimiento "calculo_de_personaje"
// Pre condiciones: -
// Post condiciones: define el personaje final, segun puntos totales y finalmente por hora de llegada a la facultad.

void calcular_personaje (int puntos_totales, float hora, char* ref_personaje) {

	if ((puntos_totales >= 13) && (puntos_totales <= 41)) {

		if (hora > HORA_DE_PARCIAL) {

			printf("Con un puntaje de %i puntos se definió el personaje -Olaf-.\n", puntos_totales);
			*ref_personaje = OLAF;

		} else {

			printf("Con un puntaje de %i puntos se definió el personaje -Stitch-.\n", puntos_totales);
			*ref_personaje = STITCH;
		}
		
	} else if ((puntos_totales >= 42) && (puntos_totales <= 68)) {

		if (hora <= HORA_DE_PARCIAL) {

			printf("Con un puntaje de %i puntos se definió el personaje -Jasmín-.\n", puntos_totales);
			*ref_personaje = JASMIN;

		} else {

			printf("Con un puntaje de %i puntos se definió el personaje -Rayo McQueen-.\n", puntos_totales);
			*ref_personaje = RAYO_MCQUEEN;
		}
	}

}

char ejec_cuestionario(char* ref_personaje){

	char transporte;
	char deshacer_manifestacion;
	int nota_parcial;
	int puntaje_total;
	float hora_de_llegada;

	elegir_transporte (&transporte);

	elegir_medio (&deshacer_manifestacion);

	ingresar_hora (&hora_de_llegada);

	ingresar_nota (&nota_parcial);

	puntaje_total = puntaje_final (transporte, deshacer_manifestacion, nota_parcial);

	calcular_personaje (puntaje_total, hora_de_llegada, ref_personaje);

return *ref_personaje; 
}