#include "IMakeNode.h"

Proprocess::IMakeNode::IMakeNode()
    : fMsh(NULL), fLength(NULL), fPoint(NULL)
{
  if (   !fMsh)  fMsh    = new int[2];
  if (!fLength)  fLength = new int[2];
  if ( !fPoint)  fPoint  = new int[2];
}

Proprocess::IMakeNode::IMakeNode(const int nx, const int ny)
    : fMsh(NULL), fLength(NULL), fPoint(NULL)
{
  if (   !fMsh)  fMsh    = new int[2];
  if (!fLength)  fLength = new int[2];
  if ( !fPoint)  fPoint  = new int[2];

  fMsh   [0] = nx;    fMsh   [1] = ny;
  fLength[0] = 1.;    fLength[1] = 1.;
  fPoint [0] = 0.;    fPoint [1] = 0.;
}

Proprocess::IMakeNode::~IMakeNode()
{
  if (   fMsh)  delete[] fMsh;
  if (fLength)  delete[] fLength;
  if ( fPoint)  delete[] fPoint;
}

void Proprocess::IMakeNode::SetMesh(const int nx, const int ny)
{
  if (!fMsh)  fMsh = new int[2];

  fMsh[0] = nx;    fMsh[1] = ny;
}

void Proprocess::IMakeNode::SetSpaceSize(const double lx, const double ly)
{
  if (!fLength)  fLength = new double[2];

  fLength[0] = lx;
  fLength[1] = ly;
}

void Proprocess::IMakeNode::SetSpacePosition(const double x, const double y)
{
  if (!fPoint)  fPoint = new double[2];

  fPoint[0] = x;
  fPoint[1] = y;
}

void Proprocess::IMakeNode::Fill()
{
  Proprocess::INodeContainer* nc = NULL;

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
      nc = new Proprocess::INodeContainer();

      nc->SetMatrixId(i, j);
      nc->SetPosition(posx, posy);
      nc->SetNodeId( node(i,j) );
      
      fNode.push_back(nc);
    }

  }

}
