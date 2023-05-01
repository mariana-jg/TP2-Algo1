#include <stdio.h>
#include <stdbool.h>
#include "dia_en_la_uni.h"
#include "papeleo.h"
#include <stdlib.h>
#include <time.h>

int main(){

	srand (( unsigned)time(NULL));

   char personaje;
    
   personaje = ejec_cuestionario(&personaje);
   
   juego_t juego;
    
   inicializar_juego(&juego, personaje);

   imprimir_terreno(juego);

   return 0;
}