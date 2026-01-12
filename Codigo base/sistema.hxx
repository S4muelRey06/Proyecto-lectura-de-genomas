#ifndef SISTEMA_HXX
#define SISTEMA_HXX

#include "sistema.h"
#include <fstream>
#include <algorithm>
#include <limits>
#include <cctype>
#include <cstring>

void Sistema::_cargar_(string nombre_archivo){
  genoma.getSqnces().clear();
  ifstream archivo(nombre_archivo);
  if (!archivo.is_open())
  {
    cout << nombre_archivo << " (Archivo erróneo): El archivo no se encuentra o no puede leerse" << endl;
    return;
  }
  string linea;
  Secuencia actual;
  while (getline(archivo, linea)){
    if (linea.empty())
      continue;

      if (linea[0] == '>'){
          if (!actual.getBases().empty() || !actual.getName().empty()){
            genoma.getSqnces().push_back(actual);
          }
          actual = Secuencia();
          string header = linea.substr(1);
          if (!header.empty() && header.back() == '\r') {
              header.pop_back();
          }
          actual.setName(header);

      }

    else{
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (linea.empty())
            continue;


      for (int i = 0; i < (short)linea.size(); i++){
        actual.getBases().push_back(linea.at(i));
      }
        actual.getLineWidths().push_back(linea.size());  
    }
  }
        if (!actual.getBases().empty() || !actual.getName().empty()) {
      genoma.getSqnces().push_back(actual);
    }

  archivo.close();
  if (genoma.getSqnces().empty()){
    cout << nombre_archivo << " no contiene ninguna secuencia." << endl;
  }
  else if(genoma.getSqnces().size() == 1){
    cout << "Se cargó " << genoma.getSqnces().size() << " secuencia correctamente desde "<<nombre_archivo<< endl;
  }
  else
  {
    cout << "Se cargaron " << genoma.getSqnces().size() << " secuencias correctamente desde "<<nombre_archivo << endl;
  }
}

void Sistema::_listar_secuencia_() {
    if (genoma.getSqnces().empty()){
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }

    cout << "Hay " << genoma.getSqnces().size() << " secuencias cargadas en memoria:" << endl;

    for (vector<Secuencia>::iterator seqIt = genoma.getSqnces().begin(); seqIt != genoma.getSqnces().end(); ++seqIt) {

        vector<char> elegidas;  
        bool hayAmbigua = false;      

        for (vector<char>::iterator it = seqIt->getBases().begin();it != seqIt->getBases().end(); ++it) {

            char c = *it;

            vector<char> opciones;

            if (c=='A' || c=='C' || c=='G' || c=='T' || c=='U') {
                opciones.push_back(c);
            } else {
                vector<char> eq = Secuencia::equivalencias(c);
                if (!eq.empty()) {
                    hayAmbigua = true;
                    for (vector<char>::iterator e = eq.begin(); e != eq.end(); ++e) {
                        opciones.push_back(*e);
                    }
                } else {
                    continue;
                }
            }

            if (opciones.empty()){
                continue;
             }
            bool cubierta = false;
            for (vector<char>::iterator o = opciones.begin(); o != opciones.end() && !cubierta; o++) {
                for (vector<char>::iterator eg = elegidas.begin(); eg != elegidas.end(); eg++) {
                    if (*eg == *o) 
                    { 
                    cubierta = true; 
                    break; 
                    }
                }
            }
            if (!cubierta) {
                elegidas.push_back(opciones.front());
            }
        }
        
        cout << "Secuencia " << seqIt->getName() << " ";
        if (hayAmbigua) {
            cout << "al menos tiene " << elegidas.size() << " bases." << endl;
        } else {
            cout << "tiene " << elegidas.size() << " bases." << endl;
        }
    }
}

void Sistema::_histograma_(string descripcion){
    char caracteres[] ={'A','C','G','T','U','R','Y','K','M','S','W','B','D','H','V','N', 'X', '-'};
    int contador=0;
    vector<char> h;
    Secuencia s;
    string aux;
    bool encontrado=false;
    
    vector<Secuencia>::iterator it;
    for (it = genoma.getSqnces().begin(); it != genoma.getSqnces().end(); it++){
        aux=it->getName();
        if (aux==descripcion){
            s=*it;   
            encontrado=true;
            break;
        }
    }
    if (!encontrado){
        cout<<"Secuencia invalida"<<endl;
    }
    else{
    for (int i=0; i<18; i++){
        contador=s.contarCaracter(caracteres[i]);
        cout << caracteres[i] << ": " << contador <<  endl;  
    }
    }
}

void Sistema::_es_subsecuencia_(string subsecuencia){
  genoma._es_subsecuencia_(subsecuencia);
}

void Sistema::_enmascarar_(string subsecuencia){
  genoma._enmascarar_(subsecuencia);
}

void Sistema::_guardar_(string nombre_archivo) {
    if (genoma.getSqnces().empty()) {
        cout << "(no hay secuencias cargadas) No hay secuencias cargadas en memoria." << endl;
        return;
    }

    ofstream archivo(nombre_archivo); // modo texto
    if (!archivo.is_open()) {
        cout << "(problemas en archivo) Error guardando en " << nombre_archivo << "." << endl;
        return;
    }
        for (size_t i = 0; i < genoma.getSqnces().size(); ++i) {
            Secuencia &s = genoma.getSqnces()[i];
            archivo << ">" << s.getName() << "\n";

            vector<char> &bases = s.getBases();
            size_t pos = 0;

            if (!s.getLineWidths().empty()) {
                for (size_t k = 0; k < s.getLineWidths().size() && pos < bases.size(); ++k) {
                    size_t ancho = s.getLineWidths()[k];
                    size_t take = min(ancho, bases.size() - pos);

                 
                    for (size_t j = 0; j < take; ++j)
                        archivo << bases[pos + j];
                    archivo << "\n";
                    pos += take;
                }
                while (pos < bases.size()) {
                    size_t ancho = s.getLineWidths().back();
                    size_t take = min(ancho, bases.size() - pos);
                    for (size_t j = 0; j < take; ++j)
                        archivo << bases[pos + j];
                    archivo << "\n";
                    pos += take;
                }
            } else {
             
                size_t ancho = 80;
                while (pos < bases.size()) {
                    size_t take = min(ancho, bases.size() - pos);
                    for (size_t j = 0; j < take; ++j)
                        archivo << bases[pos + j];
                    archivo << "\n";
                    pos += take;
                }
            }
        }
        archivo.close();
        cout << "(escritura exitosa) Las secuencias han sido guardadas en "
             << nombre_archivo << "." << endl;
    }
Genoma Sistema::getGenoma() {
    return genoma;
}

void Sistema::setGenoma(Genoma g) {
    genoma = g;
}

void Sistema::_codificar_(string nombre_archivo) {
    if (genoma.getSqnces().empty()) 
    {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }

    genoma._codificar_();

    ofstream archivo(nombre_archivo, ios::binary);
    if (!archivo.is_open()) 
    {
        cout << "No se pueden guardar las secuencias en el archivo " << nombre_archivo << "." << endl;
        return;
    }

    short n = genoma.getBasesPresentes().size();
    archivo.write(reinterpret_cast<char*>(&n), sizeof(short));

    for (int i = 0; i < n; i++) 
    {
        archivo.write(&genoma.getBasesPresentes()[i], 1);
        long long f = genoma.getFrecuencia()[i];
        archivo.write(reinterpret_cast<char*>(&f), sizeof(long long));
    }

    int ns = genoma.getSqnces().size();
    archivo.write(reinterpret_cast<char*>(&ns), sizeof(int));

    for (int i = 0; i < ns; i++) 
    {
        string nombre = genoma.getSqnces()[i].getName();
        short li = nombre.size();
        archivo.write(reinterpret_cast<char*>(&li), sizeof(short));

        for (int j = 0; j < li; j++) 
        {
            archivo.write(&nombre[j], 1);
        }

        vector<char>& basesSeq = genoma.getSqnces()[i].getBases();
        long long wi = basesSeq.size();
        archivo.write(reinterpret_cast<char*>(&wi), sizeof(long long));

        short xi = 0;
        if (!genoma.getSqnces()[i].getLineWidths().empty()) 
        {
            xi = genoma.getSqnces()[i].getLineWidths()[0];
        }
        archivo.write(reinterpret_cast<char*>(&xi), sizeof(short));

        unsigned char byte = 0;
        int bitPos = 0;

        for (int j = 0; j < basesSeq.size(); j++) 
        {
            int pos = 0;
            while (genoma.getBasesPresentes()[pos] != basesSeq[j]) 
            {
                pos++;
            }

            string& code = genoma.getCodigos()[pos];

            for (int k = 0; k < code.size(); k++) 
            {
                if (code[k] == '1') 
                {
                    byte |= 1u << (7 - bitPos);
                }

                bitPos++;
                if (bitPos == 8) 
                {
                    archivo.write(reinterpret_cast<char*>(&byte), 1);
                    byte = 0;
                    bitPos = 0;
                }
            }
        }

        if (bitPos > 0) 
        {
            archivo.write(reinterpret_cast<char*>(&byte), 1);
        }
    }

    archivo.close();
    cout << "Secuencias codificadas y guardadas en " << nombre_archivo << endl;
}

void Sistema::_decodificar_(string nombre_archivo) {
    vector<Secuencia> tmp_sqnces;
    vector<char>      tmp_bases;
    vector<long long> tmp_frecs;

    ifstream in(nombre_archivo, ios::binary);
    if (!in.is_open()) {
        cout << "No se pueden cargar las secuencias desde " << nombre_archivo << "." << endl;
        return;
    }

    short n = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(short));
    if (!in.good() || n < 0) {
        cout << "No se pueden cargar las secuencias (cabecera de simbolos invalida)." << endl;
        in.close();
        return;
    }

    tmp_bases.resize(n);
    tmp_frecs.resize(n);

    for (int i = 0; i < n; ++i) {
        char c = 0;
        long long f = 0;
        in.read(reinterpret_cast<char*>(&c), sizeof(char));
        in.read(reinterpret_cast<char*>(&f), sizeof(long long));
        if (!in.good()) {
            cout << "No se pueden cargar las secuencias (lectura simbolos/frecuencias)." << endl;
            in.close();
            return;
        }
        tmp_bases[i] = c;
        tmp_frecs[i] = f;
    }

    ArbolHuffman ar;
    ar.generar(tmp_bases, tmp_frecs);
    NodoHuffman* raiz = ar.getRaiz();
    if (raiz == NULL) {
        cout << "No se pueden cargar las secuencias (arbol de Huffman vacio)." << endl;
        in.close();
        return;
    }

    int ns = 0;
    in.read(reinterpret_cast<char*>(&ns), sizeof(int));
    if (!in.good() || ns < 0) {
        cout << "No se pueden cargar las secuencias (cantidad de secuencias invalida)." << endl;
        in.close();
        return;
    }
    
    unsigned char byte_buf = 0;  
    int bit_pos = 8;             

    for (int si = 0; si < ns; ++si) {
        short li = 0;
        in.read(reinterpret_cast<char*>(&li), sizeof(short));
        if (!in.good() || li < 0) {
            cout << "No se pueden cargar las secuencias (longitud de nombre invalida)." << endl;
            in.close();
            return;
        }

        string nombre(li, '\0');
        if (li > 0) {
            in.read(&nombre[0], li * sizeof(char));
            if (!in.good()) {
                cout << "No se pueden cargar las secuencias (nombre)." << endl;
                in.close();
                return;
            }
        }
        bit_pos = 8; 

        long long wi = 0;
        short xi = 0;
        in.read(reinterpret_cast<char*>(&wi), sizeof(long long));
        in.read(reinterpret_cast<char*>(&xi), sizeof(short));
        if (!in.good() || wi < 0 || xi < 0) {
            cout << "No se pueden cargar las secuencias (wi/xi invalidos)." << endl;
            in.close();
            return;
        }

        Secuencia seq;
        seq.setName(nombre);
        vector<char>& out = seq.getBases();
        out.reserve(static_cast<size_t>(wi)); 

        if (raiz->esHoja()) {
            char unico = raiz->obtenerDato();
            for (long long k = 0; k < wi; ++k) {
                out.push_back(unico);
            }
        } else {
            for (long long k = 0; k < wi; ++k) {
                NodoHuffman* cursor = raiz;
                while (cursor != NULL && !cursor->esHoja()) {
                    if (bit_pos >= 8) {
                        if (!in.read(reinterpret_cast<char*>(&byte_buf), 1)) {
                            cout << "No se pueden cargar las secuencias (flujo binario invalido o truncado)." << endl;
                            in.close();
                            return;
                        }
                        bit_pos = 0;
                    }
                    int bit = ((byte_buf & (1u << (7 - bit_pos))) ? 1 : 0);
                    bit_pos++;

                    if (bit == 0) {
                        cursor = cursor->obtenerHijoIzq();
                    } else {
                        cursor = cursor->obtenerHijoDer();
                    }

                    if (cursor == NULL) {
                        cout << "No se pueden cargar las secuencias (ruta de bits invalida)." << endl;
                        in.close();
                        return;
                    }
                }

                if (cursor == NULL) {
                    cout << "No se pueden cargar las secuencias (cursor nulo)." << endl;
                    in.close();
                    return;
                }

                out.push_back(cursor->obtenerDato());
            }
        }

        if (bit_pos != 8) {
            bit_pos = 8;
        }

        if (xi > 0) {
            long long full = wi / xi;
            long long rem  = wi % xi;
            for (long long t = 0; t < full; ++t) {
                seq.getLineWidths().push_back(xi);
            }
            if (rem > 0) {
                seq.getLineWidths().push_back(static_cast<short>(rem));
            }
        } else {
            if (wi > 0) {
                seq.getLineWidths().push_back(static_cast<short>(wi));
            }
        }

        tmp_sqnces.push_back(seq);
    }

    in.close();

    genoma.getSqnces().clear();
    genoma.getBasesPresentes().clear();
    genoma.getFrecuencia().clear();
    genoma.getCodigos().clear();

    genoma.getSqnces() = tmp_sqnces;
    genoma.getBasesPresentes() = tmp_bases;
    genoma.getFrecuencia() = tmp_frecs;

    cout << "Secuencias decodificadas desde " << nombre_archivo << " y cargadas en memoria." << endl;
}

void Sistema::_ruta_mas_corta_(string descripcion, int i, int j, int x, int y){
    vector<Secuencia>::iterator it;
    string aux;
    for (it = genoma.getSqnces().begin(); it != genoma.getSqnces().end(); it++){
        aux=it->getName();
        if (aux==descripcion){
            
            it->generarMatriz();
            it->generarGrafo();
            if (i < 0 || i >= it->getMatriz().size() || j < 0 || j >= it->getMatriz()[0].size()){
                cout<<"La base en la posicion "<<i<<","<<j<<" no existe"<<endl;
                return;
            }
            if (x < 0 || x >= it->getMatriz().size() || y < 0 || y >= it->getMatriz()[0].size()){
                cout<<"La base en la posicion "<<x<<","<<y<<" no existe"<<endl;
                return;
            }
            cout<< "Para la secuencia "<< descripcion <<" el camino mas corto entre"<<it->getMatriz()[i][j]<<" y "<<it->getMatriz()[x][y]<<" es:"<<endl;
            int inicio = it->getIndices()[i][j];
            int fin = it->getIndices()[x][y];
            pair<float, vector<int>> resultado = it->getGrafo().dijkstraConFin(inicio, fin);
            float costo = resultado.first;
            vector<int> ruta = resultado.second;
            for (int k = ruta.size() - 1; k >= 0; k--){
                int v = ruta[k];
                cout<< it->getMatriz()[ it->getGrafo().obtenerVertices()[v].getX()][it->getGrafo().obtenerVertices()[v].getY()]<< ", ";
            }
            cout<<"El costo total es "<<costo<<endl;
            return;
            }
           }
    cout<<"La secuencia "<<descripcion<<" no existe"<<endl;
    }

void Sistema::_base_remota_(string descripcion, int i, int j){
    vector<Secuencia>::iterator it;
    string aux;
    pair<int,int> base_remota;
    vector<int> ruta_remota;
    float max_dist = 0;
    for (it = genoma.getSqnces().begin(); it != genoma.getSqnces().end(); it++){
        aux=it->getName();
        if (aux==descripcion){

            it->generarMatriz();
            it->generarGrafo();
            if (i < 0 || i >= it->getMatriz().size() || j < 0 || j >= it->getMatriz()[0].size()){
                cout<<"La base en la posicion "<<i<<","<<j<<" no existe"<<endl;
                return;
            }
            char base_origen = it->getMatriz()[i][j];
            int inicio = it->getIndices()[i][j];
            vector<pair<int,int>> posiciones_base;
            for (int x = 0; x < it->getMatriz().size(); x++){
                for (int y = 0; y < it->getMatriz()[x].size(); y++){
                    if (it->getMatriz()[x][y] == base_origen && !(x==i && y==j)){
                        posiciones_base.push_back({x,y});
                    }
                }
            }

            if (posiciones_base.empty()){
                cout<<"No hay base remota para la base "<<base_origen<<endl;
                return;
            }
            max_dist = -1;
            
            
            for (int idx = 0; idx < posiciones_base.size(); idx++){
                int x2 = posiciones_base[idx].first;
                int y2 = posiciones_base[idx].second;

                int fin = it->getIndices()[x2][y2]; // índice del nodo destino en el grafo

                pair<float, vector<int>> resultado = it->getGrafo().dijkstraConFin(inicio, fin);
                float costo = resultado.first;
                vector<int> ruta = resultado.second;

                // Si este candidato tiene mayor costo, actualizamos la base remota
                if (costo > max_dist){
                    max_dist = costo;
                    base_remota = posiciones_base[idx]; // coordenadas [x2, y2]
                    ruta_remota = ruta;                 // guardamos la ruta
                }
            }
            
        cout<<"Para la secuencia "<<descripcion
            <<", la base remota está ubicada en ["<<base_remota.first<<","<<base_remota.second<<"], "
            <<"y la ruta entre la base en ["<<i<<","<<j<<"] y la base remota es: ";

        for (int k = ruta_remota.size() - 1; k >= 0; k--){
            int v = ruta_remota[k];
            cout << it->getMatriz()[ it->getGrafo().obtenerVertices()[v].getX() ][ it->getGrafo().obtenerVertices()[v].getY() ] << ", ";
        }
        cout<<"El costo total de la ruta es "<<max_dist<<endl;
        return;
           }
    }
    cout<<"La secuencia "<<descripcion<<" no existe"<<endl;
    }
#endif