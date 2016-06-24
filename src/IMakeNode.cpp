#include <iostream>
#include <cmath>
#include "IMakeNode.h"

void Preprocess2d::INodeContainer::Show()
{
  std::cout << "\n Node ID: " << fNodeId << std::endl;
  std::cout << " Matrix number: ( " << fMatI << ", " << fMatJ << " )" << std::endl;
  std::cout << " X: " << fPosX << " [m] , Y: " << fPosY << " [m] " << std::endl;
  std::cout << " Flag: " << fFlag << std::endl;
}


Preprocess2d::IMakeNode::IMakeNode()
    : fMsh(NULL), fLength(NULL), fPoint(NULL)
{
  if (   !fMsh)  fMsh    = new int[2];
  if (!fLength)  fLength = new double[2];
  if ( !fPoint)  fPoint  = new double[2];
}

Preprocess2d::IMakeNode::IMakeNode(const int nx, const int ny)
    : fMsh(NULL), fLength(NULL), fPoint(NULL)
{
  if (   !fMsh)  fMsh    = new int[2];
  if (!fLength)  fLength = new double[2];
  if ( !fPoint)  fPoint  = new double[2];

  fMsh   [0] = nx;    fMsh   [1] = ny;
  fLength[0] = 1.;    fLength[1] = 1.;
  fPoint [0] = 0.;    fPoint [1] = 0.;
}

Preprocess2d::IMakeNode::~IMakeNode()
{
  if (   fMsh)  delete[] fMsh;
  if (fLength)  delete[] fLength;
  if ( fPoint)  delete[] fPoint;
}

void Preprocess2d::IMakeNode::SetMesh(const int nx, const int ny)
{
  if (!fMsh)  fMsh = new int[2];

  fMsh[0] = nx;    fMsh[1] = ny;
}

void Preprocess2d::IMakeNode::SetSpaceSize(const double lx, const double ly)
{
  if (!fLength)  fLength = new double[2];

  fLength[0] = lx;
  fLength[1] = ly;
}

void Preprocess2d::IMakeNode::SetSpacePosition(const double x, const double y)
{
  if (!fPoint)  fPoint = new double[2];

  fPoint[0] = x;
  fPoint[1] = y;
}

void Preprocess2d::IMakeNode::Fill()
{
  Preprocess2d::INodeContainer* nc = NULL;

  // calculate dx, dy
  const double dx = fLength[0] / fMsh[0];
  const double dy = fLength[1] / fMsh[1];
  
  double posx, posy;

  for (int i=0; i<fMsh[1]; i++) {    // y direction
    // calculate y position
    posy = fPoint[1] + i * dy;

    for (int j=0; j<fMsh[0]; j++) {    // x direction
      // calculate x position
      posx = fPoint[0] + j * dx;

      // fill
      nc = new Preprocess2d::INodeContainer();

      nc->SetMatrixId(i, j);
      nc->SetPosition(posx, posy);
      nc->SetNodeId( node(i,j) );
      
      fNode.push_back(nc);
    }

  }

  // set flags for boundary
  fNode.at( node(0,0) )->SetFlags(2);

}


std::vector<int> Preprocess2d::IMakeNode::MakeCircle(const double x0, const double y0, const double r)
{
  std::vector<int> nd;

  for (std::vector<int>::size_type i=0; i<fNode.size(); i++) {
    // if the node position is inside this circle, then ...
    if ( pow(fNode.at(i)->X()-x0, 2) + pow(fNode.at(i)->Y()-y0, 2) <= pow(r,2) ) 
      nd.push_back( fNode.at(i)->GetNodeId() );
  }

  return nd;
}


std::vector<int> Preprocess2d::IMakeNode::MakeRectangle(const double x0, const double y0,
                                                        const double lx, const double ly)
{
  std::vector<int> nd;

  for (std::vector<int>::size_type i=0; i<fNode.size(); i++) {
    // if the node position is inside given rectangle range, then ..
    if ( fNode.at(i)->X() >= x0 && fNode.at(i)->X() <= x0+lx && 
         fNode.at(i)->Y() >= y0 && fNode.at(i)->Y() <= y0+ly )
      nd.push_back( fNode.at(i)->GetNodeId() );
  }

  return nd;
}


std::vector<int> Preprocess2d::IMakeNode::GetVertexNode()
{
  std::vector<int> vertex;

  vertex.push_back( node(0,0) );
  vertex.push_back( node(0,fMsh[0]-1) );
  vertex.push_back( node(fMsh[1]-1,0) );
  vertex.push_back( node(fMsh[1]-1,fMsh[0]-1) );

  return vertex;
}

std::vector<int> Preprocess2d::IMakeNode::GetBoundaryNode(const std::string& opt)
{
  std::vector<int> bdy;

  if (opt=="t" || opt=="top") {
    for (int j=1; j<fMsh[0]-1; j++)
      bdy.push_back( node(fMsh[1]-1,j) );
  }
  else if (opt=="b" || opt=="bottom") {
    for (int j=1; j<fMsh[0]-1; j++)
      bdy.push_back( node(0,j) );
  }
  else if (opt=="l" || opt=="left") {
    for (int i=1; i<fMsh[1]-1; i++)
      bdy.push_back( node(i,0) );
  }
  else if (opt=="r" || opt=="right") {
    for (int i=1; i<fMsh[1]-1; i++)
      bdy.push_back( node(i,fMsh[0]-1) );
  }
  else {
    for (int i=1; i<fMsh[1]-1; i++) {
      for (int j=1; j<fMsh[0]-1; j++)
        bdy.push_back( node(i,j) );
    }
  }
  
  return bdy;
}


