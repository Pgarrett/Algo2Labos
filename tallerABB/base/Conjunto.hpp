#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der; 
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;

	// funciones auxiliares

		void find(const T& key, Nodo* &f, Nodo* &c);
		bool isComplex(Nodo* child);
		bool isLeaf(Nodo* child);
		unsigned int countChilds(Nodo* n) const;

};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL)
{}

template <class T>
Conjunto<T>::~Conjunto()
{ 
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	Nodo* n = this->raiz_;
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

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	if (this->raiz_ == NULL) {
		this->raiz_ = new Nodo(clave);
	} else {
		Nodo* n = this->raiz_;
		while (n != NULL) {
			if (clave > n->valor) {
				n = n->der;
			} else {
				n = n->izq;
			}
		}
		n = new Nodo(clave);
	}
}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	unsigned int result = 1;
	Nodo* root = this->raiz_;
	if (root != NULL) {
		Nodo* right = root->der;
		Nodo* left = root->izq;
		result += countChilds(right);
		result += countChilds(left);
	}
	std::cout << "result: " << result << std::endl;
	return result;
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{
	Nodo* father;
	Nodo* child;
	find(clave, father, child);
	if (child != NULL) {
		if (isComplex(child)) {
		} else if (isLeaf(child)) {
		} else {
		}
	}
}

template <class T>
const T&  Conjunto<T>::minimo() const
{
	T t;
	Nodo* n = this->raiz_;
	while(n->izq != NULL) {
		t = n->valor;
		n = n->izq;
	}
	return t;
}

template <class T>
const T&  Conjunto<T>::maximo() const
{
	T t;
	Nodo* n = this->raiz_;
	while(n->der != NULL) {
		t = n->valor;
		n = n->der;
	}
	return t;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {

}

template <class T>
void Conjunto<T>::find(const T& key, Nodo* &f, Nodo* &c) {

}

template <class T>
bool Conjunto<T>::isComplex(Nodo* child) {
	return true;
}

template <class T>
bool Conjunto<T>::isLeaf(Nodo* child) {
	return true;
}

template <class T>
unsigned int Conjunto<T>::countChilds(Nodo* n) const {
	if (n == NULL) {
		return 0;
	}
	return 1 + countChilds(n->izq) + countChilds(n->der);
}
#endif // CONJUNTO_HPP_
