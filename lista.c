#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "lista.h"

#define EXITO 0
#define INICIO 0
#define ERROR -1
#define DIFERENCIA 2

typedef struct nodo{
  void* dato;
  struct nodo* siguiente;
}nodo_t;

struct lista{
  nodo_t* inicio;
  nodo_t* final;
  int cantidad;
};

struct lista_iterador{
  int cantidad;
  nodo_t* posicion;
  lista_t* lista;
};

void insertar(nodo_t* insertado, nodo_t* chequeado){
  insertado->siguiente = chequeado->siguiente;
  chequeado->siguiente = insertado;
}

void agregar_dato(nodo_t* nodo, void* elemento){
  if(!elemento){
    nodo->dato = NULL;
  }else{
    nodo->dato = elemento;
  }
}

int insertar_ultimo(lista_t* lista, nodo_t* nuevo, void* elemento){
  agregar_dato(nuevo, elemento);
  nuevo->siguiente = NULL;
  if(!lista->inicio){
    lista->inicio = nuevo;
    lista->final = nuevo;
  }else{
    nodo_t* ultimo = lista->final;
    ultimo->siguiente = nuevo;
    lista->final = nuevo;
  }
  lista->cantidad++;
  return EXITO;
}

int borrar_primero(lista_t* lista){
  nodo_t* aux = lista->inicio;
  lista->inicio = aux->siguiente;
  free(aux);
  lista->cantidad--;
  return EXITO;
}

lista_t* lista_crear(){
  lista_t* lista;
  lista = calloc(1, sizeof(lista_t));
  if(!lista){
    return NULL;
  }
  return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
  nodo_t* nuevo;
  if(!lista){
    return ERROR;
  }
  nuevo = malloc(sizeof(nodo_t));
  if(!nuevo){
    return ERROR;
  }
  return insertar_ultimo(lista, nuevo, elemento);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
  if(!lista || (int)(posicion) < INICIO){
    return ERROR;
  }
  int anterior = ((int)(posicion)-1);
  nodo_t* insertado = malloc(sizeof(nodo_t));
  if(!insertado){
    return ERROR;
  }
  agregar_dato(insertado, elemento);
  nodo_t* chequeado = lista->inicio;
  if((int)(posicion) == INICIO){
    insertado->siguiente = chequeado;
    lista->inicio = insertado;
    lista->cantidad++;
    return EXITO;
  }
  if(lista->cantidad < (int)(posicion)){
    return insertar_ultimo(lista, insertado, elemento);
  }
  for(int i = 0; i < anterior; i++){
    chequeado = (chequeado->siguiente);
  }
  insertar(insertado, chequeado);
  lista->cantidad++;
  return EXITO;
}

int lista_borrar(lista_t* lista){
  if(!lista || !lista->cantidad){
    return ERROR;
  }
  nodo_t* borrado;
  borrado = lista->final;
  nodo_t* final_nuevo;
  final_nuevo = lista->inicio;
  for(int i = 0; i < (lista->cantidad - DIFERENCIA); i++){
    final_nuevo =  final_nuevo->siguiente;
  }
  lista->final = final_nuevo;
  final_nuevo->siguiente = NULL;
  free(borrado);
  lista->cantidad--;
  if(lista->cantidad == 0){
    lista->inicio = NULL;
    lista->final = NULL;
  }
  return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista || !lista->cantidad){
    return ERROR;
  }
  if((lista->cantidad-1) <= (int)(posicion)){
    return lista_borrar(lista);
  }
  if((int)(posicion) == INICIO){
    return borrar_primero(lista);
  }
  int anterior = ((int)(posicion) - 1);
  nodo_t* buscador = lista->inicio;
  nodo_t* borrado;
  for(int i = 0; i < anterior; i++){
    buscador = buscador->siguiente;
  }
  borrado = buscador->siguiente;
  buscador->siguiente = borrado->siguiente;
  free(borrado);
  lista->cantidad--;
  return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
  if(!lista || (int)(posicion) >= lista->cantidad || (int)(posicion) < INICIO){
    return NULL;
  }
  if((lista->cantidad -1) == (int)(posicion)){
    return lista->final->dato;
  }
  nodo_t* buscado;
  buscado = lista->inicio;
  for(int i = 0; i < (int)(posicion); i++){
    buscado = buscado->siguiente;
  }
  return (void*)(buscado->dato);
}

void* lista_ultimo(lista_t* lista){
  if(!lista || lista->cantidad == 0){
    return NULL;
  }
  if(lista->final->dato == NULL){
    return NULL;
  }
  return lista->final->dato;
}

bool lista_vacia(lista_t* lista){
  if(lista == NULL){
    return true;
  }else if(lista->cantidad == 0){
    return true;
  }
  return false;
}

size_t lista_elementos(lista_t* lista){
  if(!lista){
    return (size_t)(NULL);
  }
  return (size_t)(lista->cantidad);
}

int lista_apilar(lista_t* lista, void* elemento){
  if(!lista){
    return ERROR;
  }
  nodo_t* nuevo;
  nuevo = malloc(sizeof(lista_t));
  if(!nuevo){
    return ERROR;
  }
  return insertar_ultimo(lista, nuevo, elemento);
}

int lista_desapilar(lista_t* lista){
  if(!lista){
    return ERROR;
  }
  if(lista->cantidad == 1){
    free(lista->inicio);
    lista->inicio = NULL;
    lista->cantidad--;
    return EXITO;
  }
  nodo_t* borrado;
  nodo_t* final_nuevo;
  borrado = lista->final;
  final_nuevo = lista->inicio;
  for(int i = 0; i < (lista->cantidad - DIFERENCIA); i++){
    final_nuevo = final_nuevo->siguiente;
  }
  final_nuevo->siguiente = NULL;
  lista->final = final_nuevo;
  free(borrado);
  lista->cantidad--;
  return EXITO;
}

void* lista_tope(lista_t* lista){
  if(!lista || !lista->inicio || !lista->final){
    return NULL;
  }
  return (void*)(lista->final->dato);
}

int lista_encolar(lista_t* lista, void* elemento){
  if(!lista){
    return ERROR;
  }
  nodo_t* nuevo = malloc(sizeof(nodo_t));
  if(!nuevo){
    return ERROR;
  }
  return insertar_ultimo(lista, nuevo, elemento);
}

int lista_desencolar(lista_t* lista){
  if(!lista){
    return ERROR;
  }
  return borrar_primero(lista);
}

void* lista_primero(lista_t* lista){
  if(!lista){
    return NULL;
  }
  return (void*)(lista->inicio->dato);
}

void destruir_nodos(nodo_t* borrado, int cantidad){
  nodo_t* auxiliar;
  for(int i = 0; i < cantidad; i++){
    auxiliar = borrado->siguiente;
    free(borrado);
    borrado = auxiliar;
  }
}

void lista_destruir(lista_t* lista){
  if(!lista){
    return;
  }
  nodo_t* borrado = lista->inicio;
  if(lista->inicio){
    destruir_nodos(borrado, lista->cantidad);
  }
  free(lista);
}

void lista_iterador_destruir(lista_iterador_t* iterador){
  free(iterador);
}

/*bool es_valido(){

}*/

lista_iterador_t* lista_iterador_crear(lista_t* lista){
  if(!lista){
    return NULL;
  }
  lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
  iterador->lista = lista;
  iterador->cantidad = lista->cantidad;
  return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
  if(iterador == NULL)
    return NULL;
  if(iterador->lista == NULL)
    return NULL;
  nodo_t* aux = iterador->posicion;
  if(aux == NULL){
    iterador->posicion = iterador->lista->inicio;
    return true;
  }
  if(!iterador->posicion->siguiente){
    return false;
  }
  iterador->posicion = aux->siguiente;
  return true;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador){
  if(iterador == NULL)
    return NULL;
  if(iterador->lista == NULL)
    return NULL;
  if(iterador->posicion == NULL)
    return NULL;

  nodo_t* devolucion = iterador->posicion;
  return (void*)(devolucion->dato);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto){
  if(!lista || !funcion){
    return;
  }
  nodo_t* posicion = lista->inicio;
  for(int i = 0; i < lista->cantidad; i++){
    funcion(posicion->dato, contexto);
    posicion = posicion->siguiente;
  }

}
