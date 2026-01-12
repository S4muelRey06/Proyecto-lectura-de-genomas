#ifndef __NODOHUFFMAN_H__
#define __NODOHUFFMAN_H__

using namespace std;

class NodoHuffman {
protected:
    char dato;
    int frecuencia;                   
    NodoHuffman* hijoIzq;     
    NodoHuffman* hijoDer;      

public:
    NodoHuffman();
    NodoHuffman(char d, int f);
    NodoHuffman(int f, NodoHuffman* izq, NodoHuffman* der);
    ~NodoHuffman();
    char obtenerDato();
    void fijarDato(char dato);
    int obtenerFrecuencia();
    void fijarFrecuencia(int f);
    NodoHuffman* obtenerHijoIzq();
    NodoHuffman* obtenerHijoDer();
    void fijarHijoIzq(NodoHuffman* izq);
    void fijarHijoDer(NodoHuffman* der);
    bool esHoja();
};

#include "NodoHuffman.hxx"
#endif
