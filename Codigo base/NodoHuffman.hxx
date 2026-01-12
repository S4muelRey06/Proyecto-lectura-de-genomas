#include "NodoHuffman.h"

NodoHuffman::NodoHuffman() {
    this->dato = '\0';
    this->frecuencia = 0;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

NodoHuffman::NodoHuffman(char s, int f) {
    this->dato = s;
    this->frecuencia = f;
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

NodoHuffman::NodoHuffman(int f, NodoHuffman* izq, NodoHuffman* der) {
    this->dato = '\0';
    this->frecuencia = f;
    this->hijoIzq = izq;
    this->hijoDer = der;
}

NodoHuffman::~NodoHuffman() {
    this->hijoIzq = nullptr;
    this->hijoDer = nullptr;
}

char NodoHuffman::obtenerDato() {
    return this->dato;
}

void NodoHuffman::fijarDato(char s) {
    this->dato = s;
}

int NodoHuffman::obtenerFrecuencia() {
    return this->frecuencia;
}

void NodoHuffman::fijarFrecuencia(int f) {
    this->frecuencia = f;
}

NodoHuffman* NodoHuffman::obtenerHijoIzq() {
    return this->hijoIzq;
}

NodoHuffman* NodoHuffman::obtenerHijoDer() {
    return this->hijoDer;
}

void NodoHuffman::fijarHijoIzq(NodoHuffman* izq) {
    this->hijoIzq = izq;
}

void NodoHuffman::fijarHijoDer(NodoHuffman* der) {
    this->hijoDer = der;
}

bool NodoHuffman::esHoja() {
    return (this->hijoIzq == nullptr&& this->hijoDer == nullptr);
}
