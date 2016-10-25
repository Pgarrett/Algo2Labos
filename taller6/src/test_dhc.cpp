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

    DiccHashCerrado<int> dhi1;

    dhi1.Definir("", 45);
    dhi1.Definir(" ", 123457);
    dhi1.Definir("alalala", 123456);
    ASSERT(dhi1.Definido(""));
    ASSERT(dhi1.Definido(" "));
    ASSERT(dhi1.Definido("alalala"));

    DiccHashCerrado<int> dhi2;
//    dhi2 = dhi1;
//    ASSERT(dhi2.Definido(""));
    for (unsigned int i = 0; i < dhi1.Claves().Longitud(); i++) {
        dhi2.Definir(dhi1.Claves().operator[](i), dhi1.Significado(dhi1.Claves().operator[](i)));
    }
    ASSERT(dhi2.Definido(""));
    ASSERT(dhi2.Definido(" "));
    ASSERT(dhi2.Definido("alalala"));
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
    dhi.Definir("etst", 135);
	dhi.Definir("alalala", 123456);
	ASSERT_EQ(dhi.Significado("test"), 45);
	ASSERT_EQ(dhi.Significado("estt"), 90);
    ASSERT_EQ(dhi.Significado("etst"), 135);
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

    i = 1;
    ASSERT_EQ(a.Significado("abbey"), i++);
    ASSERT_EQ(a.Significado("favourite"), i++);
    ASSERT_EQ(a.Significado("make"), i++);
    ASSERT_EQ(a.Significado("condition"), i++);
    ASSERT_EQ(a.Significado("seek"), i++);
    ASSERT_EQ(a.Significado("official"), i++);
    ASSERT_EQ(a.Significado("wander"), i++);
    ASSERT_EQ(a.Significado("dorm"), i++);
    ASSERT_EQ(a.Significado("funeral"), i++);
    ASSERT_EQ(a.Significado("compliance"), i++);
    ASSERT_EQ(a.Significado("manual"), i++);
    ASSERT_EQ(a.Significado("favour"), i++);
    ASSERT_EQ(a.Significado("illustrate"), i++);
    ASSERT_EQ(a.Significado("producer"), i++);
    ASSERT_EQ(a.Significado("braid"), i++);
    ASSERT_EQ(a.Significado("easy"), i++);
    ASSERT_EQ(a.Significado("palace"), i++);
    ASSERT_EQ(a.Significado("chalk"), i++);
    ASSERT_EQ(a.Significado("disappear"), i++);
    ASSERT_EQ(a.Significado("population"), i++);
    ASSERT_EQ(a.Significado("fate"), i++);
    ASSERT_EQ(a.Significado("sunshine"), i++);
    ASSERT_EQ(a.Significado("conclusion"), i++);
    ASSERT_EQ(a.Significado("tendency"), i++);
    ASSERT_EQ(a.Significado("junior"), i++);
    ASSERT_EQ(a.Significado("contrary"), i++);
    ASSERT_EQ(a.Significado("answer"), i++);
    ASSERT_EQ(a.Significado("suspect"), i++);
    ASSERT_EQ(a.Significado("accompany"), i++);
    ASSERT_EQ(a.Significado("cabin"), i++);
    ASSERT_EQ(a.Significado("mood"), i++);
    ASSERT_EQ(a.Significado("tournament"), i++);
    ASSERT_EQ(a.Significado("trustee"), i++);
    ASSERT_EQ(a.Significado("solo"), i++);
    ASSERT_EQ(a.Significado("hay"), i++);
    ASSERT_EQ(a.Significado("gradient"), i++);
    ASSERT_EQ(a.Significado("complain"), i++);
    ASSERT_EQ(a.Significado("teacher"), i++);
    ASSERT_EQ(a.Significado("spend"), i++);
    ASSERT_EQ(a.Significado("discover"), i++);
    ASSERT_EQ(a.Significado("classroom"), i++);
    ASSERT_EQ(a.Significado("flavor"), i++);
    ASSERT_EQ(a.Significado("available"), i++);
    ASSERT_EQ(a.Significado("doll"), i++);
    ASSERT_EQ(a.Significado("lot"), i++);
    ASSERT_EQ(a.Significado("fruit"), i++);
    ASSERT_EQ(a.Significado("packet"), i++);
    ASSERT_EQ(a.Significado("neck"), i++);
    ASSERT_EQ(a.Significado("strikebreaker"), i++);
    ASSERT_EQ(a.Significado("witness"), i++);
    ASSERT_EQ(a.Significado("distinct"), i++);
    ASSERT_EQ(a.Significado("look"), i++);
    ASSERT_EQ(a.Significado("bland"), i++);
    ASSERT_EQ(a.Significado("represent"), i++);
    ASSERT_EQ(a.Significado("kid"), i++);
    ASSERT_EQ(a.Significado("amber"), i++);
    ASSERT_EQ(a.Significado("asset"), i++);
    ASSERT_EQ(a.Significado("horse"), i++);
    ASSERT_EQ(a.Significado("opinion"), i++);
    ASSERT_EQ(a.Significado("suite"), i++);
    ASSERT_EQ(a.Significado("pig"), i++);
    ASSERT_EQ(a.Significado("horn"), i++);
    ASSERT_EQ(a.Significado("rugby"), i++);
    ASSERT_EQ(a.Significado("penetrate"), i++);
    ASSERT_EQ(a.Significado("efflux"), i++);
    ASSERT_EQ(a.Significado("pray"), i++);
    ASSERT_EQ(a.Significado("conversation"), i++);
    ASSERT_EQ(a.Significado("applaud"), i++);
    ASSERT_EQ(a.Significado("skate"), i++);
    ASSERT_EQ(a.Significado("feminist"), i++);
    ASSERT_EQ(a.Significado("tongue"), i++);
    ASSERT_EQ(a.Significado("behave"), i++);
    ASSERT_EQ(a.Significado("lift"), i++);
    ASSERT_EQ(a.Significado("occasion"), i++);
    ASSERT_EQ(a.Significado("seller"), i++);
    ASSERT_EQ(a.Significado("crop"), i++);
    ASSERT_EQ(a.Significado("node"), i++);
    ASSERT_EQ(a.Significado("wife"), i++);
    ASSERT_EQ(a.Significado("warrant"), i++);
    ASSERT_EQ(a.Significado("systematic"), i++);
    ASSERT_EQ(a.Significado("escape"), i++);
    ASSERT_EQ(a.Significado("train"), i++);
    ASSERT_EQ(a.Significado("city"), i++);
    ASSERT_EQ(a.Significado("meaning"), i++);
    ASSERT_EQ(a.Significado("breast"), i++);
    ASSERT_EQ(a.Significado("accumulation"), i++);
    ASSERT_EQ(a.Significado("employee"), i++);
    ASSERT_EQ(a.Significado("overall"), i++);
    ASSERT_EQ(a.Significado("real"), i++);
    ASSERT_EQ(a.Significado("abortion"), i++);
    ASSERT_EQ(a.Significado("shave"), i++);
    ASSERT_EQ(a.Significado("leftovers"), i++);
    ASSERT_EQ(a.Significado("include"), i++);
    ASSERT_EQ(a.Significado("buy"), i++);
    ASSERT_EQ(a.Significado("grimace"), i++);
    ASSERT_EQ(a.Significado("golf"), i++);
    ASSERT_EQ(a.Significado("simplicity"), i++);
    ASSERT_EQ(a.Significado("inquiry"), i++);
    ASSERT_EQ(a.Significado("incapable"), i++);
    ASSERT_EQ(a.Significado("old"), i++);
    ASSERT_EQ(a.Significado("root"), i++);
    ASSERT_EQ(a.Significado("hot"), i++);
    ASSERT_EQ(a.Significado("training"), i++);
    ASSERT_EQ(a.Significado("engagement"), i++);
    ASSERT_EQ(a.Significado("gradual"), i++);
    ASSERT_EQ(a.Significado("tone"), i++);
    ASSERT_EQ(a.Significado("pottery"), i++);
    ASSERT_EQ(a.Significado("provide"), i++);
    ASSERT_EQ(a.Significado("innovation"), i++);
    ASSERT_EQ(a.Significado("bomb"), i++);
    ASSERT_EQ(a.Significado("nose"), i++);
    ASSERT_EQ(a.Significado("essential"), i++);
    ASSERT_EQ(a.Significado("punch"), i++);
    ASSERT_EQ(a.Significado("will"), i++);
    ASSERT_EQ(a.Significado("similar"), i++);
    ASSERT_EQ(a.Significado("bend"), i++);
    ASSERT_EQ(a.Significado("opposition"), i++);
    ASSERT_EQ(a.Significado("factor"), i++);
    ASSERT_EQ(a.Significado("owner"), i++);
    ASSERT_EQ(a.Significado("past"), i++);
    ASSERT_EQ(a.Significado("instinct"), i++);
    ASSERT_EQ(a.Significado("notebook"), i++);
    ASSERT_EQ(a.Significado("mail carrier"), i++);
    ASSERT_EQ(a.Significado("decoration"), i++);
    ASSERT_EQ(a.Significado("excavate"), i++);
    ASSERT_EQ(a.Significado("mouse"), i++);
    ASSERT_EQ(a.Significado("crouch"), i++);
    ASSERT_EQ(a.Significado("premium"), i++);
    ASSERT_EQ(a.Significado("clinic"), i++);
    ASSERT_EQ(a.Significado("elect"), i++);
    ASSERT_EQ(a.Significado("minimum"), i++);
    ASSERT_EQ(a.Significado("indication"), i++);
    ASSERT_EQ(a.Significado("deficiency"), i++);
    ASSERT_EQ(a.Significado("dull"), i++);
    ASSERT_EQ(a.Significado("approach"), i++);
    ASSERT_EQ(a.Significado("avenue"), i++);
    ASSERT_EQ(a.Significado("zone"), i++);
    ASSERT_EQ(a.Significado("outlook"), i++);
    ASSERT_EQ(a.Significado("glue"), i++);
    ASSERT_EQ(a.Significado("break in"), i++);
    ASSERT_EQ(a.Significado("expenditure"), i++);
    ASSERT_EQ(a.Significado("pest"), i++);
    ASSERT_EQ(a.Significado("soldier"), i++);
    ASSERT_EQ(a.Significado("exception"), i++);
    ASSERT_EQ(a.Significado("inject"), i++);
    ASSERT_EQ(a.Significado("manage"), i++);
    ASSERT_EQ(a.Significado("wagon"), i++);
    ASSERT_EQ(a.Significado("hike"), i++);
    ASSERT_EQ(a.Significado("translate"), i++);
    ASSERT_EQ(a.Significado("action"), i++);
    ASSERT_EQ(a.Significado("agony"), i++);
    ASSERT_EQ(a.Significado("exhibition"), i++);
    ASSERT_EQ(a.Significado("state"), i++);
    ASSERT_EQ(a.Significado("sentiment"), i++);
    ASSERT_EQ(a.Significado("ceremony"), i++);
    ASSERT_EQ(a.Significado("inhabitant"), i++);
    ASSERT_EQ(a.Significado("solution"), i++);
    ASSERT_EQ(a.Significado("carpet"), i++);
    ASSERT_EQ(a.Significado("costume"), i++);
    ASSERT_EQ(a.Significado("end"), i++);
    ASSERT_EQ(a.Significado("please"), i++);
    ASSERT_EQ(a.Significado("ribbon"), i++);
    ASSERT_EQ(a.Significado("defeat"), i++);
    ASSERT_EQ(a.Significado("country"), i++);
    ASSERT_EQ(a.Significado("hope"), i++);
    ASSERT_EQ(a.Significado("impress"), i++);
    ASSERT_EQ(a.Significado("situation"), i++);
    ASSERT_EQ(a.Significado("cane"), i++);
    ASSERT_EQ(a.Significado("happen"), i++);
    ASSERT_EQ(a.Significado("square"), i++);
    ASSERT_EQ(a.Significado("blade"), i++);
    ASSERT_EQ(a.Significado("illness"), i++);
    ASSERT_EQ(a.Significado("freighter"), i++);
    ASSERT_EQ(a.Significado("asylum"), i++);
    ASSERT_EQ(a.Significado("salt"), i++);
    ASSERT_EQ(a.Significado("progressive"), i++);
    ASSERT_EQ(a.Significado("transaction"), i++);
    ASSERT_EQ(a.Significado("coffee"), i++);
    ASSERT_EQ(a.Significado("shareholder"), i++);
    ASSERT_EQ(a.Significado("suit"), i++);
    ASSERT_EQ(a.Significado("umbrella"), i++);
    ASSERT_EQ(a.Significado("tribute"), i++);
    ASSERT_EQ(a.Significado("sigh"), i++);
    ASSERT_EQ(a.Significado("due"), i++);
    ASSERT_EQ(a.Significado("hurl"), i++);
    ASSERT_EQ(a.Significado("burial"), i++);
    ASSERT_EQ(a.Significado("quote"), i++);
    ASSERT_EQ(a.Significado("ample"), i++);
    ASSERT_EQ(a.Significado("rough"), i++);
    ASSERT_EQ(a.Significado("normal"), i++);
    ASSERT_EQ(a.Significado("prey"), i++);
    ASSERT_EQ(a.Significado("walk"), i++);
    ASSERT_EQ(a.Significado("color-blind"), i++);
    ASSERT_EQ(a.Significado("broken"), i++);
    ASSERT_EQ(a.Significado("energy"), i++);
    ASSERT_EQ(a.Significado("vigorous"), i++);
    ASSERT_EQ(a.Significado("team"), i++);
    ASSERT_EQ(a.Significado("tax"), i++);
    ASSERT_EQ(a.Significado("information"), i++);
    ASSERT_EQ(a.Significado("emergency"), i++);
    ASSERT_EQ(a.Significado(""), i++);

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
