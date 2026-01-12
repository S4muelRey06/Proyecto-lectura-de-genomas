#ifndef __ARBOLHUFFMAN_H__
#define __ARBOLHUFFMAN_H__

#include "NodoHuffman.h"
#include <vector>
class ArbolHuffman
{
protected:
    NodoHuffman *raiz;

public:
    ArbolHuffman();
    ~ArbolHuffman();
    NodoHuffman *getRaiz();
    bool esVacio();
    int datoRaiz();
    int altura();
    int altura(NodoHuffman *nodo);
    unsigned int tamano();
    unsigned int tamano(NodoHuffman *nodo);
    void generar(vector<char> &bases, vector<long long> &frecuencias);
    void preOrden();
    void preOrden(NodoHuffman *nodo);
};
#include "ArbolHuffman.hxx"
#endif