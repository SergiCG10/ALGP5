#include <iostream>

#include "Laberinto.h"

using namespace std;

void Laberinto::inicializar(int f, int c){

    laberinto = new int* [f];

    for(int i = 0; i < f; i++){
        laberinto[i] = new int [c];
        for(int j = 0; j < c; j++){
            laberinto [i][j] = 0;
        }
    }

    recorridos = new bool* [f];

    for(int i = 0; i < f; i++){
        recorridos[i] = new bool [c];
        for(int j = 0; j < c; j++){
            recorridos [i][j] = false;
        }
    }
}   

void Laberinto::liberar(){
    for(int i = 0; i< filas; i++){
        delete [] laberinto[i];
    }
    delete [] laberinto;

    for(int i = 0; i< filas; i++){
        delete [] recorridos[i];
    }
    delete [] recorridos;
}

Laberinto::Laberinto(){
    filas = 0;
    columnas = 0;
    monedas = 0;

    laberinto = NULL;
    inicio = make_pair(-1, -1);
    salida = make_pair(-1, -1);
}

Laberinto::Laberinto(int f, int c, int fIni, int cIni, int fFin, int cFin){
    if( f < 0 || c < 0){
        throw out_of_range("El numero de filas o de columnas es erróneo");
    }
    inicio = make_pair(fIni, cIni);
    if( fFin == -1 && cFin == -1){
        fFin = cFin = c;
    }
    salida = make_pair(fFin, cFin);
    inicializar(f,c);
    filas = f;
    columnas = c;
    monedas = 0;
}

int Laberinto::getFilas() const{
    return filas;
}

int Laberinto::getColumnas() const{
    return columnas;
}

int Laberinto::getMonedas() const{
    return monedas;
}
const int& Laberinto::getPosicion(int f, int c) const{
    if(f < 0 || f >= this->getFilas() || c < 0 || c >= this->getColumnas()){
        throw out_of_range("getPosicion::Valor de fila o de columna erróneo");
    }
    return laberinto[f][c];
}

int& Laberinto::setPosicion(int f, int c ){
    if(f < 0 || f >= this->getFilas() || c < 0 || c >= this->getColumnas()){
        throw out_of_range("setPosicion::Valor de fila o de columna erróneo");
    }
    return laberinto[f][c]; 
}

const bool& Laberinto::getRecorrida(int f, int c) const{
    if(f < 0 || f >= this->getFilas() || c < 0 || c >= this->getColumnas()){
        throw out_of_range("getRecorrida::Valor de fila o de columna erróneo");
    }
    return recorridos[f][c];
}

void Laberinto::setRecorrida(int f, int c, bool valor){
    if(f < 0 || f >= this->getFilas() || c < 0 || c >= this->getColumnas()){
        throw out_of_range("setRecorrida::Valor de fila o de columna erróneo");
    }
    if(valor == true && getPosicion(f,c) == 1){
        monedas++;
    }
    recorridos[f][c] = valor;
}

const pair<int,int>& Laberinto::getPosicionInicial() const{
    return inicio;
}

void Laberinto::setPosicionInicialTo(pair<int,int> p){
    if(p.first < 0 || p.first >= this->getFilas() || p.second < 0 || p.second >= this->getColumnas()){
        throw out_of_range("setPosicionInicialTo::Valor de fila o de columna erróneo");
    }
    recorridos[p.first][p.second] = 1;
    inicio = p;
}

const pair<int,int>& Laberinto::getPosicionFinal() const{
    return salida;
}

void Laberinto::setPosicionFinalTo(pair<int,int> p){
    if(p.first < 0 || p.first >= this->getFilas() || p.second < 0 || p.second >= this->getColumnas()){
        throw out_of_range("setPosicionInicialTo::Valor de fila o de columna erróneo");
    }
    salida = p;
}

Laberinto::Laberinto(const Laberinto& lab){
    inicio = lab.inicio;
    salida = lab.salida;
    this->filas = lab.getFilas();
    this->columnas = lab.getColumnas();
    monedas = 0;
    inicializar(filas, columnas);

    for(int i = 0; i < filas; i++){
        for(int j = 0; j <columnas; j++){
            this->setPosicion(i,j) = lab.getPosicion(i,j);
        }
    }

    for(int i = 0; i < filas; i++){
        for(int j = 0; j <columnas; j++){
            this->setRecorrida(i,j, lab.getRecorrida(i,j)) ;
        }
    }
}

Laberinto& Laberinto::operator = (const Laberinto& lab){
    liberar();
    inicio = lab.inicio;
    salida = lab.salida;
    this->filas = lab.getFilas();
    this->columnas = lab.getColumnas();
    monedas = 0;
    inicializar(filas, columnas);

    for(int i = 0; i < filas; i++){
        for(int j = 0; j <columnas; j++){
            this->setPosicion(i,j) = lab.getPosicion(i,j);
        }
    }
    
    for(int i = 0; i < filas; i++){
        for(int j = 0; j <columnas; j++){
            this->setRecorrida(i,j, lab.getRecorrida(i,j)) ;
        }
    }
    
    
    return *this;
}

bool Laberinto::esSalida(int f, int c){
    return ( f == salida.first  ) && ( c == salida.second );
}

bool Laberinto::loadLaberinto(string fichero){

    liberar();
    ifstream fich(fichero);
    int f, c = 0;
    int posInicialF = 0, posInicialC = 0;
    int posFinalF = 0, posFinalC = 0;
    bool hecho = true;
    
    if(fich){
        fich >> f >> c;
        fich >> posInicialF >> posInicialC;
        fich >> posFinalF >> posFinalC;

        if(f < 0 || c < 0){
            throw out_of_range("Error, el lado del laberinto almacenado en el fichero es erróneo");
        }
        
        inicializar(f , c);
        this->filas = f;
        this->columnas = c;
        monedas = 0;
        inicio = make_pair(posInicialF,posInicialC);
        salida = make_pair(posFinalF, posFinalC);

        int aux;
        for(int i =0 ; i< filas; i++){
            for(int j = 0; j < columnas; j++){
                fich >> aux;
                this->setPosicion(i,j) = aux;
            }
        }
        
        fich.close();
    }else{
        cerr<< "Error al abrir el fichero de entrada"<<endl;
        hecho = false;
        
    }

    return hecho;
}

bool Laberinto::saveLaberinto(string fichero){

    ofstream f(fichero);
    bool hecho = true;

    if(f){
        f << this->getFilas() <<" "<< this->getColumnas();
        f <<endl;
        f << inicio.first << " " << inicio.second <<endl;
        f << salida.first << " " << salida.second <<endl;
        for(int i = 0; i < this->getFilas(); i++){
            for(int j = 0; j < this->getColumnas(); j++){
                f << getPosicion(i,j) << " ";
            }
            f << endl;
        }

        f.close();
    }else{
        hecho = false;
    }

    return hecho;
    
}

void Laberinto::imprimirLaberinto(){
    if(this->getFilas() >1 && this->getColumnas() > 1){
        cout<<endl;
        for(int i = 0; i < columnas +2; i++){
            cout<<" ■";
        }
        cout<<endl;
        for(int i = 0; i < filas; i++){
            if(i != filas -1){
                    cout<<" ■";
            }else{
                cout<<"  ";
            }
            for(int j = 0; j < columnas; j++){
                if( this->getPosicion(i,j) == 1){
                    cout<<" ○";
                }else if( this->getPosicion(i,j) == -1 ) {
                    cout<<" ■";
                }else{
                    cout<<"  ";
                }
            }
            if(i != 0){
                    cout<<" ■";
            }
            cout<<endl;
        }
        for(int i = 0; i < columnas +2; i++){
            cout<<" ■";
        }
        cout<<endl<<endl;
        cout<<"Monedas: ○"<<endl;
        cout<<endl<<endl;
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}

void Laberinto::imprimirLaberintoRecorrido(){
    if(this->getFilas() >1 && this->getColumnas() > 1){
        cout<<endl;
        for(int i = 0; i < columnas +2; i++){
            cout<<" ■";
        }
        cout<<endl;
        for(int i = 0; i < filas; i++){
            if(i != filas-1){
                    cout<<" ■";
            }else{
                cout<<"  ";
            }
            for(int j = 0; j < columnas; j++){
                
                if( !getRecorrida(i,j)){
                    if( this->getPosicion(i,j) == 1){
                        cout<<" ○";
                    }else if( this->getPosicion(i,j) == -1 ) {
                        cout<<" ■";
                    }else{
                        cout<<"  ";
                    }
                    
                }else{
                    cout<<" □";
                }
            }
            if(i != 0){
                    cout<<" ■";
            }
            cout<<endl;
        }
        for(int i = 0; i < columnas +2; i++){
            cout<<" ■";
        }
        cout<<endl<<endl;
        cout<<"Monedas: ○"<<endl;
        cout<<"Numero de monedas obtenidas: "<<this->getMonedas();
        cout<<endl<<endl;
    }else{
        cout<<"El tamaño del laberinto es demasiado pequeño, o es 0"<<endl;
    }
    
}
