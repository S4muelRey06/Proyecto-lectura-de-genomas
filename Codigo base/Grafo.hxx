#ifndef GRAFO_HXX
#define GRAFO_HXX
#include "Grafo.h"
#include <queue>
#include <stack>


template <class T>
Grafo<T>::Grafo() {
    dirigido = false;  
}

template <class T>
Grafo<T>::Grafo(bool dir) {
    dirigido = dir;  
}

template <class T>
void Grafo<T>::setDirigido(bool dirigido) {
        this->dirigido = dirigido;
}

template <class T>
bool Grafo<T>::esDirigido() {
        return dirigido;
}

template <class T>
vector<T>& Grafo<T>::obtenerVertices() {
    return vertices;
}

template<class T>
vector< vector<float> >& Grafo<T>::obtenerMatrizDeAdyacencia() {
    return matrizDeAdyacencia;
}
    
template<class T>
void Grafo<T>::agregarVertice(T v) {
    vertices.push_back(v);
    int n = vertices.size();
    matrizDeAdyacencia.resize(n);

    for (int i = 0; i < n; i++) {
        matrizDeAdyacencia[i].resize(n, 0.0);
    }
}

template <class T>
void Grafo<T>::agregarArista(int origen, int destino, float peso) {
    matrizDeAdyacencia[origen][destino] = peso;
    if (!dirigido) {
        matrizDeAdyacencia[destino][origen] = peso;
    }
}


template <class T>
void Grafo<T>::preOrden(int inicio) {
    if (vertices.empty() || inicio >= vertices.size()) {
        cout << "(grafo vacío o índice inválido)\n";
        return;
    }

    vector<bool> visitado(vertices.size(), false);
    preOrdenRec(inicio, visitado);
    cout << endl;
}

template <class T>
void Grafo<T>::preOrdenRec(int actual, vector<bool>& visitado) {
    if (visitado[actual]) return;

    // Visitar
    cout << vertices[actual] << " ";
    visitado[actual] = true;

    // Explorar hijos en orden natural
    for (int j = 0; j < matrizDeAdyacencia[actual].size(); j++) {
        if (matrizDeAdyacencia[actual][j] != 0 && !visitado[j]) {
            preOrdenRec(j, visitado);
        }
    }
}

template <class T>
void Grafo<T>::recorridoVecindario(int inicio){
    if (vertices.empty() || inicio >= vertices.size()) {
    cout << "grafo vacío o índice inválido";
    return;
}
        vector<bool> visitado(vertices.size(), false);
        queue<int> cola;
        cola.push(inicio);
        visitado[inicio] = true;

        while (!cola.empty()) {
            int indice = cola.front();
            cola.pop();

            cout <<"Estoy en "<< vertices[indice] << " ";

            for (int j = 0; j < matrizDeAdyacencia[indice].size(); j++) {
                if (matrizDeAdyacencia[indice][j] != 0 && !visitado[j]) {
                    visitado[j] = true;
                    cola.push(j);
                }
            }
        }
        cout << endl;
    }

template <class T>
vector<float> Grafo<T>::dijkstra(int inicio) {

    int n = vertices.size();
    vector<float> dist(n, 100);
    vector<bool> visitado(n, false);
    dist[inicio] = 0;
    for (int i = 0; i < n; i++) {
        float minimo = 100;
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && dist[v] < minimo) {
                minimo = dist[v];
                u = v;
            }
        }
        visitado[u] = true;
        for (int v = 0; v < n; v++) {
            if (matrizDeAdyacencia[u][v] != 0 && !visitado[v] && dist[u] + matrizDeAdyacencia[u][v] < dist[v]) {
                dist[v] = dist[u] + matrizDeAdyacencia[u][v];
            }
        }
    }
    return dist;   
}

template <class T>
pair<float, vector<int>> Grafo<T>::dijkstraConFin(int inicio, int fin) {
    int n = vertices.size();
    vector<float> dist(n, 10000);
    vector<bool> visitado(n, false);    
    vector<int> padre(n, -1);
    dist[inicio] = 0;
    for (int i = 0; i < n; i++) {
        float minimo = 10000;
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && dist[v] < minimo) {
                minimo = dist[v];
                u = v;
            }
        }
        visitado[u] = true;
        if (u==fin){
            break;
        }
        for (int v = 0; v < n; v++) {
           float peso = matrizDeAdyacencia[u][v];
           if (peso == 0){ 
              continue;          
           }
        if (!visitado[v] && dist[u] + peso < dist[v]) {
            dist[v] = dist[u] + peso;
            padre[v] = u;
        }
        }
    }
    vector<int> ruta;
    int actual = fin;
    while (actual != -1) {
        ruta.push_back(actual);
        actual = padre[actual];
    }
    return { dist[fin], ruta };   
}


template <class T>
vector<int> Grafo<T>::primModificado(int inicio, int limite, int productos) {

    int n = vertices.size();
    vector<bool> visitado(n, false);
    visitado[inicio] = true;
    vector<int> recorrido;
    recorrido.push_back(inicio);

    int productosEnRobot = 0;
    int productosRecogidos = 0; 
    int actual = inicio;


    while (productosRecogidos < productos) {  
        float menor = 1000;
        int siguiente = -1;

        for (int j = 0; j < n; j++) {
            if (!visitado[j] && matrizDeAdyacencia[actual][j] != 0 && matrizDeAdyacencia[actual][j] < menor) {
                menor = matrizDeAdyacencia[actual][j];
                siguiente = j;
            }
        }

        if (siguiente == -1){
            break;
        }

        visitado[siguiente] = true;
        productosEnRobot++;
        productosRecogidos++;
        recorrido.push_back(siguiente);
        actual = siguiente;

        if (productosEnRobot == limite) {
            recorrido.push_back(inicio);
            actual = inicio;
            productosEnRobot = 0;
        }
    }
    if (recorrido.back() != inicio)
        recorrido.push_back(inicio);

    return recorrido;
}

template <class T>
vector<int> Grafo<T>::prim(int inicio) {
    int n = vertices.size();
    vector<bool> visitado(n, false);
    vector<int> padre(n, -1);
    vector<float> llave(n, 100);
    llave[inicio] = 0;

    for (int i = 0; i < n - 1; i++) {
        float minimo = 100;
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && llave[v] < minimo) {
                minimo = llave[v];
                u = v;
            }
        }
        visitado[u] = true;
        for (int v = 0; v < n; v++) {
            if (matrizDeAdyacencia[u][v] != 0 && !visitado[v] && matrizDeAdyacencia[u][v] < llave[v]) {
                llave[v] = matrizDeAdyacencia[u][v];
                padre[v] = u;
            }
        }
    }
    vector<int> recorrido;
    for (int i = 0; i < n; i++) {
        if (padre[i] != -1)
            recorrido.push_back(i);
    }

    vector<pair<int,int>> mst;
    for(int i = 0; i < n; i++){
       if(padre[i] != -1)
        mst.push_back({padre[i], i});
    }
 

    return recorrido;
}
template <class T>
vector<pair<int,int>> Grafo<T>::kruskal() {

    int n = vertices.size();

    vector<int> componente(n);
    for (int i = 0; i < n; i++){
        componente[i] = i;
    }  

    vector<pair<int,int>> mst;
    int aristasTomadas = 0;
    while (aristasTomadas < n - 1) {
        float menor = 1000;
        int u = -1;
        int v = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrizDeAdyacencia[i][j] != 0 && componente[i] != componente[j] && matrizDeAdyacencia[i][j] < menor) {
                    menor = matrizDeAdyacencia[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        if (u == -1){
            break;
        }  
        mst.push_back(pair<int,int>(u, v));
        aristasTomadas++;

        int compU = componente[u];
        int compV = componente[v];
        for (int k = 0; k < n; k++) {
            if (componente[k] == compV)
                componente[k] = compU;
        }
    }

    return mst;
}
#endif
