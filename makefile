DIR_SRC = ./src
DIR_BIN = ./bin

CC = g++-7
CFLAGS = -std=c++11

TARGET = expression_interpreter
OBJECTS = $(DIR_BIN)/Parser.o $(DIR_BIN)/Tokenizer.o $(DIR_BIN)/Exception.o
BIN_TARGET = $(DIR_BIN)/$(TARGET)

TARGET: $(DIR_BIN)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) ./bin/main.o $(OBJECTS) -o $(BIN_TARGET)

$(DIR_BIN)/main.o: ./src/main.cc $(OBJECTS)
	$(CC) $(CFLAGS) -c $(DIR_SRC)/main.cc $(OBJECTS)  -o $(DIR_BIN)/main.o

$(DIR_BIN)/Tokenizer.o: $(DIR_SRC)/Tokenizer.cc
	$(CC) $(CFLAGS) -c $(DIR_SRC)/Tokenizer.cc -o $(DIR_BIN)/Tokenizer.o 

$(DIR_BIN)/Parser.o: ${DIR_SRC}/Parser.cc $(DIR_BIN)/Exception.o
	$(CC) $(CFLAGS) -c $(DIR_BIN)/Exception.o $(DIR_SRC)/Parser.cc -o $(DIR_BIN)/Parser.o 

$(DIR_BIN)/Exception.o: ${DIR_SRC}/Exception.cc
	$(CC) $(CFLAGS) -c $(DIR_SRC)/Exception.cc -o $(DIR_BIN)/Exception.o

clean:
	rm $(OBJECTS) $(DIR_BIN)/main.o $(BIN_TARGET)

run:
	./$(BIN_TARGET)


