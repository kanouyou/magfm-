#include <iostream>
#include "IMakeMaterial.h"

void Preprocess2d::IMaterialContainer::Show()
{
  std::cout << "\n Material name: " << fMat << std::endl;
  std::cout << " Density: " << fRho << " [kg/m3]" << std::endl;
  std::cout << " Heat Capacity: " << fC << " [J/kg/K]" << std::endl;
  std::cout << " Thermal Conductivity: ( " << fk[0] << ", " << fk[1] 
            << " ) [W/m/K]" << std::endl;
  std::cout << " Flags: " << fFlag << std::endl;
}

void Preprocess2d::IMakeMaterial::Initialize()
{
  IMaterialContainer* mat = NULL;

  const int n = Preprocess2d::IMakeNode::GetNodeEntries();

  // initialize the material
  for (int i=0; i<n; i++) {
    mat = new IMaterialContainer();
    fMat.push_back(mat);
  }
}

Preprocess2d::IMaterialContainer* Preprocess2d::IMakeMaterial::GetMatEntry(const int i, const int j)
{
  const int nd = Preprocess2d::IMakeNode::node(i,j);

  return fMat.at(nd);
}

void Preprocess2d::IMakeMaterial::SetMaterial(const int id, const std::string& name, const double rho,
                                              const double C, std::array<double,2> k, const int flag)
{
  fMat.at(id)->SetName(name);
  fMat.at(id)->SetDensity(rho);
  fMat.at(id)->SetCapacity(C);
  fMat.at(id)->SetConductivity(k);
  fMat.at(id)->SetFlags(flag);
}


