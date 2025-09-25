#include "Sensor.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

Sensor::Sensor(std::string n) : nome(n) {}
std::string Sensor::getNome() const { return nome; }
int Sensor::getQuantidade() const { return (int)valores.size(); }
void Sensor::adicionarValor(double v) { valores.push_back(v); }



std::vector<double> Sensor::mediaMovel3() const {
    const int N = 3;
    std::vector<double> mm;
    if ((int)valores.size() < N) return mm;
    double soma = valores[0] + valores[1] + valores[2];
    mm.push_back(soma / N);
    for (size_t i = 3; i < valores.size(); ++i) {
        soma += valores[i] - valores[i-3];
        mm.push_back(soma / N);
    }
    return mm;
}

double Sensor::ultimaMediaMovel3() const {
    auto mm = mediaMovel3();
    if (mm.empty()) throw std::runtime_error("Sem dados para MM3");
    return mm.back();
}

double Sensor::mediaMovel3Anterior() const {
    auto mm = mediaMovel3();
    if (mm.size() < 2) throw std::runtime_error("Sem janelas suficientes para comparar MM3");
    return mm[mm.size()-2];
}

bool Sensor::variacaoAnormal10() const {
    try {
        double ult = ultimaMediaMovel3();
        double ant = mediaMovel3Anterior();
        if (std::abs(ant) < 1e-12) return std::abs(ult) > 1e-12;
        double variacao = (ult - ant) / std::abs(ant);
        return std::abs(variacao) >= 0.10; // 10%
    } catch (...) {
        return false;
    }
}

double Sensor::coefAngular() const {
    size_t n = valores.size();
    if (n < 2) throw std::runtime_error("Regressão requer ao menos 2 pontos");
    double sumx=0, sumy=0, sumxy=0, sumx2=0;
    for (size_t i=0;i<n;++i){
        double x = (double)i;
        double y = valores[i];
        sumx+=x; sumy+=y; sumxy+=x*y; sumx2+=x*x;

        
    }
    double denom = n*sumx2 - sumx*sumx;
    if (std::abs(denom) < 1e-12) throw std::runtime_error("Variância de x zero");
    double a = (n*sumxy - sumx*sumy)/denom;
    return a;
}

double Sensor::coefLinear() const {
    size_t n = valores.size();
    if (n < 2) throw std::runtime_error("Regressão requer ao menos 2 pontos");
    double sumx=0, sumy=0;
    for (size_t i=0;i<n;++i){ sumx += (double)i; sumy += valores[i]; }
    double a = coefAngular();
    double b = (sumy - a*sumx) / (double)n;
    return b;
}

double Sensor::preverProximo() const {
    size_t n = valores.size();
    double a = coefAngular();
    double b = coefLinear();
    return a * (double)n + b; // próxima posição x = n
}
