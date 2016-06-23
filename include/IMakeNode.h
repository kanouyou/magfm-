#ifndef IMakeNode_HH
#define IMakeNode_HH

namespace Proprocess
{ 
  class INodeContainer;    
  class IMakeNode; 
}


/*! contain the node number and position information */
class Proprocess :: INodeContainer
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
class Proprocess :: IMakeNode
{

  public:
    /*! constructor */
    IMakeNode();

    IMakeNode(const int nx, const int ny);

    /*! deconstructor */
    ~IMakeNode();

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
    Proprocess::INodeContainer* GetNodeEntry(int i, int j) { return fNode[node(i,j)]; }

    /*! get this node container */
    Proprocess::INodeContainer* GetNodeEntry(int i) { return fNode[i]; }

    /*! get node container vector */
    std::vector<Proprocess::INodeContainer*> GetNode() { return fNode; }

    /*! get total node entries */
    int GetNodeEntries() const { return fNode.size(); }


  private:
    /*! mesh number */
    int* fMsh;
    /*! space length */
    double* fLength;
    /*! space center position */
    double* fPoint;
    /*! node container */
    std::vector<Proprocess::INodeContainer*> fNode;
};

#endif
