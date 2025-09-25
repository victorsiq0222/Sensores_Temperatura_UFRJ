#include "Sensor.h"
#include <stdexcept>
#include <cmath>
#include <numeric> // accumulate

// Construtor: só guarda o nome. A série começa vazia.
Sensor::Sensor(std::string n) : nome(std::move(n)) {}

// Retorna o nome (ex.: "sensor_lab")
std::string Sensor::getNome() const { return nome; }

// Quantidade de amostras na série
int Sensor::getQuantidade() const { return static_cast<int>(valores.size()); }

// Insere um novo valor na série e também registra um DadoSensor correspondente.
// Isso mostra a composição pedida no enunciado.
void Sensor::adicionarValor(double v) {
    valores.push_back(v);
    dados.emplace_back("temperatura", v);
}

// Média móvel de janela 3 (MM3)
// Se tiver menos de 3 amostras, retorna vetor vazio.
std::vector<double> Sensor::mediaMovel3() const {
    const int N = 3;
    std::vector<double> mm;
    if (static_cast<int>(valores.size()) < N) return mm;

    // Deslizo uma janela de tamanho 3 e tiro a média
    for (size_t i = 0; i + N <= valores.size(); ++i) {
        double soma = valores[i] + valores[i+1] + valores[i+2];
        mm.push_back(soma / 3.0);
    }
    return mm;
}

// Pega a última MM3 (se não existir, lanço exceção pra avisar)
double Sensor::ultimaMediaMovel3() const {
    auto mm = mediaMovel3();
    if (mm.empty()) throw std::runtime_error("Amostras insuficientes para MM3.");
    return mm.back();
}

// Pega a penúltima MM3 (se não existir, também lanço exceção)
double Sensor::mediaMovel3Anterior() const {
    auto mm = mediaMovel3();
    if (mm.size() < 2) throw std::runtime_error("Amostras insuficientes para MM3 anterior.");
    return mm[mm.size()-2];
}

// Verifica se a variação relativa entre as duas últimas MM3 é maior ou igual a 10%
// |(ultima - anterior)/anterior| >= 0.10
// Se não tiver dados suficientes, eu pego a exceção e simplesmente retorno false.
bool Sensor::variacaoAnormal10() const {
    try {
        double ult = ultimaMediaMovel3();
        double ant = mediaMovel3Anterior();
        if (ant == 0.0) return false; // evita divisão por zero
        double variacao = (ult - ant) / std::abs(ant);
        return std::abs(variacao) >= 0.10;
    } catch (const std::exception&) {
        return false;
    }
}

// Cálculo do coeficiente angular "a" da regressão linear simples:
// x = 0..n-1; y = valores[x]
// Fórmulas padrão de mínimos quadrados.
double Sensor::coefAngular() const {
    const size_t n = valores.size();
    if (n < 2) throw std::runtime_error("Amostras insuficientes para regressão.");

    // somas de x e x^2 fechadas (progressões)
    double sumx  = (n - 1) * (double)n / 2.0;
    double sumx2 = (n - 1) * (double)n * (2.0*(n-1) + 1.0) / 6.0;

    // soma de y:
    double sumy = std::accumulate(valores.begin(), valores.end(), 0.0);

    // soma de x*y:
    double sumxy = 0.0;
    for (size_t i = 0; i < n; ++i) sumxy += (double)i * valores[i];

    double denom = (double)n * sumx2 - sumx * sumx;
    if (denom == 0.0) throw std::runtime_error("Denominador zero na regressão.");
    return ((double)n * sumxy - sumx * sumy) / denom;
}

// Coeficiente linear "b" usando a = coefAngular()
double Sensor::coefLinear() const {
    const size_t n = valores.size();
    if (n < 2) throw std::runtime_error("Amostras insuficientes para regressão.");

    double sumx = (n - 1) * (double)n / 2.0;
    double sumy = std::accumulate(valores.begin(), valores.end(), 0.0);
    double a = coefAngular();
    return (sumy - a * sumx) / (double)n;
}

// Faz a previsão do próximo valor na posição x = n (porque a série vai de 0..n-1)
double Sensor::preverProximo() const {
    const size_t n = valores.size();
    if (n < 2) throw std::runtime_error("Amostras insuficientes para previsão.");
    double a = coefAngular();
    double b = coefLinear();
    return a * (double)n + b; // próxima posição x = n
}
