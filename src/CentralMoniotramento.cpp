// Arquivo com os métodos de Sensor.h

# include "Sensor.h"
# include <vector>


// vetor de objetos sensores:
std::vector<Sensor> sensores;

// função para listar os sensores existentes:
void lista_sensores(){

    i=1;
    for (auto &s : sensores){
        std:: cout << "Nome do sensor:" << s.modelo << "Tamanho da série:" << s.size << std::endl;
        i++;
    }
}
// função para inserir um novo sensor:
void inserir_sensor(std::string nome , int tamanho){

    // instanciando um novo sensor apartir da classe Sensor:
    Sensor novo_sensor;
    novo_sensor.modelo = nome;
    novo_sensor.size = tamanho;

    // adicionando o novo sensor ao vetor de sensores:
    sensores.push_back(novo_sensor)

}