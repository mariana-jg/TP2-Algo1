#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "utiles.h"
#include "papeleo.h"
#include "dia_en_la_uni.h"

#define MAX_FILAS 30
#define MAX_COLUMNAS 30

#define DIMENSION_N1 22
#define DIMENSION_N2 17
#define DIMENSION_N3 12

#define NUMERO_NIVEL1 1
#define NUMERO_NIVEL2 2
#define NUMERO_NIVEL3 3

#define CANT_FUEGOS_N1  10
#define CANT_MEDIAS_N1  5
#define CANT_BOTELLAS_N1 4
#define CANT_INTERRUPTOR_N1 1
#define CANT_PAPELEOS_N1 2
#define CANT_MOVIMIENTOS_N1 40
#define CANT_MARTILLOS_N1 4
#define CANT_EXTINTORES_N1 4

#define CANT_FUEGOS_N2  5
#define CANT_MEDIAS_N2  4
#define CANT_BOTELLAS_N2 3
#define CANT_INTERRUPTOR_N2 1
#define CANT_PAPELEOS_N2 3
#define CANT_MOVIMIENTOS_N2 30
#define CANT_MARTILLOS_N2 5
#define CANT_EXTINTORES_N2 2

#define CANT_FUEGOS_N3  3
#define CANT_MEDIAS_N3  3
#define CANT_BOTELLAS_N3 2
#define CANT_INTERRUPTOR_N3 0
#define CANT_PAPELEOS_N3 4
#define CANT_MOVIMIENTOS_N3 20
#define CANT_MARTILLOS_N3 6
#define CANT_EXTINTORES_N3 2

#define FUEGOS_EXTINTOS_OLAF_N1 2
#define FUEGOS_EXTINTOS_OLAF_N2 1
#define PAPELEOS_QUEMADOS_STITCH_N3 1
#define MOVIMIENTOS_EXTRAS_RAYO_N1 10
#define MARTILLO_EXTRA_JASMIN 1

#define FUEGOS 'F'
#define MEDIAS 'M'
#define BOTELLAS 'G'
#define INTERRUPTOR 'I'
#define PAPELEOS 'P'

/*Pre-condiciones: 
    -
Post-condiciones: 
    el procedimiento inicializara los campos que representan a los topes en 0 (cero) de los vectores que conforman el registro nivel_t.*/
void inicializar_topes (nivel_t* nivel) {

    nivel->tope_paredes = 0;
    nivel->tope_obstaculos = 0;
    nivel->tope_herramientas = 0;
    nivel->tope_papeleos = 0;  

}    

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    la función retorna "dimension_tablero" que es DIMENSION_N1, DIMENSION_N2, DIMENSION_N3.*/
int definir_dimension_tablero (int numero_nivel) {

    int dimension;

    if (numero_nivel == NUMERO_NIVEL1) {
        dimension = DIMENSION_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
        dimension = DIMENSION_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        dimension = DIMENSION_N3;        
    }

    return dimension;

}    

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    el procedimiento otorga una coordenada aleatoria (fila y columna) que tenga concordancia con el tamaño del tablero segun el nivel ingresado.*/
void coordenada_random (coordenada_t* ref_coordenada, int numero_nivel) {

    (*ref_coordenada).fil = rand () % definir_dimension_tablero(numero_nivel) + 0;
    (*ref_coordenada).col = rand () % definir_dimension_tablero(numero_nivel) + 0;

}

/*Pre-condiciones: 
    -
Post-condiciones: 
    la función compara dos coordenadas del tablero ingresadas, regresando una respuesta equivalente a 'true' si se cumple la igualdad.*/
bool mismas_coordenadas (coordenada_t coordenada_1, coordenada_t coordenada_2) {

    return ((coordenada_1.fil == coordenada_2.fil) && (coordenada_1.col == coordenada_2.col));

}


/*Pre-condiciones: 
    el vector 'paredes' ya debera estar cargado para que sea posible compararlo.
Post-condiciones: 
    la función comparara dos coordenadas (una referente a un objeto al cual quiero ubicar y una correspondiente al vector 'paredes'), regresando una 
        respuesta equivalente a 'true' si se cumple la igualdad.*/
bool coordenada_ocupada_con_pared (coordenada_t objeto, coordenada_t paredes[MAX_PAREDES], int tope_paredes) {
    
    bool ocupado_con_pared = false;

    for (int i = 0; i < tope_paredes ; i++) {

        if (mismas_coordenadas(paredes[i], objeto) == true) {
        ocupado_con_pared = true;
        }  

    }

    return ocupado_con_pared;
}

/*Pre-condiciones: 
    la 'pos_inicial_jugador' ya debera estar cargada para que sea posible compararla.
Post-condiciones: 
    la función comparara dos coordenadas (una referente a un objeto al cual quiero ubicar y la otra correspondiente a la pos_inicial_jugador), regresando una 
        respuesta equivalente a 'true' si se cumple la igualdad.*/
bool coordenada_ocupada_con_jugador (coordenada_t objeto, coordenada_t pos_inicial_jugador) {
    
    bool ocupado_con_jugador = false;

        if (mismas_coordenadas(pos_inicial_jugador, objeto) == true) {
        ocupado_con_jugador = true;    
        }  
    
    return ocupado_con_jugador;
}

/*Pre-condiciones: 
    el vector 'paredes' ya debera estar cargado para que sea posible compararlo.
Post-condiciones: 
    la función comparara dos coordenadas (una referente a un objeto (caso especifico: FUEGO) al cual quiero ubicar y la otra correspondiente al vector 'paredes', 
        regresando una respuesta equivalente a 'true' si se cumple ambas coordenadas son adyacentes.*/
bool adyacente (coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t objeto) {

    bool es_adyacente = false;

    for (int i = 0; i < tope_paredes ; i++){

        int distancia = abs(paredes[i].fil - objeto.fil) + abs(paredes[i].col - objeto.col);

        if (distancia == 1){
            es_adyacente = true;    
        }
    }

    return es_adyacente;
}

/*Pre-condiciones: 
    el vector 'papeleos' debe estar cargado anteriormente para poder compararlo.
Post-condiciones: 
    la función comparara dos coordenadas (una referente a un objeto al cual quiero ubicar y la otra una correspondiente al vector 'papeleos'), regresando una 
        respuesta equivalente a 'true' si se cumple la igualdad.*/
bool coordenada_ocupada_con_papeleo (coordenada_t objeto, papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos) {

    bool ocupado_con_papeleo = false;

    for (int i = 0; i < tope_papeleos ; i++) {

        if (mismas_coordenadas(papeleos[i].posicion, objeto) == true) {
            ocupado_con_papeleo = true;    
        }  
    }

    return ocupado_con_papeleo;
}

/*Pre-condiciones: 
    el vector 'obstaculos' debe estar cargado anteriormente para poder compararlo.
Post-condiciones: 
    la función comparara dos coordenadas (una referente a un objeto al cual quiero ubicar y la otra una correspondiente al vector 'obstaculos'), regresando una 
        respuesta equivalente a 'true' si se cumple la igualdad.*/
bool coordenada_ocupada_con_obstaculo (coordenada_t objeto, objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos) {

    bool ocupado_con_obstaculo = false;

    for (int i = 0; i < tope_obstaculos; i++) {

        if (mismas_coordenadas(obstaculos[i].posicion, objeto) == true) {
            ocupado_con_obstaculo = true;    
        }  
    }

    return ocupado_con_obstaculo;
}

/*Pre-condiciones: 
        "numero_nivel" debe ser 1, 2, o 3;
        el vector 'paredes', 'papeleos' y pos_inicial_jugador deben estar cargados anteriormente.
Post-condiciones: 
    el procedimiento carga un vector del tipo objeto_t, llenando tipo y posicion (la cual se verifica que ya no se encuentre ocupada, ademas
    de que si el objeto es FUEGO, comprobara que sea una posicion adyacente a una pared).*/
void cargar_vector_objetos_obstaculos(objeto_t vector[], int cant_objeto, char objeto, int* tope, int numero_nivel, coordenada_t paredes[MAX_PAREDES], 
    int tope_paredes, coordenada_t pos_inicial_jugador, papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos) {
   
   if (objeto == FUEGOS) {

       for (int i = 0; i < cant_objeto; i++) {

            vector[*tope].tipo = objeto;
            coordenada_t coordenada;

            do {
                coordenada_random(&coordenada, numero_nivel);
                vector[*tope].posicion = coordenada;
            } while (coordenada_ocupada_con_pared(coordenada, paredes, tope_paredes) ||
                 coordenada_ocupada_con_jugador(coordenada, pos_inicial_jugador)|| 
                 coordenada_ocupada_con_papeleo(coordenada, papeleos, tope_papeleos) ||
                 (adyacente(paredes, tope_paredes, coordenada) == false));

            (*tope)++;

        }

    } else {

        for (int i = 0; i < cant_objeto; i++) {

            vector[*tope].tipo = objeto;
            coordenada_t coordenada;

            do {
                coordenada_random(&coordenada, numero_nivel);
                vector[*tope].posicion = coordenada;
            } while (coordenada_ocupada_con_pared(coordenada, paredes, tope_paredes) ||
                 coordenada_ocupada_con_jugador(coordenada, pos_inicial_jugador) || 
                 coordenada_ocupada_con_papeleo(coordenada, papeleos, tope_papeleos));

            (*tope)++;
        }
    }
}

/*Pre-condiciones: 
        "numero_nivel" debe ser 1, 2, o 3;
        el vector 'paredes', 'papeleos', 'obstaculos' y la pos_inicial_jugador deben estar cargados anteriormente.
Post-condiciones: 
    el procedimiento carga un vector del tipo objeto_t, llenando tipo y posicion (la cual se verifica que ya no se encuentre ocupada).*/
void cargar_vector_objetos_herramientas(objeto_t vector[], int cant_objeto, char objeto, int* tope, int numero_nivel, coordenada_t paredes[MAX_PAREDES], 
    int tope_paredes, coordenada_t pos_inicial_jugador, papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos, objeto_t obstaculos[MAX_OBSTACULOS], 
    int tope_obstaculos) {
   
    for (int i = 0; i < cant_objeto; i++) {
        vector[*tope].tipo = objeto;
        coordenada_t coordenada;

        do {
        coordenada_random(&coordenada, numero_nivel);
        vector[*tope].posicion = coordenada;
        } while (coordenada_ocupada_con_pared(coordenada, paredes, tope_paredes) ||
             coordenada_ocupada_con_jugador(coordenada, pos_inicial_jugador) || 
             coordenada_ocupada_con_papeleo(coordenada, papeleos, tope_papeleos) ||
             coordenada_ocupada_con_obstaculo(coordenada, obstaculos, tope_obstaculos));
      
        (*tope)++;
    
    }
}

/*Pre-condiciones: 
        "numero_nivel" debe ser 1, 2, o 3;
        el vector 'paredes' y pos_inicial_jugador deben estar cargados anteriormente.
Post-condiciones: 
    el procedimiento carga un vector del tipo papeleo_t, llenando posicion (la cual se verifica que ya no se encuentre ocupada), id y estado de recoleccion.*/
void cargar_vector_papeleos (papeleo_t vector[], int cant_papeleos, int* tope, int numero_nivel, coordenada_t paredes[MAX_PAREDES], 
    int tope_paredes, coordenada_t pos_inicial_jugador) {

    for (int i = 0; i < cant_papeleos; i++) {

    	vector[*tope].id_papeleo = (i+1);
        vector[*tope].recolectado = false;
        coordenada_t coordenada;

        do {
            coordenada_random(&coordenada, numero_nivel);
            vector[*tope].posicion = coordenada;
        } while ((coordenada_ocupada_con_pared(coordenada, paredes, tope_paredes) == true) ||
             (coordenada_ocupada_con_jugador(coordenada, pos_inicial_jugador) == true));

        (*tope)++;
    }
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3; 
    "amigo_pide_favor" debe ser JASMIN, OLAF, RAYO_MCQUEEN O STITCH (CONSTANTES en dia_en_la_uni).
Post-condiciones: 
    la función retorna "cantidad_fuegos" con su valor segun el nivel y el personaje enviado por parametro.*/
int cantidad_fuegos (int numero_nivel, char amigo_pide_favor) {

    int cantidad_fuegos;

    if (numero_nivel == NUMERO_NIVEL1) {
        if (amigo_pide_favor == OLAF) {
            cantidad_fuegos = CANT_FUEGOS_N1-FUEGOS_EXTINTOS_OLAF_N1;
        } else {cantidad_fuegos = CANT_FUEGOS_N1;
        }    
    } else if (numero_nivel == NUMERO_NIVEL2) {
        if (amigo_pide_favor == OLAF) {
            cantidad_fuegos = CANT_FUEGOS_N2-FUEGOS_EXTINTOS_OLAF_N2;
        } else {cantidad_fuegos = CANT_FUEGOS_N2;
        }   
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_fuegos = CANT_FUEGOS_N3;
    }

    return cantidad_fuegos;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    la función retorna "cantidad_medias" que es CANT_MEDIAS_N1, CANT_MEDIAS_N2 o CANT_MEDIAS_N3.*/
int cantidad_medias (int numero_nivel) {

    int cantidad_medias;

    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_medias = CANT_MEDIAS_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
        cantidad_medias = CANT_MEDIAS_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_medias = CANT_MEDIAS_N3;
    }
    return cantidad_medias;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    la función retorna "cantidad_interruptores" que es CANT_INTERRUPTOR_N1, CANT_INTERRUPTOR_N2 o CANT_INTERRUPTOR_N3.*/
int cantidad_interruptores (int numero_nivel) {

    int cantidad_interruptores;

    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_interruptores = CANT_INTERRUPTOR_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
        cantidad_interruptores = CANT_INTERRUPTOR_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_interruptores = CANT_INTERRUPTOR_N3;
    }

    return cantidad_interruptores;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    la función retorna "cantidad_botellas" que es CANT_BOTELLAS_N1, CANT_BOTELLAS_N2 o CANT_BOTELLAS_N3.*/
int cantidad_botellas (int numero_nivel) {

    int cantidad_botellas;

    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_botellas = CANT_BOTELLAS_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
        cantidad_botellas = CANT_BOTELLAS_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_botellas = CANT_BOTELLAS_N3;
    }

    return cantidad_botellas;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3; 
    "amigo_pide_favor" debe ser JASMIN, OLAF, RAYO_MCQUEEN O STITCH (CONSTANTES en dia_en_la_uni).
Post-condiciones: 
    la función retorna "cantidad_papeleos" con su valor segun el nivel y el personaje enviado por parametro.*/
int cantidad_papeleos (int numero_nivel, char amigo_pide_favor) {

    int cantidad_papeleos;

    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_papeleos = CANT_PAPELEOS_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
        cantidad_papeleos = CANT_PAPELEOS_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        if (amigo_pide_favor == STITCH){
            cantidad_papeleos = CANT_PAPELEOS_N3-PAPELEOS_QUEMADOS_STITCH_N3;
        } else {
        cantidad_papeleos = CANT_PAPELEOS_N3;
        }
    }

    return cantidad_papeleos;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3; 
    "amigo_pide_favor" debe ser JASMIN, OLAF, RAYO_MCQUEEN O STITCH (CONSTANTES en dia_en_la_uni).
Post-condiciones: 
    la función retorna "cantidad_movimientos_iniciales" con su valor segun el nivel y el personaje enviado por parametro.*/
int cantidad_movimientos_iniciales (int numero_nivel, char amigo_pide_favor) {

    int cantidad_movimientos_iniciales;

    if (numero_nivel == NUMERO_NIVEL1) {
        if (amigo_pide_favor == RAYO_MCQUEEN) {
            cantidad_movimientos_iniciales = CANT_MOVIMIENTOS_N1+MOVIMIENTOS_EXTRAS_RAYO_N1;
        } else {
        cantidad_movimientos_iniciales = CANT_MOVIMIENTOS_N1;
        }
    } else if (numero_nivel == NUMERO_NIVEL2) {
        cantidad_movimientos_iniciales = CANT_MOVIMIENTOS_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_movimientos_iniciales = CANT_MOVIMIENTOS_N3;
    }

    return cantidad_movimientos_iniciales;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3; 
    "amigo_pide_favor" debe ser JASMIN, OLAF, RAYO_MCQUEEN O STITCH (CONSTANTES en dia_en_la_uni).
Post-condiciones: 
    la función retorna "cantidad_martillos" con su valor segun el nivel y el personaje enviado por parametro.*/
int cantidad_martillos (int numero_nivel, char amigo_pide_favor) {

    int cantidad_martillos;

    if (amigo_pide_favor == JASMIN) {
        if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_martillos = CANT_MARTILLOS_N1+MARTILLO_EXTRA_JASMIN;
    } else if (numero_nivel == NUMERO_NIVEL2) {
       cantidad_martillos = CANT_MARTILLOS_N2+MARTILLO_EXTRA_JASMIN;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_martillos = CANT_MARTILLOS_N3+MARTILLO_EXTRA_JASMIN;
    }
    } else {   
    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_martillos = CANT_MARTILLOS_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
       cantidad_martillos = CANT_MARTILLOS_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_martillos = CANT_MARTILLOS_N3;
    }
}

    return cantidad_martillos;
}

/*Pre-condiciones: 
    "numero_nivel" debe ser 1, 2, o 3;
Post-condiciones: 
    la función retorna "cantidad_extintores" que es CANT_EXTINTORES_N1, CANT_EXTINTORES_N2 o CANT_EXTINTORES_N3.*/
int cantidad_extintores (int numero_nivel) {

    int cantidad_extintores;

    if (numero_nivel == NUMERO_NIVEL1) {
        cantidad_extintores = CANT_EXTINTORES_N1;
    } else if (numero_nivel == NUMERO_NIVEL2) {
       cantidad_extintores = CANT_EXTINTORES_N2;
    } else if (numero_nivel == NUMERO_NIVEL3) {
        cantidad_extintores = CANT_EXTINTORES_N3;
    }
    return cantidad_extintores;
}

// Pre y post en papeleo.h
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char amigo_pide_favor) {

    inicializar_topes(nivel);

    obtener_paredes(NUMERO_NIVEL1, nivel->paredes, &(nivel->tope_paredes), &(nivel->pos_inicial_jugador)); 

    cargar_vector_papeleos(nivel->papeleos, cantidad_papeleos(numero_nivel, amigo_pide_favor), &(nivel->tope_papeleos), numero_nivel, 
        nivel->paredes, nivel->tope_paredes, nivel->pos_inicial_jugador);


    cargar_vector_objetos_obstaculos(nivel->obstaculos, cantidad_fuegos(numero_nivel, amigo_pide_favor), FUEGOS, &(nivel->tope_obstaculos), numero_nivel,
        nivel->paredes, nivel->tope_paredes, nivel->pos_inicial_jugador, nivel->papeleos, nivel->tope_papeleos);
    cargar_vector_objetos_obstaculos(nivel->obstaculos, cantidad_medias(numero_nivel), MEDIAS, &(nivel->tope_obstaculos),numero_nivel,
        nivel->paredes, nivel->tope_paredes, nivel->pos_inicial_jugador, nivel->papeleos,nivel->tope_papeleos);

    cargar_vector_objetos_herramientas(nivel->herramientas, cantidad_botellas(numero_nivel), BOTELLAS, &(nivel->tope_herramientas), numero_nivel, 
        nivel->paredes, nivel->tope_paredes, nivel->pos_inicial_jugador, nivel->papeleos,nivel->tope_papeleos, nivel->obstaculos, nivel->tope_obstaculos);
    cargar_vector_objetos_herramientas(nivel->herramientas, cantidad_interruptores(numero_nivel), INTERRUPTOR, &(nivel->tope_herramientas), numero_nivel,
        nivel->paredes, nivel->tope_paredes, nivel->pos_inicial_jugador, nivel->papeleos,nivel->tope_papeleos, nivel->obstaculos, nivel->tope_obstaculos);



    
}

/*Pre-condiciones: 
        "numero_nivel" debe ser 1, 2, o 3;
        "amigo_pide_favor" debe ser JASMIN, OLAF, RAYO_MCQUEEN O STITCH (CONSTANTES en dia_en_la_uni).
Post-condiciones: 
    el procedimiento carga un registro del tipo juego_t, llenando cantidad de martillos, movimientos y extintores,
        ademas de la posicion (que debe ser la inicial al comenzar el juego) y el estado de ahuyenta_randall..*/
void cargar_jugador (jugador_t* jugador, int numero_nivel, char amigo_pide_favor, coordenada_t posicion_inicial) {

    jugador->martillos = cantidad_martillos(numero_nivel, amigo_pide_favor);
    jugador->movimientos = cantidad_movimientos_iniciales (numero_nivel, amigo_pide_favor);
    jugador->extintores = cantidad_extintores (numero_nivel);
    jugador->posicion = posicion_inicial;
    jugador->ahuyenta_randall = false;

}

// Pre y post en papeleo.h
void inicializar_juego (juego_t* juego, char amigo_pide_favor) {

    juego->nivel_actual = NUMERO_NIVEL1;
    juego->personaje_tp1 = amigo_pide_favor;

    inicializar_nivel(&(juego->niveles[0]), NUMERO_NIVEL1, amigo_pide_favor);
    inicializar_nivel(&(juego->niveles[1]), NUMERO_NIVEL2, amigo_pide_favor);
    inicializar_nivel(&(juego->niveles[2]), NUMERO_NIVEL3, amigo_pide_favor); 

    cargar_jugador (&(juego->jugador), juego->nivel_actual, amigo_pide_favor, juego->niveles[(juego->nivel_actual)-1].pos_inicial_jugador);

} 

// Pre y post en papeleo.h
void imprimir_terreno(juego_t juego) {
				
	int dimension = definir_dimension_tablero(juego.nivel_actual);

	char mapa[dimension][dimension];

	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			mapa[i][j] = ' ';

	mapa[juego.niveles[(juego.nivel_actual-1)].pos_inicial_jugador.fil][juego.niveles[(juego.nivel_actual-1)].pos_inicial_jugador.col] = 'W';

	for (int i = 0; i < juego.niveles[(juego.nivel_actual-1)].tope_paredes; i++) {
		mapa[juego.niveles[(juego.nivel_actual-1)].paredes[i].fil][juego.niveles[(juego.nivel_actual-1)].paredes[i].col] = '*';
	}

	for (int i = 0; i < juego.niveles[(juego.nivel_actual-1)].tope_papeleos; i++) {
		mapa[juego.niveles[(juego.nivel_actual-1)].papeleos[i].posicion.fil][juego.niveles[(juego.nivel_actual-1)].papeleos[i].posicion.col] = 'P';
	}

    for (int i = 0; i < juego.niveles[(juego.nivel_actual-1)].tope_obstaculos; i++) {
        mapa[juego.niveles[(juego.nivel_actual-1)].obstaculos[i].posicion.fil][juego.niveles[(juego.nivel_actual-1)].obstaculos[i].posicion.col] = 
            juego.niveles[(juego.nivel_actual-1)].obstaculos[i].tipo;
    }

    for (int i = 0; i < juego.niveles[(juego.nivel_actual-1)].tope_herramientas; i++) {
        mapa[juego.niveles[(juego.nivel_actual-1)].herramientas[i].posicion.fil][juego.niveles[(juego.nivel_actual-1)].herramientas[i].posicion.col] = 
            juego.niveles[(juego.nivel_actual-1)].herramientas[i].tipo;
    }


	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			printf(" %c ", mapa[i][j]);
		}
        printf("\n");
    }
}