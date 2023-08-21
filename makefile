CC=g++
STD=-std=c++11 -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) utaxi.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


utaxi.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/app.o $(BUILD_DIR)/passenger.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/person.o $(BUILD_DIR)/location.o $(BUILD_DIR)/trip.o $(BUILD_DIR)/errors.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/app.o $(BUILD_DIR)/passenger.o $(BUILD_DIR)/driver.o $(BUILD_DIR)/person.o $(BUILD_DIR)/location.o $(BUILD_DIR)/trip.o $(BUILD_DIR)/errors.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o utaxi.out

$(BUILD_DIR)/main.o: code/main.cpp code/app.cpp code/app.hpp code/passenger.hpp code/driver.hpp code/person.hpp code/trip.hpp code/location.hpp code/errors.hpp code/handlers.hpp code/my_server.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c code/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/app.o: code/app.cpp code/app.hpp code/passenger.hpp code/driver.hpp code/person.hpp code/trip.hpp code/location.hpp code/errors.hpp
	$(CC) $(CF) -c code/app.cpp -o $(BUILD_DIR)/app.o

$(BUILD_DIR)/passenger.o: code/passenger.cpp code/passenger.hpp code/person.hpp code/trip.hpp code/location.hpp
	$(CC) $(CF) -c code/passenger.cpp -o $(BUILD_DIR)/passenger.o

$(BUILD_DIR)/driver.o: code/driver.cpp code/driver.hpp code/person.hpp code/trip.hpp code/location.hpp
	$(CC) $(CF) -c code/driver.cpp -o $(BUILD_DIR)/driver.o

$(BUILD_DIR)/person.o: code/person.cpp code/person.hpp code/trip.hpp code/location.hpp
	$(CC) $(CF) -c code/person.cpp -o $(BUILD_DIR)/person.o

$(BUILD_DIR)/trip.o: code/trip.cpp code/trip.hpp code/location.hpp
	$(CC) $(CF) -c code/trip.cpp -o $(BUILD_DIR)/trip.o

$(BUILD_DIR)/location.o: code/location.cpp code/location.hpp
	$(CC) $(CF) -c code/location.cpp -o $(BUILD_DIR)/location.o

$(BUILD_DIR)/errors.o: code/errors.cpp code/errors.hpp
	$(CC) $(CF) -c code/errors.cpp -o $(BUILD_DIR)/errors.o

$(BUILD_DIR)/my_server.o: code/my_server.cpp code/my_server.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c code/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/handlers.o: code/handlers.cpp code/handlers.hpp code/app.cpp code/app.hpp code/passenger.hpp code/driver.hpp code/person.hpp code/trip.hpp code/location.hpp code/errors.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c code/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o




.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null