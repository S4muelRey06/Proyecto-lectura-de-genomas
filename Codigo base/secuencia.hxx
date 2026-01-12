#ifndef SECUENCIA_HXX
#define SECUENCIA_HXX
#include "secuencia.h"

string Secuencia::getName(){
    return this->name;
}
vector<char> Secuencia::equivalencias(char c) {
  switch (c) {
      case 'A': case 'C': case 'G': case 'T': case 'U': 
          return vector<char>{c};
      case 'R':  
          return vector<char>{'A','G'};
      case 'Y':  
          return vector<char>{'C','T'};
      case 'S':  
          return vector<char>{'G','C'};
      case 'W':  
          return vector<char>{'A','T'};
      case 'K':  
          return vector<char>{'G','T'};
      case 'M':  
          return vector<char>{'A','C'};
      case 'B':  
          return vector<char>{'C','G','T'};
      case 'D':  
          return vector<char>{'A','G','T'};
      case 'H':  
          return vector<char>{'A','C','T'};
      case 'V':  
          return vector<char>{'A','C','G'};
      case 'N':  
          return vector<char>{'A','C','G','T'};
      default:   
          return vector<char>{};
  }
}


int Secuencia::contarSubsecuencia(string subsecuencia){
  if (subsecuencia.empty()) 
      return 0;
  int contador = 0;

  for (vector<char>::iterator a = bases.begin(); a != bases.end(); ++a) {
      if ((bases.end() - a) < subsecuencia.size()) break;

      vector<char>::iterator b = a;
      bool coincide = true;

      for (size_t j = 0; j < subsecuencia.size(); j++, b++) {
          vector<char> P = Secuencia::equivalencias(subsecuencia[j]);
          vector<char> S = Secuencia::equivalencias(*b);

          bool inter = false;
          for (vector<char>::iterator ip = P.begin(); ip != P.end() && !inter; ip++) {
              for (vector<char>::iterator is = S.begin(); is != S.end(); is++) {
                  if (*ip == *is) 
                  {
                    inter = true; 
                   break; 
                  }
              }
          }
          if (!inter) { 
              coincide = false; 
              break; 
          }
      }
      if (coincide){   
       contador++;
      }
  }

  return contador;
}
void Secuencia::setName(string name){
    this->name = name;
}
int Secuencia::enmascarar(string subsecuencia){
  vector<char>::iterator a;
  vector<char>::iterator b;
  int contador=0;
  for (a = bases.begin(); a != bases.end(); a++){
    string comparar = "";
    b = a;
    if ((bases.end() - a) < subsecuencia.size()){
      continue;
    }
    for (int j = 0; j < subsecuencia.size(); b++, j++){
        comparar = comparar + *b;
    }
    if (comparar == subsecuencia){
    contador++;
    b=a;  
      for (int j = 0; j < subsecuencia.size(); j++,b++){
        *b = 'X';
      }
    }
  }
  return contador;
}
int Secuencia::contarCaracter(char caracter){
    int contador = 0;
    for (vector<char>::iterator it = bases.begin(); it != bases.end(); ++it){
        if (*it == caracter){
            contador++;  
    }
    }
    return contador;
}
vector<vector<char>>& Secuencia::getMatriz(){
    return matriz;
}
vector<vector<int>>& Secuencia::getIndices(){
    return indices;
}    

Grafo<Coordenada>& Secuencia::getGrafo(){
    return grafo;
}

void Secuencia::generarMatriz() {
    int index = 0; 
    matriz.clear();
    for (short width : lineWidths) {
        vector<char> fila;
        fila.reserve(width);
        for (int i = 0; i < width; i++) {
            if (index < bases.size()) {
                fila.push_back(bases[index++]);
            }
        }
        matriz.push_back(fila);
    }
    for (int i = 0; i < matriz.size(); i++) {
        cout << "Fila " << i << ": ";
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
}

void Secuencia::generarGrafo(){
    indices.clear();
    grafo = Grafo<Coordenada>(false);
    indices.resize(matriz.size());
    
    int indice=0;// Este lo puse aqui, porque es el que va a poner los numero en una matriz paralela, que indique que numero dentro del vector de vertices ocupa cada coordenada (o sea cada base XD)
    int distancia=0;
    for (int i = 0; i < matriz.size(); i++) {
        indices[i].resize(matriz[i].size());
        for (int j = 0; j < matriz[i].size(); j++) {
            Coordenada c1(i, j);
            grafo.agregarVertice(c1);
            indices[i][j] = indice++;
        }
    }
     for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz[i].size(); j++) {
                int v = indices[i][j];
                if (j + 1 < matriz[i].size()) {//derecha
                    int v2 = indices[i][j+1];
                    float distancia = calcularDistancia(i, j, i, j+1);
                    grafo.agregarArista(v, v2, distancia);
                    grafo.agregarArista(v2, v, distancia); 
                }    
                if (j - 1 >= 0) {//izquierda
                    int v2 = indices[i][j-1];
                    float distancia = calcularDistancia(i, j, i, j-1);
                    grafo.agregarArista(v, v2, distancia);
                    grafo.agregarArista(v2, v, distancia);
                }   
                if (i + 1 < matriz.size()) {//abajo
                    int v2 = indices[i+1][j];
                    float distancia = calcularDistancia(i, j, i+1, j);
                    grafo.agregarArista(v, v2, distancia);
                    grafo.agregarArista(v2, v, distancia);
                }
                if (i - 1 >= 0) {//arriba
                    int v2 = indices[i-1][j];
                    float distancia = calcularDistancia(i, j, i-1, j);
                    grafo.agregarArista(v, v2, distancia);
                    grafo.agregarArista(v2, v, distancia);
                }
            }
        }
    cout << "[DEBUG MATRIZ] (" ")\n";
    cout << "Filas = " << matriz.size() << "\n";
    cout << "Matriz generada:\n";

    for (int i = 0; i < matriz.size(); i++) {
        cout << "Fila " << i << ": ";
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
    
    cout << "[DEBUG] Matriz de índices:\n";
    for (int i = 0; i < indices.size(); i++) {
        cout << "Fila " << i << ": ";
        for (int j = 0; j < indices[i].size(); j++) {
            cout << indices[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "[DEBUG] Matriz de adyacencia (distancias):\n";

    for (int i = 0; i < grafo.obtenerMatrizDeAdyacencia().size(); i++) {
        for (int j = 0; j < grafo.obtenerMatrizDeAdyacencia()[i].size(); j++) {
            cout << grafo.obtenerMatrizDeAdyacencia()[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

float Secuencia::calcularDistancia(int i, int j, int x, int y){
    char a = matriz[i][j];
    char b = matriz[x][y];
    int num1 = (int)a;
    int num2 = (int)b;
    float resultado = 1.0f/(1+abs(num1-num2));
    cout<<resultado<<endl;
    return resultado;
}
#endif