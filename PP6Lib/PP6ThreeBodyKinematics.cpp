//****************************************************************************
// Class for defining various kinematic routines.
//****************************************************************************

// --CLASS DESCRIPTION [MISC] --
// // Class for defining various kinematic routines.

#include <cstdlib>

#include "PP6ThreeBodyKinematics.hpp"

ThreeBodyKinematics::ThreeBodyKinematics(double m1, double m2, double m3, double mParent) :
    m1_(m1), m2_(m2), m3_(m3), mParent_(mParent),
    m1Sq_(m1*m1), m2Sq_(m2*m2), m3Sq_(m3*m3), mParentSq_(mParent*mParent),
    mDTot_(m1 + m2 + m3),
    massInt_(mParent - (m1+m2+m3)),
    mSqDTot_(m1*m1 + m2*m2 + m3*m3),
    m12_(0.0), m23_(0.0), m13_(0.0),
    m12Sq_(0.0), m23Sq_(0.0), m13Sq_(0.0),
    c12_(0.0), c23_(0.0), c13_(0.0),
    pi_(acos(-1.0)), piO2_(acos(-1.0)/2.0), invPi_(1.0/acos(-1.0))
{
  // Constructor
  mass_.clear(); mMin_.clear(); mMax_.clear(); mSqMin_.clear(); mSqMax_.clear();
  mSq_.clear();
  mSqDiff_.clear();
  mDiff_.clear();

  mass_.push_back(m1_);
  mass_.push_back(m2_);
  mass_.push_back(m3_);

  mSq_.push_back(m1Sq_);
  mSq_.push_back(m2Sq_);
  mSq_.push_back(m3Sq_);

  // DP max and min kinematic boundary for circumscribed box
  // (see figure in PDG book).
  for (int i = 0; i < 3; i++) {
    mMin_.push_back(mDTot_ - mass_[i]);
    mMax_.push_back(mParent_ - mass_[i]);
    mSqMin_.push_back(mMin_[i]*mMin_[i]);
    mSqMax_.push_back(mMax_[i]*mMax_[i]);
    mSqDiff_.push_back(mSqMax_[i] - mSqMin_[i]);
    mDiff_.push_back(mMax_[i] - mMin_[i]);
  }
}

ThreeBodyKinematics::~ThreeBodyKinematics()
{
  // Destructor
}

void ThreeBodyKinematics::updateKinematics(double m13Sq, double m23Sq)
{
  // Sets the internal private data members 
  // m13Sq and m23Sq, as well as m13 and m23.
  // Also calculate m12Sq and m12, given mParent defined in the constructor.
  // Lastly, calculate the helicity cosines.

  // Update the 3 mass-squares
  this->updateMassSquares(m13Sq, m23Sq);

  // Now update the helicity cosines
  this->calcHelicities();
}

void ThreeBodyKinematics::updateParentMassSq(double parentMassSq)
{
  // Update the parent (e.g. B) mass (useful if we have smeared MC that is different from PDG value)
  // or we are using parent mass that is not constrained. The parent mass can also be updated
  // using updateKinematics().
  mParentSq_ = parentMassSq;
  if (mParentSq_ > 0.0) {
    mParent_ = sqrt(mParentSq_);
  } else {
    mParent_ = 0.0;
  }
}

void ThreeBodyKinematics::updateMassSquares(double m13Sq, double m23Sq)
{
  m13Sq_ = m13Sq;
  if (m13Sq_ > 0.0) {
    m13_ = sqrt(m13Sq_);
  } else {
    m13_ = 0.0;
  }

  m23Sq_ = m23Sq;
  if (m23Sq_ > 0.0) {
    m23_ = sqrt(m23Sq_);
  } else {
    m23_ = 0.0;
  }

  // Now calculate m12Sq and m12.
  this->calcm12Sq();

  // Calculate momenta of tracks in parent (B, D etc.) rest-frame
  this->calcBframeMomenta();
}

void ThreeBodyKinematics::calcm12Sq()
{
  // Calculate m12Sq from m13Sq and m23Sq.
  m12Sq_ = mParentSq_ + mSqDTot_ - m13Sq_ - m23Sq_;

  // If m12Sq is too low, return lower limit,
  // and modify m13Sq accordingly.
  if (m12Sq_ < mSqMin_[2]) {
    m12Sq_ = mSqMin_[2] + 1.0e-3;
    m13Sq_ = mParentSq_ + mSqDTot_ - m12Sq_ - m23Sq_;
  }

  if (m12Sq_ > 0.0) {
    m12_ = sqrt(m12Sq_);
  } else {
    m12_ = 0.0;
  }
}

void ThreeBodyKinematics::calcBframeMomenta()
{
  double e1 = (mParentSq_ + m1Sq_ - m23Sq_) / (2.0*mParent_);
  double e2 = (mParentSq_ + m2Sq_ - m13Sq_) / (2.0*mParent_);
  double e3 = (mParentSq_ + m3Sq_ - m12Sq_) / (2.0*mParent_);

  p1_B_ = this->pCalc(e1, m1Sq_);
  p2_B_ = this->pCalc(e2, m2Sq_);
  p3_B_ = this->pCalc(e3, m3Sq_);
}

void ThreeBodyKinematics::calcHelicities()
{
  // Calculate helicity angle cosines, given m12Sq, m13Sq and m23Sq.
  // The notation is confusing for the helicity angle cosines:
  // cij is helicity angle for the pair which is made from tracks i and j.
  // It is the angle between tracks i and k in the ij rest frame  
  // Make sure that setMassSqVars is run first.
  int zero(0), one(1), two(2);

  c12_ = cFromM(m12Sq_, m13Sq_, m12_, zero, one, two);
  p1_12_ = qi_; p3_12_ = qk_; // i, j = 12 (rest frame), k = 3
  c23_ = cFromM(m23Sq_, m12Sq_, m23_, one, two, zero);
  p2_23_ = qi_; p1_23_ = qk_; // i, j = 23 (rest frame), k = 1
  c13_ = cFromM(m13Sq_, m23Sq_, m13_, two, zero, one);
  p1_13_ = qi_; p2_13_ = qk_; // i, j = 31 (rest frame), k = 2

}

double ThreeBodyKinematics::cFromM(double mijSq, double mikSq, double mij, int i, int j, int k) 
{
  // Routine to calculate the cos(helicity) variables from the masses of the particles.
  // cij is helicity angle for the pair which is made from tracks i and j.
  // It is the angle between tracks i and k in the ij rest frame.
  double EiCmsij = (mijSq - mSq_[j] + mSq_[i])/(2.0*mij);
  double EkCmsij = (mParentSq_ - mijSq - mSq_[k])/(2.0*mij);

  if (EiCmsij < mass_[i]) {
    return 0.0;
  }
  if (EkCmsij < mass_[k]) {
    return 0.0;
  }

  // Find track i and k momenta in ij rest frame
  qi_ = this->pCalc(EiCmsij, mSq_[i]);
  qk_ = this->pCalc(EkCmsij, mSq_[k]);

  // Find ij helicity angle
  double result = -(mikSq - mSq_[i] - mSq_[k] - 2.0*EiCmsij*EkCmsij)/(2.0*qi_*qk_);

  if (result > 1.0) {
    result = 1.0;
  } else if (result < -1.0) {
    result = -1.0;
  }

  if (i == 1) {result *= -1.0;}

  return result;

}

double ThreeBodyKinematics::mFromC(double mijSq, double cij, double mij, int i, int j, int k) 
{
  // Returns the mass-squared for a pair of particles, i,j, given their
  // invariant mass (squared) and the helicity angle.
  // cij is helicity angle for the pair which is made from tracks i and j.
  // It is the angle between tracks i and k in the ij rest frame.

  double EiCmsij = (mijSq - mSq_[j] + mSq_[i])/(2.0*mij);
  double EkCmsij = (mParentSq_ - mijSq - mSq_[k])/(2.0*mij);

  if (fabs(EiCmsij - mass_[i]) > 1e-6 && EiCmsij < mass_[i]) {
    return 0.0;
  }
  if (fabs(EkCmsij - mass_[k]) > 1e-6 && EkCmsij < mass_[k]) {
    return 0.0;
  }

  // Find track i and k momenta in ij rest fram
  double qi = this->pCalc(EiCmsij, mSq_[i]);
  double qk = this->pCalc(EkCmsij, mSq_[k]);

  // Find mikSq
  double result = mSq_[i] + mSq_[k] + 2.0*EiCmsij*EkCmsij - 2.0*qi*qk*cij;

  if (result < mSqMin_[j]) {
    result = mSqMin_[j];
  }

  return result;

}

void ThreeBodyKinematics::genFlatPhaseSpace()
{
  // Routine to generate flat phase-space events. Used by the sigGen() function.
  // DP max kinematic boundaries in circumscribed box
  // See DP figure in PDG book.
  // m13max=mbrec-mass(2)
  // m13sqmax=m13max*m13max
  // m23max=mbrec-mass(1)
  // m23sqmax=m23max*m23max

  // Generate m13sq and m23sq flat within DP overall rectangular 
  // kinematic boundary

  do {
    m13Sq_ = mSqMin_[1] + mSqDiff_[1]*rand()/RAND_MAX;
    m23Sq_ = mSqMin_[0] + mSqDiff_[0]*rand()/RAND_MAX;
  } while( ! this->withinDPLimits() );

  this->updateKinematics( m13Sq_, m23Sq_ );
}

bool ThreeBodyKinematics::withinDPLimits() const
{
  return this->withinDPLimits(m13Sq_,m23Sq_);
}

bool ThreeBodyKinematics::withinDPLimits(double m13Sq, double m23Sq) const
{
  // Find out whether the point (m13Sq,m23Sq) is within the limits of the
  // Dalitz plot. The limits are specified by the invariant masses
  // of the parent (e.g. B) and its three daughters that were
  // defined in the constructor of this class. Here
  // m_13Sq = square of invariant mass of daughters 1 and 3 
  // m_23Sq = square of invariant mass of daughters 2 and 3.

  bool withinDP = false;

  // First check that m13Sq is within its absolute min and max
  if (!((m13Sq > mSqMin_[1]) && (m13Sq < mSqMax_[1]))) {
    return false;
  }

  // Now for the given value of m13Sq calculate the local min and max of m23Sq
  double m13 = sqrt(m13Sq);

  double e3Cms13 = (m13Sq - m1Sq_ + m3Sq_)/(2.0*m13);
  double p3Cms13 = this->pCalc(e3Cms13, m3Sq_);

  double e2Cms13 = (mParentSq_ - m13Sq - m2Sq_)/(2.0*m13);
  double p2Cms13 = this->pCalc(e2Cms13, m2Sq_);

  double term = 2.0*e2Cms13*e3Cms13 + m2Sq_ + m3Sq_;

  double m23SqLocMin = term - 2.0*p2Cms13*p3Cms13;
  double m23SqLocMax = term + 2.0*p2Cms13*p3Cms13;

  // Check whether the given value of m23Sq satisfies these bounds
  if (m23Sq > m23SqLocMin && m23Sq < m23SqLocMax) {    
    withinDP = true;
  }

  return withinDP;
}

double ThreeBodyKinematics::pCalc(double energy, double massSq) const
{
  // Routine to calculate the momentum of a particle, given its energy and 
  // invariant mass (squared).
  double arg = energy*energy - massSq;

  if (arg < 0.0) {
    arg = 0.0;
  }
  double pCalcVal = sqrt(arg);
  return pCalcVal;

}

void ThreeBodyKinematics::flipAndUpdateKinematics()
{
  // Flips the DP variables m13^2 <-> m23^2.
  // Used in the case of symmetrical Dalitz plots (i.e. when two of
  // the daughter tracks are the same type) within the Dynamics()
  // function.
  this->updateKinematics(m23Sq_, m13Sq_);

}

