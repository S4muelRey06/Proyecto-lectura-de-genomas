#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Comando
{
  string nombre;
  string uso;
  int parametros;
};

int validarParametros(string PALABRAS[], int total, Comando c[]);
int leer(string comando, string PALABRAS[]);
string minuscula(string a);

#endif
