#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <thread>

#define RED "\e[0;31m"
#define CYN "\e[0;36m"
#define GRN "\e[0;32m"
#define YELLOW  "\033[33m"  
#define WHITE   "\033[37m"      /* White */
#define MAGENTA "\033[35m"      /* Magenta */

#define NC "\e[0m"


// ----------------------------------------------------------------------------
 
using Fila   = std::vector<int>;
using Cells = std::vector<Fila>;
using namespace std;


// ----------------------------------------------------------------------------
 

 

 
// ----------------------------------------------------------------------------
 
int getNeighbor(int fila, int col, Cells& tablero, int numFilas, int numCols) {
    // use modulus to get wrapping effect at tablero edges
    return tablero.at((fila + numFilas) % numFilas).at((col + numCols) % numCols);
}

int sumarVecinos(int filas, int columnas, Cells& tablero, int numFilas, int numCols){
  int cuentaVecinos = 0;
  vector<int>deltas {-1, 0, 1};
  for (int col : deltas) {
    for (int fila : deltas){
      if (col || fila){
        cuentaVecinos += getNeighbor(filas + fila, columnas + col, tablero, numFilas, numCols);
      }
    }
  }

  return cuentaVecinos;
}

 
void mostrarCelda(int celda) {

  if (celda == 1)
    cout << YELLOW "■" NC << std::flush;
  else
    cout << WHITE "■" NC << std::flush;  
}
 
void mostrarFila(const Fila& fila) {
    std::cout << "|" << std::flush;
    for (int celda : fila) {mostrarCelda(celda);}
    std::cout << "|\n" << std::flush;
}
 
void mostrarCeldas(Cells tablero) {
    for (const Fila& fila : tablero) { mostrarFila(fila); }
}
 
int tick(Cells& tablero, int fila, int col, int numFilas, int numCols) {
    int cuenta = sumarVecinos(fila, col, tablero, numFilas, numCols);
    bool birth = !tablero.at(fila).at(col) && cuenta == 3;
    bool survive = tablero.at(fila).at(col) && (cuenta == 2 || cuenta == 3);
    return birth || survive;
}
 
void updateCeldas(Cells& tablero, int numFilas, int numCols) {
    Cells original = tablero;
    for (int fila = 0; fila < numFilas; fila++) {
        for (int col = 0; col < numCols; col++) {
            tablero.at(fila).at(col) = tick(original, fila, col, numFilas, numCols);
        }
    }
}

void startGame(Cells tablero, int generaciones, int nFilas, int nCol, int timeWait){
	for (int gen = 0; gen < generaciones; gen++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        printf("\033[2J");
        printf("\033[%d;%dH", 0, 0);
        std::cout << "\nGeneración " << gen << ":\n" << "\r";
        mostrarCeldas(tablero);
        updateCeldas(tablero, nFilas, nCol);
    }
}
 
int main () {

	Cells tablero1 = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };

	int generacion = 20;
	int numFilas = 10;
	int numCols = 20;
	int timeWait = 700; // ms

	startGame(tablero1, generacion, numFilas, numCols, timeWait);
}