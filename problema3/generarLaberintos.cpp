#include <iostream>
#include "Laberinto.h"

using namespace std;

int main( int argc, char* argv[] ){

    Laberinto l;
    int opcion;
    bool almacenado = false;
    string directorioGuardado;
    string aux;
    string nombre;
    int tipo;
    bool nombreGuardado = false;
    string nombreFichero;
    char respuesta = 'n';
    int posX, posY;

    if( argc != 2 && argc != 1){
        cerr<<"Error. Parámetros incorrectos."<<endl;
        cerr<<"Uso: ./generarLaberintos"<<endl;
        cerr<<"opcional: <nombreDelDirectorioDeGuardado>";
    }
    if(argc == 2){
        directorioGuardado = argv[1];
    }else{
        directorioGuardado = ".";
    }
    
    do{
        cout<<"Que desea hacer?"<<endl;
        cout<<"\t1: crear un laberinto"<<endl;
        cout<<"\t2: editar el laberinto almacenado"<<endl;
        cout<<"\t3: editar la posición de inicio"<<endl;
        cout<<"\t4: editar la posición de salida"<<endl;
        cout<<"\t5: guardar el laberinto almacenado"<<endl;
        cout<<"\t6: cargar un laberinto almacenado"<<endl;
        cout<<"\t7: imprimir el laberinto almacenado"<<endl;
        cout<<"\t8: cambiar el directorio donde guardar"<<endl;
        cout<<"\totro: terminar"<<endl;
        cin>>opcion;
        switch (opcion){
            case 1:
                cout<<"De que tamaño desea crear el laberinto"<<endl;
                int filas;
                int columnas;
                cin>>filas;

                while(filas <= 0){
                    cout<<"El valor de filas no puede ser menor que 0\t";
                    cin>>filas;
                }

                cin>>columnas;

                while(columnas <= 0){
                    cout<<"El valor de columnas no puede ser menor que 0\t";
                    cin>>columnas;
                }

                almacenado = true;
                l = Laberinto(filas, columnas);

                int i,j;

                do{
                    cout<<"¿Que posición desea cambiar? (-1 para terminar) \t";
                    cin>>i;
                    while( i < -1 && i >= l.getFilas()){
                        cout<<"Numero de fila errónea, vuelva a introducir:\t";
                        cin>>i;
                    }
                    if(i != -1){
                        cin>>j;
                        while( j < -1 && j >= l.getColumnas()){
                            cout<<"Numero de columna errónea, vuelva a introducir:\t";
                            cin>>j;
                        }  
                        cout<<"Que desea que sea, muro (-1), casilla libre (0), casilla con moneda (1)"<<endl;
                        
                        cin>>tipo;
                        while(tipo != -1 && tipo != 0 && tipo != 1){
                            cout<<"Valor erróneo, vuelva a introducir, muro (-1), casilla libre (0), casilla con moneda (1)"<<endl;
                            cin>>tipo;
                        }
                        l.setPosicion(i,j) = tipo;

                    }
                    
                }while(i != -1);
                break;
            case 2:

                int f,c;
                bool valor;
                if(almacenado){

                    do{
                        cout<<"¿Que fila desea cambiar? (-1 para terminar) \t";
                        cin>>f;
                        while( f < -1 && f >= l.getFilas()){
                            cout<<"Numero de fila errónea, vuelva a introducir:\t";
                            cin>>f;
                        }
                        if(f != -1){
                            do{
                                cout<<"¿Que columna de la fila "<<f<<" desea cambiar?: (-1 para terminar)"<<endl;
                                cin>> c;
                                if(c >=0 && c <l.getColumnas() ){
                                    cout<<"Que desea que sea, muro (-1), casilla libre (0), casilla con moneda (1)"<<endl;
                                    cin>>tipo;
                                    while(tipo != -1 && tipo != 0 && tipo != 1){
                                        cout<<"Valor erróneo, vuelva a introducir, muro (-1), casilla libre (0), casilla con moneda (1)"<<endl;
                                        cin>>tipo;
                                    }
                                    l.setPosicion(f,c) = tipo;
                                }else if( c != -1){
                                    cout<<"Valor "<<c<<"de columna erróneo"<<endl;
                                }
                            }while( c != -1);

                        }
                        
                    }while(f != -1);
                }else{
                    cout<<"No hay ningún laberinto almacenado"<<endl;
                }
                
                break;
            case 3:

                if(almacenado){
                    cout<<"La posición actual de inicio es "<<l.getPosicionInicial().first<<" "<<l.getPosicionInicial().second<<endl;
                    cout<<"¿Que nueva posición de inicio desea establecer?\t ";
                    cin>>posX>>posY;
                    l.setPosicionInicialTo( make_pair(posX, posY));
                }else{
                    cout<<"No hay ningún laberinto almacenado"<<endl;
                }

                break;
            case 4:

                if(almacenado){
                    cout<<"La posición actual de salida es "<<l.getPosicionFinal().first<<" "<<l.getPosicionFinal().second<<endl;
                    cout<<"¿Que nueva posición de salida desea establecer?\t ";
                    cin>>posX>>posY;
                    l.setPosicionFinalTo( make_pair(posX, posY));
                }else{
                    cout<<"No hay ningún laberinto almacenado"<<endl;
                }
                break;
            case 5:
                aux = directorioGuardado;
                if(nombreGuardado && almacenado){
                    cout<<"¿Desea guardar el laberinto con otro nombre? s/n \t";
                    cin>>respuesta;

                }

                if( (!nombreGuardado || respuesta == 's' ) && almacenado){
                    respuesta = 'n';
                    cout<<"¿Como desea que se llame el fichero donde va a guardar el laberinto? \t";
                    cin>>nombre;
                    aux += "/" + nombre;
                    nombreFichero = aux;
                    nombreGuardado = true;
                }else{
                    cout<<"No hay ningún laberinto guardado"<<endl;
                }
                if(almacenado)
                    l.saveLaberinto( nombreFichero );

                break;
            case 6:
                aux = ".";
                cout<<"¿Como se llama el fichero de donde va a copiar el laberinto? \t";
                cin>>nombre;
                aux += "/" + nombre;
                nombreGuardado = true;
                nombreFichero = aux;
                l.loadLaberinto( nombreFichero );
                almacenado = true;
                break;
            case 7:
                l.imprimirLaberinto();
                break;
            case 8:
                cout<<"Introduzca la nueva carpeta donde guardar: \t";
                cin>>directorioGuardado;
                break;
            default :
                opcion = -1;
        }
    }while(opcion >0 && opcion <9);
}