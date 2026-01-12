#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__
#include <list>
using namespace std;
template <class T>
class NodoGeneral
{
public:
    T dato;
    list<NodoGeneral<T>*> desc;

public:
    NodoGeneral();
    ~NodoGeneral();
    T &obtenerDato();
    void fijarDato(T &val);
    void limpiarLista();
    void adicionarDesc(T &nval);
    bool eliminarDesc(T &val);
    bool esHoja();
};
#include "NodoGeneral.hxx"
#endif
