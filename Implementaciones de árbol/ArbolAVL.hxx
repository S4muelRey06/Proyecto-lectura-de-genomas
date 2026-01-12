#include "ArbolAVL.h"
#include <queue>
using namespace std;
template <class T>
ArbolAVL<T>::ArbolAVL()
{
    this->raiz = NULL;
}
template <class T>
ArbolAVL<T>::~ArbolAVL()
{
    if (this->raiz != NULL)
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
bool ArbolAVL<T>::esVacio()
{
    return this->raiz == NULL;
}

template <class T>
T ArbolAVL<T>::datoRaiz()
{
    return (this->raiz)->obtenerDato();
}

template <class T>
int ArbolAVL<T>::altura()
{
    if (this->esVacio())
    {
        return -1;
    }
    else
    {
        return altura(this->raiz);
    }
}
template <class T>
int ArbolAVL<T>::altura(NodoAVL<T> *nodo)
{
    int valt;
    if (nodo->esHoja())
    {
        valt = 0;
    }
    else
    {
        int alt_izq = -1;
        int alt_der = -1;
        if (nodo->obtenerHijoIzq() != NULL)
        {
            alt_izq = altura(nodo->obtenerHijoIzq());
        }
        if (nodo->obtenerHijoDer() != NULL)
        {
            alt_der = altura(nodo->obtenerHijoDer());
        }
        if (alt_izq > alt_der)
        {
            valt = alt_izq + 1;
        }
        else
        {
            valt = alt_der + 1;
        }
    }
    return valt;
}

template <class T>
unsigned int ArbolAVL<T>::tamano()
{
    if (this->esVacio())
    {
        return 0;
    }
    else
    {
        return this->tamano(this->raiz);
    }
}
template <class T>
unsigned int ArbolAVL<T>::tamano(NodoAVL<T> *nodo)
{
    unsigned int tam = 0;
    if (nodo->obtenerHijoIzq() != NULL)
    {
        tam = tam + tamano(nodo->obtenerHijoIzq());
    }
    if (nodo->obtenerHijoDer() != NULL)
    {
        tam = tam + tamano(nodo->obtenerHijoDer());
    }
    return tam + 1;
}

template <class T>
bool ArbolAVL<T>::erase(T val)
{
    NodoAVL<T> *nodo = this->raiz;
    NodoAVL<T> *padre = NULL;
    vector<NodoAVL<T> *> ancestros;

    // Buscar nodo iterativamente
    while (nodo != NULL && nodo->obtenerDato() != val)
    {
        ancestros.push_back(nodo);
        padre = nodo;

        if (val < nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoIzq();
        }
        else
        {
            nodo = nodo->obtenerHijoDer();
        }
    }

    if (nodo == NULL)
    {
        return false;
    }

    NodoAVL<T> *aEliminar = nodo;
    NodoAVL<T> *reemplazo = NULL;

    // Nodo con dos hijos: mayor de los menores
    if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL)
    {
        NodoAVL<T> *padreMax = nodo;
        NodoAVL<T> *maxIzq = nodo->obtenerHijoIzq();

        ancestros.push_back(maxIzq);

        while (maxIzq->obtenerHijoDer() != NULL)
        {
            padreMax = maxIzq;
            maxIzq = maxIzq->obtenerHijoDer();
            ancestros.push_back(maxIzq);
        }

        nodo->fijarDato(maxIzq->obtenerDato());
        aEliminar = maxIzq;
        reemplazo = maxIzq->obtenerHijoIzq();

        if (padreMax->obtenerHijoDer() == maxIzq)
        {
            padreMax->fijarHijoDer(reemplazo);
        }
        else
        {
            padreMax->fijarHijoIzq(reemplazo);
        }
    }
    // Nodo con un hijo o sin hijos
    else
    {
        if (nodo->obtenerHijoIzq() != NULL)
        {
            reemplazo = nodo->obtenerHijoIzq();
        }
        else
        {
            reemplazo = nodo->obtenerHijoDer();
        }

        if (padre == NULL)
        {
            this->raiz = reemplazo;
        }
        else
        {
            if (padre->obtenerHijoIzq() == nodo)
            {
                padre->fijarHijoIzq(reemplazo);
            }
            else
            {
                padre->fijarHijoDer(reemplazo);
            }
        }
    }

    // CORRECCIÓN: Remover aEliminar del vector ancestros
    typename vector<NodoAVL<T> *>::iterator it = ancestros.begin();
    while (it != ancestros.end())
    {
        if (*it == aEliminar)
        {
            it = ancestros.erase(it);
        }
        else
        {
            it++;
        }
    }

    delete aEliminar;

    if (this->raiz == NULL)
    {
        return true;
    }

    // Balancear ancestros desde abajo usando índices para mayor seguridad
    for (int i = ancestros.size() - 1; i >= 0; i--)
    {
        NodoAVL<T> *actual = ancestros[i];
        NodoAVL<T> *balanceado = balancear(actual);

        if (i > 0)
        {
            NodoAVL<T> *padreAct = ancestros[i-1];
            if (padreAct->obtenerHijoIzq() == actual)
            {
                padreAct->fijarHijoIzq(balanceado);
            }
            else
            {
                padreAct->fijarHijoDer(balanceado);
            }
        }
        else
        {
            this->raiz = balanceado;
        }
    }

    return true;
}

template <class T>
void ArbolAVL<T>::preOrden()
{
    if (!this->esVacio())
    {
        this->preOrden(this->raiz);
    }
}

template <class T>
void ArbolAVL<T>::preOrden(NodoAVL<T> *nodo)
{

    if (nodo != NULL)
    {
        cout << nodo->obtenerDato() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolAVL<T>::posOrden()
{
    if (!this->esVacio())
    {
        this->posOrden(this->raiz);
    }
}

template <class T>
void ArbolAVL<T>::posOrden(NodoAVL<T> *nodo)
{

    if (nodo != NULL)
    {
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        cout << nodo->obtenerDato() << " ";
    }
}
template <class T>
bool ArbolAVL<T>::buscar(T val)
{
    NodoAVL<T> *nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado)
    {
        if (val < nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoIzq();
        }
        else if (val > nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoDer();
        }
        else
        {
            encontrado = true;
        }
    }
    return encontrado;
}

template <class T>
void ArbolAVL<T>::inOrden()
{
    if (!this->esVacio())
    {
        this->inOrden(this->raiz);
    }
}
template <class T>
void ArbolAVL<T>::inOrden(NodoAVL<T> *nodo)
{
    if (nodo != NULL)
    {
        this->inOrden(nodo->obtenerHijoIzq());
        cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
template <class T>
void ArbolAVL<T>::nivelOrden()
{
    if (!this->esVacio())
    {
        std::queue<NodoAVL<T> *> aux;
        aux.push(this->raiz);
        NodoAVL<T> *nodo;
        while (!aux.empty())
        {
            nodo = aux.front();
            aux.pop();
            cout << nodo->obtenerDato() << " ";
            if (nodo->obtenerHijoIzq() != NULL)
            {
                aux.push(nodo->obtenerHijoIzq());
            }
            if (nodo->obtenerHijoDer() != NULL)
            {
                aux.push(nodo->obtenerHijoDer());
            }
        }
    }
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::balancear(NodoAVL<T>* nodo)
{
    if (nodo == NULL)
    {
        return NULL;
    }

    int altIzq;
    int altDer;

    if (nodo->obtenerHijoIzq() == NULL)
    {
        altIzq = -1;
    }
    else
    {
        altIzq = altura(nodo->obtenerHijoIzq());
    }

    if (nodo->obtenerHijoDer() == NULL)
    {
        altDer = -1;
    }
    else
    {
        altDer = altura(nodo->obtenerHijoDer());
    }

    int fb = altIzq - altDer;

    // Caso Izquierda - Izquierda o Izquierda - Derecha
    if (fb > 1)
    {
        int altIzqIzq;
        int altIzqDer;

        if (nodo->obtenerHijoIzq()->obtenerHijoIzq() == NULL)
        {
            altIzqIzq = -1;
        }
        else
        {
            altIzqIzq = altura(nodo->obtenerHijoIzq()->obtenerHijoIzq());
        }

        if (nodo->obtenerHijoIzq()->obtenerHijoDer() == NULL)
        {
            altIzqDer = -1;
        }
        else
        {
            altIzqDer = altura(nodo->obtenerHijoIzq()->obtenerHijoDer());
        }

        int fbIzq = altIzqIzq - altIzqDer;

        if (fbIzq >= 0)
        {
            return rotacionSimpleDer(nodo);
        }
        else
        {
            return rotacionDobleIzqDer(nodo);
        }
    }

    // Caso Derecha - Derecha o Derecha - Izquierda
    if (fb < -1)
    {
        int altDerIzq;
        int altDerDer;

        if (nodo->obtenerHijoDer()->obtenerHijoIzq() == NULL)
        {
            altDerIzq = -1;
        }
        else
        {
            altDerIzq = altura(nodo->obtenerHijoDer()->obtenerHijoIzq());
        }

        if (nodo->obtenerHijoDer()->obtenerHijoDer() == NULL)
        {
            altDerDer = -1;
        }
        else
        {
            altDerDer = altura(nodo->obtenerHijoDer()->obtenerHijoDer());
        }

        int fbDer = altDerIzq - altDerDer;

        if (fbDer <= 0)
        {
            return rotacionSimpleIzq(nodo);
        }
        else
        {
            return rotacionDobleDerIzq(nodo);
        }
    }

    return nodo;
}


template <class T>
bool ArbolAVL<T>::insert(T val)
{
     bool insertado = false;
    NodoAVL<T> *nodo = this->raiz;
    NodoAVL<T> *padre = NULL;
    vector<NodoAVL<T> *> ancestros;

    while (nodo != NULL)
    {
        padre = nodo;
        ancestros.push_back(nodo);

        if (val < nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoIzq();
        }
        else if (val > nodo->obtenerDato())
        {
            nodo = nodo->obtenerHijoDer();
        }
        else
        {
            return false;
        }
    }

    NodoAVL<T> *nuevo = new NodoAVL<T>(val);
    insertado = true;

    if (padre == NULL)
    {
        this->raiz = nuevo;
    }
    else
    {
        if (val < padre->obtenerDato())
        {
            padre->fijarHijoIzq(nuevo);
        }
        else
        {
            padre->fijarHijoDer(nuevo);
        }
    }
 
    for (typename vector<NodoAVL<T> *>::reverse_iterator it = ancestros.rbegin(); it != ancestros.rend(); it++)
    {
        NodoAVL<T> *actual = *it;
        NodoAVL<T> *balanceado = balancear(actual);

        typename vector<NodoAVL<T> *>::reverse_iterator padreIt = it + 1;
        if (padreIt != ancestros.rend())
        {
            NodoAVL<T> *padreAct = *padreIt;
            if (padreAct->obtenerHijoIzq() == actual)
            {
                padreAct->fijarHijoIzq(balanceado);
            }
            else
            {
                padreAct->fijarHijoDer(balanceado);
            }
        }
        else
        {
            this->raiz = balanceado;
        }
    } 

    return insertado;
}



template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionSimpleDer(NodoAVL<T> *n2)
{
    NodoAVL<T> *n1 = n2->obtenerHijoIzq();
    n2->fijarHijoIzq(n1->obtenerHijoDer());
    n1->fijarHijoDer(n2);


    return n1;
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionSimpleIzq(NodoAVL<T> *n1)
{
    NodoAVL<T> *n2 = n1->obtenerHijoDer();
    n1->fijarHijoDer(n2->obtenerHijoIzq());
    n2->fijarHijoIzq(n1);

    return n2;
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionDobleIzqDer(NodoAVL<T> *nodo)
{
    nodo->fijarHijoIzq(rotacionSimpleIzq(nodo->obtenerHijoIzq()));
    return rotacionSimpleDer(nodo);
}

template <class T>
NodoAVL<T> *ArbolAVL<T>::rotacionDobleDerIzq(NodoAVL<T> *nodo)
{
    nodo->fijarHijoDer(rotacionSimpleDer(nodo->obtenerHijoDer()));
    return rotacionSimpleIzq(nodo);
}
//LA RELACIÓN ES UN VIAJE, NO UN DESTINO.