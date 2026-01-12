#ifndef SECUENCIA_H
#define SECUENCIA_H
#include <vector>
#include <string>
#include <iostream>
#include "Grafo.h"
#include "coordenada.h"
using namespace std;

class Secuencia {
private:
  string name;
  vector<char>   bases;
  vector<short> lineWidths;
  Grafo<Coordenada> grafo;
  vector<vector<char>> matriz;
  vector<vector<int>> indices;

public:
  string getName();
  vector<vector<char>>& getMatriz();
  vector<vector<int>>& getIndices();
  Grafo<Coordenada>& getGrafo();
  void setName(string name);
  static vector<char> equivalencias(char c);
  vector<char>& getBases() { return bases; }
  void setBases(vector<char> v) { bases = v; }
  vector<short>& getLineWidths() { return lineWidths; }
  void setLineWidths(vector<short> v) { lineWidths = v; }
  int contarSubsecuencia(string subsecuencia);
  int enmascarar(string subsecuencia);
  int contarCaracter(char caracter);
  void generarMatriz();
  void generarGrafo();
  float calcularDistancia(int i, int j, int x, int y);
  
};
#endif