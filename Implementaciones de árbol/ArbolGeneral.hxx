#include "ArbolGeneral.h"
#include <queue>
using namespace std;
template <class T>

ArbolGeneral<T>::ArbolGeneral()
{
    this->raiz = NULL;
}
template <class T>
ArbolGeneral<T>::ArbolGeneral(T val)
{
    NodoGeneral<T> *nodo = new NodoGeneral<T>;
    nodo->fijarDato(val);
    this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral()
{
    delete this->raiz;
    this->raiz = NULL;
}
template <class T>
bool ArbolGeneral<T>::esVacio()
{
    return this->raiz == NULL;
}
template <class T>
NodoGeneral<T> *ArbolGeneral<T>::obtenerRaiz()
{
    return this->raiz;
}
template <class T>

void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T> *nraiz)
{
    this->raiz = nraiz;
}
template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n)
{
    bool ok = false;
    if (this->esVacio())
    {
        NodoGeneral<T> *nodo = new NodoGeneral<T>;
        nodo->fijarDato(n);
        this->fijarRaiz(nodo);
        ok = true;
    }
    else
    {
        return insertarNodo(this->raiz, padre, n);
    }
    return ok;
}
template <class T>
bool ArbolGeneral<T>::insertarNodo(NodoGeneral<T> *nodo, T padre, T n)
{
    bool adicionado = false;
    if (nodo->obtenerDato() == padre)
    {
        nodo->adicionarDesc(n);
        adicionado = true;
    }
    else
    {
        typename list<NodoGeneral<T> *>::iterator it;
        for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
        {
            adicionado = this->insertarNodo(*it, padre, n);
            if (adicionado)
            {
                break;
            }
        }
    }
    return adicionado;
}

template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n)
{

    bool eliminado = false;
    if (this->esVacio())
    {
        return eliminado;
    }
    else if (this->raiz->obtenerDato() == n)
    {
        delete this->raiz;
        this->raiz = NULL;
        eliminado = true;
        return eliminado;
    }
    else
    {
        return eliminarNodo(this->raiz, n);
    }
}
template <class T>
bool ArbolGeneral<T>::eliminarNodo(NodoGeneral<T> *nodo, T n)
{
    bool eliminado = false;
    typename list<NodoGeneral<T> *>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
        if ((*it)->obtenerDato() == n)
        {
            delete *it;
            nodo->desc.erase(it);
            eliminado = true;
            break;
        }
        else
        {
            eliminado = this->eliminarNodo(*it, n);
            if (eliminado)
            {
                break;
            }
        }
    }
    return eliminado;
}

template <class T>
bool ArbolGeneral<T>::buscar(T n)
{
    if (this->esVacio())
    {
        return false;
    }
    else
    {
        return buscar(this->raiz, n);
    }
}

template <class T>
bool ArbolGeneral<T>::buscar(NodoGeneral<T> *nodo, T n)
{
    // Si el arbol no está vacío:
    // comparo dato en el nodo actual con dato parametro
    // si es ese retorno true, si no moverme en los hijos y hacer el llamado buscar
    bool encontrado = false;
    if (nodo->obtenerDato() == n)
    {
        encontrado = true;
    }
    else
    {
        typename list<NodoGeneral<T> *>::iterator it;
        for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
        {
            encontrado = this->buscar(*it, n);
            if (encontrado)
            {
                break;
            }
        }
    }
    return encontrado;
}

template <class T>
unsigned int ArbolGeneral<T>::tamano()
{
    if (this->esVacio())
    {
        return 0;
    }
    else
    {
        return this->tamano(this->raiz);
    }
    // Si el arbol está vacío: return 0
    // Para cada hijo llamo tamaño
    // uso acumulador, retorno el valor acumulado +1 para contame a mi mismo
}
template <class T>
unsigned int ArbolGeneral<T>::tamano(NodoGeneral<T> *nodo)
{
    unsigned int tam = 0;
    typename list<NodoGeneral<T> *>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
        tam = tam + tamano(*it);
    }
    return tam + 1;
}

template <class T>
int ArbolGeneral<T>::altura()
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
int ArbolGeneral<T>::altura(NodoGeneral<T> *nodo)
{
    int alt = -1;
    if (nodo->esHoja())
    {
        alt = 0;
    }
    else
    {
        int alth;
        typename list<NodoGeneral<T> *>::iterator it;
        for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
        {
            alth = this->altura(*it);
            if (alt < alth + 1)
            {
                alt = alth + 1;
            }
        }
    }
    return alt;
}
template <class T>
void ArbolGeneral<T>::preOrden()
{
    if (!this->esVacio())
    {
        this->preOrden(this->raiz);
    }
}
template <class T>
void ArbolGeneral<T>::preOrden(NodoGeneral<T> *nodo)
{
    cout << " " << nodo->obtenerDato() << " ";
    typename list<NodoGeneral<T> *>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
        this->preOrden(*it);
    }
}


template <class T>
void ArbolGeneral<T>::preOrden(Nodo *nodo)
{
    typename list<NodoGeneral<T> *>::iterator it;
    if (this.esHoja()){
        
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
        acumulador=acumulador+preorden(nodo)
    }
    return acumulador;
}
}
template <class T>
void ArbolGeneral<T>::posOrden()
{
    if (!this->esVacio())
    {
        this->posOrden(this->raiz);
    }
    // llamar a posorden sobre cada hijo
    // imprimir en pantalla el dato del nodo acrual
}
template <class T>
void ArbolGeneral<T>::posOrden(NodoGeneral<T> *nodo)
{
    typename list<NodoGeneral<T> *>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
        this->posOrden(*it);
    }
    cout << " " << nodo->obtenerDato() << " ";
}
template <class T>
void ArbolGeneral<T>::nivelOrden()
{
    queue<NodoGeneral<T> *> aux;
    typename list<NodoGeneral<T> *>::iterator it;

    aux.push(this->raiz);

    while (!aux.empty())
    {
        NodoGeneral<T> *actual = aux.front();
        aux.pop();

        cout << actual->obtenerDato() << " ";

        for (it = actual->desc.begin(); it != actual->desc.end(); ++it)
        {
            aux.push(*it);
        }
    }
}