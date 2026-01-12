#include <iostream>
#include <vector>
#include "ArbolHuffman.h"

using namespace std;

int main() {
    // Ejemplo de bases y sus frecuencias
    vector<char> bases = {'A', 'C', 'G', 'T'};
    vector<int> frecuencias = {5, 9, 12, 13};

    // Crear el árbol de Huffman
    ArbolHuffman arbol;
    arbol.generar(bases, frecuencias);

    // Mostrar preorden
    cout << "Recorrido preorden del árbol de Huffman:" << endl;
    arbol.preOrden();

    // Mostrar altura
    cout << "Altura del árbol: " << arbol.altura() << endl;

    // Mostrar tamaño
    cout << "Tamaño del árbol: " << arbol.tamano() << endl;

    return 0;
}
