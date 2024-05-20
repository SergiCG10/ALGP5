#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "Laberinto.h"

using namespace std;

int arriba( vector<vector<int>> m, int i, int j){
    if( i > 0){
        return  m[i-1][j];
    }else{
        return -1;
    }
}

int derecha(vector<vector<int>> m, int i, int j){
   
    if(j + 1  < m[i].size() ){
        return m[i][j+1];
    }else{
        return -1;
    }
}

int diagonalSupDcha(vector<vector<int>> m, int i, int j){
    if( i > 0 && j +1 < m[i].size() ){
        return m[i-1][j+1];
    }else{
        return -1;
    }
}

int maximo(int n, int m, int l){
    int max;

    max = n;

    if(m > max){
        max = m;
    }
    if(l > max){
        max = l;
    }

    return max;
}

void imprimir(vector<vector<int>>matriz){
    cout<<"    ";
    for(int j = 0; j < matriz[0].size() ;j++){
        cout<<j<<"  ";
    }
    cout<<endl;
    for(int i = 0; i < matriz.size(); i++){
        cout<<i<<"  ";
        for(int j = 0; j < matriz[i].size(); j++){
            if(matriz[i][j] == -1 || matriz[i][j]> 10){
                cout<<matriz[i][j]<<" ";
            }else{
                cout<<" "<<matriz[i][j]<<" ";
            }    
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

vector< vector<int> > generarMatrizMonedas(Laberinto l){
    vector< vector<int>> salida;
    salida.resize(l.getFilas());
    int valor = 0;
    bool llegamosMuro = false;

    for(int i = 0; i< l.getFilas(); i++){
        salida[i].resize(l.getColumnas());
    }

    //Rellenamos caso base para la posicion 0, n-1
    if(l.getPosicion(0, l.getColumnas()-1) != -1){
        salida[0][l.getColumnas()-1 ] = l.getPosicion(0,l.getColumnas() -1 ) == 1 ? 1: 0;
    }
    salida[0][l.getColumnas()-1 ] = -1;

    //Rellenamos caso base de la primera fila
    for(int j = l.getColumnas() - 2; j >= 0 ; j--){

        llegamosMuro = llegamosMuro || l.getPosicion(0,j) == -1;

        if(!llegamosMuro){
            valor = l.getPosicion(0,j+1) == 1 ? 1: 0;
            salida[0][j] = salida[0][j+1] + valor;
        }else{
            salida[0][j] = -1;
        }
        
    }

    llegamosMuro = false;
    //Rellenamos caso base de la primera columna
    for(int i = 1; i < l.getFilas(); i++){

        llegamosMuro = llegamosMuro || l.getPosicion(i,l.getColumnas()-1) == -1;

        if(!llegamosMuro){   
            valor = l.getPosicion(i-1,l.getColumnas()-1) == 1 ? 1: 0;
            salida[i][l.getColumnas()-1] = salida[i-1][l.getColumnas()-1] + valor;
        }else{
            salida[i][l.getColumnas()-1] = -1;
        }
        
    }

    llegamosMuro = false;    
    for(int i = 1; i < l.getFilas() ; i++){
        
        for(int j = l.getColumnas()-2; j >=0; j--){
            
            llegamosMuro = l.getPosicion(i,j) == -1;
            if(!llegamosMuro){
                
                valor = l.getPosicion(i,j) == 1 ? 1: 0;
                salida[i][j] = maximo( salida[i-1][j], salida[i][j+1], salida[i-1][j+1] ) ;

                if( salida[i][j]!=-1){
                    salida[i][j]+= valor;
                }

            }else{
               salida[i][j] = -1;
            }
            
        }
    }
    return salida;
}

pair< vector<pair<int,int>>, bool> reconstruirCamino(vector<vector<int>> matriz){
    vector<pair<int,int>> v;
    int posI = matriz.size() -1, posJ = 0;
    int max;
    bool posible = true;
    pair< vector<pair<int,int>>, bool> salida;

    if( matriz[0][matriz[0].size()] == -1){
        posible = false;
    }else{
        v.push_back( make_pair(posI,posJ));
    }

    while( (posI != 0 || posJ != matriz[0].size()-1 ) && posible ){

        max = maximo( arriba(matriz, posI, posJ), derecha(matriz, posI, posJ), diagonalSupDcha(matriz, posI, posJ) );

        if(max == -1){
            posible = false;
        }else{
            if( max == diagonalSupDcha(matriz, posI, posJ) ){
                posI--;
                posJ++;
            }else if(max ==  arriba(matriz, posI, posJ) ){
                posI--;
            }else if(max == derecha(matriz, posI, posJ)){
                posJ++;
            }else{
                cout<<"Error";
            }
            v.push_back( make_pair(posI,posJ) );
        } 
    }
    salida.first = v;
    salida.second = posible;

    return salida;
}

int main(int argc, char* argv[]){
    Laberinto lab;
    string archivo;
    vector<vector<int>> matriz;
    pair<vector<pair<int,int>>,bool> sol;
    const int tiempo = 500;
   

    if(argc == 2){
        archivo = argv[1];
        if(lab.loadLaberinto( archivo )){
        
            matriz = generarMatrizMonedas(lab);
            cout<<endl<<"Laberinto propuesto:"<<endl;
            lab.imprimirLaberinto();
            sol = reconstruirCamino(matriz);
            if(sol.second){
                imprimir(matriz);
            }

            cout<<"Introduzca cualquier letra para continuar"<<endl;
            string str;
            cin>>str;
            system("clear");
            
            if(sol.second){
                for(int i = sol.first.size()-1 ; i >= 0; i--){
                    cout<<"Una solución que maximiza el número de monedas es:"<<endl;
                    lab.imprimirLaberintoRecorrido();
                    std::this_thread::sleep_for(std::chrono::milliseconds(tiempo));
                    system("clear");
                    lab.setRecorrida( sol.first[i].first, sol.first[i].second, true ) ;
                }
                cout<<"Una solución que maximiza el número de monedas es:"<<endl;
                lab.imprimirLaberintoRecorrido();
            }else{
                cout<<"No hay solución para este laberinto"<<endl;
            }
            
        }else{
            cerr<<"Error abriendo el archivo"<<endl;
        }
    }else{
        cerr<<"Uso: ./problema3.bin laberintos/<nombreDelFichero"<<endl;
    }
   
}   
