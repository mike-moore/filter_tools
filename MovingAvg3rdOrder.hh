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
#ifndef MOVING_AVG_3RD_ORDER_HH
#define MOVING_AVG_3RD_ORDER_HH

#include "Filter.hh"

///////////////////////////////////////////////////////////////
/// @class MovingAvg3rdOrder class defines a three point
///        moving average filter
/// @ingroup DSP
/// @brief Three point moving average digital filter.
///////////////////////////////////////////////////////////////
class MovingAvg3rdOrder : public Filter {

 public:
  //////////////////////////////////////////////////////////
  /// @brief The default c'tor constructs the
  ///        MovingAvg3rdOrder class
  ////////////////////////////////////////////////////////////
  MovingAvg3rdOrder();
  //////////////////////////////////////////////////////////
  /// @brief The default d'tor destructs the
  ///        MovingAvg3rdOrder class
  ////////////////////////////////////////////////////////////
  ~MovingAvg3rdOrder();

};

#endif  // MOVING_AVG_3RD_ORDER_HH
