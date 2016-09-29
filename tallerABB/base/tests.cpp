#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

void test_insertar() {
	Conjunto<int> c;
	c.insertar(42);
	ASSERT( c.pertenece(42) );

	// Chequear insertar más elementos
}

void test_cardinal() {
	// Completar
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);
	ASSERT(c.cardinal() == 8);
}

void test_remover() {
	// Chequear por lo menos los siguientes 3 casos:
 	// - Borrar una hoja
 	// - Borrar un nodo interno con un hijo
 	// - Borrrun nodo interno con dos hijos
 	Conjunto<int> c;
 	c.insertar(42);
 	c.insertar(30);
    c.insertar(35);
    c.insertar(33);
    c.insertar(15);
    c.insertar(20);
    c.insertar(18);
    c.insertar(25);
    c.insertar(12);
    c.insertar(13);
    c.insertar(8);
    c.insertar(44);
    c.insertar(43);
    c.insertar(104);
    c.insertar(98);
    c.insertar(90);
    c.insertar(100);
    c.insertar(450);
    c.insertar(130);

	bool pertenencia;

	// caso que chequea borrar una hoja
	c.remover(15);
	pertenencia = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
				&& c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
				&& c.pertenece(130) && c.pertenece(43);
 	ASSERT( pertenencia );

 	// Completar
 	ASSERT( false );

}

void test_maximo() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);
	ASSERT_EQ( c.maximo(), 450 );
}

void test_minimo() {
	Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);
	ASSERT_EQ( c.minimo(), -460 );
}

int main() {

	RUN_TEST(test_insertar);
	RUN_TEST(test_cardinal);
	RUN_TEST(test_remover);
	RUN_TEST(test_maximo);
	RUN_TEST(test_minimo);
	return 0;
}
