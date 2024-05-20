#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void ImprimeMatriz(vector<vector<int>> matrix);
void Floyd(const vector<vector<int>> & vuelos, vector<vector<int>> & predecesores, vector<vector<int>> & tiempos);
void GetPath(const vector<vector<int>> & predecesores, int & partida, int & destino,vector<int> & camino);
static const int ESCALA=1;

int main(int argc, char* argv[])
{
    if(argc!=3){
        cout<<"Numero incorrecto de parametros. Ejecute el programa como sigue: % programa <num_ciudades> <semilla>"<<endl;
        return -1;
    }
    
    int ciudades=atoi(argv[1]);
    int semilla=atoi(argv[2]);
    char respuesta='\0';
    vector<vector<int>> matrix;
    if(ciudades<4)
        ciudades=4;

    matrix.resize(ciudades);
    for(int i=0;i<ciudades;i++)
        matrix[i].resize(ciudades);

    cout<<"¿Desea rellenar la matriz a mano? (escriba y en caso afirmativo)"<<endl;
    cin>>respuesta;
    
    if(respuesta !='y')
    {
        cout<<"Se procede a inicializar con valores aleatorios"<<endl;
        for(int i=0;i<ciudades;i++){
            for(int j=0;j<ciudades;j++){
                if(i!=j)
                    matrix[i][j]=rand()%10;
                else
                    matrix[i][j]=0;
            }
        }
    }else{
        for(int i=0;i<ciudades;i++){
            for(int j=0;j<ciudades;j++){
                if(i!=j){
                    cin>>matrix[i][j];
                }
                else
                    matrix[i][j]=0;
            }
        }    
    }

    int partida,destino;
    cout<<"\nSe muestran los vuelos disponibles a continuación."<<endl;
    ImprimeMatriz(matrix);
    cout<<"Introduzca ciudad de partida (int)"<<endl;
    cin>>partida;
    while(partida<0 || partida>ciudades-1)
    {
        cout<<"Introduzca una ciudad en el rango [0,"<<ciudades-1<<"]"<<endl;
        cin>>partida;
    }
    cout<<"Introduzca ciudad de destino (int)"<<endl;
    cin>>destino;
    while(destino<0 || destino>ciudades-1)
    {
        cout<<"Introduzca una ciudad en el rango [0,"<<ciudades-1<<"]"<<endl;
        cin>>destino;
    }

    if(partida==destino)
    {
        cout<<"El viaje tiene una duracion de 0 horas, la partida y el origen coinciden"<<endl;
        return 0;
    }
    else{
        vector<vector<int>> predecesores, tabla;
        Floyd(matrix,predecesores,tabla);
    
    
    vector<int> VueloMasCorto;
    GetPath(predecesores, partida, destino,VueloMasCorto);
    cout<<"Vuelo mas corto entre "<<partida<<" y "<<destino<<endl;
    for(int i=0;i<VueloMasCorto.size();i++)
        cout<<VueloMasCorto[i]<<" -> ";
        
    
    }
    return 0;
}

void ImprimeMatriz(vector<vector<int>> matrix)
{
    cout<<"    ";
    for(int i=0;i<matrix.size();i++)
        cout<<i+1<<" ";
    cout<<endl;
    cout<<"    ";

    for(int i=0;i<matrix.size();i++)
        cout<<"--";
    cout<<endl;
    for(int i=0; i<matrix.size();i++){
        cout<<i<<"|  ";
        for(int j=0;j<matrix.size();j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
}

void Floyd(const vector<vector<int>> & vuelos, vector<vector<int>> & predecesores, vector<vector<int>> & tiempos){
    
    int n=vuelos.size(); 
    tiempos=vuelos;
    //ImprimeMatriz(tiempos);
    predecesores.resize(n);
    for(int i=0;i<n;i++)
        predecesores[i].resize(n);
    for(int i=0;i<n;i++)
        predecesores[i][i]=-1;
                                //calculo de la tabla  
    for (int k=0; k<n; k++)
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++){
                if(tiempos[i][j]!=-1 && tiempos[i][k]!=-1 && tiempos[k][j]!=-1)
                    if (tiempos[i][k] + tiempos[k][j] < tiempos[i][j]){
                        tiempos[i][j] = tiempos[i][k] + tiempos[k][j];
                        predecesores[i][j]=k;
                    }
            }
    ImprimeMatriz(predecesores);
            
    
}

void GetPath(const vector<vector<int>> & predecesores, int & partida,int & destino, vector<int> & camino){
    if (predecesores[partida][destino] == -1) {
        return;
    }
    camino.push_back(partida);
    while (partida != destino) {
        partida = predecesores[partida][destino];
        camino.push_back(partida);
    }


}