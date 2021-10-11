#include "Animal.h"
#include <stdio.h>
#include <stdlib.h>

void CrearTransimperativer(Animal* a ){
    a = malloc(sizeof(Animal));
    char* orden_tipos[] = {"Fuerza", "Velocidad", "Resistencia"};
    char* tipo = malloc(sizeof(char));
    printf("Ingrese estadisticas del animal:\n");
    for (int i = 0; i < 3; i++){
        printf("%s (tipo a ingresar; e=int, f=float, c=char): ", orden_tipos[i]);
        scanf("%c", tipo);
        printf("Valor: ");
        void* p_valor;
        switch (*tipo){
            case 'e': ;
                int* i_valor;
                scanf("%d", i_valor);
                p_valor = malloc(sizeof(i_valor));
                p_valor = &i_valor;
                break;
            case 'f': ;
                float* f_valor;
                scanf("%f", f_valor);
                p_valor = malloc(sizeof(f_valor));
                p_valor = &f_valor;                
                break;
            case 'c': ;
                char* c_valor;
                scanf("%c", c_valor);
                p_valor = malloc(sizeof(c_valor));
                p_valor = &c_valor;
                break;
        }

        switch(i){
            case 0:
                a->fuerza = p_valor;
                a->tipo_fuerza = *tipo;
                break;
            case 1:
                a->velocidad = p_valor;
                a->tipo_velocidad = *tipo;
                break;
            case 2:
                a->resistencia = p_valor;
                a->tipo_resistencia = *tipo;
                break;
        }
    }
}
void Borrar (Animal* a ){
    free(a);
}
void MostrarAnimal (Animal* a ) {
    //Revisa esto despues weon, estoy bien seguro que lo va a explotar porque DUMB SHIT (tipos y wea).
    printf("Fuerza: %s\n", a->fuerza);
    printf("Velocidad: %s\n", a->velocidad);
    printf("Resistencia: %s\n", a->resistencia);
}
void Reproducir (Animal* a1 , Animal* a2 , Animal* hijo ) {
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
    int random = rand() % 2;
    if(random == 0){
        a1->comerHuir(a1,a2);
        MostrarAnimal(a1);
    }
    else{
        a2->comerHuir(a2,a1);
        MostrarAnimal(a2);
    }
}
int Comparar (Animal* a1 , Animal * a2 ) {
    //*************************************
    // Si el primer animal tiene mas atributos mayores se retorna 0, sino se retorna 1.
    //**************************************
    int contador = 0;
    int fuerza_1 = (a1->tipo_fuerza == 'c')? atoi((char*)a1->fuerza)/4 : *(int*)a1->fuerza;
    int fuerza_2 = (a2->tipo_fuerza == 'c')? atoi((char*)a2->fuerza)/4 : *(int*)a2->fuerza;
    contador = fuerza_1 > fuerza_2 ? contador + 1 : contador - 1;
    int vel_1 = (a1->tipo_velocidad == 'c')? atoi((char*)a1->velocidad)/4 : *(int*)a1->velocidad;
    int vel_2 = (a2->tipo_velocidad == 'c')? atoi((char*)a2->velocidad)/4 : *(int*)a2->velocidad;
    contador = (vel_1 > vel_2) ? contador + 1 : contador - 1;
    if(contador > 1){ //Optimizacion es mi pasion LOL
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
    for (int x = 0; x < 1000; x++){
        for (int y = 0; y < 1000; y++){
            free(&(Mundo[x][y]));
        }
        free(Mundo[x]);
    }
    free(Mundo);
}

void MostrarMundo (Animal** Mundo ) {
    for (int x = 0; x < 1000; x++){
        for (int y = 0; y < 1000; y++){
            if(&(Mundo[x][y]) != NULL){
                MostrarAnimal(&(Mundo[x][y]));
            }
        }
    }
}
void ReproduccionSimple (Animal* a1 , Animal* a2 , Animal* hijo ) {
    //*************************************
    // Si el valor que retorna es 0 entonces el animal hijo recibe
    // todo del animal a1, sino el animal hijo recibe todo del animal a2.
    //*************************************
    int resultado = Comparar(a1, a2);
    hijo = malloc(sizeof(Animal));
    if(resultado == 0){
        hijo->tipo_fuerza = a1->tipo_fuerza;
        hijo->fuerza = malloc(sizeof(a1->fuerza));
    }
}
void ReproduccionCruzada (Animal* a1 , Animal* a2 , Animal* hijo ) {

}
void ComerSiempre (Animal* a1 , Animal * a2 ) {

}
void HuirSiempre (Animal* a1 , Animal * a2 ) {

}
void ComerAleatorio (Animal* a1 , Animal * a2 ) {

}