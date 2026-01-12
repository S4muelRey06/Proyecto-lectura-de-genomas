#ifndef GENOMA_HXX
#define GENOMA_HXX

#include <fstream>
#include "genoma.h"
#include "secuencia.h"
vector<Secuencia>& Genoma::getSqnces() { 
  return sqnces; 
}
void Genoma:: setSqnces(vector<Secuencia> v) {
  sqnces = v; 
}

ArbolHuffman Genoma::getArbol(){
  return arbol;
}
void Genoma::setArbol(ArbolHuffman a){
  arbol = a;
} 
vector<string>& Genoma :: getCodigos(){
  return codigos;
}
void Genoma :: setCodigos(vector<string> v){
  codigos = v;
}
vector<char>& Genoma::getBasesPresentes(){
  return basesPresentes;
}
void Genoma::setBasesPresentes(vector<char> v){
  basesPresentes = v;
}
vector<long long>& Genoma::getFrecuencia(){
  return frecuencias;
}
void Genoma::setFrecuencia(vector<long long> v){
  frecuencias = v;
}

void Genoma::_es_subsecuencia_(string subsecuencia) {
  int contador = 0;

  if (sqnces.empty()) {
    cout << "No hay secuencias cargadas en memoria." << endl;
    return;
  }

    for (vector<Secuencia>::iterator it = sqnces.begin(); it != sqnces.end(); ++it) {
    contador += it->contarSubsecuencia(subsecuencia);
  }

  if (contador == 0) {
    cout << "La subsecuencia no existe dentro ninguna de las secuencias cargadas en memoria" << endl;
  } else {
    cout << "La subsecuencia se encuentra " << contador
         << " veces dentro de las secuencias guardadas en memoria" << endl;
  }
}

void Genoma::_enmascarar_(string subsecuencia) {
  vector<Secuencia>::iterator it;
  if (sqnces.empty()) {
    cout << "No hay secuencias cargadas en memoria." << endl;
    return;
  }

  int contador = 0;

    for (it = sqnces.begin(); it != sqnces.end(); ++it) {
    contador += it->enmascarar(subsecuencia);
  }

  if (contador == 0) {
    cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada" << endl;
  } else {
    cout << contador << " subsecuencia(s) han sido enmascaradas dentro de las secuencias cargadas en memoria." << endl;
  }
}

void Genoma::_codificar_(){
  basesPresentes.clear();
  codigos.clear();
  frecuencias.clear();
  char caracteres[] ={'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N', 'X', '-'};
      int contador=0;
      Secuencia s;
      vector<Secuencia>::iterator it;
      for (it = sqnces.begin(); it != sqnces.end(); it++){
              for (int i=0; i<18; i++){
                  contador=0;
                  contador=it->contarCaracter(caracteres[i]);
                  if (contador>0){
                    bool yaExiste = false;
                    for (int j = 0; j < basesPresentes.size(); j++) {
                        if (basesPresentes[j] == caracteres[i]) {
                            frecuencias[j] += contador; 
                            yaExiste = true;
                            break;
                        }
                    }
                    if (!yaExiste) {
                        basesPresentes.push_back(caracteres[i]);
                        frecuencias.push_back(contador);
                  } 
              }
          }
      }
  arbol.generar(basesPresentes, frecuencias);
  codigos.resize(basesPresentes.size(), "");
  obtenerCodigos(arbol.getRaiz(), "");
  }

void Genoma::obtenerCodigos(NodoHuffman* nodo, string codigoActual) {
    if (nodo == NULL) {
        return;
    }
    if (nodo->esHoja()) {
        for (size_t i = 0; i < basesPresentes.size(); i++) {
            if (basesPresentes[i] == nodo->obtenerDato()) {
                codigos[i] = codigoActual;
                break;
            }
        }
    } else {
        obtenerCodigos(nodo->obtenerHijoIzq(), codigoActual + "0");
        obtenerCodigos(nodo->obtenerHijoDer(), codigoActual + "1");
    }
}


#endif