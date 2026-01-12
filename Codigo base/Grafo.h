#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Grafo
{
protected:
   vector<T> vertices;
   vector<vector<float>> matrizDeAdyacencia; //o la implemento como arreglo normal de 100x100?
   bool dirigido;

public:
    Grafo();
    Grafo(bool dirigido);
    bool esDirigido();
    void setDirigido(bool dirigido);
    vector< vector<float> >& obtenerMatrizDeAdyacencia();
    vector<T>& obtenerVertices();
    void agregarVertice(T v);
    void agregarArista(int origen, int destino, float peso);
    void preOrden(int inicio);
    void preOrdenRec(int inicio, vector<bool>& visitado);
    void recorridoVecindario(int inicio);
    vector<int> primModificado(int inicio, int limite, int productos);
    vector<int> prim(int inicio);
    vector<float> dijkstra(int inicio);
    vector<pair<int, int>> kruskal();
    pair<float, vector<int>>dijkstraConFin(int inicio, int fin);
};
#include "Grafo.hxx"
#endif