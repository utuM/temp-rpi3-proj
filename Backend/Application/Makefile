################################################################################
#
#	Motor Tester Backend Make-script
#
# Author: Kostiantyn Komarov
# Email:  kostyantyn.komarov@droid-technologies.com
# Date:   2026-MAY-21
#
################################################################################

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra \
        -DMOTOR_BACKEND \
		-I ../../Common/Include \
		-I ../../Common/Include/Global \
		-I ../../Common/Include/Logic \
		-I ../../Common/Include/Logic/Motor \
		-I ../../Common/Include/Logic/Test \
		-I ../../Common/Include/Network \
		-I ../../Common/Include/Network/Packet \
		-I ../../Common/Include/Network/Packet/Payload \
		-I ../../Common/Include/Tools \
		-I ../Libs/Include \
		-I ../Libs/Include/Global \
		-I ../Libs/Include/Hardware \
		-I ../Libs/Include/Hardware/Multiplexer \
		-I ../Libs/Include/Hardware/Sensor \
		-I ../Libs/Include/Logic \
		-I ../Libs/Include/Logic/Measurement \
		-I ../Libs/Include/Logic/Phase
		
LDFLAGS  = 

SRC = $(wildcard *.cpp \
        ../../Common/Source/*.cpp ../../Common/Source/**/*.cpp \
		../../Common/Source/**/**/*.cpp \
		../../Common/Source/**/**/**/*.cpp \
		../../Common/Source/**/**/**/**/*.cpp \
        ../Libs/Source/*.cpp ../Libs/Source/**/*.cpp \
		../Libs/Source/**/**/*.cpp \
		../Libs/Source/**/**/**/*.cpp \
		../Libs/Source/**/**/**/**/*.cpp)
OBJ = $(SRC:.cpp=.o)

PROJECT_NAME = motortester
SERVICE_NAME = $(PROJECT_NAME)-backend
BIN          = $(SERVICE_NAME)

all: $(BIN)

$(BIN) : $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

install:
	@sudo cp $(BIN) /usr/local/bin/
	@sudo cp systemd/$(SERVICE_NAME).service /etc/systemd/system/
	@sudo systemctl daemon-reload
	@sudo systemctl enable $(SERVICE_NAME)

uninstall:
	@sudo systemctl disable $(SERVICE_NAME)
	@sudo rm -f /usr/local/bin/$(BIN)
	@sudo rm -f /etc/systemd/system/$(SERVICE_NAME).service
	@sudo systemctl daemon-reload

clean:
	@rm -f $(OBJ) $(BIN)