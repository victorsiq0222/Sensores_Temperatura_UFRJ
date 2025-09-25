CXX=g++
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic

OBJS=main.o Sensor.o DadoSensor.o CentralMonitoramento.o

all: sensores

sensores: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

main.o: main.cpp CentralMonitoramento.h Sensor.h DadoSensor.h
Sensor.o: Sensor.cpp Sensor.h DadoSensor.h
DadoSensor.o: DadoSensor.cpp DadoSensor.h
CentralMonitoramento.o: CentralMonitoramento.cpp CentralMonitoramento.h Sensor.h DadoSensor.h

clean:
	rm -f $(OBJS) sensores
