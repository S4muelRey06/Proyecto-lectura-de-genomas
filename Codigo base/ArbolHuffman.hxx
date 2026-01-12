#include "ArbolHuffman.h"
#include <iostream>
#include <queue>
#include <vector>

ArbolHuffman::ArbolHuffman() {
    raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman() {
    if (raiz != NULL) {
        vector<NodoHuffman*> pila;
        pila.push_back(raiz);

        while (!pila.empty()) {
            NodoHuffman* actual = pila.back();
            pila.pop_back();

            if (actual->obtenerHijoIzq() != NULL) {
                pila.push_back(actual->obtenerHijoIzq());
            }
            if (actual->obtenerHijoDer() != NULL) {
                pila.push_back(actual->obtenerHijoDer());
            }

            delete actual;
        }
    }
}
bool ArbolHuffman::esVacio()
{
    return this->raiz == nullptr;
}

int ArbolHuffman::datoRaiz()
{
    return (this->raiz)->obtenerFrecuencia();
}
NodoHuffman *ArbolHuffman::getRaiz()
{
    return this->raiz;
}
int ArbolHuffman::altura()
{
    if (this->esVacio())
    {
        return -1;
    }
    else
    {
        return altura(this->raiz);
    }
}

int ArbolHuffman::altura(NodoHuffman *nodo)
{
    int valt;
    if (nodo->esHoja())
    {
        valt = 0;
    }
    else
    {
        int alt_izq = -1;
        int alt_der = -1;
        if (nodo->obtenerHijoIzq() != NULL)
        {
            alt_izq = altura(nodo->obtenerHijoIzq());
        }
        if (nodo->obtenerHijoDer() != NULL)
        {
            alt_der = altura(nodo->obtenerHijoDer());
        }
        if (alt_izq > alt_der)
        {
            valt = alt_izq + 1;
        }
        else
        {
            valt = alt_der + 1;
        }
    }
    return valt;
}

unsigned int ArbolHuffman::tamano()
{
    if (this->esVacio())
    {
        return 0;
    }
    else
    {
        return this->tamano(this->raiz);
    }
}

unsigned int ArbolHuffman::tamano(NodoHuffman *nodo)
{
    unsigned int tam = 0;
    if (nodo->obtenerHijoIzq() != NULL)
    {
        tam = tam + tamano(nodo->obtenerHijoIzq());
    }
    if (nodo->obtenerHijoDer() != NULL)
    {
        tam = tam + tamano(nodo->obtenerHijoDer());
    }
    return tam + 1;
}

void ArbolHuffman::preOrden()
{
    if (!this->esVacio())
    {
        this->preOrden(this->raiz);
    }
}


void ArbolHuffman::preOrden(NodoHuffman *nodo)
{
    if (nodo != NULL)
    {
        cout<< nodo->obtenerDato() << ":" << nodo->obtenerFrecuencia() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}
void ArbolHuffman::generar(vector<char> &bases, vector<long long> &frecuencias) {
    for (int i = 0; i < frecuencias.size() - 1; i++) {
        for (int j = i + 1; j < frecuencias.size(); j++) {
            if (frecuencias[j] < frecuencias[i]) {
                int auxF = frecuencias[i];
                frecuencias[i] = frecuencias[j];
                frecuencias[j] = auxF;

                char auxC = bases[i];
                bases[i] = bases[j];
                bases[j] = auxC;
            }
        }
    }
    vector<NodoHuffman*> nodos;
    for (size_t i = 0; i < bases.size(); i++) {
        NodoHuffman* nuevo = new NodoHuffman(bases[i], frecuencias[i]);
        nodos.push_back(nuevo);
    }

    while (nodos.size() > 1) 
    
    {
        int min1 = 0;
        for (size_t i = 1; i < nodos.size(); i++) {
            if (nodos[i]->obtenerFrecuencia() < nodos[min1]->obtenerFrecuencia()) {
                min1 = i;
            }
        }

        
        int min2 = -1;
        for (size_t i = 0; i < nodos.size(); i++) {
            if (i != (size_t)min1) {
                if (min2 == -1) {
                    min2 = i;
                } else if (nodos[i]->obtenerFrecuencia() < nodos[min2]->obtenerFrecuencia()) {
                    min2 = i;
                }
            }
        }
        
        NodoHuffman* padre = new NodoHuffman('\0', nodos[min1]->obtenerFrecuencia() + nodos[min2]->obtenerFrecuencia());
        
        if (nodos[min1]->obtenerFrecuencia() < nodos[min2]->obtenerFrecuencia()) {
            padre->fijarHijoIzq(nodos[min2]);
            padre->fijarHijoDer(nodos[min1]);
        } else {
            padre->fijarHijoIzq(nodos[min1]);
            padre->fijarHijoDer(nodos[min2]);
        }
        
        if (min1 > min2) {
            nodos.erase(nodos.begin() + min1);
            nodos.erase(nodos.begin() + min2);
        } else {
            nodos.erase(nodos.begin() + min2);
            nodos.erase(nodos.begin() + min1);
        }

        nodos.push_back(padre);
    }
    if (nodos.size()==1){
    raiz = nodos[0];
}
}

