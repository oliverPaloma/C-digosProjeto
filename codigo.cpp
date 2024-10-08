#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

void selectEos(int opcao, double Tc, double Pc, double omega, double T, double V_min, double V_max, int num_points);

int main() {
    std::vector<std::string> componentes;
    std::vector<double> Tc;
    std::vector<double> Pc;
    std::vector<double> omega;

    //std::ifstream arquivo("/home/paloma-j-oliveira/Área de trabalho/properties");
    std::ifstream arquivo("/home/palomajo/Área de Trabalho/Paloma/properties");//abre o arquivo

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo 'properties'." << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream stream(linha);
        std::string nome;
        double temp, pressao, fator;
        stream >> nome >> temp >> pressao >> fator;
        componentes.push_back(nome);  
        Tc.push_back(temp);
        Pc.push_back(pressao);
        omega.push_back(fator);
    }

    arquivo.close(); 

    std::cout << "Componentes disponíveis:" << std::endl; //exibe
    for (size_t i = 0; i < componentes.size(); ++i) {
        std::cout << i << ": " << componentes[i]
                  << " | Tc: " << Tc[i] << " | Pc: " << Pc[i]
                  << " | omega: " << omega[i] << std::endl;
    }

    int indiceEscolhido;
    std::cout << "Escolha um componente pelo índice: ";
    std::cin >> indiceEscolhido;

    double T;
    std::cout << "Digite a temperatura (T): ";
    std::cin >> T;

    int opcao;
    std::cout << "Escolha a equação de estado: 0-vdW, 1-SRK, 2-PR: ";
    std::cin >> opcao;
    
    double V_min = 0.1, V_max = 1.0;  //intervao de v
    int num_points = 10;  //pontos de v

    selectEos(opcao, Tc[indiceEscolhido], Pc[indiceEscolhido], omega[indiceEscolhido], T, V_min, V_max, num_points);

    return 0;
}

void selectEos(int opcao, double Tc, double Pc, double omega, double T, double V_min, double V_max, int num_points) {
    const double R = 8.314;  
    double psi, sigma, epsilon, b, alphaT, Tr, alphaTr, P;

    std::string filename = "pressao_T" + std::to_string(static_cast<int>(T)) + ".txt";
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    outfile << "Volume\tPressao\n";
    
    double dV = (V_max - V_min) / (num_points - 1); //incremento de volume no intervalo

    for (int i = 0; i < num_points; ++i) {     //loop calcula pressaoo em diferentes volumes e salva no arquivo
       double V = V_min + i * dV;  //Volume atual

      
        switch (opcao) {
            case 0: //van der waals vdW
                psi = 27.0 / 64.0;
                sigma = 0;
                epsilon = 0;
                alphaTr = 1;  

                b = (R * Tc) / (8 * Pc);  
                alphaT = psi * (R * R * Tc * Tc) / Pc;  

                P = (R * T) / (V - b) - (alphaT / ((V + epsilon * b) * (V + sigma * b)));
                std::cout << "Pressão (vdW): " << P << " Pa" << std::endl;
                break;

            case 1: //soave-redlich-kwong SRK
                psi = 0.42748;
                sigma = 1;
                epsilon = 0;

                Tr = T / Tc;
                alphaTr = pow(1 + (0.480 + 1.574 * omega - 0.176 * omega * omega) * (1 - sqrt(Tr)), 2);  
                b = 0.08664 * (R * Tc) / Pc;  
                alphaT = psi * (alphaTr * R * R * Tc * Tc) / Pc; 

                P = (R * T) / (V - b) - (alphaT / ((V + epsilon * b) * (V + sigma * b)));
                std::cout << "Pressão (SRK): " << P << " Pa" << std::endl;
                break;

            case 2: //peng-robinson PR
                psi = 0.45724;
                sigma = 1 + sqrt(2);
                epsilon = 1 - sqrt(2);

                Tr = T / Tc;
                alphaTr = pow(1 + (0.37464 + 1.54226 * omega - 0.26992 * omega * omega) * (1 - sqrt(Tr)), 2);  

                b = 0.07780 * (R * Tc) / Pc; 
                alphaT = psi * (alphaTr * R * R * Tc * Tc) / Pc;  

                P = (R * T) / (V - b) - (alphaT / ((V + epsilon * b) * (V + sigma * b)));
                std::cout << "Pressão (PR): " << P << " Pa" << std::endl;
                break;

            default:
                std::cout << "Opção inválida." << std::endl;
                return;
        }
        outfile << V << "\t" << P << "\n";
    }

    outfile.close();
    std::cout << "Dados armazenados no arquivo: " << filename << std::endl;
}