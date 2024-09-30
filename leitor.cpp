#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct ComponenteQuimico {
    std::string nome;
    double Tc;    // Temperatura crítica
    double Pc;    // Pressão crítica
    double omega; // Fator acêntrico
};

std::vector<ComponenteQuimico> lerArquivo(const std::string& nomeArquivo) {
    std::vector<ComponenteQuimico> componentes;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return componentes;
    }

    while (std::getline(arquivo, linha)) {
        std::istringstream stream(linha);
        ComponenteQuimico componente;
        std::string Tc_str, Pc_str, omega_str;

        // Lê as colunas separadas por espaços ou tabs
        stream >> componente.nome >> Tc_str >> Pc_str >> omega_str;

        // Converte strings para números
        componente.Tc = std::stod(Tc_str);         // Converte a temperatura
        componente.Pc = std::stod(Pc_str);         // Converte a pressão
        componente.omega = std::stod(omega_str);   // Converte o fator acêntrico

        componentes.push_back(componente);
    }

    arquivo.close();
    return componentes;
}

int main() {
    const std::string nomeArquivo = "properties";// até funciona se executar pelo terminal e o arquivo estiver na mesma pasta que o leitor.cpp
    //colocar o endereço do arquivo como mostra abaixo
    //const std::string nomeArquivo = "/home/paloma-j-oliveira/Área de trabalho/properties";

    std::vector<ComponenteQuimico> componentes = lerArquivo(nomeArquivo);

    // Exibe os componentes lidos
    for (const auto& componente : componentes) {
        std::cout << "Nome: " << componente.nome 
                  << ", Tc: " << componente.Tc 
                  << ", Pc: " << componente.Pc 
                  << ", Omega: " << componente.omega << std::endl;
    }

    return 0;
}
