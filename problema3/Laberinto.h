#ifndef Laberinto
#define _LABERINTO

#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Clase Laberinto. Utilizada para representar un laberinto con funciones auxiliares para su construcción y resolución
 *
 * @param laberinto. Matriz booleana que contendrá el laberinto. -1 para valores donde hay pared, 0 si se puede pasar, 1 si hay una moneda
 * @param filas. Numero de filas del laberinto
 * @param columnas Numero de columnas del laberinto
 */
class Laberinto{
    private:

        int** laberinto;
        bool** recorridos;
        int filas;
        int columnas;
        int monedas;

        pair<int,int> inicio, salida;

        /**
         * @brief Funcion privada inicializar. Inicializa el laberinto con f filas y  c columnas
         *
         * @param f. Numero de filas de la matriz 
         * @param c Numero de columnas de la matriz
         */
        void inicializar(int f, int c);

        /**
         * @brief Funcion liberar. Libera la memoria de la matriz
         */
        void liberar();

    public:    

        /**
         * @brief Constructor por defecto de la clase laberinto. Crea un laberinto vacío, con 0 filas y 0 columnas
         */
        Laberinto();

        /**
         * @brief Constructor por parámetro de la clase laberinto. Crea un laberinto con f filas y c columnas, con todas las posiciones a true (recorribles)
         *
         * @param f. Numero de filas de la matriz 
         * @param c Numero de columnas de la matriz
         *
         */
        Laberinto(int f, int c, int fIni = 0, int cIni = 0, int fFin = -1, int cFin = -1);

        /**
         * @brief Funcion getFilas. Devuelve el tamaño de filas de la matriz 
         */
        int getFilas() const;

        /**
         * @brief Funcion getColumnas. Devuelve el tamaño de columnas de la matriz 
         */
        int getColumnas() const;

        /**
         * @brief Funcion getMonedas. Devuelve las monedas recolectadas;
         */
        int getMonedas() const;
        /**
         * @brief Funcion getPosicion. Devuelve el valor de una casilla (f,c). Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const int& getPosicion(int f, int c) const;

        /**
         * @brief Funcion setPosicion. Establece el valor de una casilla (f,c). Función setter
         * Si el valor es -1 (una pared), si es 0 (camino), y para 1 sería una moneda.
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        int& setPosicion(int f, int c);

        /**
         * @brief Funcion getRecorrida. Devuelve si casilla (f,c) ha sido recorrida. Función getter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        const bool& getRecorrida(int f, int c) const;

        /**
         * @brief Funcion setRecorrida. Establece el valor de una casilla (f,c). Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         * @param valor Valor nuevo para la posicion (f,c) de recorridos
         */
        void setRecorrida(int f, int c, bool valor);

        /**
         * @brief Funcion getPosicionInicial. Devuelve la posicion inicial. Función getter
         */
        const pair<int,int>& getPosicionInicial() const;

        /**
         * @brief Funcion setPosicionInicialTo. Establece la posicion inicial. Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        void setPosicionInicialTo(pair<int,int> p);

        /**
         * @brief Funcion getPosicionFinal. Devuelve la posicion final. Función getter
         */
        const pair<int,int>& getPosicionFinal() const;

        /**
         * @brief Funcion setPosicionFinalTo. Establece la posicion final. Función setter
         *
         * @param f Filas de la posición
         * @param c Columnas de la posición
         */
        void setPosicionFinalTo(pair<int,int> p);
        
        /**
         * @brief Constructor de copia de la clase laberinto. Crea un laberinto a partir de otro.
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto(const Laberinto& lab);

        /**
         * @brief Operador de asignación, copia un laberinto en otro.   
         *
         * @param lab. Laberinto del que copiar el nuestro
         */
        Laberinto& operator = (const Laberinto& lab);

        /**
         * @brief Funcion salida. Determina si estás en la salida o no a partir de la posicion actual
         */
        bool esSalida(int f, int c);

        /**
         *
         */
        void loadLaberinto(string fichero);

        /**
         *
         */
        void saveLaberinto(string fichero);
        /**
         * @brief Funcion imprimirLaberinto. Imprime el laberinto por pantalla
         */
        void imprimirLaberinto();

        void imprimirLaberintoRecorrido();
};

#endif 