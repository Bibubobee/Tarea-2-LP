#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Animal.h"
#include "Mundo.h"

int main(void){
    /**********************************************************************************
     * Es el main, primera funcion que se lee al abrir el ejecutable, aqui se encuentran
     * las acciones a realizar en la simulacion.
    ***********************************************************************************/
    srand(time(0)); //Seed del randomizador.
    animal_size = sizeof(Animal);

    /*************************** Creacion de la Matriz Mundo y aux_mundo ***************************/
    Mundo = (Animal**)calloc(1000, animal_size);
    for(int i = 0; i < 1000; i++){
        Mundo[i] = (Animal*)calloc(1000, animal_size);
    }

    aux_mundo = (Animal***)calloc(1000, animal_size);
    for(int i = 0; i < 1000; i++){
        aux_mundo[i] = (Animal**)calloc(1000, animal_size);
        for(int j = 0; j < 1000; j++){
            aux_mundo[i][j] = (Animal*)calloc(4, animal_size);
        }
    }
    /***********************************************************************************************/
    /****************Si quieren hacer casos controlados pueden crear como en este ejemplo los animales.*************************/
    /*********Tambien pueden colocarlos en posiciones dentro de aux_mundo si quieren probar algo ***************
    ************************en especial, pero deben hacerlo a mano, no con Colocar().******************************************/
    /*Animal ani_1;
    Animal ani_2;
    Animal ani_3;
    ani_1.tipo_fuerza = 'e';
    ani_1.tipo_velocidad = 'f';
    ani_1.tipo_resistencia = 'c';
    ani_1.fuerza = malloc(sizeof(int));
    ani_1.velocidad = malloc(sizeof(float));
    ani_1.resistencia = malloc(sizeof(char));
    *(int*)ani_1.fuerza = 5;
    *(float*)ani_1.velocidad = 5.5;
    *(char*)ani_1.resistencia = 'U';
    ani_1.coordenadas[0] = 0;
    ani_1.coordenadas[1] = 0;
    ani_1.reproduccion = &ReproduccionSimple;
    ani_1.comerHuir = &ComerSiempre;

    ani_2.tipo_fuerza = 'f';
    ani_2.tipo_velocidad = 'e';
    ani_2.tipo_resistencia = 'c';
    ani_2.fuerza = malloc(sizeof(float));
    ani_2.velocidad = malloc(sizeof(int));
    ani_2.resistencia = malloc(sizeof(char));
    *(float*)ani_2.fuerza = 5.7;
    *(int*)ani_2.velocidad = 6;
    *(char*)ani_2.resistencia = 'Z';
    ani_2.coordenadas[0] = 1;
    ani_2.coordenadas[1] = 0;
    ani_2.reproduccion = &ReproduccionCruzada;
    ani_2.comerHuir = &HuirSiempre;

    ani_3.tipo_fuerza = 'e';
    ani_3.tipo_velocidad = 'f';
    ani_3.tipo_resistencia = 'c';
    ani_3.fuerza = malloc(sizeof(int));
    ani_3.velocidad = malloc(sizeof(float));
    ani_3.resistencia = malloc(sizeof(char));
    *(int*)ani_3.fuerza = 5;
    *(float*)ani_3.velocidad = 3.25;
    *(char*)ani_3.resistencia = 'P';
    ani_3.coordenadas[0] = 0;
    ani_3.coordenadas[1] = 1;
    ani_3.reproduccion = &ReproduccionCruzada;
    ani_3.comerHuir = &ComerAleatorio;

    Colocar(&ani_1);
    Colocar(&ani_2);
    Colocar(&ani_3);*/
    /*************************************************************************************************************/

    int seguir_juego = 1;
    int eleccion;
    while(seguir_juego){
        printf("Elija una opcion:\n1.Crear Animal  2.Pasar un turno  3.Mostrar Mundo  4.Terminar el juego ");
        scanf("%d", &eleccion);
        switch(eleccion){
            case 1: ;
                Animal a;
                CrearTransimperativer(&a);
                Colocar(&a);
                break;
            case 2:
                PasaTurno();
                break;
            case 3:
                MostrarMundo(Mundo);
                break;
            case 4:
                BorrarMundo(Mundo);
                seguir_juego = 0;
                break;
        }
    }
    //Liberación de memoria del aux_mundo.
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            free(aux_mundo[i][j]);
        }
        free(aux_mundo[i]);
    }
    free(aux_mundo);
}