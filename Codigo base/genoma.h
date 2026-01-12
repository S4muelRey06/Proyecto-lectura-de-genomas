#ifndef GENOMA_H
#define GENOMA_H
#include "secuencia.h"
#include "secuencia.hxx"
#include "ArbolHuffman.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Genoma {
private:
  vector<Secuencia> sqnces;
  ArbolHuffman arbol;
  vector<string> codigos;
  vector<char> basesPresentes;
  vector<long long> frecuencias;

public:
  vector<Secuencia>& getSqnces(); 
  void setSqnces(vector<Secuencia> v); 
  ArbolHuffman getArbol();
  void setArbol(ArbolHuffman a); 
  vector<string>& getCodigos();
  void setCodigos(vector<string> v);
  vector<char>& getBasesPresentes();
  void setBasesPresentes(vector<char> v);
  vector<long long>& getFrecuencia();
  void setFrecuencia(vector<long long> v);
  void _es_subsecuencia_(string subsecuencia);
  void _enmascarar_(string subsecuencia);
  void obtenerCodigos(NodoHuffman* nodo, string codigoActual); 
  void _codificar_();
};
#endif
