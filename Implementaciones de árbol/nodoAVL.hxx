#include "nodoAVL.h"

template <class T>
NodoAVL<T>::NodoAVL()
{
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
}
template <class T>
NodoAVL<T>::NodoAVL(T val)
{
    this->hijoDer = NULL;
    this->hijoIzq = NULL;
    this->dato = val;
}
template <class T>
NodoAVL<T>::~NodoAVL()
{
    if (this->hijoIzq != NULL)
    {
        delete this->hijoIzq;
        this->hijoIzq = NULL;
    }
    if (this->hijoDer != NULL)
    {
        delete this->hijoDer;
        this->hijoDer = NULL;
    }
}
template <class T>
T &NodoAVL<T>::obtenerDato()
{
    return this->dato;
}

template <class T>
void NodoAVL<T>::fijarDato(T val)
{
    this->dato = val;
}

template <class T>
NodoAVL<T> *NodoAVL<T>::obtenerHijoIzq()
{
    return this->hijoIzq;
}

template <class T>
NodoAVL<T> *NodoAVL<T>::obtenerHijoDer()
{
    return this->hijoDer;
}

template <class T>
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T> *izq)
{
    this->hijoIzq = izq;
}

template <class T>
void NodoAVL<T>::fijarHijoDer(NodoAVL<T> *der)
{
    this->hijoDer = der;
}

template <class T>
bool NodoAVL<T>::esHoja()
{
    return (this->hijoIzq == NULL && this->hijoDer == NULL);
}