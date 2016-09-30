#include <iostream>
#include "mini_test.h"

#include "Conjunto.hpp"

template<typename T>
std::string to_s(const T& m) {
    std::ostringstream os;
    os << m;
    return os.str();
}

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

    Conjunto<int> c1;
    c1.insertar(42);
    c1.insertar(44);
    c1.insertar(104);
    c1.insertar(450);
    c1.insertar(-46);
    c1.insertar(-460);
    c1.insertar(130);
    c1.insertar(43);

	bool pertenenciaUnHijo;

	// caso que chequea borrar un nodo interno con un hijo
	c1.remover(44);
	pertenenciaUnHijo = c1.pertenece(42) && !c1.pertenece(44) && c1.pertenece(104)
				&& c1.pertenece(450) && c1.pertenece(-46) && c1.pertenece(-460)
				&& c1.pertenece(130) && c1.pertenece(43);
 	ASSERT( pertenenciaUnHijo );

	std::cout << std::endl;
	std::cout << "UN HIJO OK "<<std::endl;

    Conjunto<int> c2;
    c2.insertar(42);
    c2.insertar(44);
    c2.insertar(104);
    c2.insertar(450);
    c2.insertar(-46);
    c2.insertar(-460);
    c2.insertar(130);
    c2.insertar(43);

    bool pertenenciaHoja;

    // caso que chequea borrar una hoja
	c2.remover(43);
	pertenenciaHoja = c2.pertenece(42) && c2.pertenece(44) && c2.pertenece(104)
                  && c2.pertenece(450) && c2.pertenece(-46) && c2.pertenece(-460)
                  && c2.pertenece(130) && !c2.pertenece(43);

	ASSERT( pertenenciaHoja );

	std::cout << "HOJA OK "<<std::endl;

	Conjunto<int> c3;
	c3.insertar(42);
	c3.insertar(44);
	c3.insertar(104);
	c3.insertar(450);
	c3.insertar(-46);
	c3.insertar(-460);
	c3.insertar(130);
	c3.insertar(43);

	bool pertenenciaDosHijos;

	// caso que chequea borrar una hoja
	c3.remover(42);
	pertenenciaDosHijos = !c3.pertenece(42) && c3.pertenece(44) && c3.pertenece(104)
					  && c3.pertenece(450) && c3.pertenece(-46) && c3.pertenece(-460)
					  && c3.pertenece(130) && c3.pertenece(43);

	ASSERT( pertenenciaDosHijos );

	std::cout << "DOS HIJOS OK "<<std::endl;

	std::cout << std::endl;
	std::cout<< "c1: ";
	c1.mostrar(std::cout);
	std::cout << std::endl;
	std::cout<< "c2: ";
	c2.mostrar(std::cout);
	std::cout << std::endl;
	std::cout<< "c3: ";
	c3.mostrar(std::cout);
	// Completar

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

void test_mostrar() {
    Conjunto<int> c;
    c.insertar(15);
    c.insertar(9);
    c.insertar(6);
    c.insertar(14);
    c.insertar(13);
    c.insertar(20);
    c.insertar(17);
    c.insertar(64);
    c.insertar(26);
    c.insertar(72);
    ASSERT_EQ( to_s(c) ,"[6, 9, 13, 14, 15, 17, 20, 26, 64, 72, ]");
}

int main() {

	RUN_TEST(test_insertar);
	RUN_TEST(test_cardinal);
	RUN_TEST(test_remover);
	RUN_TEST(test_maximo);
	RUN_TEST(test_minimo);
    RUN_TEST(test_mostrar);
	return 0;
}
