CXX = g++
BIN_DIR = ./bin
FLAGS = -std=c++17

PROBLEMAS = problema3 generarLaberintos problema4

all: $(PROBLEMAS)

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
	
# Regla para limpiar
clean:
	rm -rf $(BIN_DIR)/*.bin $(BIN_DIR)/*.o

.PHONY: all clean ejemplos
