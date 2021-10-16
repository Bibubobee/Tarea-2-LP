#ifndef MUNDO_H
#define MUNDO_H

Animal** Mundo;
Animal*** aux_mundo; //Arreglo "del futuro", simula todas las interacciones "simultaneamente"
int animal_size;
int dir[4][2] = {{998,0}, {0,998}, {1,0}, {0,1}};

void Colocar(Animal* a);
void MasDe2Animales(Animal* arr, int cant);
void MoverDeCasillaOcupada(Animal* a);
void PasaTurno();
#endif