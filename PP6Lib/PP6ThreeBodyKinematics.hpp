//! \file   PP6ThreeBodyKinematics.hpp
//! \author Ben Morgan
//! \brief  Declaration of ThreeBodyKinematics class
#ifndef PP6THREEBODYKINEMATICS_HPP
#define PP6THREEBODYKINEMATICS_HPP

#include <cmath>
#include <vector>

class ThreeBodyKinematics {
 public:
  ThreeBodyKinematics(double m1, double m2, double m3, double mParent);
  virtual ~ThreeBodyKinematics();

  void updateKinematics(double m13Sq, double m23Sq);
  void updateKinematics(double m13Sq, double m23Sq, double mParentSq) {
    // Update the parent mass
    this->updateParentMassSq(mParentSq);
    // Update everything else
    this->updateKinematics(m13Sq, m23Sq);
  }
  void flipAndUpdateKinematics();

  void genFlatPhaseSpace();

  bool withinDPLimits() const;
  bool withinDPLimits(double m13Sq, double m23Sq) const;

  double getm12() const {return m12_;}
  double getm23() const {return m23_;}
  double getm13() const {return m13_;}

  double getm12Sq() const {return m12Sq_;}
  double getm23Sq() const {return m23Sq_;}
  double getm13Sq() const {return m13Sq_;}

  double getc12() const {return c12_;}
  double getc23() const {return c23_;}
  double getc13() const {return c13_;}

  double getmParent() const {return mParent_;}
  double getmParentSq() const {return mParentSq_;}

  double getDPBoxArea() const {return (mSqMax_[1] - mSqMin_[1])*(mSqMax_[0] - mSqMin_[0]);}

  double getm1() const {return m1_;}
  double getm2() const {return m2_;}
  double getm3() const {return m3_;}

  double getm23SqMin() const {return mSqMin_[0];}
  double getm13SqMin() const {return mSqMin_[1];}
  double getm12SqMin() const {return mSqMin_[2];}

  double getm23SqMax() const {return mSqMax_[0];}
  double getm13SqMax() const {return mSqMax_[1];}
  double getm12SqMax() const {return mSqMax_[2];}

  double getm23Min() const {return sqrt(mSqMin_[0]);}
  double getm13Min() const {return sqrt(mSqMin_[1]);}
  double getm12Min() const {return sqrt(mSqMin_[2]);}

  double getm23Max() const {return sqrt(mSqMax_[0]);}
  double getm13Max() const {return sqrt(mSqMax_[1]);}
  double getm12Max() const {return sqrt(mSqMax_[2]);}

  double getp1_12() const {return p1_12_;}
  double getp3_12() const {return p3_12_;}
  double getp2_23() const {return p2_23_;}
  double getp1_23() const {return p1_23_;}
  double getp1_13() const {return p1_13_;}
  double getp2_13() const {return p2_13_;}

  double getp1_B() const {return p1_B_;}
  double getp2_B() const {return p2_B_;}
  double getp3_B() const {return p3_B_;}

 protected:
  // various helper methods that are called by the public methods
  double pCalc(double energy, double massSq) const;
  double cFromM(double mijSq, double mikSq, double mij, int i, int j, int k);
  double mFromC(double mijSq, double cij, double mij, int i, int j, int k);
  void updateParentMassSq(double parentMassSq);
  void updateMassSquares(double m13Sq, double m23Sq);
  void calcm12Sq();
  void calcHelicities();
  void calcBframeMomenta();

 private:
  double m1_, m2_, m3_, mParent_;
  double m1Sq_, m2Sq_, m3Sq_, mParentSq_;
  std::vector<double> mass_, mMin_, mMax_, mSq_, mSqMin_, mSqMax_, mSqDiff_, mDiff_;
  double mDTot_, massInt_, mSqDTot_;

  double m12_, m23_, m13_;
  double m12Sq_, m23Sq_, m13Sq_;
  double c12_, c23_, c13_;
  double pi_, piO2_, invPi_;

  double qi_, qk_;

  // Momenta of tracks in 1-2 rest frame
  double p1_12_, p3_12_;
  // Momenta of tracks in 2-3 rest frame
  double p2_23_, p1_23_;
  // Momenta of tracks in 1-3 rest frame
  double p1_13_, p2_13_;

  // Momenta of tracks in B rest frame
  double p1_B_, p2_B_, p3_B_;
};

#endif
