///////////////////////////////////////////////////////////////
/// @class FilterTest
/// @ingroup DSP
///
/// @brief Test class for the Filter base class. We will use
///        a three point moving average filter to test the
///        filter base class. Test data and expected filter
///        output data for verification was obtained by
///        using the filter_designer.m Matlab script.
///        The image below shows a plot of the true sinusoid
///        signal, sin(x), a noisy version, and the three
///        point moving average filtered version. This is
///        the data that was used to verify the proper output
///        of the Filter class's filter function.
///
/// @image html avg_filter_verif.png "Filter Verification"
///
/// @author
///         $Author: Mike Moore $
///
/// Contact: mickety.mike@gmail.com
///
/// Created on: Sat May 31 2014
///////////////////////////////////////////////////////////////
#include "../Filter.hh"
#include "gtest/gtest.h"

class FilterTest : public testing::Test {
 protected:

  ////////////////////////////////////////////////////////////
  /// @brief Filter test setup function
  ////////////////////////////////////////////////////////////
  virtual void SetUp(void) {
	 buildTestSignals();
	 buildMovingAverage();
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
  /// @brief Test helper function to setup our filter
  ///        weights. This configuration is for a three point
  ///        moving average filter.
  ////////////////////////////////////////////////////////////
  virtual void buildMovingAverage(void){
	 numInputWeights = 3;
	 numOutputWeights = 1;
     inputWeights[0] = 0.33333;
     inputWeights[1] = 0.33333;
     inputWeights[2] = 0.33333;
     outputWeights[0]   = 1;
  }
  ////////////////////////////////////////////////////////////
  /// @brief Filter test tear down function
  ////////////////////////////////////////////////////////////
  virtual void TearDown(void) {
  }
  ////////////////////////////////////////////////////////////
  /// @brief Declare the testArticle
  ////////////////////////////////////////////////////////////
  Filter testArticle;
  ////////////////////////////////////////////////////////////
  /// @brief Length of the test signal.
  ////////////////////////////////////////////////////////////
  static const unsigned int TEST_SIGNAL_LENGTH = 10;
  ////////////////////////////////////////////////////////////
  /// @brief This is our sample test signal. It's a discrete
  ///        version of a sin wave:
  ///        sin(x) where x = [0, 1, 2, ... 9]
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
  ////////////////////////////////////////////////////////////
  /// @brief Number of input weights in this test. Three
  ///        for a three point moving average filter.
  ////////////////////////////////////////////////////////////
  unsigned int numInputWeights;
  ////////////////////////////////////////////////////////////
  /// @brief Define the input weights for the test
  ////////////////////////////////////////////////////////////
  float inputWeights[3];
  ////////////////////////////////////////////////////////////
  /// @brief Number of output weights in this test. One
  ///        for a three point moving average filter.
  ////////////////////////////////////////////////////////////
  unsigned int numOutputWeights;
  ////////////////////////////////////////////////////////////
  /// @brief Define the output weights for the test
  ////////////////////////////////////////////////////////////
  float outputWeights[3];
};

////////////////////////////////////////////////////////////
/// @brief Unit test for the Filter Default Constructor
////////////////////////////////////////////////////////////
TEST_F(FilterTest, Constructor) {
  Filter tFilter = Filter(numInputWeights, inputWeights,
		                 numOutputWeights, outputWeights);
  for (unsigned int i=0; i<numInputWeights; i++){
    ASSERT_FLOAT_EQ(inputWeights[i], tFilter.GetInputWeights()[i]);
  }
  for (unsigned int i=0; i<numOutputWeights; i++){
    ASSERT_FLOAT_EQ(outputWeights[i], tFilter.GetOutputWeights()[i]);
  }
}

////////////////////////////////////////////////////////////
/// @brief Unit test for the Filter GetCurrentOutputValue
////////////////////////////////////////////////////////////
TEST_F(FilterTest, FilterFunctionTest) {
  Filter tFilter = Filter(numInputWeights, inputWeights,
		                 numOutputWeights, outputWeights);
  // Initialize it with the moving average filter data
  for (unsigned int i=0; i<TEST_SIGNAL_LENGTH; i++){
	float filterOutput = tFilter.filter(sample_signal[i]);
	ASSERT_NEAR(expected_filtered[i], filterOutput, error_tolerance);
  }
}
