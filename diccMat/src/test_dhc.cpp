#include <iostream>
#include <fstream>
#include "DiccMat.hpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_Definido () {

	DiccMat<int> dhi = DiccMat<int>(6,6);

	ASSERT(!dhi.Definido(Coor(4,5)));
	dhi.Definir(Coor(4,5), 45);
	ASSERT(dhi.Definido(Coor(4,5)));
}

void test_Definir () {

    DiccMat<int> dhi = DiccMat<int>(6,6);

    dhi.Definir(Coor(4,5), 45);
    dhi.Definir(Coor(3,5), 123456);
    ASSERT(dhi.Definido(Coor(4,5)));
    ASSERT(dhi.Definido(Coor(3,5)));
}

void test_Significado () {

	DiccMat<int> dhi = DiccMat<int>(6,6);

	dhi.Definir(Coor(4,5), 45);
	dhi.Definir(Coor(5,5), 90);
	dhi.Definir(Coor(0,0), 123456);
	ASSERT_EQ(dhi.Significado(Coor(4,5)), 45);
	ASSERT_EQ(dhi.Significado(Coor(5,5)), 90);
	ASSERT_EQ(dhi.Significado(Coor(0,0)), 123456);
    dhi.Definir(Coor(4,5), 65);
    ASSERT(dhi.Significado(Coor(4,5)) != 45);
    ASSERT_EQ(dhi.Significado(Coor(4,5)), 65);
}

void test_Borrar () {

	DiccMat<int> dhi = DiccMat<int>(6,6);

    dhi.Definir(Coor(4,5), 45);
    dhi.Definir(Coor(5,5), 90);
    dhi.Definir(Coor(1,3), 135);
    dhi.Definir(Coor(0,0), 123456);
    ASSERT_EQ(dhi.Significado(Coor(4,5)), 45);
    ASSERT_EQ(dhi.Significado(Coor(5,5)), 90);
    ASSERT_EQ(dhi.Significado(Coor(1,3)), 135);
    ASSERT_EQ(dhi.Significado(Coor(0,0)), 123456);

	dhi.Borrar(Coor(4,5));
	ASSERT(!dhi.Definido(Coor(4,5)));
	ASSERT(dhi.Definido(Coor(1,3)));
	ASSERT(dhi.Definido(Coor(0,0)));

    dhi.Definir(Coor(4,5), 45);
    ASSERT_EQ(dhi.Significado(Coor(4,5)), 45);
    dhi.Borrar(Coor(4,5));
    ASSERT(!dhi.Definido(Coor(4,5)));
}

/*void test_claves(){
	DiccMat<int> dhi = DiccMat<int>(6,6);
	Conj<Coor> claves;

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir(Coor(1,3),40);
	dhi.Definir(Coor(1,5),38);

	claves = dhi.Claves();
    ASSERT(claves.Pertenece(Coor(1,3)));

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir(Coor(1,3),56);

//	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar(Coor(1,5));

//	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar(Coor(1,3));

//	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );
}*/

int main() {

	RUN_TEST(test_Definido);
	RUN_TEST(test_Definir);
	RUN_TEST(test_Significado);
	RUN_TEST(test_Borrar);
//	RUN_TEST(test_claves);

	return 0;
}
