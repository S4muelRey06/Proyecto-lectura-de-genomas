#ifndef __ARBOLAVL_H__
#define __ARBOLAVL_H__

#include "nodoAVL.h"
using namespace std;
template <class T>
class ArbolAVL
{
protected:
    NodoAVL<T> *raiz;

public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio();
    T datoRaiz();
    int altura();
    int altura(NodoAVL<T> *nodo);
    unsigned int tamano();
    unsigned int tamano(NodoAVL<T> *nodo);
    bool insert(T val);
    bool erase(T val);
    bool buscar(T val);
    void preOrden();
    void preOrden(NodoAVL<T> *nodo);
    void inOrden();
    void inOrden(NodoAVL<T> *nodo);
    void posOrden();
    void posOrden(NodoAVL<T> *nodo);
    void nivelOrden();
    NodoAVL<T> *balancear(NodoAVL<T> *nodo);
    NodoAVL<T> *rotacionSimpleDer(NodoAVL<T> *y);
    NodoAVL<T> *rotacionSimpleIzq(NodoAVL<T> *x);
    NodoAVL<T> *rotacionDobleIzqDer(NodoAVL<T> *nodo);
    NodoAVL<T> *rotacionDobleDerIzq(NodoAVL<T> *nodo);
    NodoAVL<T> *insertarRec(NodoAVL <T> *nodo, T val, bool &insertado);
    NodoAVL<T> *eliminarRec(NodoAVL<T> *nodo, T val, bool &eliminado);
};
#include "ArbolAVL.hxx"
#endif