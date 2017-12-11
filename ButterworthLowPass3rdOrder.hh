///////////////////////////////////////////////////////////////
/// @ingroup This class defines a three point moving average
///          filter. It derives from the generic digital
///          Filter base class.
///
/// @author
///         $Author: Mike Moore $
///
/// Contact: mickety.mike@gmail.com
///
/// Created on: Sat May 31 2014
///
///////////////////////////////////////////////////////////////
#ifndef BUTTERWORTH_LOW_PASS_3RD_ORDER_HH
#define BUTTERWORTH_LOW_PASS_3RD_ORDER_HH

#include "Filter.hh"

///////////////////////////////////////////////////////////////
/// @class ButterworthLowPass3rdOrder class defines a three point
///        moving average filter
/// @ingroup DSP
/// @brief Three point moving average digital filter.
///////////////////////////////////////////////////////////////
class ButterworthLowPass3rdOrder : public Filter {

 public:
  //////////////////////////////////////////////////////////
  /// @brief The default c'tor constructs the
  ///        ButterworthLowPass3rdOrder class
  ////////////////////////////////////////////////////////////
  ButterworthLowPass3rdOrder();
  //////////////////////////////////////////////////////////
  /// @brief The default d'tor destructs the
  ///        ButterworthLowPass3rdOrder class
  ////////////////////////////////////////////////////////////
  ~ButterworthLowPass3rdOrder();

};

#endif  // BUTTERWORTH_LOW_PASS_3RD_ORDER_HH
