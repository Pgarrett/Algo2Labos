#include <iostream>

#include "Pila.h"

Pila::Pila()
{
	prim = NULL;
	tam = 0;
}

Pila::~Pila()
{
}

void Pila::apilar(ElemPila& elem)
{
	Nodo* n = new Nodo;
	n->elem = elem;
	if (tam == 0)
	{
		n->sig = NULL;
	}
	else
	{
		n->sig = prim;
	}
	this->prim = n;
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
	Nodo* siguiente = antPrimero->sig;
	this->prim = siguiente;
	antPrimero = NULL;
	delete antPrimero;
	this->tam--;
}

Nat Pila::tamanio() const
{
	return this->tam;
}