#include "IMakeNode.h"

Proprocess::IMakeNode::IMakeNode()
    : fMsh(NULL)
{
  if (!fMsh)  fMsh = new int[2];
}

Proprocess::IMakeNode::IMakeNode(const int nx, const int ny)
    : fMsh(NULL)
{
  if (!fMsh)  fMsh = new int[2];

  fMsh[0] = nx;    fMsh[1] = ny;
}

Proprocess::IMakeNode::~IMakeNode()
{
  if (fMsh)  delete[] fMsh;
}
