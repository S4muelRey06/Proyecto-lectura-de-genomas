#include <iostream>
#include <string>
#include "comandos.h"
#include "genoma.hxx"
#include "sistema.h"
#include "sistema.hxx"

using namespace std;

//COMANDOS

int main() {
  Comando c[12] = {
      {"cargar", "cargar <nombre_archivo>", 1},
      {"listar_secuencias", "listar_secuencias", 0},
      {"histograma", "histograma <descripcion_secuencia>", 1},
      {"es_subsecuencia", "es_subsecuencia <subsecuencia>", 1},
      {"enmascarar", "enmascarar <subsecuencia>", 1},
      {"guardar", "guardar <nombre_archivo>", 1},
      {"codificar", "codificar <archivo.fabin>", 1},
      {"decodificar", "decodificar <archivo.fabin>", 1},
      {"ruta_mas_corta", " ruta_mas_corta <descripcion> i j x y", 5},
      {"base_remota", "base_remota <descripcion> i j", 3},
      {"ayuda", "ayuda [comando] o solamente ayuda para visualizar los comnandos", 1},
      {"salir", "salir", 0}};
  string PALABRAS[6];
  string palabra_aux;
  bool encontrado = false;
  Sistema g=Sistema();
  string comando = "";
  while (comando.compare("salir") != 0) {
    cout << "$";
    getline(cin, comando);
    int total = leer(comando, PALABRAS);
    PALABRAS[0] = minuscula(PALABRAS[0]);
    if (PALABRAS[0].compare("ayuda") == 0) {
      if (total == 1) {
        cout << "A continuación se presentan los comandos disponibles:\n";
        for (int i = 0; i < 12; i++) {
          cout << "- " << c[i].nombre << endl;
        }
      } else if (total == 2) {
        PALABRAS[1] = minuscula(PALABRAS[1]);
        bool encontrado = false;
        for (int i = 0; i < 12; i++) {
          if (PALABRAS[1] == c[i].nombre) {
            cout << "Uso correcto: " << c[i].uso << endl;
            encontrado = true;
            break;
          }
        }
        if (!encontrado) {
          cout << "Comando no reconocido. Escriba 'ayuda' para ver la lista de "
                  "  comandos.\n";
        }
      } else {
        cout << "Uso incorrecto. Escriba 'ayuda' o 'ayuda <comando>'\n";
      }
    } else {
      int validacion = validarParametros(PALABRAS, total, c);
      if (validacion == -1) {
        cout << "Comando no reconocido. Escriba 'ayuda' para ver la lista de "
                "comandos disponibles.\n";
      } else if (validacion == -2) {
        cout << "Error: Escribe 'ayuda [comando] ' para ver el uso y cantidad correcta de parametros del comando"<< endl;
      } else {
        switch (validacion) {
        case 0:
          g._cargar_(PALABRAS[1]);
          break;
        case 1:
          g. _listar_secuencia_(); 
          break;
        case 2:
          g._histograma_(PALABRAS[1]);
          break;
        case 3:
          g._es_subsecuencia_(PALABRAS[1]);
          break;
        case 4:
          g._enmascarar_(PALABRAS[1]);
          break;
        case 5:
          g._guardar_(PALABRAS[1]);
          break;
        case 6:
          g._codificar_(PALABRAS[1]);
          break;
        case 7:
          g._decodificar_(PALABRAS[1]);
          break;
        case 8:
          g._ruta_mas_corta_(PALABRAS[1], stoi(PALABRAS[2]), stoi(PALABRAS[3]), stoi(PALABRAS[4]), stoi(PALABRAS[5]));
          break;
        case 9:
          g._base_remota_(PALABRAS[1], stoi(PALABRAS[2]), stoi(PALABRAS[3])); 
          break;
        }
      }
    }
  }
}

int validarParametros(string PALABRAS[], int total, Comando c[]) {
  int valido = -1;
  string nombre;
  for (int i = 0; i < 12; i++) {
    if (PALABRAS[0].compare(c[i].nombre) == 0) {
      nombre = c[i].nombre;
      if ((total - 1) == c[i].parametros) {
        valido = i;
        break;
      } else {
        cout << "El comando " << nombre << " debe tener exactamente "
             << c[i].parametros << " parametros" << endl;
        valido = -2;
        break;
      }
    }
  }
  return valido;
}

int leer(string comando, string PALABRAS[]) {
  string palabra_aux;
  int total = 0;
  palabra_aux = "";
  for (int i = 0; i < comando.size(); i++) {
    if (comando[i] != ' ') {
      palabra_aux += comando[i];
    } else {
      if (!palabra_aux.empty() && total < 6) {
        PALABRAS[total] = palabra_aux;
        total++;
        palabra_aux = "";
      }
    }
  }
  if (!palabra_aux.empty() && total < 6) {
    PALABRAS[total] = palabra_aux;
    total++;
  }
  return total;
}

string minuscula(string a) {
  for (int i = 0; i < a.size(); i++) {
    a[i] = tolower(a[i]);
  }
  return a;
  
}