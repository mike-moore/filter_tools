#include "MovingAvg3rdOrder.hh"

//////////////////////////////////////////////////////////
/// @brief The c'tor constructs the filter weights
///        necessary for a three point moving average.
////////////////////////////////////////////////////////////
MovingAvg3rdOrder::MovingAvg3rdOrder()
{
  _numInWeights = 3;
  _numOutWeights = 1;
  _inputWeights[0] = 0.33333;
  _inputWeights[1] = 0.33333;
  _inputWeights[2] = 0.33333;
  _outputWeights[0]   = 1;
}

////////////////////////////////////////////////////////////
/// @brief Default  d'tor
////////////////////////////////////////////////////////////
MovingAvg3rdOrder::~MovingAvg3rdOrder() {

}
