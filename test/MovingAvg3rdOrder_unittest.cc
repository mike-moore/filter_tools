///////////////////////////////////////////////////////////////
/// @class MovingAvg3rdOrderTest
/// @ingroup DSP
///
/// @brief Test class for the Three Point Moving Average
////       Filter. We will use
///
/// @author
///         $Author: Mike Moore $
///
/// Contact: mickety.mike@gmail.com
///
/// Created on: Sat May 31 2014
///////////////////////////////////////////////////////////////
#include "../MovingAvg3rdOrder.hh"
#include "gtest/gtest.h"

class MovingAvg3rdOrderTest : public testing::Test {
 protected:

  ////////////////////////////////////////////////////////////
  /// @brief Moving Avg Third Order test setup function
  ////////////////////////////////////////////////////////////
  virtual void SetUp(void) {
	 buildTestSignals();
     error_tolerance = 0.0001;
  }
  ////////////////////////////////////////////////////////////
  /// @brief Test helper function to setup our test signals
  ///        used for the remainder of the test.
  ////////////////////////////////////////////////////////////
  virtual void buildTestSignals(void){
	 sample_signal[0] =  0.0376; sample_signal[1] = 0.1914;
	 sample_signal[2] = -0.0321; sample_signal[3] = 0.2486;
	 sample_signal[4] =  0.2722; sample_signal[5] = 0.2189;
	 sample_signal[6] =  0.3395; sample_signal[7] = 0.4517;
	 sample_signal[8] =  0.7344; sample_signal[9] = 0.7320;
	 expected_filtered[0] = 0.0125; expected_filtered[1] = 0.0763;
	 expected_filtered[2] = 0.0656; expected_filtered[3] = 0.1359;
	 expected_filtered[4] = 0.1629; expected_filtered[5] = 0.2466;
	 expected_filtered[6] = 0.2769; expected_filtered[7] = 0.3367;
	 expected_filtered[8] = 0.5085; expected_filtered[9] = 0.6394;
  }

  ////////////////////////////////////////////////////////////
  /// @brief Test tear down function
  ////////////////////////////////////////////////////////////
  virtual void TearDown(void) {
  }

  ////////////////////////////////////////////////////////////
  /// @brief Length of the test signal.
  ////////////////////////////////////////////////////////////
  static const unsigned int TEST_SIGNAL_LENGTH = 10;
  ////////////////////////////////////////////////////////////
  /// @brief This is our sample test signal. It's a discrete
  ///        version of a sin wave:
  ///        sin(x)
  ////////////////////////////////////////////////////////////
  float sample_signal[TEST_SIGNAL_LENGTH];
  ////////////////////////////////////////////////////////////
  /// @brief This is the expected value after putting it
  ///        through a simple 3 point moving average filter.
  ///        Refer to matlab code filter_design.m to see
  ///        how these expected values were generated.
  ////////////////////////////////////////////////////////////
  float expected_filtered[TEST_SIGNAL_LENGTH];
  ////////////////////////////////////////////////////////////
  /// @brief This defines the error tolerance for this filter
  ///        test. As long as the expected filtered values
  ///        agree with the output filtered values to within
  ///        this tolerance (set in test setUp routine), we
  ///        pass the filter test.
  ////////////////////////////////////////////////////////////
  float error_tolerance;

};

////////////////////////////////////////////////////////////
/// @brief Unit test for the Filter Default Constructor
////////////////////////////////////////////////////////////
TEST_F(MovingAvg3rdOrderTest, DefaultConstructor) {
  MovingAvg3rdOrder avgFilter;
  for (unsigned int i=0; i<TEST_SIGNAL_LENGTH; i++){
	float filterOutput = avgFilter.filter(sample_signal[i]);
	ASSERT_NEAR(expected_filtered[i], filterOutput, error_tolerance);
  }
}
