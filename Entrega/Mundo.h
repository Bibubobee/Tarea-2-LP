#ifndef MUNDO_H
#define MUNDO_H
#include "Animal.h"

Animal** Mundo;
Animal*** aux_mundo; //Arreglo "del futuro", simula todas las interacciones "simultaneamente"
int animal_size;
int dir[4][2] = {{999,0}, {0,999}, {1,0}, {0,1}};

void Colocar(Animal* a);
void TransferirAnimal(Animal* a1, Animal* a2);
void CopiarPunteroVoid(void** p_1, char* tipo_1, void** p_2, char* tipo_2);
void MasDe2Animales(Animal* arr, int cant);
void MoverDeCasillaOcupada(Animal* a);
void PasaTurno();
#endif