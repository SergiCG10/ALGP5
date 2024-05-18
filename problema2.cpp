#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void ImprimeMatriz(vector<vector<int>> matrix);
void RellenarMatriz(vector<vector<int>> matrix);
static const int RETRASO=1;

int main(int argc, char* argv[])
{
    if(argc!=3){
        cout<<"Numero incorrecto de parametros. Ejecute el programa como sigue: % programa <num_ciudades> <semilla>"<<endl;
        return -1;
    }
    
    int ciudades=atoi(argv[1]);
    int semilla=atoi(argv[2]);
    char respuesta;
    vector<vector<int>> matrix;
    if(ciudades<4)
        ciudades=4;

    matrix.resize(ciudades);
    for(int i=0;i<ciudades;i++)
        matrix[i].resize(ciudades);

    cout<<"¿Desea rellenar la matriz a mano? (escriba 'y' en caso afirmativo)"<<endl;
    cin>>respuesta;
    
    if(respuesta=!'y')
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

    ImprimeMatriz(matrix);
    
    
    return 0;
}

void ImprimeMatriz(vector<vector<int>> matrix)
{
    for(int i=0; i<matrix.size();i++){
        for(int j=0;j<matrix.size();j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    cout<<endl;
}

void RellenarMatriz(vector<vector<int>> matrix){

}