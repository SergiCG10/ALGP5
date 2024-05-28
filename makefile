CXX = g++
BIN_DIR = ./bin
FLAGS = -std=c++17

PROBLEMAS = problema3 generarLaberintos problema4 problema1 problema2

all: $(PROBLEMAS)

#Regla de construcción para problema1
problema1: $(BIN_DIR)/problema1.bin

$(BIN_DIR)/problema1.bin: problema1/problema1.cpp
	$(CXX) $(FLAGS) -o $@ $^

#Regla de construcción para problema2
problema2: $(BIN_DIR)/problema2.bin

$(BIN_DIR)/problema2.bin: problema2/problema2.cpp
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para Laberinto.o
$(BIN_DIR)/Laberinto.o: problema3/Laberinto.cpp problema3/Laberinto.h
	$(CXX) $(FLAGS) -o $@ -c $<

# Regla de construcción para problema3
problema3: $(BIN_DIR)/problema3.bin

$(BIN_DIR)/problema3.bin: problema3/problema3.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^

# Regla de construcción para generarLaberintos
generarLaberintos: $(BIN_DIR)/generarLaberintos.bin

$(BIN_DIR)/generarLaberintos.bin: problema3/generarLaberintos.cpp $(BIN_DIR)/Laberinto.o
	$(CXX) $(FLAGS) -o $@ $^

#Regla de construcción para problema4
problema4: $(BIN_DIR)/problema4.bin

$(BIN_DIR)/problema4.bin: problema4/problema4.cpp
	$(CXX) $(FLAGS) -o $@ $^

#Ejemplos de ejecución 
	make ejemplos

# Regla para mostrar ejemplos de ejecución
ejemplos:
	@echo
	@echo "Problema 1\n"
	@echo "\tPara el problema1, pruebe a ejecutar: \n\t\t./bin/problema1.bin\n"
	@echo "\t\tDespués de esto, añada dos números distintos entre 1 y 5 ambos inclusive, para calcular el recorrido desde el primero al segundo \n"

	@echo "Problema 2\n"
	@echo "\tPara el problema2, pruebe a ejecutar: \n\t\t./bin/problema2.bin 5 123123124\n"
	@echo "\t\tDespués de ejecutar el programa, añada:"
	@echo "\t\t\"y 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 1 10 10 10 10 0 4\"\n"  
	@echo "\t\tOtro ejemplo: tras ejecutar con la misma llamada, añada \"n 1 2\"\n"

	@echo "Problema 3\n"
	@echo "\tPara el problema3 pruebe a ejecutar: \n\t\t./bin/problema3.bin bin/laberintos/ejemploPropuesto\n"
	@echo "\tOtro ejemplo: \n\t\t./bin/problema3.bin bin/laberintos/ejemploGrande\n"
	@echo "\tOtro ejemplo: \n\t\t./bin/problema3.bin bin/laberintos/ejemploSinSol2\n"
	@echo "\tTras ejecutar, pulse cualquier tecla para ver el camino que maximiza las monedas\n"

	@echo "Problema 4\n"
	@echo "\tPara el problema4 pruebe a ejecutar: \n\t\t./bin/problema4.bin\n"
	@echo "\t\tDespués de esto, añada \"5 5 n 3242 5\" para ejecutar para una montaña de tamaño 5x5 "
	@echo "\t\tDespués de esto, para otro ejemplo, añada \"10 10 n 1092301923 15\" para ejecutar para una montaña de tamaño 10x10 \n\n"

# Regla para limpiar
clean:
	rm -rf $(BIN_DIR)/*.bin $(BIN_DIR)/*.o

.PHONY: all clean ejemplos
