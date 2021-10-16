#ifndef SIMULACION_C
#define SIMULACION_C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Animal.c"
#include "Mundo.c"

int main(){
    /**********************************************************************************
     * Es el main, primera funcion que se lee al abrir el ejecutable, aqui se encuentran
     * las acciones a realizar en la simulacion.
    ***********************************************************************************/
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

    /*
    Animal a;
    CrearTransimperativer(&a);
    Animal arreglo[1];
    arreglo[0] = a;
    MostrarAnimal(&a);
    Borrar(&(arreglo[0]));//EJEMPLO A SEGUIR
    */
}
#endif