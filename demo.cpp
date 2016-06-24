#include <iostream>
#include <array>
#include "IMakeNode.h"
#include "IMakeMaterial.h"

using namespace Preprocess2d;

void checknode()
{
  IMakeMaterial* node = new IMakeMaterial();
  node->SetMesh(30,40);

  node->SetSpaceSize(1.5, 0.5);
  node->Fill();
 
  std::vector<int> nd = node->GetVertexNode();
  for (std::vector<int>::size_type i=0; i<nd.size(); i++)
    std::cout << nd.at(i) << std::endl;

}

int main(int argc, char** argv)
{
  
  checknode();

  return 0;
}
