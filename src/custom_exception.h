/*
 * FEASST - Free Energy and Advanced Sampling Simulation Toolkit
 * http://pages.nist.gov/feasst, National Institute of Standards and Technology
 * Harold W. Hatch, harold.hatch@nist.gov
 *
 * Permission to use this data/software is contingent upon your acceptance of
 * the terms of LICENSE.txt and upon your providing
 * appropriate acknowledgments of NIST's creation of the data/software.
 *
 * Authors: Nathan Mahynksi wrote this class
 *          Harold Hatch editted
 */

#ifndef CUSTOM_EXCEPTION_H_
#define CUSTOM_EXCEPTION_H_

#include <exception>
#include <string>
#include <sstream>

namespace feasst {

/**
 * Customize the way that exceptions are handled and thrown.
 */
class CustomException : public std::exception {
 public:
  /// Instantiate an exeption with a user-defined error message.
  CustomException(std::stringstream& m);

  /// Return the user's message
  const char* what() const throw() { return msg_.c_str(); }

 protected:
  std::string msg_;

  /// Add additional information to the message, such as the thread number.
  void catMessage_();
};

}  // namespace feasst

#endif  // CUSTOM_EXCEPTION_H_
