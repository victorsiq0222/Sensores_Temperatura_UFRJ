#pragma once
#include <string>

/*
 * A ideia dessa classe é representar UM "dado" do sensor.
 * Como o trabalho é de temperatura, vou usar "temperatura" como nome do dado,
 * mas deixo genérico (nome + valor) pra mostrar que poderia ter outras coisas.
 */
class DadoSensor {
private:
    std::string nomeDoDado; // ex.: "temperatura"
    double valorDoDado;     // ex.: 25.3

public:
    // Construtor básico: recebe o nome do dado e o valor
    DadoSensor(std::string nome, double valor);

    // Getter pro nome do dado (só leitura)
    std::string getNome() const;

    // Getter pro valor do dado (só leitura)
    double getValor() const;
};
