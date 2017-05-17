#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class Elem>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.

		void agregar(const Elem&);


		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const Elem&) const;


		// Borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const Elem&);

		// Devuelve el mínimo elemento del conjunto según <.
		const Elem& minimo() const;

		// Devuelve el máximo elemento del conjunto según <.
		const Elem& maximo() const;

		// Devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// Muestra el conjunto como una secuencia ordenada de menor a mayor.
    // por ejemplo: 
    //  {3,2,5,1,6}.to_string() = "1 2 3 5 6 "
    //  {}.to_string() == " "
    //  Sin las comillas
    //  Hint: pueden usar estructuras adicionales para resolverlo (o no)
		void to_string(std::ostream&) const;

    std::string show() const {
      std::ostringstream os;
      os << *this;
      return os.str();
    }

		friend ostream& operator<<(ostream& os, const Conjunto<Elem> &c) {
			c.to_string(os);
			return os;
		}

	private:

		// La representación de un nodo interno.
		struct Nodo {
			// El constructor, toma el elemento al que representa el nodo.
			Nodo(const Elem& v);
			// El elemento al que representa el nodo.
			Elem valor;
			// Puntero a la raíz del subárbol izq.
			Nodo* izq;
			// Puntero a la raíz del subárbol der.
			Nodo* der;
        //    Nodo* mami;
		};

		// Puntero a la raíz de nuestro árbol.
    // Pueden completarlo con más variables
		Nodo* raiz_;
        int cantElems;

       typedef std::unique_ptr<Elem> Type;
	// funciones auxiliares
    void  borrarYMantener(const Elem& v, Nodo* miNodo, Nodo *mami);
    Nodo* sucesorInOrder(Nodo* miNodo);
    bool soyHijoMenor(Nodo* miNodo, Nodo* mami);

};

template <class Elem>
void Conjunto<Elem>::borrarYMantener(const Elem& v, Conjunto<Elem>::Nodo *miNodo, Conjunto<Elem>::Nodo *mami) {
    if ((miNodo->der == nullptr) && (miNodo->izq == nullptr))
    {
        delete miNodo;
    } else
    {
        if (miNodo->der == nullptr)
        {
            if (mami->der == miNodo)
            {
                mami->der = miNodo->izq;
            } else {mami->izq = miNodo->izq;}
             delete miNodo;
        } else
        {
            Nodo* sucesor = sucesorInOrder(miNodo);
            miNodo->valor = sucesor->valor;

            delete sucesor;
        }
    }
}

template <class Elem>
typename Conjunto<Elem>::Nodo* Conjunto<Elem>::sucesorInOrder(Conjunto<Elem>::Nodo *miNodo)
{
    Nodo* actual = miNodo;
    if (actual != nullptr) actual = actual->izq;
    while (actual != nullptr && actual->der != nullptr)
    {
        actual = actual->der;
    }
    return actual; //ver si no pierdo memoriass
}
template <class Elem>
bool Conjunto<Elem>::soyHijoMenor(Conjunto<Elem>::Nodo *miNodo, Conjunto<Elem>::Nodo *mami)
{
    return mami->izq == miNodo;
}

template <class Elem>
Conjunto<Elem>::Nodo::Nodo(const Elem& v) : valor(v), izq(nullptr), der(nullptr) {}

template <class Elem>
Conjunto<Elem>::Conjunto() : raiz_(nullptr), cantElems(0)
{
}

template <class Elem>
Conjunto<Elem>::~Conjunto() {
    Nodo* actual = raiz_;
    while (raiz_ != nullptr)
    {
        remover(raiz_->valor);
    }
}

template <class Elem>
bool Conjunto<Elem>::pertenece(const Elem& miElem) const {
    Nodo* actual = raiz_;
    while (actual != nullptr)
    {
        if (actual->valor > miElem)
        {
            actual = actual->izq;
        } else
        {
            if (actual->valor < miElem)
            {
                actual = actual->der;
            } else
            {
                return true;
            }
        }
    }
    return false;
}

template <class Elem>
void Conjunto<Elem>::agregar(const Elem& miElem)
{
    Nodo* actual = raiz_;
    bool insertado = false;
    while (actual != nullptr && !insertado)
    {
        if (miElem > actual->valor)
        {
            if (actual->der != nullptr) {
                actual = actual->der;
            } else
            {
                actual->der = new Nodo(miElem);
                cantElems++;
                insertado = true;
            }
        } else
        {
            if (actual->izq != nullptr) {
                actual = actual->izq;
            } else
            { if(actual->valor > miElem) {
                    actual->izq = new Nodo(miElem);
                    insertado = true;
                    cantElems++;
                }
            }
        }
    }
    if (raiz_ == nullptr)
    {
        raiz_ = new Nodo(miElem);
        cantElems++;
    }
}

template <class Elem>
unsigned int Conjunto<Elem>::cardinal() const {
	return cantElems;
}

template <class Elem>
void Conjunto<Elem>::remover(const Elem& miElem) {
    Nodo* mami = nullptr;
    Nodo* actual = raiz_;
    while (actual != nullptr)
    {
        if (actual->valor > miElem)
        {
            actual = actual->izq;
        } else
        {
            if (actual->valor < miElem)
            {
                actual = actual->der;
            } else { borrarYMantener(miElem, actual, mami);
                cantElems--;}
        }

        mami = actual;
    }
}

template <class Elem>
const Elem&  Conjunto<Elem>::minimo() const {
	// Completar con implementación
  return raiz_->valor;
}

template <class Elem>
const Elem&  Conjunto<Elem>::maximo() const
{
	// Completar con implementación
  return raiz_->valor;
}

template <class Elem>
void Conjunto<Elem>::to_string(std::ostream& os) const {

}

#endif // CONJUNTO_HPP_
