#ifndef __ARBOLBINARIOORD_H__
#define __ARBOLBINARIOORD_H__

#include "NodoBinario.h"

template <class T>
class ArbolBinarioOrd
{
protected:
    NodoBinario<T> *raiz;

public:
    ArbolBinarioOrd();
    ~ArbolBinarioOrd();
    bool esVacio();
    T datoRaiz();
    int altura();
    int altura(NodoBinario<T> *nodo);
    unsigned int tamano();
    unsigned int tamano(NodoBinario<T> *nodo);
    bool insertar(T val);
    bool eliminar(T val);
    bool buscar(T val);
    void preOrden();
    void preOrden(NodoBinario<T> *nodo);
    void inOrden();
    void inOrden(NodoBinario<T> *nodo);
    void posOrden();
    void posOrden(NodoBinario<T> *nodo);
    void nivelOrden();
};
#include "ArbolBinarioOrd.hxx"
#endif