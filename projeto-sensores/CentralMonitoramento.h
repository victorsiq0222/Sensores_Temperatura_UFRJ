#pragma once
#include <vector>
#include <string>
#include "Sensor.h"

/*
 * A CentralMonitoramento é responsável por gerenciar vários sensores.
 * Funções principais:
 *  - adicionar sensor (sem duplicar nome)
 *  - inserir valor em um sensor específico (por nome)
 *  - listar sensores e quantidades
 *  - relatórios: evolução de MM3, ordenar por última MM3, variações anormais
 *  - regressão + previsão de um sensor
 */
class CentralMonitoramento {
private:
    std::vector<Sensor> sensores; // "banco de dados" em memória
    // busca linear pelo nome; retorna índice ou -1 se não achar
    int buscarSensorPorNome(const std::string& nome) const;

public:
    // Cria um novo sensor (se não existir) e já lista todos no final
    bool adicionarSensor(const std::string& nome);

    // Insere um valor (double) em um sensor existente
    bool inserirValorNoSensor(const std::string& nomeSensor, double valor);

    // Lista os sensores e quantas amostras cada um tem
    void listarSensores() const;

    // Recebe uma lista de nomes (>=3) e imprime a evolução das MM3 de cada um
    void mostrarEvolucaoMM3(const std::vector<std::string>& nomes) const;

    // Ordena (e imprime) os sensores pela última MM3 (descendente)
    void ordenarPorUltimaMM3() const;

    // Mostra quem teve variação anormal (>=10%) entre as DUAS últimas MM3
    void mostrarVariacoesAnormais10() const;

    // Mostra a regressão (y = a*x + b) e uma previsão do próximo ponto
    void regressaoEPrevisao(const std::string& nomeSensor) const;
};
