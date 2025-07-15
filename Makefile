# Diretórios
BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
SRC_DIR = src

# Compilador e opções
CC = g++  # Usando o compilador g++ para C++
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -g  # Incluindo diretório de cabeçalhos e opções de compilação
EXEC = tp3.out  # Nome do executável
OBJS = $(OBJ_DIR)/voo.o $(OBJ_DIR)/arvore.o $(OBJ_DIR)/filtro.o $(OBJ_DIR)/main.o  # Arquivos objeto

# Regra padrão para compilar tudo
all: $(BIN_DIR)/$(EXEC)

# Regra para criar o executável
$(BIN_DIR)/$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)  # Cria o diretório bin se não existir
	$(CC) $(CFLAGS) -o $@ $^

# Regras para criar os arquivos objeto
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/voo.hpp $(INCLUDE_DIR)/arvore.hpp $(INCLUDE_DIR)/filtro.hpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/voo.o: $(SRC_DIR)/voo.cpp $(INCLUDE_DIR)/voo.hpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/arvore.o: $(SRC_DIR)/arvore.cpp $(INCLUDE_DIR)/arvore.hpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/filtro.o: $(SRC_DIR)/filtro.cpp $(INCLUDE_DIR)/filtro.hpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) -c $< -o $@



# Regra para Valgrind
valgrind: $(BIN_DIR)/$(EXEC)
	valgrind --leak-check=full --log-file=valgrind_output.txt $(BIN_DIR)/$(EXEC)

# Regra para limpar arquivos gerados
clean:
	rm -f $(BIN_DIR)/$(EXEC) $(OBJ_DIR)/*.o

# Regra para executar o programa
run: all  # Garante que o executável esteja atualizado antes de executar
	./$(BIN_DIR)/$(EXEC)

.PHONY: all clean run  # Declara alvos como 'phony'
