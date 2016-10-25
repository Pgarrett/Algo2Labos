#ifndef DICCHASHCERRADO_H_
#define DICCHASHCERRADO_H_

#include "Lista.h"

#ifndef TAM_TABLA_INI
#define TAM_TABLA_INI 100
#endif
#ifndef UMBRAL_FC
#define UMBRAL_FC      0.75
#endif


namespace aed2 {

    template<class S>
    class DiccHashCerrado {
    public:

        typedef String K;

        DiccHashCerrado();

        ~DiccHashCerrado();

        bool Definido(const K &clave) const;

        void Definir(const K &clave, const S &significado);

        S &Significado(const K &clave);

        void Borrar(const K &clave);

        Nat CantClaves() const;

        // solo para test!!
        Lista<K> Claves() const;

        float factorCarga() const;

        Nat colisiones() const;

    private:

        struct TElem {
            K clave;
            S signif;

            TElem(const K &c, const S &v) : clave(c), signif(v) {}
        };


        Lista<TElem> *_tabla;
        Nat _cant_elems;
        Nat _tam;


        Nat fn_hash(const String &str) const {

            Nat hash = 0;
            for (unsigned int i = 0; i < str.length(); i++) {
                hash += (charToNat(str[i]) /** 2^(str.length() - i)*/);
            }
            hash = hash % _tam;

            return hash;
        }

        Nat charToNat(char c) const {
            return (Nat) (c);
        }


        void redimensionarTabla() {
            typename Lista<TElem>::Iterador itViejo;

            Nat tamViejo = this->_tam;
            this->_tam = this->_tam * 2;
            Lista<TElem> *tablaVieja = this->_tabla;
            this->_tabla = new Lista<TElem>[this->_tam];
            this->_cant_elems = 0;
            for (unsigned int i = 0; i < tamViejo; i++) {
                itViejo = tablaVieja[i].CrearIt();
                while (itViejo.HaySiguiente()) {
                    this->Definir(itViejo.Siguiente().clave, itViejo.Siguiente().signif);
                    itViejo.Avanzar();
                }
            }
            delete[] tablaVieja;
        }

    };

/********************************************************************************
 * Implementacion
 ********************************************************************************/

    template<class S>
    DiccHashCerrado<S>::DiccHashCerrado()
            : _cant_elems(0), _tam(TAM_TABLA_INI) {
        this->_tabla = new Lista<TElem>[TAM_TABLA_INI];
    }

    template<class S>
    DiccHashCerrado<S>::~DiccHashCerrado() {

        delete[] this->_tabla;
        this->_cant_elems = 0;
    }

    template<class S>
    bool DiccHashCerrado<S>::Definido(const K &clave) const {

        Nat hashValue = fn_hash(clave);
        typename Lista<TElem>::Iterador it;

        it = this->_tabla[hashValue].CrearIt();
        bool found = false;
        while (it.HaySiguiente() && !found) {
            if (it.Siguiente().clave == clave) {
                found = true;
            }
            it.Avanzar();
        }
        return found;
    }


    template<class S>
    void DiccHashCerrado<S>::Definir(const K &clave, const S &significado) {

        if (factorCarga() > UMBRAL_FC)
            redimensionarTabla();

        if (this->Definido(clave)) {
            this->Borrar(clave);
        }
        this->_tabla[fn_hash(clave)].AgregarAtras(*new TElem(clave, significado));
        this->_cant_elems++;
    }


    template<class S>
    S &DiccHashCerrado<S>::Significado(const K &clave) {

        assert(Definido(clave));
        Nat hashValue = fn_hash(clave);
        typename Lista<TElem>::Iterador it;

        it = this->_tabla[hashValue].CrearIt();
        bool found = false;
        S result;
        while (it.HaySiguiente() && !found) {
            if (it.Siguiente().clave == clave) {
                found = true;
                result = it.Siguiente().signif;
            }
            it.Avanzar();
        }
        return *(new S(result));
    }


    template<class S>
    void DiccHashCerrado<S>::Borrar(const K &clave) {

        assert(Definido(clave));

        Nat hashValue = fn_hash(clave);
        typename Lista<TElem>::Iterador it;

        it = this->_tabla[hashValue].CrearIt();
        bool found = false;
        while (it.HaySiguiente() && !found) {
            if (it.Siguiente().clave == clave) {
                found = true;
                it.EliminarSiguiente();
            } else {
                it.Avanzar();
            }
        }
        this->_cant_elems--;
    }

    template<class S>
    Nat DiccHashCerrado<S>::CantClaves() const {

        return this->_cant_elems;
    }

// solo para test!!
    template<class S>
    Lista<typename DiccHashCerrado<S>::K> DiccHashCerrado<S>::Claves() const {
        Lista<K> ret;
        typename Lista<TElem>::const_Iterador it;

        for (Nat i = 0; i < _tam; i++) {
            for (it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
                ret.AgregarAtras(it.Siguiente().clave);
        }

        return ret;
    }

// solo para test!!
    template<class S>
    float DiccHashCerrado<S>::factorCarga() const {

        return float(_cant_elems) / _tam;
    }

// solo para test!!
    template<class S>
    Nat DiccHashCerrado<S>::colisiones() const {

        Nat ret = 0;
        for (Nat i = 0; i < _tam; i++) {
            if (_tabla[i].Longitud() > 1)
                ret = ret + _tabla[i].Longitud() - 1;
        }

        return ret;
    }


} /* namespace aed2 */

#endif /* DICCHASHCERRADO_H_ */
