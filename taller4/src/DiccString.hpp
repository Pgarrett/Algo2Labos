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
                Nodo* getNode(const string clave, Nodo*& p, unsigned int step);
                void removeLeafNode(Nodo*& p, Nodo*& c, const string clave);
                void removeIntermediateValue(Nodo*& n);

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
//    this->claves;
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
        this->claves.remover(s);
    }
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    this->claves.insertar(clave);
    if (this->raiz == NULL) {
        this->raiz = new Nodo();
    }
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < clave.length(); i++) {
        int c = (int) clave[i];
        if (n->siguientes[c] == NULL) {
            n->siguientes[c] = new Nodo();
        }
        n = n->siguientes[c];
        if (i == clave.length() - 1) {
            T* v = new T();
            *v = significado;
            n->definicion = v;
        }
    }
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
        int c = (int) clave[i];
        n = n->siguientes[c];
        v = n->definicion;
    }
    return *v;
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    T* v;
    Nodo* n = this->raiz;
    for (int i = 0; i < clave.length(); i++) {
        int c = (int) clave[i];
        n = n->siguientes[c];
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
    Nodo* p = NULL;
	Nodo* n = getNode(clave, p, clave.length());
    if (isLeafNode(n)) {
        removeLeafNode(p, n, clave);
    } else {
        removeIntermediateValue(n);
    }
    this->claves.remover(clave);
}

template <typename T>
bool DiccString<T>::isLeafNode(const Nodo* n) const {
    for (unsigned int i = 0; i < 256; i++) {
        if (n->siguientes[i] != NULL) {
            return false;
        }
    }
    return true;
}

template <typename T>
typename DiccString<T>::Nodo* DiccString<T>::getNode(const string clave, Nodo*& p, unsigned int step) {
    Nodo* n = this->raiz;
    for (unsigned int i = 0; i < step; i++) {
        p = n;
        int c = (int)clave[i];
        n = n->siguientes[c];
    }
    return n;
}

template <typename T>
void DiccString<T>::removeLeafNode(Nodo*& p, Nodo*& c, const string clave) {
    int i = clave.length();
    while (i > 0) {
        if (isLeafNode(c)) {
            delete[] c->siguientes;
            c->siguientes = NULL;
//            T* v;
//            v = c->definicion;
//            delete v;
//            v = NULL;
            delete c;
            c = NULL;
        }
        c = getNode(clave, p, i);
        i--;
    }
}

template <typename T>
void DiccString<T>::removeIntermediateValue(Nodo*& n) {
    T* v;
    v = n->definicion;
    delete v;
}

#endif
