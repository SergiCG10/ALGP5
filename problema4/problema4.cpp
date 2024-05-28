#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

//para escribir menos
typedef vector<vector<int>> vvint;

void imprimirMatriz(const vvint& orig);
vvint SolucionProblema4(const vvint& mountain);
int costeMinimo(const vvint& costes, vvint& cache,
    int altura, int anchura);
//Sobrecarga de funciones
int minimo(int valor1, int valor2);
int minimo(int valor1, int valor2, int valor3);
vector<int> obtenerSolucion(const vvint& cache);

int main (int argc, char *argv[]) {

  char entradaManual = '\0';
  int altura=0, ancho=0, i, j;
  cout << "Introduzca la altura de la montaña: ";
  cin >> altura;
  while (altura < 0){
    cout << "Altura no válida (altura >= 0): ";
    cin >> altura;
  }

  cout << "Introduzca el ancho de la montaña: ";
  cin >> ancho;
  while (altura < 0){
    cout << "Ancho no válido (ancho >= 0): ";
    cin >> ancho;
  }
  
  vvint mountain;
  if(altura > 0){
  mountain.resize(altura);
  if(ancho > 0)
    for(i = 0; i < altura; i++)
      mountain[i].resize(ancho);
  }

  cout << "Quiere introducir manualmente los costes de la montaña? [y/n] ";
  cin >> entradaManual;
  while(entradaManual != 'y' &&
      entradaManual != 'n'){
    cout << "entrada no válida [y/n] ";
    cin >> entradaManual;
  }

  if(entradaManual == 'y'){
    for(i = 0; i < altura; i++){
      for (j = 0; j < ancho; j++) {
        cout << "Piedra en la altura " << i << " y en el ancho " << j << ": ";
        cin >> mountain[i][j];
      }
    }
  }else{
    unsigned int seed = 0;
    int topeSuperior = 0;
    cout << "Introduzca una semilla: ";
    cin >> seed;
    srand(seed);
    cout << "Introduzca el coste máximo posible (mayor o igual a 5): ";
    cin >> topeSuperior;
    while (topeSuperior < 5){
      cout << "Numero no permitido (tiene que ser mayor o igual a 5): ";
      cin >> topeSuperior;
    }
    for(i = 0; i < altura; i++)
      for(j = 0; j < ancho; j++)
        mountain[i][j] = rand()%topeSuperior+1;
  }
  imprimirMatriz(mountain);
  vvint resultado;
  resultado = SolucionProblema4(mountain);
  cout << endl << "Este es el resultado: " << endl;
  imprimirMatriz(resultado);
  vector<int> vector = obtenerSolucion(resultado);
  cout << endl << "Debe de escalar la montaña de la siguiente forma (contando desde 0, se lee de derecha a izquierda): " << endl;
  for(i = vector.size()-1; i >= 1; i--)
    cout << vector[i] << "-";
  cout << vector[i];
  cout << endl;
  return 0;
}

void imprimirMatriz(const vvint& orig){
  for(vector<int> nvector: orig){
    for(int nvalor: nvector)
      cout << nvalor << " ";
    cout << endl;
  }
}

vvint SolucionProblema4(const vvint& mountain){
  vvint resultado;
  int i;

  if(mountain.size() == 0 || mountain[0].size() == 0){ //No tiene altura o ancho
    resultado.resize(1);
    resultado[0].resize(1, 0);
    return resultado;
  } 

  resultado.resize(mountain.size());
  for(i = 0; i < mountain.size(); i++)
    resultado[i].resize(mountain[0].size(), -1);
  
  if(resultado[0].size() == 1){ //Montaña de ancho 1
      
    i = resultado.size()-1;
    resultado[i][0] = mountain[i][0];
    for(i = i-1; i >= 0; i--)
      resultado[i][0] = resultado[i+1][0] + mountain[i][0];

  }else
    for(i = 0; i < resultado[0].size(); i++)
      costeMinimo(mountain, resultado, 0, i);

  return resultado;
}

int costeMinimo(const vvint& costes, vvint& cache,
    int altura, int anchura){

  if(altura == costes.size()-1){
    cache[altura][anchura] = costes[altura][anchura];
    return costes[altura][anchura];
  }
  if(cache[altura][anchura] != -1)
    return cache[altura][anchura];
  if(anchura == 0){ //Estamos a la izquierda del todo
    cache[altura][anchura] = costes[altura][anchura] +
      minimo(
          costeMinimo(costes, cache, altura+1, anchura),
          costeMinimo(costes, cache, altura+1, anchura+1)
          );
  }else if(anchura == costes[0].size()-1){ //Estamos a la derecha del todo
    cache[altura][anchura] = costes[altura][anchura] +
      minimo(
          costeMinimo(costes, cache, altura+1, anchura-1),
          costeMinimo(costes, cache, altura+1, anchura)
          );
  }else{ //No estamos en los bordes
    cache[altura][anchura] = costes[altura][anchura] +
      minimo(
          costeMinimo(costes, cache, altura+1, anchura-1),
          costeMinimo(costes, cache, altura+1, anchura),
          costeMinimo(costes, cache, altura+1, anchura+1)
          );
  }
  return cache[altura][anchura];
}

int minimo(int valor1, int valor2){
  return valor1 < valor2 ? valor1 : valor2;
}

int minimo(int valor1, int valor2, int valor3){
  if(valor1 <  valor2)
    return valor1 < valor3 ? valor1 : valor3;
  else
    return valor2 < valor3 ? valor2 : valor3;
}

vector<int> obtenerSolucion(const vvint& cache){
  vector<int> laSolucion;
  laSolucion.reserve(cache.size());

  if(cache[0].size() == 1){ //Montaña de uno de ancho
    for(int i = 0; i < cache.size(); i++)
      laSolucion.push_back(0);
    return laSolucion;
  }

  int i, j, minimo, jMejor;
  minimo = cache[0][0];
  jMejor = 0;
  for(j = 1; j < cache[0].size(); j++)
    if(cache[0][j] < minimo){
      minimo = cache[0][j];
      jMejor = j;
    }
  laSolucion.push_back(jMejor);

  for(i = 1; i < cache.size(); i++){
    if(jMejor == 0){//Estamos en el borde de la izquierda
      if(cache[i][0] > cache[i][1])
        jMejor = 1;
    }else if(jMejor == cache[0].size()-1){ //Ahora en el de la derecha
      if(cache[i][jMejor] > cache[i][jMejor-1]) //Ahora en el de la derecha
        --jMejor;

    }else{ //No estamos en los bordes
      if(cache[i][jMejor-1] < cache[i][jMejor+1])
        jMejor = cache[i][jMejor-1] < cache[i][jMejor] ?
          jMejor-1 : jMejor;
      else
        jMejor = cache[i][jMejor+1] < cache[i][jMejor] ?
          jMejor+1 : jMejor;
    }
    laSolucion.push_back(jMejor);
  }
  return laSolucion;
}
