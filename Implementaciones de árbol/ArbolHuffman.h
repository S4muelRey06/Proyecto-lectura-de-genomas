#ifndef __ARBOLHUFFMAN_H__
#define __ARBOLHUFFMAN_H__

#include "NodoHuffman.h"

class ArbolHuffman
{
protected:
    NodoHuffman *raiz;

public:
    ArbolHuffman();
    ~ArbolHuffman();
    bool esVacio();
    int datoRaiz();
    int altura();
    int altura(NodoHuffman *nodo);
    unsigned int tamano();
    unsigned int tamano(NodoHuffman *nodo);
    void generar(vector<char> bases, vector<int> frecuencias);
    void preOrden();
    void preOrden(NodoHuffman *nodo);
};
#include "ArbolHuffman.hxx"
#endif