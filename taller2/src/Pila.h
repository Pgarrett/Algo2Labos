#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 * 
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:

    // Constructor sin parámetros. Crea una pila vacía.
    Pila();

    // Constructor por copia. Crea una nueva instancia de una Pila
    // que debe ser igual a la pasada por parámetro.
    Pila(const Pila& otra);

    // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
    ~Pila();

    // El constructor puede ser visto como un generador
    void apilar(const T& elem);

    // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
    // PRE: la pila no es vacía
    void desapilar();
  
  // Observadores básicos

    // Devuelve true si la Pila es vacía, false en caso contrario.
    bool esVacia() const;

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    T& tope();

    // Devuelve una referencia al elemento en el tope de la Pila.
    // PRE: La Pila no está vacía.
    const T& tope() const;

  // Otras operaciones

    // Devuelve la cantidad de elementos que hay en la pila.
    aed2::Nat tamanio() const;

    // Modifica esta instancia de Pila de tal manera que termine
    // siendo una copia de la Pila pasada por parámetro.
    // Devuelve una referencia a si misma.
    Pila& operator = (const Pila& otra);

    // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
    // Compara dos instancias de Pila. Devuelve true si son iguales
    // y false en caso contrario.
    bool operator == (const Pila& otra) const;

    /**
     * Muestra la lista en un ostream.
     * formato de salida:
     *   [e_0, e_1, e_2, ...]
     * donde e_i es el resultado del "mostrar" el elemento i.
     * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
     *
     * Nota: imprimir sobre os, es decir: os << "[" << ...
     * 
     * ATENCION:
     * 
     *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
     * 
     *  - El primer elemento que se muestra representa al tope de la pila, es
     *    decir, los elementos se muestran en orden inverso al que fueron apilados.
     */
    template<typename S>
    friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
      T elem;
      Nodo* sig;

      Nodo(T e)
      : elem (e)
      {
        sig = NULL;
      }

    };

    Nodo* tope_;
    aed2::Nat tamanio_;
};

template <typename T>
Pila<T>::Pila()
{
    this->tope_ = NULL;
    this->tamanio_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
  this->tope_ = NULL;
  this->tamanio_ = 0;
  if (!otra.esVacia())
  {
    // int t = otra.tamanio_;
    aed2::Nat t = otra.tamanio_;
    // int i = 0;
    aed2::Nat i = 0;
    Pila<T>* p = new Pila<T>();
    Nodo* n = otra.tope_;
    while (i < t)
    {
      p->apilar(n->elem);
      n = n->sig;
      i++;
    }
    i = 0;
    while (i < t)
    {
      this->apilar(p->tope());
      p->desapilar();
      i++;
    }

    //aca no tenes q borrar estas variables, por el aliasing podrias estan rompiendo toda la pila
    //o sea si [e_1,e_2,e_3] y e_3 = n, si n=null => e_3 = null y todo mal!!!
    n = NULL;
    delete n;
    p = NULL;
    delete p;
  }
}

template <typename T>
Pila<T>::~Pila()
{
  while (this->tamanio_ != 0)
  {
    desapilar();
  }
}

template <typename T>
void Pila<T>::apilar(const T& e)
{
  Nodo* n = new Nodo(e);
  if (this->tamanio_ == 0)
  {
    n->sig = NULL;
  }
  else
  {
    n->sig = this->tope_;
  }
  this->tope_ = n;
  //lo mismo q arriba con este delete, los deletes van en el desapilar 
  n = NULL;
  delete n;
  this->tamanio_++;
}

template <typename T>
void Pila<T>::desapilar()
{
  Nodo* antPrimero = this->tope_;
  if (antPrimero != NULL) {
    Nodo* siguiente = antPrimero->sig;
    this->tope_ = siguiente;
    //si le asignas null antes de borrarlo perdes la referencia, directamente tenes q llamar al delete y si a siguiente lo pones en null y y lo deleteas, tope_ = siguiente = null y encima deleteado, se rompio toda tu pila y todo mal!!!
    antPrimero = NULL;
    //Este delete deberia ir fuera del if, siempre que no sea una lista vacia deberias poder borrar el primero cuando desapilas
    delete antPrimero;
    siguiente = NULL;
    delete siguiente;
    this->tamanio_--;
  }
}

template <typename T>
bool Pila<T>::esVacia() const
{
  return this->tamanio_ == 0;
}

template <typename T>
T& Pila<T>::tope()
{
  return this->tope_->elem;
}

template <typename T>
const T& Pila<T>::tope() const
{
  return this->tope_->elem;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
  return this->tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator=(const Pila& otra)
{
  while (this->tamanio_ != 0)
  {
    desapilar();
  }
  aed2::Nat t = otra.tamanio_;
  aed2::Nat i = 0;
  // int t = otra.tamanio_;
  // int i = 0;
  Pila<T>* p = new Pila<T>();
  Nodo* n = otra.tope_;
  while (i < t)
  {
    p->apilar(n->elem);
    n = n->sig;
    i++;
  }
  i = 0;
  while (i < t)
  {
    this->apilar(p->tope());
    p->desapilar();
    i++;
  }
  //no lo voy a decir de nuevo (?)
  n = NULL;
  delete n;
  p = NULL;
  delete p;
  return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila)
{
  // Este codigo me suena familiar... jaja
  os << "[";
  aed2::Nat i = 0;
  aed2::Nat t = pila.tamanio_;
  Pila<T>* p = new Pila<T>(pila);
  while (i < t)
  {
    os << p->tope();
    if (i < t - 1) os << ", ";
    p->desapilar();
    i++;
  }
  p = NULL;
  delete p;
  os << "]";
}