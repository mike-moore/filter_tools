///////////////////////////////////////////////////////////////
/// @defgroup DSP Digital Signal Processing Module
///  The DSP module will contain classes for doing
///  digital signal processing. The first class to
///  be implemented will be the filter base class.
///  We will then derive  two filters from the base
///  class to cover discrete FIR and IIR digital
///  filters.
///
/// @author
///         $Author: Mike Moore $
///
/// Contact: mickety.mike@gmail.com
///
/// Created on: Sat May 31 2014
///
///////////////////////////////////////////////////////////////
#ifndef FILTER_HH
#define FILTER_HH

/// @note This is the maximum allowable size for any filter
///       built with this class. It is expected that twenty
///       will be more than enough for our application.
#define MAX_FILTER_SIZE 20

///////////////////////////////////////////////////////////////
/// @class Filter
/// @ingroup DSP
/// @brief Base class for a generic digital filter
///        implementation. The implementation relies on the
///        following discrete equation for the digital output
///        signal y[n] as a function of x[n]: \par
///
/// <CENTER>
///   \f$ a[0]*y[n] = b[0]x[n]+b[1]x[n-1]+...+b[N]x[n-B+1]
///   -a[1]y[n-1]-...-a[N]y[n-N+1] \f$
/// </CENTER>
///
/// The class allows you to set the a and b weights in
/// order to construct any digital filter. Here is an example
/// of its use to replicate a three point moving average
/// filter.
///
/// @image html avg_filter_verif.png "Moving Average Filter"
///////////////////////////////////////////////////////////////
class Filter {

 public:
  //////////////////////////////////////////////////////////
  /// @brief This constructor will construct the filter
  ///        with all the necessary parameters to build a
  ///        custom filter.
  ////////////////////////////////////////////////////////////
  Filter(float numInWeights, float* inWeights,
		  float numOutWeights, float* outWeights);
  //////////////////////////////////////////////////////////
  /// @brief The default c'tor constructs the Filter base
  ///        class.
  ////////////////////////////////////////////////////////////
  Filter();
  //////////////////////////////////////////////////////////
  /// @brief The default d'tor destructs the Filter base
  ///        class.
  ////////////////////////////////////////////////////////////
  ~Filter();
  ////////////////////////////////////////////////////////////
  /// @brief Main filter routine. This is a virtual function
  ///        and it is expected that filters which derive
  ///        from this base class will implement their own
  ///        version of this routine.
  /// @param inputValue input value.
  /// @return Output from the filter
  ////////////////////////////////////////////////////////////
  virtual float filter(float inputValue);
  ////////////////////////////////////////////////////////////
  /// @brief An accessor function to get the current input
  ///        buffer of the filter.
  /// @return The current input buffer of the filter.
  ////////////////////////////////////////////////////////////
  inline float* GetCurrentInputBuffer(void){
	                              return _inputBuffer; }
  ////////////////////////////////////////////////////////////
  /// @brief An accessor function to get the current output
  ///        buffer of the filter.
  /// @return The current output buffer of the filter.
  ////////////////////////////////////////////////////////////
  inline float* GetCurrentOutputBuffer(void){
	                              return _outputBuffer; }
  ////////////////////////////////////////////////////////////
  /// @brief An accessor function to get the filter's input
  ///        weights.
  /// @return The filters input weights
  ////////////////////////////////////////////////////////////
  inline float* GetInputWeights(void){
	                              return _inputWeights; }
  ////////////////////////////////////////////////////////////
  /// @brief An accessor function to get the filter's output
  ///        weights.
  /// @return The filters output weights
  inline float* GetOutputWeights(void){
	                              return _outputWeights; }

 protected:
  ////////////////////////////////////////////////////////////
  /// @brief Initializes the input and output buffers of the
  ///        filter to 0.0;
  /// @param buff      -- The input or output buffer it initialize.
  /// @param buff_size -- Size of the buffer
  ////////////////////////////////////////////////////////////
  void initBuffer(float* buff, unsigned int buff_size);
  ////////////////////////////////////////////////////////////
  /// @brief Buffer holding the input signal values.
  ////////////////////////////////////////////////////////////
  float _inputBuffer[MAX_FILTER_SIZE];
  ////////////////////////////////////////////////////////////
  /// @brief Buffer holding the output signal values.
  ////////////////////////////////////////////////////////////
  float _outputBuffer[MAX_FILTER_SIZE];
  ////////////////////////////////////////////////////////////
  /// @brief The number of input weights.
  ////////////////////////////////////////////////////////////
  unsigned int _numInWeights;
  ////////////////////////////////////////////////////////////
  /// @brief Weights to be applied to the input signal and
  ///        delayed values of the input signal in order to
  ///        generate the output signal.
  ////////////////////////////////////////////////////////////
  float _inputWeights[MAX_FILTER_SIZE];
  ////////////////////////////////////////////////////////////
  /// @brief The number of output weights.
  ////////////////////////////////////////////////////////////
  unsigned int _numOutWeights;
  ////////////////////////////////////////////////////////////
  /// @brief Weights to be applied to the filter output signal
  ///        and delayed values of the output signal in order
  ///        to generate the next filter output.
  ////////////////////////////////////////////////////////////
  float _outputWeights[MAX_FILTER_SIZE];


};

#endif  // FILTER_HH
