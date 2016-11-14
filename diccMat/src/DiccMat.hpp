#ifndef DICCMAT_H_
#define DICCMAT_H_

#include "aed2/Arreglo.h"
#include "aed2/Conj.h"

namespace aed2 {

    struct Coor {
        Nat latitud;
        Nat longitud;

        Coor(const Nat la, const Nat lo) : latitud(la), longitud(lo) {}
    };

    template<class S>
    class DiccMat {
    public:

        typedef String K;

        DiccMat(const Nat l, const Nat a);

        ~DiccMat();

        bool Definido(const Coor &clave) const;

        void Definir(const Coor &clave, const S &significado);

        S& Significado(const Coor &clave);

        void Borrar(const Coor &clave);

        Conj<Coor>& Claves() const;
        Nat CantClaves() const;

    private:

        struct TElem {
            bool infoValida;
            Conj<Coor>::Iterador itClaves;
            S signif;

            TElem(const bool infoV, const S &v) : infoValida(infoV), signif(v) {
                Conj<Coor> c = Conj<Coor>();
                itClaves = c.CrearIt();
            }
        };

        Arreglo<TElem>* _posiciones;
        Conj<Coor>* _claves;
        Nat _ancho;
        Nat _largo;
        Nat _cantClaves;

        Nat aplanar(const Coor &c) const {
            return (c.longitud * this->_ancho) + c.latitud;
        }

    };

/********************************************************************************
 * Implementacion
 ********************************************************************************/

    template<class S>
    DiccMat<S>::DiccMat(const Nat l, const Nat a) {
        this->_posiciones = new Arreglo<TElem>(a * l);
        this->_claves = new Conj<Coor>();
        this->_ancho = a;
        this->_largo = l;
    }

    template<class S>
    DiccMat<S>::~DiccMat() {
        delete this->_posiciones;
        this->_posiciones = NULL;
        delete this->_claves;
        this->_claves = NULL;
    }

    template<class S>
    bool DiccMat<S>::Definido(const Coor &clave) const {
        Nat claveA = aplanar(clave);
        if (this->_posiciones->Definido(claveA)) {
            TElem t = this->_posiciones->operator[](claveA);
            return t.infoValida;
        }
        return false;
    }


    template<class S>
    void DiccMat<S>::Definir(const Coor &clave, const S &significado) {
        Nat claveA = aplanar(clave);
        TElem t = TElem(true, significado);
        if (this->Definido(clave)) {
            TElem t2 = this->_posiciones->operator[](claveA);
            t.itClaves = t2.itClaves;
        } else {
            t.itClaves = this->_claves->AgregarRapido(clave);
            this->_cantClaves++;
        }
        this->_posiciones->Definir(claveA, t);
    }


    template<class S>
    S& DiccMat<S>::Significado(const Coor &clave) {
        assert(Definido(clave));
        TElem* t = &(this->_posiciones)->operator[](aplanar(clave));
        return t->signif;
    }


    template<class S>
    void DiccMat<S>::Borrar(const Coor &clave) {
        assert(Definido(clave));
        Nat claveA = aplanar(clave);
        TElem t = this->_posiciones->operator[](claveA);
        t.itClaves.EliminarSiguiente();
        this->_posiciones->operator[](claveA) = TElem(false, t.signif);
        this->_cantClaves--;
    }

    template<class S>
    Conj<Coor>& DiccMat<S>::Claves() const {
        return *this->_claves;
    }

    template<class S>
    Nat DiccMat<S>::CantClaves() const {
        return this->_cantClaves;
    }

} /* namespace aed2 */

#endif /* DiccMat_H_ */
