#include "Pila.h"
#include "mini_test.h"

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p;
  ASSERT_EQ(p.tamanio(), 0);
  ASSERT(p.esVacia());
}

void test_apilar() {
  ElemPila eP1;
  eP1.id = 1;
  eP1.nombre = "elem1";
  eP1.descripcion = "descripcionElem1";
  Pila p;
  p.apilar(eP1);
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT(!p.esVacia());
  // ASSERT(false);
}

void test_desapilar() {
  ElemPila eP1;
  eP1.id = 1;
  eP1.nombre = "elem1";
  eP1.descripcion = "descripcionElem1";
  Pila p;
  p.apilar(eP1);
  // std::cout << std::endl;
  if (p.tamanio() == 1)
  {
    ElemPila eP2;
    eP2.id = 2;
    eP2.nombre = "elem2";
    eP2.descripcion = "descripcionElem2";
    p.apilar(eP2);
    if (p.tamanio() == 2)
    {
      p.desapilar();
      ASSERT_EQ(p.tamanio(), 1);
    }
    else {
      ASSERT(false);
    }
  }
  else 
  {
    ASSERT(false);
  }
}

void test_asignacion() {
  // HACER	
  ASSERT(false);
}

void dameTope()
{
  if (ASSERT(!p.esVacia()))
  {
    p.tope();
  }
  ElemPila eP1;
  eP1.id = 1;
  eP1.nombre = "elem1";
  eP1.descripcion = "descripcionElem1";
  Pila p;
  p.apilar(eP1);
  ElemPila eP2;
  eP2.id = 2;
  eP2.nombre = "elem2";
  eP2.descripcion = "descripcionElem2";
  p.apilar(eP2);

  ElemPila eP3 = p.tope();
  std::cout << "Tope: id=" << eP3.id << ". nombre=" << eP3.nombre << ". descripcion=" << eP3.descripcion << std::endl;
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(dameTope);
  RUN_TEST(test_asignacion);
  // HACER MAS TEST

  return 0;
}
