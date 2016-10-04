#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>

using namespace std;

template<class T>
class Conjunto {
public:

    // Constructor. Genera un conjunto vacío.
    Conjunto();

    // Destructor. Debe dejar limpia la memoria.
    ~Conjunto();

    // Inserta un elemento en el conjunto. Si éste ya existe,
    // el conjunto no se modifica.
    void insertar(const T &);

    // Decide si un elemento pertenece al conjunto o no.
    bool pertenece(const T &) const;

    // borra un elemento del conjunto. Si éste no existe,
    // el conjunto no se modifica.
    void remover(const T &);

    // devuelve el mínimo elemento del conjunto según <.
    const T &minimo() const;

    // devuelve el máximo elemento del conjunto según <.
    const T &maximo() const;

    // devuelve la cantidad de elementos que tiene el conjunto.
    unsigned int cardinal() const;

    // muestra el conjunto.
    void mostrar(std::ostream &) const;

    friend ostream &operator<<(ostream &os, const Conjunto<T> &c) {
        c.mostrar(os);
        return os;
    }

private:

    // la representación de un nodo interno.
    struct Nodo {
        // el constructor, toma el elemento al que representa el nodo.
        Nodo(const T &v);

        // el elemento al que representa el nodo.
        T valor;
        // puntero a la raíz del subárbol izq.
        Nodo *izq;
        // puntero a la raíz del subárbol der.
        Nodo *der;
    };

    // puntero a la raíz de nuestro árbol.
    Nodo *raiz_;
    unsigned int _cardinal;

    // funciones auxiliares

    void find(const T &key, Nodo *&f, Nodo *&c) const;

    bool hasTwoChildren(Nodo *child);

    bool hasOneChild(Nodo *child);

    void deleteTwoChildrenNode(Nodo *&father, Nodo *&child);

    void deleteOneChildNode(Nodo *&father, Nodo *&child);

    void deleteLeafNode(Nodo *&father, Nodo *&child);

    void deleteTwoChildrenRoot(Nodo *&father, Nodo *&child);
    void inOrder(Nodo *&r, std::ostream &os) const;
    void swapValues(Nodo* &p, Nodo* &q);

};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v)
        : valor(v), izq(NULL), der(NULL) {}

template<class T>
Conjunto<T>::Conjunto() : raiz_(NULL), _cardinal(0) {}

template<class T>
Conjunto<T>::~Conjunto() {
    while (this->_cardinal != 0) {
        remover(this->raiz_->valor);
    }
}

template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    Nodo *n = this->raiz_;
    bool exists = false;
    while (n != NULL && !exists) {
        if (n->valor == clave) {
            exists = true;
        } else if (clave > n->valor) {
            n = n->der;
        } else {
            n = n->izq;
        }
    }
    return exists;
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    if (this->raiz_ == NULL) {
        this->raiz_ = new Nodo(clave);
    } else {
        Nodo *n = this->raiz_;
        Nodo *father;
        bool goesL = false;
        while (n != NULL) {
            father = n;
            if (clave > n->valor) {
                n = n->der;
                goesL = false;
            } else {
                n = n->izq;
                goesL = true;
            }
        }
        if (goesL) {
            father->izq = new Nodo(clave);
        } else {
            father->der = new Nodo(clave);
        }
    }
    this->_cardinal++;
}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_cardinal;
}

template<class T>
void Conjunto<T>::remover(const T &clave) {
    Nodo *father = NULL;
    Nodo *child = NULL;
    find(clave, father, child);
    if (child != NULL) {
        if (hasTwoChildren(child)) {
            deleteTwoChildrenNode(father, child);
        } else if (hasOneChild(child)) {
            deleteOneChildNode(father, child);
        } else {
            deleteLeafNode(father, child);
        }
    }
    this->_cardinal--;
}

template<class T>
const T &Conjunto<T>::minimo() const {
    Nodo* n = this->raiz_;
    while (n->izq != NULL) {
        n = n->izq;
    }
    return n->valor;
}

template<class T>
const T& Conjunto<T>::maximo() const {
    Nodo* n = this->raiz_;
    while (n->der != NULL) {
        n = n->der;
    }
    return n->valor;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &os) const {
    os << "[";
    Nodo* r = this->raiz_;
    inOrder(r, os);
    os << "]";
}

template<class T>
void Conjunto<T>::find(const T &key, Nodo *&f, Nodo *&c) const{
    bool exists = false;
    f = this->raiz_;
    c = this->raiz_;
    while (c != NULL && !exists) {
        if (c->valor == key) {
            exists = true;
        } else if (key > c->valor) {
            f = c;
            c = c->der;
        } else {
            f = c;
            c = c->izq;
        }
    }
}

template<class T>
bool Conjunto<T>::hasTwoChildren(Nodo *child) {
    return child->izq != NULL && child->der != NULL;
}

template<class T>
bool Conjunto<T>::hasOneChild(Nodo *child) {
    return child->izq != NULL || child->der != NULL;
}

template<class T>
void Conjunto<T>::deleteTwoChildrenNode(Nodo *&father, Nodo *&child) {
//    if (father->valor == child->valor) {
//        deleteTwoChildrenRoot(father, child);
//    } else {
        Nodo* n = child->izq;
        while (n->der != NULL) {
            n = n->der;
        }
        Nodo* p = NULL;
        find(n->valor, p, n);
        swapValues(child, n);
        if (hasOneChild(n)) {
            deleteOneChildNode(p, n);
        } else {
            deleteLeafNode(p, n);
        }
//        if (father->izq->valor == child->valor) {
//            father->izq = n;
//        } else {
//            father->der = n;
//        }
//    }
}

template<class T>
void Conjunto<T>::deleteOneChildNode(Nodo *&father, Nodo *&child) {
    Nodo* n;
    if (child->der != NULL) {
        n = child->der;
    } else {
        n = child->izq;
    }
    if (child == raiz_){
        this->raiz_ = n;
    }else{
        if (father->der == child) {
            father->der = n;
        } else {
            father->izq = n;
        }
    }
    delete(child);
    child = NULL;
}

template<class T>
void Conjunto<T>::deleteLeafNode(Nodo *&father, Nodo *&child) {
    if (father->valor != child->valor) {
        if (father->izq != NULL) {
            if (father->izq->valor == child->valor) {
                father->izq = NULL;
            } else {
                father->der = NULL;
            }
        }
        delete(child);
        child = NULL;
    } else {
        delete(this->raiz_);
        this->raiz_ = NULL;
    }
}

template<class T>
void Conjunto<T>::deleteTwoChildrenRoot(Nodo *&father, Nodo *&child) {
    Nodo* n = this->raiz_->izq;
    while (n->der != NULL) {
        n = n->der;
    }
    Nodo* p = NULL;
    find(n->valor, p, n);
    if (hasOneChild(n)) {
        deleteOneChildNode(p, n);
    } else {
        deleteLeafNode(p, n);
    }
    this->raiz_ = n;
}

template<class T>
void Conjunto<T>::inOrder(Nodo *&r, std::ostream &os) const {
    if (r != NULL) {
        inOrder(r->izq, os);
        os << r->valor;
        if (r->valor != this->maximo()) {
            os << ", ";
        }
        inOrder(r->der, os);
    }
}

template <class T>
void Conjunto<T>::swapValues(Nodo* &p, Nodo* &q){
    T r = p->valor;
    p->valor = q->valor;
    q->valor = r;
}

#endif // CONJUNTO_HPP_
