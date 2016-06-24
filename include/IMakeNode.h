#ifndef IMakeNode_HH
#define IMakeNode_HH

#include <vector>

namespace Preprocess2d
{ 
  class INodeContainer;    
  class IMakeNode; 
}


/*! contain the node number and position information */
class Preprocess2d :: INodeContainer
{
  public:
    /*! constructor */
    INodeContainer() : fFlag(0), fNodeId(0),
                       fMatI(0), fMatJ(0),
                       fPosX(0.), fPosY(0.) {}

    /*! deconstructor */
    ~INodeContainer() {}

    /*! set matrix id */
    void SetMatrixId(const int i, const int j) {
      fMatI = i;
      fMatJ = j;
    }

    /*! set position */
    void SetPosition(const double x, const double y) {
      fPosX = x;
      fPosY = y;
    }

    /*! set node id number */
    void SetNodeId(const int id) {
      fNodeId = id;
    }

    /*! get node id number */
    int GetNodeId() const { return fNodeId; }

    /*! set node flags */
    void SetFlags(const int flag) {
      fFlag = flag;
    }

    /*! get matrix id */
    int* GetMatrixId() {
      int* id = new int[2];
      id[0] = fMatI;
      id[1] = fMatJ;

      return id;
    }

    int I() const { return fMatI; }

    int J() const { return fMatJ; }

    /*! get position */
    double* GetPosition() {
      double* pos = new double[2];
      pos[0] = fPosX;
      pos[1] = fPosY;

      return pos;
    }

    double X() const { return fPosX; }

    double Y() const { return fPosY; }

    /*! get flags */
    int GetFlags() const { return fFlag; }

    /*! show the information of this node */
    void Show();


  private:
    /*! node flag */
    int    fFlag;
    /*! node id number */
    int    fNodeId;
    /*! matrix id number */
    int    fMatI;
    int    fMatJ;
    /*! position */
    double fPosX;
    double fPosY;

};

/*********************************************/

/*!
 *  cut the mesh of zone /Omega
 */
class Preprocess2d :: IMakeNode
{

  public:
    /*! constructor */
    IMakeNode();

    IMakeNode(const int nx, const int ny);

    /*! deconstructor */
    virtual ~IMakeNode();

    /*! set mesh number */
    void SetMesh(const int nx, const int ny);

    /*! get mesh number */
    int* GetMesh() { return fMsh; }

    /*! set length of space \Omega */
    void SetSpaceSize(const double lx, const double ly);

    /*! set position of space */
    void SetSpacePosition(const double x=0., const double y=0.);

    /*! get space size */
    double* GetSpaceSize() { return fLength; }

    /*! get space position */
    double* GetSpacePosition() { return fPoint; }

    /*! get the node id number */
    int node(const int i, const int j) const { return j + fMsh[0]*i; }

    /*! fill node information into container */
    void Fill();

    /*! get node container */
    Preprocess2d::INodeContainer* GetNodeEntry(int i, int j) { return fNode.at(node(i,j)); }

    /*! get this node container */
    Preprocess2d::INodeContainer* GetNodeEntry(int i) { return fNode.at(i); }

    /*! get node container vector */
    std::vector<Preprocess2d::INodeContainer*> GetNode() { return fNode; }

    /*! get total node entries */
    int GetNodeEntries() const { return fNode.size(); }

    /*! get node id for circular geometry */
    std::vector<int> MakeCircle(const double x0, const double y0, const double r);

    /*! get node id if the node is inside the rectange */
    std::vector<int> MakeRectangle(const double x0, const double y0, 
                                   const double lx, const double ly);


    /*! get nodes on the boundary */
    std::vector<int> GetVertexNode();

    /*! get boundary node */
    std::vector<int> GetBoundaryNode(const std::string& opt="all");


  private:
    /*! mesh number */
    int* fMsh;
    /*! space length */
    double* fLength;
    /*! space center position */
    double* fPoint;
    /*! node container */
    std::vector<Preprocess2d::INodeContainer*> fNode;
};

#endif
