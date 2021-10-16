#ifndef MUNDO_C
#define MUNDO_C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Mundo.h"

void Colocar(Animal* a){
    /**********************************************************************************
     * Input:   Animal* a
     * Pone una copia del animal en la coordenada que tiene guardada, lo pone en (y,x).
    ***********************************************************************************/
    Mundo[a->coordenadas[1]][a->coordenadas[0]] = *a;
}

/*********************** Funciones pensadas para trabajar los eventos con el aux_mundo* *********************************/
void MasDe2Animales(Animal* arr, int cant){
    /**********************************************************************************
     * Input:   Animal* arr, 
     *          int cant
     * Procedimiento que resuelve los casos donde más de 2 animales caen en la misma casilla,
     * compara la fuerza entre todos los animales y mantiene los 2 más fuertes en la casilla.
    ***********************************************************************************/
    Animal* m_1 = &arr[0];
    Animal* m_2 = &arr[1];
    for(int i = 2; i < cant; i++){
        int fuer_1 = (m_1->tipo_fuerza == 'c')? atoi((char*)m_1->fuerza)/4 : *(int*)m_1->fuerza;
        int fuer_2 = (m_2->tipo_fuerza == 'c')? atoi((char*)m_2->fuerza)/4 : *(int*)m_2->fuerza;
        Animal* a = &arr[i];
        int fuer_a = (a->tipo_fuerza == 'c')? atoi((char*)a->fuerza)/4 : *(int*)a->fuerza;
        if(fuer_a > fuer_1){
            Borrar(m_1);
            *m_1 = *a;
        }
        else if (fuer_a > fuer_2){
            Borrar(m_2);
            *m_2 = *a;
        }
        Borrar(a); //Creo que ahi deberia está.
    }
}

void MoverDeCasillaOcupada(Animal* a){
    /**********************************************************************************
     * Input:   Animal* a
     * Procedimiento que resuelve los casos donde un animal debe colocarse en una casilla sin ocupar,
     * revisa en el orden indicado por dir (Izquierda->Arriba->Derecha->Abajo).
    ***********************************************************************************/
    for(int i = 0; i < 4; i++){
        int nueva_coord[2] = {(a->coordenadas[0] + dir[i][0]) % 1000, (a->coordenadas[1] + dir[i][1]) % 1000};
        if((aux_mundo[nueva_coord[1]][nueva_coord[0]][0]).fuerza != NULL){
            a->coordenadas[0] = nueva_coord[0];
            a->coordenadas[1] = nueva_coord[1];
            (aux_mundo[nueva_coord[1]][nueva_coord[0]][0]) = *a;
            return;
        }
    }
    Borrar(a);
    return;
}


void PasaTurno(){
    /**********************************************************************************
     * Encargado de realizar el paso de un instante de tiempo, trabaja con una matriz
     * auxiliar que se encarga de simular la simultaneidad del evento.
    ***********************************************************************************/
    //Copiar Mundo en Aux Mundo en las nuevas posiciones.
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            Animal* a = &(Mundo[i][j]);
            if(a->fuerza != NULL){
                int random = rand() % 4;
                a->coordenadas[0] = (a->coordenadas[0] + dir[random][0]) % 1000;
                a->coordenadas[1] = (a->coordenadas[1] + dir[random][1]) % 1000;

                for(int k = 0; k < 4; k++){
                    if(aux_mundo[a->coordenadas[1]][a->coordenadas[0]][k].fuerza != NULL){
                        aux_mundo[i][j][k] = *a;
                    }
                }
                Borrar(&(Mundo[i][j])); //Hacer como que se movió el animal
            }
        }
    }
    //Resolver encuentros
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            int contador_a = 0;
            for(int k = 0; k < 4; k++){ //Cuenta cuantos animales están en una casilla.
                Animal* a = &(aux_mundo[i][j][k]);
                if(aux_mundo[a->coordenadas[1]][a->coordenadas[0]][k].fuerza != NULL){
                    contador_a += 1;
                }
                else{
                    break;
                }
            }
            if(contador_a > 2){
                MasDe2Animales(aux_mundo[i][j], contador_a);
                contador_a = 2;
            }
            if(contador_a == 2){ //Sección de Reproduccion + Combate
                Animal hijo;
                Reproducir(&(aux_mundo[i][j][0]), &(aux_mundo[i][j][1]), &hijo);
                MoverDeCasillaOcupada(&hijo);
                ComerOHuir(&(aux_mundo[i][j][0]), &(aux_mundo[i][j][1]));
            }       
        }
    }
    //Retorno a la matriz del Mundo real.
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            Mundo[i][j] = aux_mundo[i][j][0];
            Borrar(&(aux_mundo[i][j][0]));
        }
    }
}
#endif