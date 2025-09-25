#include <iostream>
#include <vector>
#include <string>
#include <limits> // pra limpar buffer do cin
#include "CentralMonitoramento.h"

/*
 * Programa principal com um menu simples.
 * A ideia é eu conseguir cadastrar sensores, inserir valores e chamar os relatórios.
 * Obs.: uso getline pra ler nomes com espaços (ex.: "sensor sala 1").
 */
int main() {
    CentralMonitoramento central; // minha "central" que guarda tudo
    std::cout << "Bem-vindo ao monitor de sensores de temperatura!\n";

    while (true) {
        // Menu de opções
        std::cout <<
            "\n1) Inserir sensor"
            "\n2) Inserir valor no sensor"
            "\n3) Evolucao MM3 (informar 3 ou mais nomes)"
            "\n4) Ordenar por ultima MM3 e variacoes anormais (±10%)"
            "\n5) Regressao e previsao (1 sensor)"
            "\n6) Sair do programa.\n"
            "Digite o numero: ";

        int numero_menu;
        if (!(std::cin >> numero_menu)) return 0; // se der ctrl+d/EOF, saio
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpa \n

        if (numero_menu == 1) {
            // Inserir um novo sensor
            std::string nome;
            std::cout << "Nome do novo sensor: ";
            std::getline(std::cin, nome);
            central.adicionarSensor(nome);

        } else if (numero_menu == 2) {
            // Inserir um valor em um sensor existente
            std::string nome;
            double valor;
            std::cout << "Nome do sensor: ";
            std::getline(std::cin, nome);
            std::cout << "Valor (double): ";
            std::cin >> valor;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            central.inserirValorNoSensor(nome, valor);

        } else if (numero_menu == 3) {
            // Mostrar evolução da MM3 para K sensores
            std::cout << "Quantos sensores (>=3)? ";
            int k; std::cin >> k;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::vector<std::string> nomes; nomes.reserve(k);
            for (int i = 0; i < k; ++i) {
                std::string n;
                std::cout << "Nome [" << i+1 << "]: ";
                std::getline(std::cin, n);
                nomes.push_back(n);
            }
            central.mostrarEvolucaoMM3(nomes);

        } else if (numero_menu == 4) {
            // Ordenar por última MM3 e verificar variações anormais
            central.ordenarPorUltimaMM3();
            central.mostrarVariacoesAnormais10();

        } else if (numero_menu == 5) {
            // Regressão + previsão do próximo valor
            std::string nome;
            std::cout << "Sensor para regressao/previsao: ";
            std::getline(std::cin, nome);
            central.regressaoEPrevisao(nome);

        } else if (numero_menu == 6) {
            std::cout << "Saindo do programa...\n";
            break;

        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
    return 0;
}
