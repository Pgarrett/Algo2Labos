#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares
                bool isLeafNode(const Nodo *child) const;
                Nodo* getNode(const string clave, unsigned int step);
                void removeLeafNode(Nodo*& c, const string clave, int index);
                void removeIntermediateValue(Nodo*& n);
                int charToInt(const char c) const;

                Nodo* raiz;
                Conj<string> claves;
};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {
    this->raiz = NULL;
    while (this->claves.cardinal() != 0) {
        string s = this->claves.minimo();
        this->Borrar(s);
    }
    Conj<string> c;
    c = d.claves;
    T v;
    while (c.cardinal() != 0 ) {
        v = d.Obtener(c.minimo());
        this->Definir(c.minimo(), v);
        c.remover(c.minimo());
    }
}

template <typename T>
DiccString<T>::~DiccString(){
    while (this->claves.cardinal() != 0) {
        string s = this->claves.minimo();
        this->Borrar(s);
    }
    delete this->raiz;
    this->raiz = NULL;
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    this->claves.insertar(clave);
    if (this->raiz == NULL) {
        this->raiz = new Nodo();
    }
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < clave.length(); i++) {
        unsigned int c = charToInt(clave[i]);
        if (n->siguientes[c] == NULL) {
            n->siguientes[c] = new Nodo();
        }
        n = n->siguientes[c];
    }
    if (n->definicion != NULL) {
        removeIntermediateValue(n);
    }
    n->definicion = new T(significado);
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    return this->claves.pertenece(clave);
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
	T* v;
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < clave.length(); i++) {
        n = n->siguientes[charToInt(clave[i])];
        v = n->definicion;
    }
    return *v;
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    T* v;
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < clave.length(); i++) {
        n = n->siguientes[charToInt(clave[i])];
        v = n->definicion;
    }
    return *v;
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return this->claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {
	Nodo* n = getNode(clave, clave.length());
    removeIntermediateValue(n);
    if (isLeafNode(n)) {
        int index = 0;
        Nodo* ultimoOcupado = raiz;
        Nodo* n1 = raiz;
        for(unsigned int i = 0; i < clave.length() - 1; i++) {
            n1 = n1->siguientes[charToInt(clave[i])];
            if(n->definicion != NULL || !isLeafNode(n1)) {
                ultimoOcupado = n1;
                index = i+1;
            }
        }
        removeLeafNode(ultimoOcupado, clave, index);
    }
    this->claves.remover(clave);
}

template <typename T>
bool DiccString<T>::isLeafNode(const Nodo* n) const {
    int result = 0;
    for (unsigned int i = 0; i < 256; i++) {
        if (n->siguientes[i] != NULL) {
            result++;
        }
    }
    return result == 0;
}

template <typename T>
typename DiccString<T>::Nodo* DiccString<T>::getNode(const string clave, unsigned int step) {
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < step; i++) {
        n = n->siguientes[charToInt(clave[i])];
    }
    return n;
}

template <typename T>
void DiccString<T>::removeLeafNode(Nodo*& c, const string clave, int index) {
    Nodo* aBorrar = c->siguientes[charToInt(clave[index])];
    c->siguientes[charToInt(clave[index])] = NULL;
    for(unsigned int i = index + 1; i < clave.length(); i++) {
        Nodo* siguiente = aBorrar->siguientes[charToInt(clave[i])];
        delete aBorrar;
        aBorrar = siguiente;
    }
    delete aBorrar;
}

template <typename T>
void DiccString<T>::removeIntermediateValue(Nodo*& n) {
    delete n->definicion;
    n->definicion = NULL;
}

template <typename T>
int DiccString<T>::charToInt(const char c) const {
    return (unsigned int) c;
}

#endif
