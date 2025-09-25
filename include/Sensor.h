#pragma once
#include <string>
#include <vector>

class Sensor {
private:
    std::string nome;
    std::vector<double> valores; // série temporal (ex.: temperaturas)

public:
    Sensor(std::string nome);
    std::string getNome() const;
    int getQuantidade() const;
    void adicionarValor(double v);

    // Média móvel N=3
    std::vector<double> mediaMovel3() const;
    double ultimaMediaMovel3() const;        // lança erro se não tiver
    double mediaMovel3Anterior() const;      // idem
    bool variacaoAnormal10() const;          // compara última vs anterior (±10%)

    // Regressão linear simples: y = a*x + b, x = 0..n-1
    double coefAngular() const;  // a
    double coefLinear() const;   // b
    double preverProximo() const;
};