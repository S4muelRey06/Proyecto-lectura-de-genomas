#include "ArbolBinarioOrd.h"
#include <queue>
using namespace std;
template <class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd()
{
    this->raiz = NULL;
}
template <class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd()
{
    if (this->raiz != NULL)
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
bool ArbolBinarioOrd<T>::esVacio()
{
    return this->raiz == NULL;
}

template <class T>
T ArbolBinarioOrd<T>::datoRaiz()
{
    return (this->raiz)->obtenerDato();
}

template <class T>
int ArbolBinarioOrd<T>::altura()
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
int ArbolBinarioOrd<T>::altura(NodoBinario<T> *nodo)
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
unsigned int ArbolBinarioOrd<T>::tamano()
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
unsigned int ArbolBinarioOrd<T>::tamano(NodoBinario<T> *nodo)
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
bool ArbolBinarioOrd<T>::insertar(T val)
{
    NodoBinario<T> *nodo = this->raiz;
    NodoBinario<T> *padre = this->raiz;
    bool insertado = false;
    bool duplicado = false;

    while (nodo != NULL && !duplicado)
    {
        padre = nodo;
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
            duplicado = true;
        }
    }

    if (!duplicado)
    {
        NodoBinario<T> *nuevo = new NodoBinario<T>(val);

        if (nuevo != NULL)
        {
            if (this->raiz == NULL)
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
        }
        insertado = true;
    }
    return insertado;
}

template <class T>
bool ArbolBinarioOrd<T>::eliminar(T val)
{
    NodoBinario<T> *nodo = this->raiz;
    NodoBinario<T> *padre = NULL;
    bool encontrado = false;

    // Buscar el nodo y su padre
    while (nodo != NULL && !encontrado)
    {
        padre = nodo;
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

    if (encontrado)
    {
        // Caso 1: nodo hoja
        if (nodo->esHoja())
        {
            if (nodo == this->raiz) // si es la raíz
            {
                delete this->raiz;
                this->raiz = NULL;
            }
            else if (padre->obtenerHijoIzq() == nodo)
            {
                padre->fijarHijoIzq(NULL);
                delete nodo;
            }
            else
            {
                padre->fijarHijoDer(NULL);
                delete nodo;
            }
        }
        // Caso 2: 1 solo hijo
        else if (nodo->obtenerHijoIzq() == NULL || nodo->obtenerHijoDer() == NULL)
        {
            NodoBinario<T> *hijo;
            if (nodo->obtenerHijoIzq() != NULL)
            {
                hijo = nodo->obtenerHijoIzq();
            }
            else if (nodo->obtenerHijoDer() != NULL)
            {
                hijo = nodo->obtenerHijoDer();
            }

            if (nodo == this->raiz)
            {
                delete this->raiz;
                this->raiz = hijo;
            }
            else if (padre->obtenerHijoIzq() == nodo)
            {
                padre->fijarHijoIzq(hijo);
                delete nodo;
            }
            else
            {
                padre->fijarHijoDer(hijo);
                delete nodo;
            }
        }
        // Caso 3: dos hijos
        else
        {
            NodoBinario<T> *padreMax = nodo;
            NodoBinario<T> *maxIzq = nodo->obtenerHijoIzq();
            while (maxIzq->obtenerHijoDer() != NULL)
            {
                padreMax = maxIzq;
                maxIzq = maxIzq->obtenerHijoDer();
            }

            nodo->fijarDato(maxIzq->obtenerDato());

            // Eliminar el máximo del subárbol izquierdo
            if (padreMax->obtenerHijoDer() == maxIzq)
            {
                if (maxIzq->obtenerHijoIzq() != NULL)
                {
                    padreMax->fijarHijoDer(maxIzq->obtenerHijoIzq());
                }
                else
                {
                    padreMax->fijarHijoDer(NULL);
                }
            }
            else
            {
                // significa que el máximo era el hijo izquierdo directo
                padreMax->fijarHijoIzq(maxIzq->obtenerHijoIzq());
            }

            delete maxIzq;
        }
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void ArbolBinarioOrd<T>::preOrden()
{
    if (!this->esVacio())
    {
        this->preOrden(this->raiz);
    }
}

template <class T>
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T> *nodo)
{
    if (nodo != NULL)
    {
        cout << nodo->obtenerDato() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolBinarioOrd<T>::posOrden()
{
    if (!this->esVacio())
    {
        this->posOrden(this->raiz);
    }
}

template <class T>
void ArbolBinarioOrd<T>::posOrden(NodoBinario<T> *nodo)
{

    if (nodo != NULL)
    {
        this->posOrden(nodo->obtenerHijoIzq());
        this->posOrden(nodo->obtenerHijoDer());
        cout << nodo->obtenerDato() << " ";
    }
}
template <class T>
bool ArbolBinarioOrd<T>::buscar(T val)
{
    NodoBinario<T> *nodo = this->raiz;
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
void ArbolBinarioOrd<T>::inOrden()
{
    if (!this->esVacio())
    {
        this->inOrden(this->raiz);
    }
}
template <class T>
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T> *nodo)
{
    if (nodo != NULL)
    {
        this->inOrden(nodo->obtenerHijoIzq());
        cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}
template <class T>
void ArbolBinarioOrd<T>::nivelOrden()
{
    if (!this->esVacio())
    {
        std::queue<NodoBinario<T> *> aux;
        aux.push(this->raiz);
        NodoBinario<T> *nodo;
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