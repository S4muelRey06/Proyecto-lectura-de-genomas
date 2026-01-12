#include <iostream>
#include "ArbolGeneral.h"
#include "ArbolBinarioOrd.h"
#include "ArbolAVL.h"

using namespace std;

int main() {
    cout << "=== PRUEBAS ARBOL GENERAL ===" << endl;
    ArbolGeneral<int> ag(1);
    ag.insertarNodo(1, 2);
    ag.insertarNodo(1, 3);
    ag.insertarNodo(2, 4);
    ag.insertarNodo(2, 5);
    ag.insertarNodo(3, 6);

    cout << "PreOrden: ";
    ag.preOrden(); cout << endl;
    cout << "PosOrden: ";
    ag.posOrden(); cout << endl;
    cout << "NivelOrden: ";
    ag.nivelOrden(); cout << endl;
    cout << "Altura: " << ag.altura() << endl;
    cout << "Tamano: " << ag.tamano() << endl;
    cout << "Buscar 5: " << (ag.buscar(5) ? "Encontrado" : "No encontrado") << endl;
    ag.eliminarNodo(2);
    cout << "PreOrden tras eliminar 2: ";
    ag.preOrden(); cout << endl;

    cout << "\n=== PRUEBAS ARBOL BINARIO ORDENADO ===" << endl;
    ArbolBinarioOrd<int> abo;
    abo.insertar(50);
    abo.insertar(30);
    abo.insertar(70);
    abo.insertar(20);
    abo.insertar(40);
    abo.insertar(60);
    abo.insertar(80);

    cout << "InOrden (ordenado): ";
    abo.inOrden(); cout << endl;
    cout << "PreOrden: ";
    abo.preOrden(); cout << endl;
    cout << "PosOrden: ";
    abo.posOrden(); cout << endl;
    cout << "NivelOrden: ";
    abo.nivelOrden(); cout << endl;

    cout << "Altura: " << abo.altura() << endl;
    cout << "Tamano: " << abo.tamano() << endl;

    cout << "Buscar 40: " << (abo.buscar(40) ? "Encontrado" : "No encontrado") << endl;
    abo.eliminar(30);
    cout << "InOrden tras eliminar 30: ";
    abo.inOrden(); cout << endl;

    cout << "\n=== PRUEBAS AVL ===" << endl;
    ArbolAVL<int> avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30); // debe rotar
    avl.insert(25);
    avl.insert(28);

    cout << "InOrden (AVL): ";
    avl.inOrden(); cout << endl;
    cout << "PreOrden: ";
    avl.preOrden(); cout << endl;
    cout << "PosOrden: ";
    avl.posOrden(); cout << endl;
    cout << "NivelOrden: ";
    avl.nivelOrden(); cout << endl;
    cout << "Altura: " << avl.altura() << endl;
    cout << "Tamano: " << avl.tamano() << endl;

    cout << "Buscar 25: " << (avl.buscar(25) ? "Encontrado" : "No encontrado") << endl;

    cout << "Eliminar 20" << endl;
    avl.erase(20);
    cout << "InOrden tras eliminar 20: ";
    avl.inOrden(); cout << endl;

    cout << "\n=== PRUEBAS EXTREMAS AVL ===" << endl;

    // Caso ascendente
    ArbolAVL<int> avlAsc;
    avlAsc.insert(1);
    avlAsc.insert(2);
    avlAsc.insert(3);
    avlAsc.insert(4);
    avlAsc.insert(5);
    cout << "Ascendente (esperado 1 2 3 4 5): ";
    avlAsc.inOrden(); cout << endl;

    // Caso descendente
    ArbolAVL<int> avlDesc;
    avlDesc.insert(5);
    avlDesc.insert(4);
    avlDesc.insert(3);
    avlDesc.insert(2);
    avlDesc.insert(1);
    cout << "Descendente (esperado 1 2 3 4 5): ";
    avlDesc.inOrden(); cout << endl;

    return 0;
}