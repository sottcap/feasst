/*
 * FEASST - Free Energy and Advanced Sampling Simulation Toolkit
 * http://pages.nist.gov/feasst, National Institute of Standards and Technology
 * Harold W. Hatch, harold.hatch@nist.gov
 *
 * Permission to use this data/software is contingent upon your acceptance of
 * the terms of LICENSE.txt and upon your providing
 * appropriate acknowledgments of NIST's creation of the data/software.
 */

#ifndef PAIR_SQUAREWELL_H_
#define PAIR_SQUAREWELL_H_

#include <memory>
#include <vector>
#include "./pair.h"

namespace feasst {

/**
 * Square well interactions.
 * The hard distance is determined by sigma,
 * the square well distance is determined by rCut,
 * and the depth of the well is epsilon.
 */
class PairSquareWell : public Pair {
 public:
  /// Constructor
  PairSquareWell(Space* space, const argtype &args = argtype());

  /// Initialize hard sphere interactions
  /// between particle types itype and jtype.
  void initHardSphere(const int itype, const int jtype);

  // Construct from restart file
  PairSquareWell(Space* space, const char* fileName);
  virtual ~PairSquareWell() {}
  virtual PairSquareWell* clone(Space* space) const;

 protected:
  // See comments of derived class from Pair
  void pairSiteSite_(const int &iSiteType, const int &jSiteType,
    double * energy, double * force, int * neighbor, const double &dx,
    const double &dy, const double &dz);

  // defaults in constructor
  void defaultConstruction_();
};

/// Factory method
shared_ptr<PairSquareWell> makePairSquareWell(Space* space,
  const argtype &args = argtype());

}  // namespace feasst

#endif  // PAIR_SQUAREWELL_H_

