#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// Declaração da função selectEos
void selectEos(int opcao, double Tc, double Pc, double omega, double T, double V);


int main() {
    std::vector<std::string> componentes;
    std::vector<double> Tc;
    std::vector<double> Pc;
    std::vector<double> omega;
    
    std::ifstream arquivo("/home/paloma-j-oliveira/Área de trabalho/properties");//abre o arquivo
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo 'properties'." << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream stream(linha);
        std::string nome;
        double temp, pressao, fator;
        stream >> nome >> temp >> pressao >> fator; //Ler os dados separados por espaços ou tabulação
        componentes.push_back(nome); //Armazenar os dados nos vetores 
        Tc.push_back(temp);
        Pc.push_back(pressao);
        omega.push_back(fator);
    }

    arquivo.close();
    
    std::cout << "Componentes disponíveis:" << std::endl; //Exibir 
    for (size_t i = 0; i < componentes.size(); ++i) {
       // std::cout << i << ": " << componentes[i] << std::endl;
        std::cout << i << ": " << componentes[i]
            << " | Tc: " << Tc[i] << " | Pc: " << Pc[i] 
            << " | omega: " << omega[i] << std::endl;

    }

    int indiceEscolhido;
    std::cout << "Escolha um componente pelo índice: ";
    std::cin >> indiceEscolhido;

    double T, V;
    std::cout << "Digite a temperatura (T): ";
    std::cin >> T;
    std::cout << "Digite o volume (V): ";
    std::cin >> V;

    
    int opcao;
    std::cout << "Escolha a equação de estado: 0-vdW, 1-SRK, 2-PR: "; //Escolher EOS
    std::cin >> opcao;

    selectEos(opcao, Tc[indiceEscolhido], Pc[indiceEscolhido], omega[indiceEscolhido], T, V);

    return 0;
}

// Função para calcular a equação de estado com base na seleção do usuário
void selectEos(int opcao, double Tc, double Pc, double omega, double T, double V) {
    // Constantes para as equações de estado
    double beta, q, Z;

    switch (opcao) {
        case 0: // Van der Waals
            beta = omega * (Pc / Tc);
            q = (27.0 / 64.0) * (Tc / omega);
            Z = 1 + beta - q * beta;
            std::cout << "Z (vdW): " << Z << std::endl;
            break;

        case 1: // Soave-Redlich-Kwong
            beta = 0.08664 * (Pc / Tc);
            q = 0.42748 * (Tc / omega);
            Z = 1 + beta - q * beta;
            std::cout << "Z (SRK): " << Z << std::endl;
            break;

        case 2: // Peng-Robinson
            beta = 0.07780 * (Pc / Tc);
            q = 0.45724 * (Tc / omega);
            Z = 1 + beta - q * beta;
            std::cout << "Z (PR): " << Z << std::endl;
            break;

        default:
            std::cout << "Opção inválida." << std::endl;
            break;
    }
}

