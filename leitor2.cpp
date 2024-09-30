#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // Vetores para armazenar os dados
    std::vector<std::string> componentes = {"ETHANE", "METHANE"};
    std::vector<double> Tc;
    std::vector<double> Pc;
    std::vector<double> omega;

    // Abrir o arquivo de entrada
    //std::ifstream arquivo("properties");
    std::ifstream arquivo("/home/paloma-j-oliveira/Área de trabalho/properties");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo 'properties'. Verifique se o arquivo existe e está no diretório correto." << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        // Cria um stream da linha atual
        std::stringstream stream(linha);

        // Variáveis temporárias para armazenar os valores de cada linha
        std::string nome;
        double temp, pressao, fator;

        // Ler os dados separados por tabulação
        stream >> nome >> temp >> pressao >> fator;

        // Armazenar os dados nos vetores correspondentes
        componentes.push_back(nome); // Adiciona o componente ao vetor de nomes
        Tc.push_back(temp);          // Adiciona a temperatura crítica
        Pc.push_back(pressao);       // Adiciona a pressão crítica
        omega.push_back(fator);      // Adiciona o fator acêntrico
    }

    // Fechar o arquivo
    arquivo.close();

    // Exibir os dados lidos para verificar
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << "Componente: " << componentes[i]
                  << ", Tc: " << Tc[i]
                  << ", Pc: " << Pc[i]
                  << ", Omega: " << omega[i] << std::endl;
    }

    return 0;
}
/* */

/*


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main() {
    // Vetores para armazenar os dados
    std::vector<std::string> componentes;
    std::vector<double> Tc;
    std::vector<double> Pc;
    std::vector<double> omega;

    // Abrir o arquivo de entrada
    //std::ifstream arquivo("properties");
   
    std::ifstream arquivo("/home/paloma-j-oliveira/Área de trabalho/properties");


    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo 'properties'. Verifique o caminho." << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        // Cria um stream da linha atual
        std::stringstream stream(linha);

        // Variáveis temporárias para armazenar os valores de cada linha
        std::string nome;
        double temp, pressao, fator;

        // Ler os dados separados por espaços ou tabulação
        stream >> nome >> temp >> pressao >> fator;

        // Armazenar os dados nos vetores correspondentes
        componentes.push_back(nome);   // Adiciona o nome do componente
        Tc.push_back(temp);            // Adiciona a temperatura crítica (Tc)
        Pc.push_back(pressao);         // Adiciona a pressão crítica (Pc)
        omega.push_back(fator);        // Adiciona o fator acêntrico (omega)
    }

    // Fechar o arquivo
    arquivo.close();

    // Exibir os dados lidos para verificar
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << "Componente: " << componentes[i]
                  << ", Tc: " << Tc[i]
                  << ", Pc: " << Pc[i]
                  << ", Omega: " << omega[i] << std::endl;
    }

    return 0;
}

*/
