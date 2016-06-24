#ifndef IMakeMaterial_HH
#define IMakeMaterial_HH

#include <vector>
#include <string>
#include <array>

#include "IMakeNode.h"

namespace Preprocess2d
{
  class IMaterialContainer;
  class IMakeMaterial; 
}


/*
 *  class to contain the material information
 */

class Preprocess2d :: IMaterialContainer
{
  public:
    /*! constructor */
    IMaterialContainer(const std::string& name, const double rho, const double C,
                       std::array<double,2> k)
        : fRho(rho), fC(C), fMat(name), fFlag(0) {
      fk[0] = k.at(0);
      fk[1] = k.at(1);
    }

    IMaterialContainer() : fRho(1.), fC(1.), fMat("Air"), fFlag(0) {
      fk[0] = 0.;
      fk[1] = 0.;
    }

    /*! deconstructor */
    ~IMaterialContainer() {}

    /*! set material density */
    void SetDensity(const double rho) { fRho = rho; }

    /*! set capacity */
    void SetCapacity(const double C) { fC = C; }

    /*! set thermal conductivity */
    void SetConductivity(const double kx, const double ky) {
      fk[0] = kx;
      fk[1] = ky;
    }

    void SetConductivity(std::array<double,2> k) {
      fk[0] = k.at(0);
      fk[1] = k.at(1);
    }

    /*! set material name */
    void SetName(const std::string& name) { fMat = name; }

    /*! set flags */
    void SetFlags(const int flag) { fFlag = flag; }

    /*! get material name */
    std::string GetName() const { return fMat; }

    /*! get material density */
    double GetDensity() const { return fRho; }

    /*! get capacity */
    double GetCapacity() const { return fC; }

    /*! get thermal conductivity */
    std::array<double, 2> GetConductivity() { return fk; }

    /*! get flag */
    int GetFalgs() const { return fFlag; }

    /*! show the material info */
    void Show();


  private:
    /*! density */
    double fRho;
    /*! capacity */
    double fC;
    /*! thermal conductivity */
    std::array<double, 2> fk;
    /*! material name */
    std::string fMat;
    /*! flag */
    int fFlag;
};


/**********************************************/

class Preprocess2d :: IMakeMaterial : public Preprocess2d::IMakeNode
{
  public:
    /*! constuctor */
    IMakeMaterial() : IMakeNode() {}

    /*! deconstructor */
    virtual ~IMakeMaterial() {}

    /*! initialized material property */
    void Initialize();

    /*! return the material container class */
    IMaterialContainer* GetMatEntry(const int nd) { return fMat.at(nd); }

    /*! return the material container class */
    IMaterialContainer* GetMatEntry(const int i, const int j);

    /*! set material for this node */
    void SetMaterial(const int id, const std::string& name, const double rho, 
                     const double C, std::array<double,2> k, const int flag);


  private:
    /*! material contaienr */
    std::vector<IMaterialContainer*> fMat;
};

#endif
