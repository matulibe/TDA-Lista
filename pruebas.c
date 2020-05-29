#include "lista.h"
#include <stdio.h>
#define MAX 50

void mostrar_elemento(void* elemento, void* contador){
  if(elemento && contador)
    printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);

}


void probar_operaciones_lista(){
 lista_t* lista = lista_crear();

  char a='a', b='b', c='c', d='d', e='e', f='f', g='g', h='h', i='i', j='j', k='k', l='l', m='m', n='n', o='o', p='p', q='q', r='r', s='s', t='t';
  char u='u', v='v', w='w', x='x', y='y', z='z';

  lista_insertar(lista, &b);
  lista_insertar(lista, &c);
  lista_insertar(lista, &d);
  lista_insertar(lista, &f);
  lista_insertar(lista, &g);
  lista_insertar(lista, &h);
  lista_insertar(lista, &j);
  lista_insertar(lista, &k);
  lista_insertar(lista, &l);
  lista_insertar(lista, &n);
  lista_insertar(lista, &o);
  lista_insertar(lista, &p);
  lista_insertar_en_posicion(lista, &q, 100);
  lista_insertar_en_posicion(lista, &r, 56);
  lista_insertar_en_posicion(lista, &s, 344);
  lista_insertar_en_posicion(lista, &t, 110);
  lista_insertar_en_posicion(lista, &u, 500);
  lista_insertar_en_posicion(lista, &v, 570);
  lista_insertar_en_posicion(lista, &x, 408);
  lista_insertar_en_posicion(lista, &z, 34);
  lista_insertar_en_posicion(lista, &a, 0);
  lista_insertar_en_posicion(lista, &e, 4);
  lista_insertar_en_posicion(lista, &i, 8);
  lista_insertar_en_posicion(lista, &m, 12);
  lista_insertar_en_posicion(lista, &y, 23);
  lista_insertar_en_posicion(lista, &w, 22);
  lista_insertar_en_posicion(lista, &w, 55);

  lista_borrar(lista);

  printf("Elementos en la lista: ");
  for(size_t i=0;i<lista_elementos(lista);i++)
    printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));

  printf("\n\n");

  printf("Imprimo la lista usando el iterador externo: \n");
  lista_iterador_t* it = lista_iterador_crear(lista);
  while(lista_iterador_tiene_siguiente(it))
    printf("%c \n", *(char*)lista_iterador_siguiente(it));
  printf("\n\n");

  lista_iterador_destruir(it);

  int contador=0;
  printf("Imprimo la lista usando el iterador interno: \n");
  lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
  printf("\n");

  lista_destruir(lista);
}

void probar_operaciones_cola(){
  lista_t* cola = lista_crear();
  int numeros[MAX] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
  int tope = 26;
  for(int i = 0; i < tope; i++){
    lista_encolar(cola, &numeros[i]);
  }

  printf("\nDesencolo los numeros y los muestro: ");
  while(!lista_vacia(cola)){
    printf("%i ", *(int*)lista_primero(cola));
    lista_desencolar(cola);
  }
  printf("\n");
  lista_destruir(cola);
}

void probar_operaciones_pila(){
  lista_t* pila = lista_crear();
  char* algo="etnematcerroc olipased es";

  for(int i=0;algo[i]!= 0;i++){
    printf("Apilo %c\n", algo[i]);
    lista_apilar(pila, &algo[i]);
  }

  printf("\nDesapilo y muestro los elementos apilados: ");
  while(!lista_vacia(pila)){
    printf("%c", *(char*)lista_tope(pila));
    lista_desapilar(pila);
  }
  printf("\n");

  lista_destruir(pila);
}

int main(){

  printf("Pruebo que la lista se comporte como lista\n");
  probar_operaciones_lista();

  printf("\nPruebo el comportamiento de cola\n");
  probar_operaciones_cola();

  printf("\nPruebo el comportamiento de pila\n");
  probar_operaciones_pila();
  return 0;
}
