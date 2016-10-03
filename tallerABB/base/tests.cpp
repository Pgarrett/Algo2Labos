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
    std::cout << std::endl;
	Conjunto<int> c;
	c.insertar(42);
	ASSERT( c.pertenece(42) );

	// Chequear insertar más elementos
}

void test_cardinal() {
    std::cout << std::endl;
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
	ASSERT_EQ(c.cardinal(), 8);
}

void test_remover() {
    std::cout << std::endl;
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

}

void testRemoverHijoIHoja() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(44);
    c.insertar(104);
    c.insertar(450);
    c.insertar(-46);
    c.insertar(-460);
    c.insertar(130);
    c.insertar(43);

    bool pertenenciaHoja;

    // caso que chequea borrar una hoja
	c.remover(43);
	pertenenciaHoja = c.pertenece(42) && c.pertenece(44) && c.pertenece(104)
                  && c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
                  && c.pertenece(130) && !c.pertenece(43);

	ASSERT( pertenenciaHoja );

}

void testRemoverRaizDosHijosGrandes() {
    std::cout << std::endl;
    Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);

	bool pertenenciaDosHijos;

	// caso que chequea borrar una hoja
	c.remover(42);
	pertenenciaDosHijos = !c.pertenece(42) && c.pertenece(44) && c.pertenece(104)
					  && c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
					  && c.pertenece(130) && c.pertenece(43);

	ASSERT( pertenenciaDosHijos );

}

void testRemoverBorde() {
    std::cout << std::endl;
    Conjunto<int> c;
	c.insertar(42);
	c.insertar(44);
	c.insertar(104);
	c.insertar(450);
	c.insertar(-46);
	c.insertar(-460);
	c.insertar(130);
	c.insertar(43);

	c.remover(-460);
	bool elimineBorde;
	elimineBorde = c.pertenece(42) && c.pertenece(44) && c.pertenece(104)
						  && c.pertenece(450) && c.pertenece(-46) && !c.pertenece(-460)
						  && c.pertenece(130) && c.pertenece(43);

    ASSERT(elimineBorde);
}

void testRemoverHijoConDosHijos() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(44);
    c.insertar(104);
    c.insertar(450);
    c.insertar(-46);
    c.insertar(-460);
    c.insertar(130);
    c.insertar(43);

    c.remover(44);
    bool pertenece;
    pertenece = c.pertenece(42) && !c.pertenece(44) && c.pertenece(104)
                   && c.pertenece(450) && c.pertenece(-46) && c.pertenece(-460)
                   && c.pertenece(130) && c.pertenece(43);

    ASSERT(pertenece);
}

void testRemoverRaizSola() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.mostrar(std::cout);
    std::cout << std::endl;
    c.remover(42);
    c.mostrar(std::cout);
    std::cout << std::endl;
}

void testRemoverRaizHijoI() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.mostrar(std::cout);
    std::cout << std::endl;
    c.remover(42);
    c.mostrar(std::cout);
    std::cout << std::endl;
}

void testRemoverRaizHijoD() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(70);
    c.mostrar(std::cout);
    std::cout << std::endl;
    c.remover(42);
    c.mostrar(std::cout);
    std::cout << std::endl;
}

void testRemoverRaizDosHijos() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(70);
    c.mostrar(std::cout);
    std::cout << std::endl;
    c.remover(42);
    c.mostrar(std::cout);
    std::cout << std::endl;
}

void testRemoverMitadCaminoI1() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(40);
    c.insertar(36);
    c.insertar(38);
    c.insertar(37);
    c.remover(40);
    bool pertenece;
    pertenece = c.pertenece(42) && c.pertenece(35) && !c.pertenece(40)
                && c.pertenece(36) && c.pertenece(38) && c.pertenece(37);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 35);
    ASSERT_EQ(c.maximo(), 42);
}

void testRemoverMitadCaminoI2() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(40);
    c.insertar(36);
    c.insertar(38);
    c.insertar(37);
    c.remover(36);
    bool pertenece;
    pertenece = c.pertenece(42) && c.pertenece(35) && c.pertenece(40)
                && !c.pertenece(36) && c.pertenece(38) && c.pertenece(37);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 35);
    ASSERT_EQ(c.maximo(), 42);
}

void testRemoverMitadCaminoD1() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(60);
    c.insertar(45);
    c.insertar(55);
    c.insertar(50);
    c.insertar(53);
    c.remover(45);
    bool pertenece;
    pertenece = c.pertenece(42) && c.pertenece(60) && !c.pertenece(45)
                && c.pertenece(55) && c.pertenece(50) && c.pertenece(53);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 42);
    ASSERT_EQ(c.maximo(), 60);
}

void testRemoverMitadCaminoD2() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(60);
    c.insertar(45);
    c.insertar(55);
    c.insertar(50);
    c.insertar(53);
    c.remover(60);
    bool pertenece;
    pertenece = c.pertenece(42) && !c.pertenece(60) && c.pertenece(45)
                && c.pertenece(55) && c.pertenece(50) && c.pertenece(53);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 42);
    ASSERT_EQ(c.maximo(), 55);
}

void testRemoverHITodoD1() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(36);
    c.insertar(37);
    c.insertar(38);
    c.insertar(39);
    c.remover(35);
    bool pertenece;
    pertenece = c.pertenece(42) && !c.pertenece(35) && c.pertenece(36)
                && c.pertenece(37) && c.pertenece(38) && c.pertenece(39);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 36);
    ASSERT_EQ(c.maximo(), 42);
}

void testRemoverHITodoD2() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(36);
    c.insertar(37);
    c.insertar(38);
    c.insertar(39);
    c.remover(37);
    bool pertenece;
    pertenece = c.pertenece(42) && c.pertenece(35) && c.pertenece(36)
                && !c.pertenece(37) && c.pertenece(38) && c.pertenece(39);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 35);
    ASSERT_EQ(c.maximo(), 42);
}

void testRemoverHDTodoI1() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(66);
    c.insertar(60);
    c.insertar(55);
    c.insertar(50);
    c.insertar(45);
    c.remover(66);
    bool pertenece;
    pertenece = c.pertenece(42) && !c.pertenece(66) && c.pertenece(60)
                && c.pertenece(55) && c.pertenece(50) && c.pertenece(45);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 42);
    ASSERT_EQ(c.maximo(), 60);
}

void testRemoverHDTodoI2() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(66);
    c.insertar(60);
    c.insertar(55);
    c.insertar(50);
    c.insertar(45);
    c.remover(55);
    bool pertenece;
    pertenece = c.pertenece(42) && c.pertenece(66) && c.pertenece(60)
                && !c.pertenece(55) && c.pertenece(50) && c.pertenece(45);
    ASSERT(pertenece);
    ASSERT_EQ(c.minimo(), 42);
    ASSERT_EQ(c.maximo(), 66);
}

void test_maximo() {
    std::cout << std::endl;
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
    std::cout << std::endl;
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

void test_minimoCamino() {
    std::cout << std::endl;
    Conjunto<int> c;
    c.insertar(42);
    c.insertar(35);
    c.insertar(40);
    c.insertar(36);
    c.insertar(38);
    c.insertar(37);
    ASSERT_EQ( c.minimo(), 35 );
}

void test_mostrar() {
    std::cout << std::endl;
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
    ASSERT_EQ( to_s(c) ,"[6, 9, 13, 14, 15, 17, 20, 26, 64, 72]");
}

void printSeparator() {
    std::cout << "====================================" << std::endl;
}

int main() {
    std::cout << std::endl;
	RUN_TEST(test_insertar);
    printSeparator();
	RUN_TEST(test_cardinal);
    printSeparator();
	RUN_TEST(test_remover);
    printSeparator();
    RUN_TEST(testRemoverBorde);
    printSeparator();
    RUN_TEST(testRemoverHijoConDosHijos);
    printSeparator();
    RUN_TEST(testRemoverHijoIHoja);
    printSeparator();
    RUN_TEST(testRemoverRaizDosHijosGrandes);
    printSeparator();
    RUN_TEST(testRemoverRaizSola);
    printSeparator();
    RUN_TEST(testRemoverRaizHijoI);
    printSeparator();
    RUN_TEST(testRemoverRaizHijoD);
    printSeparator();
    RUN_TEST(testRemoverRaizDosHijos);
    printSeparator();
    RUN_TEST(testRemoverMitadCaminoI1);
    printSeparator();
    RUN_TEST(testRemoverMitadCaminoI2);
    printSeparator();
    RUN_TEST(testRemoverMitadCaminoD1);
    printSeparator();
    RUN_TEST(testRemoverMitadCaminoD2);
    printSeparator();
    RUN_TEST(testRemoverHITodoD1);
    printSeparator();
    RUN_TEST(testRemoverHITodoD2);
    printSeparator();
    RUN_TEST(testRemoverHDTodoI1);
    printSeparator();
    RUN_TEST(testRemoverHDTodoI2);
    printSeparator();
	RUN_TEST(test_maximo);
    printSeparator();
	RUN_TEST(test_minimo);
    printSeparator();
    RUN_TEST(test_minimoCamino);
    printSeparator();
    RUN_TEST(test_mostrar);
	return 0;
}
