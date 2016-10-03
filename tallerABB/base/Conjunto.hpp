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

//    unsigned int countChildren(Nodo *n) const;

    void deleteTwoChildrenNode(Nodo *&father, Nodo *&child);

    void deleteOneChildNode(Nodo *&father, Nodo *&child);

    void deleteLeafNode(Nodo *&father, Nodo *&child);

    void deleteTwoChildrenRoot(Nodo *&father, Nodo *&child);
    void inOrder(Nodo *&r, std::ostream &os) const;

};

template<class T>
Conjunto<T>::Nodo::Nodo(const T &v)
        : valor(v), izq(NULL), der(NULL) {}

template<class T>
Conjunto<T>::Conjunto() : raiz_(NULL), _cardinal(0) {}

template<class T>
Conjunto<T>::~Conjunto() {
    Nodo* r = this->raiz_;
    while (this->_cardinal != 0) {
        remover(r->valor);
        r = this->raiz_;
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
    Nodo *father;
    Nodo *child;
    find(clave, father, child);
    if (child != NULL) {
        if (hasTwoChildren(child)) {
            deleteTwoChildrenNode(father, child);
        } else if (hasOneChild(child)) {
            deleteOneChildNode(father, child);
        } else {
            deleteLeafNode(father, child);
        }
        if (child->valor == father->valor) {
            delete father;
            father = NULL;
            this->raiz_ = NULL;
        } else {
            delete child;
        }
        child = NULL;
    }
    this->_cardinal--;
}

template<class T>
const T &Conjunto<T>::minimo() const {
    Nodo* n = this->raiz_;
    Nodo* parent = n;
    n = n->izq;
    while (n != NULL) {
        parent = n;
        n = n->izq;
    }
    return parent->valor;
}

template<class T>
const T& Conjunto<T>::maximo() const {
    Nodo* n = this->raiz_;
    Nodo* parent = n;
    n = n->der;
    while (n != NULL) {
        parent = n;
        n = n->der;
    }
    return parent->valor;
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
    Nodo* n = this->raiz_;
    f = n;
    c = n;
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

//template<class T>
//unsigned int Conjunto<T>::countChildren(Nodo *n) const {
//    if (n == NULL) {
//        return 0;
//    }
//    return 1 + countChildren(n->izq) + countChildren(n->der);
//}

template<class T>
void Conjunto<T>::deleteTwoChildrenNode(Nodo *&father, Nodo *&child) {
    if (father->valor == child->valor) {
        deleteTwoChildrenRoot(father, child);
    } else {
        Nodo* lastNode;
        Nodo* n = child->izq;
        while (n != NULL) {
            lastNode = n;
            n = n->der;
        }
        Nodo* p;
        find(lastNode->valor, p, lastNode);
        if (hasOneChild(lastNode)) {
            deleteOneChildNode(p, lastNode);
        } else {
            deleteLeafNode(p, lastNode);
        }
        lastNode->der = child->der;
        lastNode->izq = child->izq;
        if (father->izq->valor == child->valor) {
            father->izq = lastNode;
        } else {
            father->der = lastNode;
        }
    }
}

template<class T>
void Conjunto<T>::deleteOneChildNode(Nodo *&father, Nodo *&child) {
    if (father->valor == child->valor) {
        if (child->izq != NULL) {
            this->raiz_ = new Nodo(child->izq->valor);
            this->raiz_->izq = child->izq->izq;
            this->raiz_->der = child->izq->der;
        } else {
            this->raiz_ = new Nodo(child->der->valor);
            this->raiz_->izq = child->der->izq;
            this->raiz_->der = child->der->der;
        }
    } else {
        Nodo* v;
        if (child->izq != NULL) {
            v = child->izq;
        } else {
            v = child->der;
        }
        if (father->izq != NULL) {
            if (father->izq->valor == child->valor) {
                father->izq = v;
            } else {
                father->der = v;
            }
        } else {
            if (father->der->valor == child->valor) {
                father->der = v;
            } else {
                father->izq = v;
            }
        }
    }
}

template<class T>
void Conjunto<T>::deleteLeafNode(Nodo *&father, Nodo *&child) {
    if (father->valor != child->valor) {
        if (father->izq->valor == child->valor) {
            father->izq = NULL;
        } else {
            father->der = NULL;
        }
    }
}

template<class T>
void Conjunto<T>::deleteTwoChildrenRoot(Nodo *&father, Nodo *&child) {
    Nodo* lastNode;
    Nodo* n = this->raiz_->izq;
    while (n != NULL) {
        lastNode = n;
        n = n->der;
    }
    Nodo* p;
    find(lastNode->valor, p, lastNode);
    if (hasOneChild(lastNode)) {
        deleteOneChildNode(p, lastNode);
    } else {
        deleteLeafNode(p, lastNode);
    }
    lastNode->der = father->der;
    lastNode->izq = father->izq;
    this->raiz_ = lastNode;
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

#endif // CONJUNTO_HPP_
