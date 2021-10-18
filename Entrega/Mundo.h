#ifndef MUNDO_H
#define MUNDO_H

Animal** Mundo;
Animal*** aux_mundo; //Arreglo "del futuro", simula todas las interacciones "simultaneamente"
int animal_size;

void Colocar(Animal* a);
void TransferirAnimal(Animal* a1, Animal* a2);
void CopiarPunteroVoid(void** p_1, char* tipo_1, void** p_2, char* tipo_2);
void MasDe2Animales(Animal* arr, int cant);
void MoverDeCasillaOcupada(Animal* a);
void PasaTurno();
#endif