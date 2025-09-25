#pragma once
#include <string>
#include <vector>
#include "DadoSensor.h"

/*
 * A classe Sensor representa um sensor de temperatura.
 * Ela guarda:
 *  - um nome (identificador do sensor)
 *  - uma série histórica de valores (double)
 *  - e, para cumprir o requisito do exercício, também guarda cada leitura como DadoSensor
 *
 * Eu uso a série de double para fazer os cálculos (MM3, regressão, etc.)
 * e o vector<DadoSensor> para mostrar que há composição (Sensor TEM vários DadoSensor).
 */
class Sensor {
private:
    std::string nome;               // nome do sensor (ex.: "sensor_sala")
    std::vector<double> valores;    // série de valores numéricos (para cálculo)
    std::vector<DadoSensor> dados;  // série de objetos DadoSensor (para composição)

public:
    // Construtor recebe o nome do sensor
    explicit Sensor(std::string nome);

    // Nome do sensor (só leitura)
    std::string getNome() const;

    // Quantidade de amostras já inseridas
    int getQuantidade() const;

    // Insere um novo valor no sensor (atualiza "valores" e também "dados" com DadoSensor)
    void adicionarValor(double v);

    // Calcula a média móvel de janela 3 sobre a série
    std::vector<double> mediaMovel3() const;

    // Pega a última MM3 calculada (erro se não houver amostras suficientes)
    double ultimaMediaMovel3() const;

    // Pega a penúltima MM3 (erro se não houver amostras suficientes)
    double mediaMovel3Anterior() const;

    // Verifica se a variação entre as DUAS últimas MM3 foi >= 10% (pra mais ou pra menos)
    bool variacaoAnormal10() const;

    // Regressão linear simples (x = 0..n-1)
    // a = coeficiente angular (inclinação da reta)
    double coefAngular() const;

    // b = coeficiente linear (intercepto)
    double coefLinear() const;

    // Previsão do próximo ponto da série (na posição x = n) usando a reta y = a*x + b
    double preverProximo() const;
};
