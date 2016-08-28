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
  p.mostrar(std::cout);
  ASSERT_EQ(p.tamanio(), 1);
  ASSERT(!p.esVacia());
  std::cout << " // termino test apilar" << std::endl;
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
    ElemPila eP3 = p.tope();
    std::cout << "Tope: id=" << eP3.id << ". nombre=" << eP3.nombre << ". descripcion=" << eP3.descripcion << std::endl;
    ElemPila eP2;
    eP2.id = 2;
    eP2.nombre = "elem2";
    eP2.descripcion = "descripcionElem2";
    p.apilar(eP2);
    if (p.tamanio() == 2)
    {
      p.mostrar(std::cout);
      ElemPila eP4 = p.tope();
      std::cout << "Tope: id=" << eP4.id << ". nombre=" << eP4.nombre << ". descripcion=" << eP4.descripcion << std::endl;
      p.desapilar();
      ElemPila eP5 = p.tope();
      std::cout << "Tope: id=" << eP5.id << ". nombre=" << eP5.nombre << ". descripcion=" << eP5.descripcion << std::endl;
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
  std::cout << " // termino test desapilar" << std::endl;
}

void test_desapilar2()
{
  ElemPila eP1;
  eP1.id = 1;
  eP1.nombre = "elem1";
  eP1.descripcion = "descripcionElem1";
  Pila p;
  p.apilar(eP1);
  p.desapilar();
  ASSERT_EQ(p.tamanio(), 0);
  std::cout << " // termino test desapilar2" << std::endl;
}

void test_asignacion() {
  // HACER	
  ASSERT(true);
}

void dameTope()
{
  Pila p;
  if (!p.esVacia())
  {
    p.tope();
  }
  ElemPila eP1;
  eP1.id = 1;
  eP1.nombre = "elem1";
  eP1.descripcion = "descripcionElem1";
  p.apilar(eP1);
  ElemPila eP2;
  eP2.id = 2;
  eP2.nombre = "elem2";
  eP2.descripcion = "descripcionElem2";
  p.apilar(eP2);
  ElemPila eP3 = p.tope();
  std::cout << "Tope: id=" << eP3.id << ". nombre=" << eP3.nombre << ". descripcion=" << eP3.descripcion << std::endl;
  std::cout << " // termino test dameTope" << std::endl;
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_desapilar2);
  RUN_TEST(dameTope);
  RUN_TEST(test_asignacion);
  // HACER MAS TEST

  return 0;
}
