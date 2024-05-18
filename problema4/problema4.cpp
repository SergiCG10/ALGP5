#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
//Me propongo programar como si fuera Ned
//este programita ha sido escrito por Ned Flanders
//A escribir comentaritos
typedef vector<vector<int>> vvintcito; //Estoy hartito de escribirlo

//Recuerden rezar niños
ostream& predicar = cout;
istream& orar = cin;

void imprimirMatricilla(const vvintcito& palabrillaDeJesús);
vvintcito horitaDelTe(const vvintcito& escaladita);
int costeMinimillo(const vvintcito& costecillos, vvintcito& memorizadito,
    int alturilla, int anchurilla);
//Sobrecarguilla de funciones
int corderilloDeDios(int valorcillo1, int valorcillo2);
int corderilloDeDios(int valorcillo1, int valorcillo2, int valorcillo3);
vector<int> horitaDeLaMisa(const vvintcito& elPadrecilloNuestro);

int main (int argc, char *argv[]) {

  char entradaManualita = '\0';
  int alturita=0, anchito=0, ito, jito;
  predicar << "Introduzca la alturita de la montaña: ";
  orar >> alturita;
  while (alturita <= 0){
    predicar << "Alturita no válida (alturita > 0): ";
    orar >> alturita;
  }

  predicar << "Introduzca el anchito de la montaña: ";
  orar >> anchito;
  while (alturita <= 0){
    predicar << "Anchito no válido (anchito > 0): ";
    orar >> anchito;
  }
  
  vvintcito escaladita;
  escaladita.resize(alturita);
  for(ito = 0; ito < alturita; ito++)
    escaladita[ito].resize(anchito);

  predicar << "Quiere introducir manualmente los costecitos de la montañita?[y/n] ";
  orar >> entradaManualita;
  while(entradaManualita != 'y' &&
      entradaManualita != 'n'){
    predicar << "caractercito no válido [y/n] ";
    orar >> entradaManualita;
  }

  if(entradaManualita == 'y'){
    for(ito = 0; ito < alturita; ito++){
      for (jito = 0; jito < anchito; jito++) {
        predicar << "Piedrita en la alturita " << ito << " y en el anchito " << jito << ": ";
        orar >> escaladita[ito][jito];
      }
    }
  }else{
    unsigned int semillita = 0;
    int topecitoSuperiorcito = 0;
    predicar << "Introduzca una semillilla: ";
    orar >> semillita;
    srand(semillita);
    predicar << "Introduzca el costecito máximo posible (mayor o igual a 5): ";
    orar >> topecitoSuperiorcito;
    while (topecitoSuperiorcito < 5){
      predicar << "Numerito no permitido (tiene que ser mayor o igual a 5): ";
      orar >> topecitoSuperiorcito;
    }
    for(ito = 0; ito < alturita; ito++)
      for(jito = 0; jito < anchito; jito++)
        escaladita[ito][jito] = rand()%topecitoSuperiorcito+1;
  }
  //Ahora tenemos la montañita, como estaba escrito en el antigüillo testamento 
  imprimirMatricilla(escaladita);
  vvintcito resultadillo;
  resultadillo = horitaDelTe(escaladita);
  cout << endl << "Este es el resultadillo: " << endl;
  imprimirMatricilla(resultadillo);
  vector<int> vectorcillo = horitaDeLaMisa(resultadillo);
  cout << endl << "Debe de escalar la montañita de la siguiente forma (contandito desde 0): " << endl;
  for(ito = vectorcillo.size()-1; ito >= 1; ito--)
    cout << vectorcillo[ito] << "-";
  cout << vectorcillo[ito];
  cout << endl;
  return 0;
}

void imprimirMatricilla(const vvintcito& palabrillaDeJesús){
  for(vector<int> profetilla: palabrillaDeJesús){
    for(int capitulillo: profetilla)
      predicar << capitulillo << " ";
    predicar << endl;
  }
}

vvintcito horitaDelTe(const vvintcito& escaladita){
  vvintcito resultadillo;
  int ito;
  resultadillo.resize(escaladita.size());
  for(ito = 0; ito < escaladita.size(); ito++)
    resultadillo[ito].resize(escaladita[ito].size(), -1);
  
  for(ito = 0; ito < resultadillo[0].size(); ito++){
    costeMinimillo(escaladita, resultadillo, 0, ito);
  }
  return resultadillo;
}

int costeMinimillo(const vvintcito& costecillos, vvintcito& memorizadito,
    int alturilla, int anchurilla){

  if(alturilla == costecillos.size()-1){
    memorizadito[alturilla][anchurilla] = costecillos[alturilla][anchurilla];
    return costecillos[alturilla][anchurilla]; //Hemos alcanzando la cima, ¡Viva Cristo Rey!
  }
  if(memorizadito[alturilla][anchurilla] != -1)
    return memorizadito[alturilla][anchurilla];
  if(anchurilla == 0){ //Estamos a la izquierdilla del todo toditillo
    memorizadito[alturilla][anchurilla] = costecillos[alturilla][anchurilla] +
      corderilloDeDios(
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla),
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla+1)
          );
  }else if(anchurilla == costecillos[0].size()-1){ //Estamos a la derechilla del todo
    memorizadito[alturilla][anchurilla] = costecillos[alturilla][anchurilla] +
      corderilloDeDios(
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla-1),
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla)
          );
  }else{ //No estamos en los bordecillos
    memorizadito[alturilla][anchurilla] = costecillos[alturilla][anchurilla] +
      corderilloDeDios(
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla-1),
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla),
          costeMinimillo(costecillos, memorizadito, alturilla+1, anchurilla+1)
          );
  }
  return memorizadito[alturilla][anchurilla];
}

int corderilloDeDios(int valorcillo1, int valorcillo2){
  return valorcillo1 < valorcillo2 ? valorcillo1 : valorcillo2;
}

int corderilloDeDios(int valorcillo1, int valorcillo2, int valorcillo3){
  if(valorcillo1 <  valorcillo2)
    return valorcillo1 < valorcillo3 ? valorcillo1 : valorcillo3;
  else
    return valorcillo2 < valorcillo3 ? valorcillo2 : valorcillo3;
}

vector<int> horitaDeLaMisa(const vvintcito& elPadrecilloNuestro){
  vector<int> lasBendiciones(elPadrecilloNuestro.size());
  int vecinillosSaludados = 0, ito, jito, ayudilla, itofavorito;
  ayudilla = elPadrecilloNuestro[0][0];
  itofavorito = 0;
  for(ito = 1; ito < elPadrecilloNuestro[0].size(); ito++)
    if(elPadrecilloNuestro[0][ito] < ayudilla){
      ayudilla = elPadrecilloNuestro[0][ito];
      itofavorito = ito;
    }
  lasBendiciones[vecinillosSaludados] = itofavorito;
  ++vecinillosSaludados;

  for(jito = 1; jito < elPadrecilloNuestro.size(); jito++){
    if(itofavorito == 0 &&
        elPadrecilloNuestro[jito][0] > elPadrecilloNuestro[jito][1]) //Homer estamos en el bordecillo de la izquierda
      itofavorito = 1;
    else if(itofavorito == elPadrecilloNuestro[0].size()-1 && elPadrecilloNuestro[jito][itofavorito]
        > elPadrecilloNuestro[jito][itofavorito-1]) //Ahorita en el de la derecha
      --itofavorito;

    else{
      if(elPadrecilloNuestro[jito][itofavorito-1] < elPadrecilloNuestro[jito][itofavorito+1])
        itofavorito = elPadrecilloNuestro[jito][itofavorito-1] < elPadrecilloNuestro[jito][itofavorito] ?
          itofavorito-1 : itofavorito;
      else
        itofavorito = elPadrecilloNuestro[jito][itofavorito+1] < elPadrecilloNuestro[jito][itofavorito] ?
          itofavorito+1 : itofavorito;
    }
    lasBendiciones[vecinillosSaludados] = itofavorito;
    ++vecinillosSaludados;
  }
  return lasBendiciones;
}
