// // funcoes relacionadas aos dados dos sensores
// # include "DadoSensor.h"
// # include <vector>

// // vetor de objetos sensores:
// std::vector<Sensor> sensores;

// // vetor de objetos novos_dados:
// std::vector<DadoSensor> novos_dados;

// // função para listar os sensores existentes:
// void lista_dados_sensores(){

//     // listando os sensores da central:
//     int i =1;
//     for (auto &s : sensores){
//         std:: cout << "Sensor" << i << "Nome do sensor:" << s.modelo << "Tamanho da série:" << s.size << std::endl;
//         i++;
//     }
    
//     // listando os dados dos sensores:
//     int i =1;
//     for (auto &d : novos_dados){
//         std:: cout << "dados do Sensor" << i << "Temperatura Coletada:" << d.teperatura << "data/hora da Coleta:" << d.data_hora << std::endl;
//         i++;
//     }
// }

// // função para inserir novos dados:
// insercao_novos_dados(temperatura, data_hora){

//     DadoSensor new_data;
//     new_data.temperatura = temperatura;
//     new_data.data_hora = data_hora;

//     // adicionando o novo dado ao vetor de novos dados::
//     novos_dados.push_back(new_data);
        
// }

#include "DadoSensor.h"

// Construtor: só guarda as infos nos atributos
DadoSensor::DadoSensor(std::string nome, double valor)
    : nomeDoDado(nome), valorDoDado(valor) {}

// Retorna o nome do dado (ex.: "temperatura")
std::string DadoSensor::getNome() const { return nomeDoDado; }

// Retorna o valor do dado (ex.: 25.3)
double DadoSensor::getValor() const { return valorDoDado; }


