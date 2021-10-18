#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Animal.h"
#include "Mundo.h"

int dir[4][2] = {{999,0}, {0,999}, {1,0}, {0,1}};

void Colocar(Animal* a){
    /**********************************************************************************
     * Input:   Animal* a
     * Pone una copia del animal en la coordenada que tiene guardada, lo pone en (y,x).
    ***********************************************************************************/
    Mundo[a->coordenadas[1]][a->coordenadas[0]] = *a;
}

void TransferirAnimal(Animal* a1, Animal* a2){
    /**********************************************************************************
     * Input:   Animal* a1
     *          Animal* a2
     * Transfiere los datos del animal a1 al a2, borrando a1 al terminar.
    ***********************************************************************************/
    CopiarPunteroVoid(&a1->fuerza, &a1->tipo_fuerza, &a2->fuerza, &a2->tipo_fuerza);
    CopiarPunteroVoid(&a1->velocidad, &a1->tipo_velocidad, &a2->velocidad, &a2->tipo_velocidad);
    CopiarPunteroVoid(&a1->resistencia, &a1->tipo_resistencia, &a2->resistencia, &a2->tipo_resistencia);

  
    a2->coordenadas[0] = a1->coordenadas[0];
    a2->coordenadas[1] = a1->coordenadas[1];
    a2->reproduccion = a1->reproduccion;
    a2->comerHuir = a1->comerHuir;
    Borrar(a1);
}

void CopiarPunteroVoid(void** p_1, char* tipo_1, void** p_2, char* tipo_2){
    /**********************************************************************************
     * Input:   void* p_1
     *          char tipo_1
     *          void* p_2
     *          char tipo_2
     * Procedimiento hecho para ordenar algunos codigos que se repetian, copia correctamente
     * memoria de un puntero void a otro (copia de p_1 a p_2). SE ASUME QUE p_2 NO APUNTABA A NADA.
    ***********************************************************************************/
    *tipo_2 = *tipo_1;
    *p_2 = malloc(sizeof(*p_1));
    switch(*tipo_2){
        case 'e':
            memcpy(*p_2, *p_1, sizeof(int));
            break;
        case 'f':
            memcpy(*p_2, *p_1, sizeof(float));
            break;
        case 'c':
            memcpy(*p_2, *p_1, sizeof(char));
            break;
    }
}

/*********************** Funciones pensadas para trabajar los eventos con el aux_mundo* *********************************/
void MasDe2Animales(Animal* arr, int cant){
    /**********************************************************************************
     * Input:   Animal* arr, 
     *          int cant
     * Procedimiento que resuelve los casos donde más de 2 animales caen en la misma casilla,
     * compara la fuerza entre todos los animales y mantiene los 2 más fuertes en la casilla.
    ***********************************************************************************/
    printf("Se encontraron mas de 2 animales en una casilla\n");
    Animal* m_1 = &arr[0];
    Animal* m_2 = &arr[1];
    for(int i = 2; i < cant; i++){
        int fuer_1 = TraductorValores(m_1->fuerza, m_1->tipo_fuerza);
        int fuer_2 = TraductorValores(m_2->fuerza, m_2->tipo_fuerza);
        Animal* a = &arr[i];
        int fuer_a = TraductorValores(a->fuerza, a->tipo_fuerza);
        if(fuer_a > fuer_1){
            if(fuer_a > fuer_2){
                if(fuer_1 > fuer_2){
                    Borrar(m_2);
                    TransferirAnimal(a,m_2);
                }
                else{
                    Borrar(m_1);
                    TransferirAnimal(a,m_1);
                }
            }
            else{
                Borrar(m_1);
                TransferirAnimal(a,m_1);
            }
        }
        else if (fuer_a > fuer_2){
            if(fuer_a > fuer_2){
                if(fuer_2 > fuer_1){
                    Borrar(m_1);
                    TransferirAnimal(a,m_1);
                }
                else{
                    Borrar(m_2);
                    TransferirAnimal(a,m_2);
                }
            }
            else{
                Borrar(m_2);
                TransferirAnimal(a, m_2);
            }
        }
        else{

            Borrar(a);
        }
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
        if((aux_mundo[nueva_coord[1]][nueva_coord[0]][0]).fuerza == NULL){
            a->coordenadas[0] = nueva_coord[0];
            a->coordenadas[1] = nueva_coord[1];
            TransferirAnimal(a, &aux_mundo[nueva_coord[1]][nueva_coord[0]][0]); //ANDA FALLANDO AQUI ALGO.
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
                    if(aux_mundo[a->coordenadas[1]][a->coordenadas[0]][k].fuerza == NULL){
                        TransferirAnimal(a, &(aux_mundo[a->coordenadas[1]][a->coordenadas[0]][k])); //LEAK AQUI
                        break;
                    }
                }
            }
        }
    }
    //Resolver encuentros
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            int contador_a = 0;
            for(int k = 0; k < 4; k++){ //Cuenta cuantos animales están en una casilla.
                Animal* a = &(aux_mundo[i][j][k]);
                if(a->fuerza != NULL){
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
            for(int k = 0; k < 4; k++){
                if(aux_mundo[i][j][k].fuerza != NULL){
                    TransferirAnimal(&aux_mundo[i][j][k], &Mundo[i][j]);
                    break;
                }
            }
        }
    }
}