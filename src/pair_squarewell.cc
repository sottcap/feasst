/*
 * FEASST - Free Energy and Advanced Sampling Simulation Toolkit
 * http://pages.nist.gov/feasst, National Institute of Standards and Technology
 * Harold W. Hatch, harold.hatch@nist.gov
 *
 * Permission to use this data/software is contingent upon your acceptance of
 * the terms of LICENSE.txt and upon your providing
 * appropriate acknowledgments of NIST's creation of the data/software.
 */

#include "./pair_squarewell.h"

namespace feasst {

PairSquareWell::PairSquareWell(Space* space, const argtype &args)
  : Pair(space, args) {
  defaultConstruction_();
  argparse_.initArgs(className_, args);
  argparse_.checkAllArgsUsed();
}

PairSquareWell::PairSquareWell(Space* space, const char* fileName)
  : Pair(space, fileName) {
  defaultConstruction_();
}

void PairSquareWell::defaultConstruction_() {
  className_.assign("PairSquareWell");
}

void PairSquareWell::initHardSphere(const int itype, const int jtype) {
  rCutijset(itype, jtype, sigij_[itype][jtype]);
}

void PairSquareWell::pairSiteSite_(const int &iSiteType, const int &jSiteType,
  double * energy, double * force, int * neighbor, const double &dx,
  const double &dy, const double &dz) {
  const double r2 = dx*dx + dy*dy + dz*dz;
  const double sigij = sigij_[iSiteType][jSiteType];
  if (r2 < sigij*sigij) {
    *energy = NUM_INF;
  } else {
    *energy = -epsij_[iSiteType][jSiteType];
  }
  *neighbor = 1;
}

PairSquareWell* PairSquareWell::clone(Space* space) const {
  PairSquareWell* p = new PairSquareWell(*this);
  p->reconstruct(space);
  return p;
}

shared_ptr<PairSquareWell> makePairSquareWell(Space* space,
  const argtype &args) {
  return make_shared<PairSquareWell>(space, args);
}

}  // namespace feasst

