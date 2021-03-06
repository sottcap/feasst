/*
 * FEASST - Free Energy and Advanced Sampling Simulation Toolkit
 * http://pages.nist.gov/feasst, National Institute of Standards and Technology
 * Harold W. Hatch, harold.hatch@nist.gov
 *
 * Permission to use this data/software is contingent upon your acceptance of
 * the terms of LICENSE.txt and upon your providing
 * appropriate acknowledgments of NIST's creation of the data/software.
 */

#include "./pair_ideal.h"

namespace feasst {

PairIdeal::PairIdeal(Space* space, const argtype &args)
  : Pair(space, args) {
  defaultConstruction_();
  argparse_.initArgs(className_, args);
  argparse_.checkAllArgsUsed();
}

PairIdeal::PairIdeal(Space* space, const char* fileName)
  : Pair(space, fileName) {
  defaultConstruction_();
}

void PairIdeal::defaultConstruction_() {
  className_.assign("PairIdeal");
}

void PairIdeal::pairSiteSite_(const int &iSiteType, const int &jSiteType,
  double * energy, double * force, int * neighbor, const double &dx,
  const double &dy, const double &dz) {
  *neighbor = 1;
}

PairIdeal* PairIdeal::clone(Space* space) const {
  PairIdeal* p = new PairIdeal(*this);
  p->reconstruct(space);
  return p;
}

shared_ptr<PairIdeal> makePairIdeal(Space* space, const argtype &args) {
  return make_shared<PairIdeal>(space, args);
}

}  // namespace feasst

