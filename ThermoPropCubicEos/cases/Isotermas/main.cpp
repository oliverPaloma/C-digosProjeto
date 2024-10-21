#include "../../ThermoPropCubicEos.hpp"


int main ()
{
  auto T = 280.; //isoterma temperatura constante
 //auto P = 30000000.; obter
  
 // auto databasePath = "/home/fellipe/Dropbox/Pessoais/Downloads/ThermoPropCubicEos/database/test.yml";
  auto databasePath = "/home/paloma-j-oliveira/Documentos/ThermoPropCubicEos/database/test.yml";
  auto components = "CO2"; //apenas um componete
  std::vector<double> Tc,Pc,omega;
  std::vector<std::vector<double>> kij(1, std::vector<double>(1)); 

  auto EoSModel = CubicEOSModel::PengRobinson; //PR escolhido
  //auto EoSModel = CubicEOSModel::VanDerWaals; // vdW escolhido
  //auto EoSModel = CubicEOSModel::SoaveRedlichKwong;  //srk escolhido

  std::vector<double> z{1.}; //fração molar

  read_database(Tc,Pc,omega,databasePath,components);
  
  CubicEOSProps props;

  //compute(props,Tc,Pc,omega,T,P,z,EoSModel,kij);
  //isoterma(EoSModel,kij, tc, pc, omega...); 

  auto Vi = 0.05/1000.; // m³/mol
  auto Vf = 0.45/1000.;
  auto npoints = 50;

  // kij aqui?
  calculateIsoterma(EoSModel,Tc,Pc,omega,T,Vi,Vf,npoints); //CubicEOSModel EoSModel, std::vector<double> Tc, std::vector<double> Pc, std::vector<double> omega, double T, double Vi, double Vf, int npoints)


  return 0;
}


