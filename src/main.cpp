# include <iostream>
# include "MyClass.h"
# include <vector>  
# include <string>
# include <iomanip>

// nesse arquivo iremos criar a interação do usuário com o programa:

int main(){
    std::cout << "Bem vindo ao programa de manutenção de sensores de temperatura!" << std::endl;

    std:: cout <<  "\n  1 - Inserir Sensor " 
                    "\n 2 - Inserir Coleta "
                    "\n 3 - Média Móvel de 3+ Sensores " 
                    "\n 4 - Ordenação por última Média Móvel + anomalia ( + - 10 % ) "
                    "\n 5 - Regressão e previsão da próxima amostra" 
                    "\n 6 - Sair do programa" << std::endl;                                           

     std:: cout << " \n Digite o número para acessar nossas informações do Menu: " << std::endl;


// menu de opções para o usuário:
    std:: cin >> numero_menu;

    switch ( numero_menu ){
        case 1:
            std::cout << "Digite o nome do sensor: ";
            std::cin >> nome;

            std::cout << "Digite o tamanho da série: ";
            std::cin >> tamanho;

            inserir_sensor(nome, tamanho); 

            std:: cout << " Sensores existentes: " << std::endl; 
            lista_sensores();

            break;
        case 2:

            inserir_coleta();
        case 3:

            media_movel();
            break;

        case 4:
            ordenacao();
            anomalia();

        case 5:

            previsao_regressao();
            break;
        case 6:

            std::cout << "Saindo do programa..." << std::endl;
            break;




    }


}
