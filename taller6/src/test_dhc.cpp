#include <iostream>
#include <fstream>
#include "DiccHashCerrado.hpp"
#include "mini_test.h"

using namespace std;
using namespace aed2;

void test_Definido () {

	DiccHashCerrado<int> dhi;

	ASSERT(!dhi.Definido("dicc"));
	dhi.Definir("test", 45);
	ASSERT(dhi.Definido("test"));
}

void test_Definir () {

	DiccHashCerrado<int> dhi;

	dhi.Definir("test", 45);
	dhi.Definir("alalala", 123456);
	ASSERT(dhi.Definido("test"));
	ASSERT(dhi.Definido("alalala"));
}

void test_String_Vacio () {

//	ASSERT(false);
    DiccHashCerrado<int> dhi;

    dhi.Definir("", 45);
    dhi.Definir("test", 45);
    dhi.Definir("alalala", 123456);

    ASSERT(dhi.Definido(""));
    ASSERT(dhi.Definido("test"));
    ASSERT(dhi.Definido("alalala"));
    ASSERT_EQ(dhi.Significado(""), 45);
    dhi.Borrar("");
    ASSERT(!dhi.Definido(""));
    ASSERT(dhi.Definido("test"));
    ASSERT(dhi.Definido("alalala"));
}

void test_Significado () {

	DiccHashCerrado<int> dhi;

	dhi.Definir("test", 45);
	dhi.Definir("estt", 90);
	dhi.Definir("alalala", 123456);
	ASSERT_EQ(dhi.Significado("test"), 45);
	ASSERT_EQ(dhi.Significado("estt"), 90);
	ASSERT_EQ(dhi.Significado("alalala"), 123456);
}

void test_Borrar () {

	DiccHashCerrado<int> dhi;

	dhi.Definir("test", 45);
	dhi.Definir("estt", 90);
	dhi.Definir("alalala", 123456);
	ASSERT_EQ(dhi.Significado("test"), 45);
	ASSERT_EQ(dhi.Significado("estt"), 90);
	ASSERT_EQ(dhi.Significado("alalala"), 123456);

	dhi.Borrar("test");
	ASSERT(!dhi.Definido("test"));
	ASSERT(dhi.Definido("estt"));
	ASSERT(dhi.Definido("alalala"));

    dhi.Definir("test", 45);
    ASSERT_EQ(dhi.Significado("test"), 45);
    dhi.Borrar("test");
    ASSERT(!dhi.Definido("test"));
}

void test_CantClaves () {

	DiccHashCerrado<int> dhi;

	ASSERT_EQ(dhi.CantClaves(), 0);
	dhi.Definir("test", 45);
	dhi.Definir("estt", 90);
	ASSERT_EQ(dhi.CantClaves(), 2);
	dhi.Definir("alalala", 123456);
	ASSERT_EQ(dhi.CantClaves(), 3);
}

void test_claves(){
	DiccHashCerrado<int> dhi;
	Lista<String> claves;

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );

	dhi.Definir("juanca",40);
	dhi.Definir("moncho",38);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Definir("moncho",56);

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 2 );

	dhi.Borrar("juanca");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 1 );

	dhi.Borrar("moncho");

	claves = dhi.Claves();

	ASSERT( dhi.CantClaves() == 0 );
}

void test_colisiones_libretas(){

	DiccHashCerrado<int> dh;

//	std::string archnom = "../data/uniforme.txt";
//	std::string archnom = "../data/gauss.txt";
	std::string archnom = "../data/libretas.txt";


	int val = 0;
	string str;

	ifstream archin(archnom.c_str());
	ASSERT(archin.good());

	while(getline(archin,str) && archin.good()){

		//cout << "Definiendo: " << str << endl;
		dh.Definir(str, val);
		val++;

		//if (val == 100) break;
	}
	archin.close();

	ASSERT_EQ(dh.CantClaves(),val);

	cout << "Factor de carga: " << dh.factorCarga() << endl;
	cout << "Colisiones: " << dh.colisiones() << endl;
}

void test_colisiones_gauss(){

    DiccHashCerrado<int> dh;

//	std::string archnom = "../data/uniforme.txt";
	std::string archnom = "../data/gauss.txt";
//    std::string archnom = "../data/libretas.txt";


    int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT(archin.good());

    while(getline(archin,str) && archin.good()){

        //cout << "Definiendo: " << str << endl;
        dh.Definir(str, val);
        val++;

        //if (val == 100) break;
    }
    archin.close();

    ASSERT_EQ(dh.CantClaves(),val);

    cout << "Factor de carga: " << dh.factorCarga() << endl;
    cout << "Colisiones: " << dh.colisiones() << endl;
}

void test_colisiones_uniforme(){

    DiccHashCerrado<int> dh;

	std::string archnom = "../data/uniforme.txt";
//	std::string archnom = "../data/gauss.txt";
//    std::string archnom = "../data/libretas.txt";


    int val = 0;
    string str;

    ifstream archin(archnom.c_str());
    ASSERT(archin.good());

    while(getline(archin,str) && archin.good()){

        //cout << "Definiendo: " << str << endl;
        dh.Definir(str, val);
        val++;

        //if (val == 100) break;
    }
    archin.close();

    ASSERT_EQ(dh.CantClaves(),val);

    cout << "Factor de carga: " << dh.factorCarga() << endl;
    cout << "Colisiones: " << dh.colisiones() << endl;
}

void test_redimensionado(){

    DiccHashCerrado<int> a;
    unsigned int i = 1;

    a.Definir("abbey", i++);
    a.Definir("favourite", i++);
    a.Definir("make", i++);
    a.Definir("condition", i++);
    a.Definir("seek", i++);
    a.Definir("official", i++);
    a.Definir("wander", i++);
    a.Definir("dorm", i++);
    a.Definir("funeral", i++);
    a.Definir("compliance", i++);
    a.Definir("manual", i++);
    a.Definir("favour", i++);
    a.Definir("illustrate", i++);
    a.Definir("producer", i++);
    a.Definir("braid", i++);
    a.Definir("easy", i++);
    a.Definir("palace", i++);
    a.Definir("chalk", i++);
    a.Definir("disappear", i++);
    a.Definir("population", i++);
    a.Definir("fate", i++);
    a.Definir("sunshine", i++);
    a.Definir("conclusion", i++);
    a.Definir("tendency", i++);
    a.Definir("junior", i++);
    a.Definir("contrary", i++);
    a.Definir("answer", i++);
    a.Definir("suspect", i++);
    a.Definir("accompany", i++);
    a.Definir("cabin", i++);
    a.Definir("mood", i++);
    a.Definir("tournament", i++);
    a.Definir("trustee", i++);
    a.Definir("solo", i++);
    a.Definir("hay", i++);
    a.Definir("gradient", i++);
    a.Definir("complain", i++);
    a.Definir("teacher", i++);
    a.Definir("spend", i++);
    a.Definir("discover", i++);
    a.Definir("classroom", i++);
    a.Definir("flavor", i++);
    a.Definir("available", i++);
    a.Definir("doll", i++);
    a.Definir("lot", i++);
    a.Definir("fruit", i++);
    a.Definir("packet", i++);
    a.Definir("neck", i++);
    a.Definir("strikebreaker", i++);
    a.Definir("witness", i++);
    a.Definir("distinct", i++);
    a.Definir("look", i++);
    a.Definir("bland", i++);
    a.Definir("represent", i++);
    a.Definir("kid", i++);
    a.Definir("amber", i++);
    a.Definir("asset", i++);
    a.Definir("horse", i++);
    a.Definir("opinion", i++);
    a.Definir("suite", i++);
    a.Definir("pig", i++);
    a.Definir("horn", i++);
    a.Definir("rugby", i++);
    a.Definir("penetrate", i++);
    a.Definir("efflux", i++);
    a.Definir("pray", i++);
    a.Definir("conversation", i++);
    a.Definir("applaud", i++);
    a.Definir("skate", i++);
    a.Definir("feminist", i++);
    a.Definir("tongue", i++);
    a.Definir("behave", i++);
    a.Definir("lift", i++);
    a.Definir("occasion", i++);
    a.Definir("seller", i++);
    a.Definir("crop", i++);
    a.Definir("node", i++);
    a.Definir("wife", i++);
    a.Definir("warrant", i++);
    a.Definir("systematic", i++);
    a.Definir("escape", i++);
    a.Definir("train", i++);
    a.Definir("city", i++);
    a.Definir("meaning", i++);
    a.Definir("breast", i++);
    a.Definir("accumulation", i++);
    a.Definir("employee", i++);
    a.Definir("overall", i++);
    a.Definir("real", i++);
    a.Definir("abortion", i++);
    a.Definir("shave", i++);
    a.Definir("leftovers", i++);
    a.Definir("include", i++);
    a.Definir("buy", i++);
    a.Definir("grimace", i++);
    a.Definir("golf", i++);
    a.Definir("simplicity", i++);
    a.Definir("inquiry", i++);
    a.Definir("incapable", i++);
    a.Definir("old", i++);
    a.Definir("root", i++);
    a.Definir("hot", i++);
    a.Definir("training", i++);
    a.Definir("engagement", i++);
    a.Definir("gradual", i++);
    a.Definir("tone", i++);
    a.Definir("pottery", i++);
    a.Definir("provide", i++);
    a.Definir("innovation", i++);
    a.Definir("bomb", i++);
    a.Definir("nose", i++);
    a.Definir("essential", i++);
    a.Definir("punch", i++);
    a.Definir("will", i++);
    a.Definir("similar", i++);
    a.Definir("bend", i++);
    a.Definir("opposition", i++);
    a.Definir("factor", i++);
    a.Definir("owner", i++);
    a.Definir("past", i++);
    a.Definir("instinct", i++);
    a.Definir("notebook", i++);
    a.Definir("mail carrier", i++);
    a.Definir("decoration", i++);
    a.Definir("excavate", i++);
    a.Definir("mouse", i++);
    a.Definir("crouch", i++);
    a.Definir("premium", i++);
    a.Definir("clinic", i++);
    a.Definir("elect", i++);
    a.Definir("minimum", i++);
    a.Definir("indication", i++);
    a.Definir("deficiency", i++);
    a.Definir("dull", i++);
    a.Definir("approach", i++);
    a.Definir("avenue", i++);
    a.Definir("zone", i++);
    a.Definir("outlook", i++);
    a.Definir("glue", i++);
    a.Definir("break in", i++);
    a.Definir("expenditure", i++);
    a.Definir("pest", i++);
    a.Definir("soldier", i++);
    a.Definir("exception", i++);
    a.Definir("inject", i++);
    a.Definir("manage", i++);
    a.Definir("wagon", i++);
    a.Definir("hike", i++);
    a.Definir("translate", i++);
    a.Definir("action", i++);
    a.Definir("agony", i++);
    a.Definir("exhibition", i++);
    a.Definir("state", i++);
    a.Definir("sentiment", i++);
    a.Definir("ceremony", i++);
    a.Definir("inhabitant", i++);
    a.Definir("solution", i++);
    a.Definir("carpet", i++);
    a.Definir("costume", i++);
    a.Definir("end", i++);
    a.Definir("please", i++);
    a.Definir("ribbon", i++);
    a.Definir("defeat", i++);
    a.Definir("country", i++);
    a.Definir("hope", i++);
    a.Definir("impress", i++);
    a.Definir("situation", i++);
    a.Definir("cane", i++);
    a.Definir("happen", i++);
    a.Definir("square", i++);
    a.Definir("blade", i++);
    a.Definir("illness", i++);
    a.Definir("freighter", i++);
    a.Definir("asylum", i++);
    a.Definir("salt", i++);
    a.Definir("progressive", i++);
    a.Definir("transaction", i++);
    a.Definir("coffee", i++);
    a.Definir("shareholder", i++);
    a.Definir("suit", i++);
    a.Definir("umbrella", i++);
    a.Definir("tribute", i++);
    a.Definir("sigh", i++);
    a.Definir("due", i++);
    a.Definir("hurl", i++);
    a.Definir("burial", i++);
    a.Definir("quote", i++);
    a.Definir("ample", i++);
    a.Definir("rough", i++);
    a.Definir("normal", i++);
    a.Definir("prey", i++);
    a.Definir("walk", i++);
    a.Definir("color-blind", i++);
    a.Definir("broken", i++);
    a.Definir("energy", i++);
    a.Definir("vigorous", i++);
    a.Definir("team", i++);
    a.Definir("tax", i++);
    a.Definir("information", i++);
    a.Definir("emergency", i++);
    a.Definir("", i++);

    std::cout << i << std::endl;
    std::cout << a.Claves() << std::endl;
}


int main() {

	RUN_TEST(test_Definido);
	RUN_TEST(test_Definir);
	RUN_TEST(test_String_Vacio);
	RUN_TEST(test_Significado);
	RUN_TEST(test_Borrar);
	RUN_TEST(test_CantClaves);
	RUN_TEST(test_claves);
	RUN_TEST(test_redimensionado);
//	RUN_TEST(test_colisiones_libretas);
//    RUN_TEST(test_colisiones_gauss);
//    RUN_TEST(test_colisiones_uniforme);

	return 0;
}
