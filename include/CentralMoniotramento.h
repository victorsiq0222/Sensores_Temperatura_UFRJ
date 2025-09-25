#pragma once
#include <vector>
#include <string>
#include "Sensor.h"

class Central {
private:
    std::vector<Sensor> sensores;

    int buscarSensorPorNome(const std::string& nome) const; // retorna índice ou -1

public:
    bool adicionarSensor(const std::string& nome);
    bool inserirValorNoSensor(const std::string& nomeSensor, double valor);
    void listarSensores() const;

    // Opções de menu que usam vários sensores
    void mostrarEvolucaoMM3(const std::vector<std::string>& nomes) const;
    void ordenarPorUltimaMM3() const;
    void mostrarVariacoesAnormais10() const;

    // Regressão + previsão para um sensor
    void regressaoEPrevisao(const std::string& nomeSensor) const;
};
