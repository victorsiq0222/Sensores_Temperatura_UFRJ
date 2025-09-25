#include "CentralMonitoramento.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Busca o índice de um sensor pelo nome (retorna -1 se não existir)
int CentralMonitoramento::buscarSensorPorNome(const std::string& nome) const {
    for (size_t i = 0; i < sensores.size(); ++i)
        if (sensores[i].getNome() == nome) return static_cast<int>(i);
    return -1;
}

// Tenta criar um sensor novo. Se já existir, avisa e não cria.
bool CentralMonitoramento::adicionarSensor(const std::string& nome) {
    if (buscarSensorPorNome(nome) != -1) {
        std::cout << "[Aviso] Sensor \"" << nome << "\" já existe.\n";
        return false;
    }
    sensores.emplace_back(nome);
    std::cout << "[OK] Sensor \"" << nome << "\" inserido.\n";
    listarSensores(); // só pra dar feedback visual
    return true;
}

// Insere um valor em um sensor existente.
// Se o sensor não existir, mostra erro.
bool CentralMonitoramento::inserirValorNoSensor(const std::string& nomeSensor, double valor) {
    int i = buscarSensorPorNome(nomeSensor);
    if (i == -1) {
        std::cout << [Erro] Sensor \"" << nomeSensor << "\" inexistente.\n";
        return false;
    }
    sensores[i].adicionarValor(valor);
    std::cout << "[OK] Valor " << valor << " adicionado ao sensor \"" << nomeSensor << "\".\n";
    listarSensores(); // feedback
    return true;
}

// Lista todos os sensores com o total de amostras
void CentralMonitoramento::listarSensores() const {
    std::cout << "\n--- Sensores na Central ---\n";
    if (sensores.empty()) { std::cout << "(vazio)\n"; return; }
    for (const auto& s : sensores) {
        std::cout << " - " << s.getNome()
                  << " | amostras: " << s.getQuantidade() << "\n";
    }
    std::cout << "---------------------------\n";
}

// Imprime a evolução da MM3 para uma lista de nomes (pede pelo menos 3)
// Para cada sensor, calcula as MM3 e imprime a sequência.
void CentralMonitoramento::mostrarEvolucaoMM3(const std::vector<std::string>& nomes) const {
    if (nomes.size() < 3) {
        std::cout << "[Aviso] Informe pelo menos 3 sensores.\n";
        return;
    }
    std::cout << "\nEvolução da MM3 (cada linha = um sensor):\n";
    for (const auto& nome : nomes) {
        int i = buscarSensorPorNome(nome);
        if (i == -1) { std::cout << " * " << nome << ": (inexistente)\n"; continue; }
        auto mm = sensores[i].mediaMovel3();
        std::cout << " * " << nome << ": ";
        if (mm.empty()) { std::cout << "(amostras < 3)\n"; continue; }
        for (double v : mm) std::cout << std::fixed << std::setprecision(2) << v << " ";
        std::cout << "\n";
    }
}

// Cria uma lista (nome, última MM3), ordena em ordem decrescente e imprime.
// Se algum sensor não tiver MM3 suficiente, é ignorado.
void CentralMonitoramento::ordenarPorUltimaMM3() const {
    if (sensores.empty()) { std::cout << "(sem sensores)\n"; return; }
    std::vector<std::pair<std::string,double>> pares;
    for (const auto& s : sensores) {
        try { pares.emplace_back(s.getNome(), s.ultimaMediaMovel3()); }
        catch (const std::exception&) { /* ignora sensores sem MM3 */ }
    }
    std::sort(pares.begin(), pares.end(),
              [](auto& a, auto& b){ return a.second > b.second; });
    std::cout << "\nOrdenados pela última MM3 (desc):\n";
    for (auto& [n, mm] : pares)
        std::cout << " - " << n << ": " << std::fixed << std::setprecision(2) << mm << "\n";
}

// Varredura simples: quem tiver variacaoAnormal10() == true é listado.
void CentralMonitoramento::mostrarVariacoesAnormais10() const {
    std::cout << "\nSensores com variação anormal (±10%) entre as duas últimas MM3:\n";
    bool algum = false;
    for (const auto& s : sensores) {
        if (s.variacaoAnormal10()) {
            algum = true;
            std::cout << "  * " << s.getNome() << "\n";
        }
    }
    if (!algum) std::cout << "  (nenhuma)\n";
}

// Faz a regressão linear e imprime a equação + previsão
void CentralMonitoramento::regressaoEPrevisao(const std::string& nomeSensor) const {
    int i = buscarSensorPorNome(nomeSensor);
    if (i == -1) { std::cout << "[Erro] Sensor não encontrado.\n"; return; }
    try {
        double a = sensores[i].coefAngular();
        double b = sensores[i].coefLinear();
        double y = sensores[i].preverProximo();
        std::cout << "\nRegressão linear de \"" << nomeSensor << "\": y = "
                  << std::fixed << std::setprecision(4) << a << " * x + " << b
                  << "\nPróxima amostra prevista: " << std::setprecision(4) << y << "\n";
    } catch (const std::exception& e) {
        std::cout << "[Aviso] " << e.what() << "\n";
    }
}
