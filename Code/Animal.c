#include "Animal.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    srand((unsigned) time(0));
}

void CrearTransimperativer(Animal* a ){
    char orden_tipos[] = {"Fuerza", "Velocidad", "Resistencia"};
    char tipo;
    printf("Ingrese estadisticas del animal:\n");
    for (int i = 0; i < 3; i++){
        printf("%s (tipo a ingresar; e=int, f=float, c=char): ", orden_tipos[i]);
        scanf("%c", tipo);
        printf("Valor: ");
        void* p_valor;
        switch (tipo){
            case 'e':
                int valor;
                scanf("%d", valor);
                p_valor = malloc(sizeof(valor));
                p_valor = &valor;
                break;
            case 'f':
                float valor;
                scanf("%f", valor);
                p_valor = malloc(sizeof(valor));
                p_valor = &valor;                
                break;
            case 'c':
                char valor;
                scanf("%c", valor);
                p_valor = malloc(sizeof(valor));
                p_valor = &valor;
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
}
void Borrar (Animal* a ){
    free(a);
}
void MostrarAnimal (Animal* a ) {
    //Revisa esto despues weon, estoy bien seguro que lo va a explotar porque DUMB SHIT (tipos y wea).
    printf("Fuerza: %s", a->fuerza);
    printf("Velocidad: %s", a->velocidad);
    printf("Resistencia: %s", a->resistencia);
}
void Reproducir (Animal* a1 , Animal* a2 , Animal* hijo ) {
    
}
void Combatir (Animal* a1 , Animal * a2 ) {

}
int Comparar (Animal* a1 , Animal * a2 ) {

}
void BorrarMundo (Animal** Mundo ) {

}
void MostrarMundo (Animal** Mundo ) {

}
void ReproduccionSimple (Animal* a1 , Animal* a2 , Animal* hijo ) {

}
void ReproduccionCruzada (Animal* a1 , Animal* a2 , Animal* hijo ) {

}
void ComerSiempre (Animal* a1 , Animal * a2 ) {

}
void HuirSiempre (Animal* a1 , Animal * a2 ) {

}
void ComerAleatorio (Animal* a1 , Animal * a2 ) {

}