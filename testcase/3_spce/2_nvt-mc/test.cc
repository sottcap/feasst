/**
 * FEASST - Free Energy and Advanced Sampling Simulation Toolkit
 * http://pages.nist.gov/feasst, National Institute of Standards and Technology
 * Harold W. Hatch, harold.hatch@nist.gov
 *
 * Permission to use this data/software is contingent upon your acceptance of
 * the terms of LICENSE.txt and upon your providing
 * appropriate acknowledgments of NIST's creation of the data/software.
 */

#include "feasst.h"

int main() {  // SPCE, SRSW_NVTMC
  auto space = feasst::makeSpace(
    {{"dimen", "3"},
     {"boxLength", "24.8586887"}});

  auto pair = feasst::makePairLJCoulEwald(space,
    {{"rCut", feasst::str(space->minl()/2.)},
     {"molTypeInForcefield", "data.spce"}});
  pair->initKSpace(5.6,   // alpha*L
                  38);   // k^2 < k2max cutoff

  // Read the pre-equilibrated configuration of 512 water molecules
  std::ostringstream ss;
  ss << space->install_dir() << "/testcase/3_spce/2_nvt-mc/test.xyz";
  std::ifstream file(ss.str().c_str());
  pair->readxyz(file);
  pair->initEnergy();

  // acceptance criteria
  const double temperature = 298;  // Kelvin
  auto criteria = feasst::makeCriteriaMetropolis(
    {{"beta", feasst::str(1./(temperature*feasst::idealGasConstant/1e3))},  // mol/KJ
     {"activ", "1."}});
  feasst::MC mc(pair, criteria);
  feasst::transformTrial(&mc, "translate", 0.1);
  mc.initLog("log", 1e4);
  mc.initMovie("movie", 1e4);
  mc.initRestart("tmp/rst", 1e4);
  mc.setNFreqTune(1e4);
  mc.runNumTrials(1e6);   // run equilibration

  // Run the production simulation
  mc.zeroStat();
  mc.runNumTrials(1e6);

  // Check average energy against Gerhard Hummer
  // https://doi.org/10.1063/1.476834
  const double
    peAv = mc.peAccumulator().average()/static_cast<double>(space->nMol()),
    peStd = mc.peAccumulator().blockStdev()/static_cast<double>(space->nMol()),
    pePublish = -46.,
    // pePublish = -46.82, # published value
    pePublishStd = 0.02;
  ASSERT(fabs(peAv - pePublish) < 2.576*(pePublishStd+peStd),  // 99% confidence
    "ERROR: The average potential energy(" << peAv << " +/- " << peStd
    << ") did not match the published value (" << pePublish << " +/- " << pePublishStd << ")");
}
