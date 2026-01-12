#ifndef SISTEMA_H
#define SISTEMA_H

#include "genoma.h"
#include <string>
#include <vector>

class Sistema {
public:
  Genoma genoma;

  void _cargar_(string nombre_archivo);
  void _listar_secuencia_();
  void _histograma_(string descripcion);
  void _es_subsecuencia_(string subsecuencia);   
  void _enmascarar_(string subsecuencia);        
  void _guardar_(string nombre_archivo);
  void _codificar_(string nombre_archivo);
  void _decodificar_(string nombre_archivo);
  void _ruta_mas_corta_(string descripcion, int x, int y, int i, int j);
  void _base_remota_(string descripcion, int i, int j);
  Genoma getGenoma();
  void setGenoma(Genoma g);
};

#endif