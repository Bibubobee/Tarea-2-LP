#ifndef ANIMAL_C
#define ANIMAL_C
#include <stdio.h>
#include <stdlib.h>
#include "Animal.h"
#include "Mundo.h"

void CrearTransimperativer(Animal* a ){
    /**********************************************************************************
     * Input:   Animal* a
     * Creación de un animal mediante inputs solicitados por Consola.
    ***********************************************************************************/
    char* orden_tipos[] = {"Fuerza", "Velocidad", "Resistencia"};
    char tipo;
    printf("Ingrese coordenada X para el animal (0-999): ");
    scanf("%d", &(a->coordenadas[0]));
    printf("Ingrese coordenada Y para el animal (0-999): ");
    scanf("%d", &(a->coordenadas[1]));
    printf("Ingrese estadisticas del animal:\n");
    for (int i = 0; i < 3; i++){
        printf("%s (tipo a ingresar; e=int, f=float, c=char): ", orden_tipos[i]);
        scanf(" %c", &tipo);
        printf("Valor: ");
        void* p_valor;
        switch (tipo){
            case 'e': ;
                int i_valor;
                scanf("%d", &i_valor);
                p_valor = malloc(sizeof(i_valor));
                *(int*)p_valor = i_valor;
                break;
            case 'f': ;
                float f_valor;
                scanf("%f", &f_valor);
                p_valor = malloc(sizeof(f_valor));
                *(float*)p_valor = f_valor;          
                break;
            case 'c': ;
                char c_valor;
                scanf(" %c", &c_valor);
                p_valor = malloc(sizeof(c_valor));
                *(char*)p_valor = c_valor;
                break;
        }

        switch(i){
            case 0:
                a->fuerza = p_valor;
                a->tipo_fuerza = tipo;
                break;
            case 1:
                a->velocidad = p_valor;
                a->tipo_velocidad = tipo;
                break;
            case 2:
                a->resistencia = p_valor;
                a->tipo_resistencia = tipo;
                break;
        }
    }
    printf("Eliga funcion de reproducción:\n");
    printf("    1. ReproduccionSimple\n");
    printf("    2. ReproduccionCruzada\n");
    int eleccion;
    scanf("%d", &eleccion);
    switch (eleccion){
        case 1:
            a->reproduccion = &ReproduccionSimple;
            break;
        case 2:
            a->reproduccion = &ReproduccionCruzada;
            break;
    }
    printf("Eliga funcion de ComerHuir:\n");
    printf("    1. ComerSiempre\n");
    printf("    2. HuirSiempre\n");
    printf("    3. ComerAleatorio\n");
    scanf("%d", &eleccion);
    switch (eleccion){
        case 1:
            a->comerHuir = &ComerSiempre;
            break;
        case 2:
            a->comerHuir = &HuirSiempre;
            break;
        case 3:
            a->comerHuir = &ComerAleatorio;
            break;
    }
}

void Borrar (Animal* a ){
    /**********************************************************************************
     * Input:   Animal* a
     * Borra un animal por referencia.
    ***********************************************************************************/
    free(a->fuerza);
    free(a->velocidad);
    free(a->resistencia);
}

void MostrarAnimal (Animal* a ) {
    /**********************************************************************************
     * Input:   Animal* a
     * Imprime en consola la Fuerza, Velocidad, Resistencia y coordenadas del animal.
    ***********************************************************************************/
    char tipos[3] = {a->tipo_fuerza, a->tipo_velocidad, a->tipo_resistencia};
    void* valores[3] = {a->fuerza, a->velocidad, a->resistencia};
    char* nombres[3] = {"Fuerza", "Velocidad", "Resistencia"};
    for(int i = 0; i < 3; i++){
        switch (tipos[i]){
            case 'e':
                printf("%s: %d\n", nombres[i], *(int*)valores[i]);
                break;
        
            case 'f':
                printf("%s: %f\n", nombres[i], *(float*)valores[i]);
                break;

            case 'c':
                printf("%s: %c\n", nombres[i], *(char*)valores[i]);
                break;
        }
    }
    printf("Coordenadas: (%d,%d)\n", a->coordenadas[1], a->coordenadas[0]);
}

void Reproducir (Animal* a1 , Animal* a2 , Animal* hijo ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     *          Animal* hijo
     * Decide al azar qué animal usa su funcion de reproduccion para realizarlo.
     * Ademas imprime por pantalla cual animal se eligió.
    ***********************************************************************************/
    int random = rand() % 2;
    if(random == 0){
        a1->reproduccion(a1,a2,hijo);
        MostrarAnimal(a1);
    }
    else{
        a2->reproduccion(a2,a1,hijo);
        MostrarAnimal(a2);
    }
}

void ComerOHuir (Animal* a1 , Animal * a2 ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Decide al azar qué animal usa su funcion de comerHuir, imprime por pantalla quién
     * fue.
    ***********************************************************************************/
    int random = rand() % 2;
    if(random == 0){
        a1->comerHuir(a1,a2);
    }
    else{
        a2->comerHuir(a2,a1);
    }
}

int Comparar (Animal* a1 , Animal * a2 ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Compara todos las estadisticas de los animales y decide cual gana por quién ganó
     * más comparaciones, la funcion retorna 0 si el animal a1 gana, 1 en caso contrario.
    ***********************************************************************************/
    int contador = 0;
    int fuerza_1 = (a1->tipo_fuerza == 'c')? atoi((char*)a1->fuerza)/4 : *(int*)a1->fuerza;
    int fuerza_2 = (a2->tipo_fuerza == 'c')? atoi((char*)a2->fuerza)/4 : *(int*)a2->fuerza;
    contador = fuerza_1 > fuerza_2 ? contador + 1 : contador - 1;
    int vel_1 = (a1->tipo_velocidad == 'c')? atoi((char*)a1->velocidad)/4 : *(int*)a1->velocidad;
    int vel_2 = (a2->tipo_velocidad == 'c')? atoi((char*)a2->velocidad)/4 : *(int*)a2->velocidad;
    contador = (vel_1 > vel_2) ? contador + 1 : contador - 1;
    if(contador > 1){ //Optimizacion es mi pasion LOL (jk)
        return 0;
    }
    else if (contador < -1)
    {
        return 1;
    }
    int res_1 = (a1->tipo_resistencia == 'c')? atoi((char*)a1->resistencia)/4 : *(int*)a1->resistencia;
    int res_2 = (a2->tipo_resistencia == 'c')? atoi((char*)a2->resistencia)/4 : *(int*)a2->resistencia;
    contador = (res_1 > res_2) ? contador + 1 : contador - 1;
    return contador > 0;
}

void BorrarMundo (Animal** Mundo ) {
    /**********************************************************************************
     * Input:   Animal** Mundo
     * Borra la Matriz Mundo.
    ***********************************************************************************/
    for (int x = 0; x < 1000; x++){
        for(int y = 0; y < 1000; y++){
            if(Mundo[x][y].fuerza != NULL){
                Borrar(&(Mundo[x][y]));
            }
        }
        free(Mundo[x]);
    }
    free(Mundo);
}

void MostrarMundo (Animal** Mundo ) {
    /**********************************************************************************
     * Input:   Animal** Mundo
     * Muestra por consola todos los animales en el Mundo.
    ***********************************************************************************/
    for (int x = 0; x < 1000; x++){
        for(int y = 0; y < 1000; y++){
            if((Mundo[x][y]).fuerza != NULL){
                MostrarAnimal(&(Mundo[x][y]));
            }
        }
    }
}

void ReproduccionSimple (Animal* a1 , Animal* a2 , Animal* hijo ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     *          Animal* hijo
     * Compara a1 con a2, luego copia todos los valores del ganador al hijo.
    ***********************************************************************************/
    int resultado = Comparar(a1, a2);
    if(!resultado){
        hijo->fuerza = malloc(sizeof(a1->fuerza));
        hijo->velocidad = malloc(sizeof(a1->velocidad));
        hijo->resistencia = malloc(sizeof(a1->resistencia));
        *hijo = *a1;
    }
    else{
        hijo->fuerza = malloc(sizeof(a2->fuerza));
        hijo->velocidad = malloc(sizeof(a2->velocidad));
        hijo->resistencia = malloc(sizeof(a2->resistencia));
        *hijo = *a2;
    }
    printf("Reproduccion Simple de:\n");
    MostrarAnimal(a1);
    return;
}
void ReproduccionCruzada (Animal* a1 , Animal* a2 , Animal* hijo ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     *          Animal* hijo
     * Compara a1 con a2, le entrega al hijo la fuerza, velocidad y funcion reproduccion
     * del ganador y la reproduccion y funcion comerHuir del perdedor.
    ***********************************************************************************/
    int resultado = Comparar(a1,a2);
    if(!resultado){
        hijo->fuerza = malloc(sizeof(a1->fuerza));
        hijo->velocidad = malloc(sizeof(a1->velocidad));
        hijo->resistencia = malloc(sizeof(a2->resistencia));
        *hijo = *a1;
        hijo->comerHuir = a2->comerHuir;
        switch(a2->tipo_resistencia){
            case 'e':
                *(int*)hijo->resistencia = *(int*)a2->resistencia;
            case 'f':
                *(float*)hijo->resistencia = *(float*)a2->resistencia;
            case 'c':
                *(char*)hijo->resistencia = *(char*)a2->resistencia;
        }
    }
    else{
        hijo->fuerza = malloc(sizeof(a2->fuerza));
        hijo->velocidad = malloc(sizeof(a2->velocidad));
        hijo->resistencia = malloc(sizeof(a1->resistencia));
        *hijo = *a2;
        hijo->comerHuir = a1->comerHuir;
        switch(a1->tipo_resistencia){
            case 'e':
                *(int*)hijo->resistencia = *(int*)a1->resistencia;
            case 'f':
                *(float*)hijo->resistencia = *(float*)a1->resistencia;
            case 'c':
                *(char*)hijo->resistencia = *(char*)a1->resistencia;
        }
    }
    printf("Reproduccion Cruzada de:\n"); //METE TODO ESTO EN MOSTRAR ANIMAL
    MostrarAnimal(a1);
}

void ComerSiempre(Animal* a1 , Animal * a2 ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Compara la fuerza de a1 con la resistencia de a2, si gana a1, a2 muere y viceversa.
    ***********************************************************************************/
    int fuerza_1 = (a1->tipo_fuerza == 'c')? atoi((char*)a1->fuerza)/4 : *(int*)a1->fuerza;
    int resistencia_2 = (a2->tipo_resistencia == 'c')? atoi((char*)a2->resistencia)/4 : *(int*)a2->resistencia;
    int booleano = fuerza_1 > resistencia_2;
    if(booleano){
        Borrar(a2);
    }
    else{
        Borrar(a1);
    }
    printf("Comer Siempre de:\n");
    MostrarAnimal(a1);
}

void HuirSiempre (Animal* a1 , Animal * a2) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Compara las velocidades de a1 y a2, si gana a1 se mueve a una casilla 
     * colindante, en el caso contrario a1 muere.
    ***********************************************************************************/
    int vel_1 = (a1->tipo_velocidad == 'c')? atoi((char*)a1->velocidad)/4 : *(int*)a1->velocidad;
    int vel_2 = (a2->tipo_velocidad == 'c')? atoi((char*)a2->velocidad)/4 : *(int*)a2->velocidad;
    int booleano = vel_1 > vel_2;
    if(booleano){
        MoverDeCasillaOcupada(a1);
    }
    else{
        Borrar(a1);
    }
    printf("Huir Siempre de:\n");
    MostrarAnimal(a1);
}
void ComerAleatorio (Animal* a1 , Animal * a2 ) {
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Compara 2 estadisticas al azar de a1 y a2 (ambos elegidos al azar), si el valor de
     * a1 es mayor a2 muere, de lo contrario a1 muere.
    ***********************************************************************************/
    int atributo_1 = rand() % 3;
    int atributo_2 = rand() % 3;
    int valor_1, valor_2;
    switch(atributo_1){
        case 0:
            valor_1 = (a1->tipo_fuerza == 'c')? atoi((char*)a1->fuerza)/4 : *(int*)a1->fuerza;
            break;
        case 1:
            valor_1 = (a1->tipo_velocidad == 'c')? atoi((char*)a1->velocidad)/4 : *(int*)a1->velocidad;
            break;
        case 2:
            valor_1 = (a1->tipo_resistencia == 'c')? atoi((char*)a1->resistencia)/4 : *(int*)a1->resistencia;
            break;    
    }
    switch(atributo_2){
        case 0:
            valor_2 = (a2->tipo_fuerza == 'c')? atoi((char*)a2->fuerza)/4 : *(int*)a2->fuerza;
            break;
        case 1:
            valor_2 = (a2->tipo_velocidad == 'c')? atoi((char*)a2->velocidad)/4 : *(int*)a2->velocidad;
            break;
        case 2:
            valor_2 = (a2->tipo_resistencia == 'c')? atoi((char*)a2->resistencia)/4 : *(int*)a2->resistencia;
            break;    
    }

    if(valor_1 > valor_2){
        Borrar(a2);
    }
    else{
        Borrar(a1);
    }
    printf("Comer Aleatorio de:\n");
    MostrarAnimal(a1);
}
#endif