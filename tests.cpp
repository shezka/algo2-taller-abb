/*
 * test.cpp
 *
 *  Created on: 04 may. 2017
 *      Author: Joaquín
 */

#include <functional>
#include <future>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "Conjunto.hpp"

using std::vector;

struct ConjuntoTest : public ::testing::Test {

	virtual void SetUp() {
		singleton.agregar(1);
		for(int i = 1; i <= 5; ++i) {
      degenerado_derecha.agregar(i);
			degenerado_izquierda.agregar(5-i);
		}
    balanceado.agregar(4);
    balanceado.agregar(6);
    balanceado.agregar(5);
    balanceado.agregar(7);
    balanceado.agregar(2);
    balanceado.agregar(3);
    balanceado.agregar(1);

	}

	Conjunto<int> vacio;
	Conjunto<int> singleton;
	Conjunto<int> degenerado_derecha;
	Conjunto<int> degenerado_izquierda;
  Conjunto<int> balanceado;

};

TEST_F(ConjuntoTest, Vacio) {
	EXPECT_FALSE(vacio.pertenece(42));
	EXPECT_EQ(vacio.cardinal(), 0);
}

TEST_F(ConjuntoTest, CardinalMaximoMinimo) {
	EXPECT_EQ(singleton.maximo(), 1);
	EXPECT_EQ(singleton.minimo(), 1);
	EXPECT_EQ(singleton.cardinal(), 1);
  EXPECT_EQ(singleton.maximo(), singleton.minimo());


	EXPECT_EQ(degenerado_derecha.minimo(), 1);
	EXPECT_EQ(degenerado_derecha.maximo(), 5);
	EXPECT_EQ(degenerado_izquierda.minimo(), 0);
	EXPECT_EQ(degenerado_izquierda.maximo(), 4);

	EXPECT_EQ(degenerado_derecha.cardinal(), 5);
	EXPECT_EQ(degenerado_izquierda.cardinal(), 5);

	EXPECT_EQ(degenerado_derecha.cardinal(), 5);
	EXPECT_EQ(degenerado_izquierda.cardinal(), 5);
}

TEST_F(ConjuntoTest, ActualizacionMaximoYMinimo) {
	EXPECT_EQ(degenerado_izquierda.minimo(), 0);
	EXPECT_EQ(degenerado_derecha.maximo(), 5);

  degenerado_derecha.remover(3);
	EXPECT_EQ(degenerado_derecha.maximo(), 5);
  degenerado_derecha.remover(5);
	EXPECT_EQ(degenerado_derecha.maximo(), 4);

  degenerado_izquierda.remover(3);
	EXPECT_EQ(degenerado_izquierda.minimo(), 0);
  degenerado_izquierda.remover(0);
	EXPECT_EQ(degenerado_izquierda.minimo(), 1);
}


TEST_F(ConjuntoTest, Pertenece) {
  for(int i = 1; i <= 5; ++i) {
    EXPECT_TRUE(degenerado_derecha.pertenece(i));
    EXPECT_TRUE(degenerado_izquierda.pertenece(5-i));
  }

  for(int i = 1; i <= 7; ++i) {
    EXPECT_TRUE(balanceado.pertenece(i));
  }

  degenerado_derecha.agregar(7);
  degenerado_izquierda.agregar(7);

  EXPECT_TRUE(degenerado_derecha.pertenece(7));
  EXPECT_TRUE(degenerado_izquierda.pertenece(7));

  EXPECT_FALSE(degenerado_derecha.pertenece(6));
  EXPECT_FALSE(degenerado_izquierda.pertenece(6));
  
  balanceado.remover(1);
  EXPECT_FALSE(balanceado.pertenece(1));
}

TEST_F(ConjuntoTest, Remover) {
  int cardinal = degenerado_derecha.cardinal();
  int c = 1;
  for(int i = 2; i <= 3; ++i) {
    degenerado_derecha.remover(i);
    EXPECT_EQ(degenerado_derecha.cardinal(), cardinal - c);

    degenerado_izquierda.remover(5-i);
    EXPECT_EQ(degenerado_izquierda.cardinal(), cardinal - c);

    c += 1; // Change name
  }

	/*Remover de elementos ausentes no debe restar cardinal*/
  vacio.remover(0);
  EXPECT_EQ(vacio.cardinal(), 0);
}

TEST_F(ConjuntoTest, Show) {
	EXPECT_EQ(vacio.show(), ""); 
	EXPECT_EQ(singleton.show(), "1 "); 
	EXPECT_EQ(degenerado_izquierda.show(), "0 1 2 3 4 "); 
	EXPECT_EQ(degenerado_derecha.show(), "1 2 3 4 5 "); 
	EXPECT_EQ(balanceado.show(), "1 2 3 4 5 6 7 "); 
}


struct Constructor {
	//Constructor() = delete;
	//Constructor& operator=(Constructor) = delete;
	bool operator<(const Constructor& c) const {return i < c.i;}
	bool operator>(const Constructor& c) const {return i > c.i;}
  bool operator==(const Constructor& c) const {return i == c.i;}
  bool operator!=(const Constructor& c) const {return i != c.i;}
	Constructor(int x) : i(x) {};
	int i;
};

TEST(Conjunto, Constructores) {
	Conjunto<Constructor> c;
	c.agregar(Constructor(3));
	ASSERT_EQ(c.minimo().i, 3);
	c.agregar(Constructor(4));
	ASSERT_EQ(c.maximo().i, 4);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
