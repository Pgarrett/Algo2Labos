#include <iostream>

#include "Pila.h"

Pila::Pila()
{
	prim = NULL;
	tam = 0;
}

Pila::~Pila()
{
	while (this->tamanio() != 0)
	{
		desapilar();
	}
}

void Pila::apilar(ElemPila& elem)
{
	Nodo* n = new Nodo;
	n->elem = elem;
	if (this->tam == 0)
	{
		n->sig = NULL;
	}
	else
	{
		n->sig = prim;
	}
	this->prim = n;
	n = NULL;
	delete n;
	this->tam++;
}

bool Pila::esVacia()
{
	return this->tam == 0;
}

ElemPila& Pila::tope()
{
	return this->prim->elem;
}

void Pila::desapilar()
{
	Nodo* antPrimero = this->prim;
	if (antPrimero != NULL) {
		Nodo* siguiente = antPrimero->sig;
		this->prim = siguiente;
		antPrimero = NULL;
		delete antPrimero;
		this->tam--;
	}
}

Nat Pila::tamanio() const
{
	return this->tam;
}

Pila& Pila::operator=(const Pila & aCopiar)
{
	int t = aCopiar.tam;
	ElemPila eps [t] = {};
	int i = 0;
	Nodo* n = aCopiar.prim;
	while (i < t)
	{
		eps[i] = n->elem;
		n = n->sig;
		i++;
	}
	i--;
	while (i >= 0)
	{
		this->apilar(eps[i]);
		i--;
	}
	return *this;
}

void Pila::mostrar(ostream& os) const
{
	os << "[";
	unsigned long i = 0;
	unsigned long t = this->tam;
	Nodo* aMostrar = this->prim;
	while (i < t)
	{
		os << aMostrar->elem;
		if (i < t - 1) os << ", ";
		aMostrar = aMostrar->sig;
		i++;
	}
	aMostrar = NULL;
	delete aMostrar;
	os << "]";
}