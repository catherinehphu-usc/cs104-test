# Put the path to your hw3/search folder here:
SRC_DIR = /home/cs104/hw-chphu/hw3/search

CC = g++
CPPFLAGS = -g -Wall -std=c++11 -I $(SRC_DIR)
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/gtest
	 ./$(BIN_DIR)/gtest

$(BIN_DIR)/gtest: $(BIN_DIR)/gtest.o $(BIN_DIR)/txt_parser.o $(BIN_DIR)/md_parser.o $(BIN_DIR)/util.o $(BIN_DIR)/webpage.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/handler.o $(BIN_DIR)/cmdhandler.o $(BIN_DIR)/searchui.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/gtest.o: gtest.cpp $(SRC_DIR)/searcheng.h $(SRC_DIR)/searchui.h $(SRC_DIR)/util.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/search: $(BIN_DIR)/txt_parser.o $(BIN_DIR)/md_parser.o $(BIN_DIR)/util.o $(BIN_DIR)/webpage.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/handler.o $(BIN_DIR)/cmdhandler.o $(BIN_DIR)/search-shell.o $(BIN_DIR)/searchui.o $(BIN_DIR)/search-shell.o
	g++ $(CPPFLAGS) $< -o $@

$(BIN_DIR)/txt_parser.o: $(SRC_DIR)/txt_parser.cpp $(SRC_DIR)/txt_parser.h $(SRC_DIR)/util.h $(SRC_DIR)/pageparser.h
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/md_parser.o: $(SRC_DIR)/md_parser.cpp $(SRC_DIR)/md_parser.h $(SRC_DIR)/util.h $(SRC_DIR)/pageparser.h
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/util.o: $(SRC_DIR)/util.cpp $(SRC_DIR)/util.h $(SRC_DIR)/webpage.h
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/webpage.o: $(SRC_DIR)/webpage.cpp $(SRC_DIR)/webpage.h $(SRC_DIR)/util.h 
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/searcheng.o: $(SRC_DIR)/searcheng.cpp $(SRC_DIR)/searcheng.h $(SRC_DIR)/util.h $(SRC_DIR)/webpage.h $(SRC_DIR)/pageparser.h
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/handler.o: $(SRC_DIR)/handler.cpp $(SRC_DIR)/handler.h $(SRC_DIR)/searcheng.h 
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/cmdhandler.o: $(SRC_DIR)/cmdhandler.cpp $(SRC_DIR)/cmdhandler.h $(SRC_DIR)/util.h $(SRC_DIR)/searcheng.h $(SRC_DIR)/handler.h 
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/search-shell.o: $(SRC_DIR)/search-shell.cpp $(SRC_DIR)/searcheng.h $(SRC_DIR)/searchui.h $(SRC_DIR)/md_parser.h $(SRC_DIR)/txt_parser.h $(SRC_DIR)/cmdhandler.h $(SRC_DIR)/util.h
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/searchui.o: $(SRC_DIR)/searchui.cpp $(SRC_DIR)/searchui.h $(SRC_DIR)/searcheng.h $(SRC_DIR)/handler.h $(SRC_DIR)/util.h 
	g++ $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

ValidTest: $(BIN_DIR) $(BIN_DIR)/gtest
	 ./$(BIN_DIR)/gests