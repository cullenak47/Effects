// ==================================================================================
// Copyright (c) 2017 HiFi-LoFi
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished
// to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ==================================================================================

#ifndef _FFTCONVOLVER_TWOSTAGEFFTCONVOLVERPARALLEL_H
#define _FFTCONVOLVER_TWOSTAGEFFTCONVOLVERPARALLEL_H

#include "/home/Cullen/FYP/Effects/Effects/include/FFTConvolver.h"
#include "/home/Cullen/FYP/Effects/Effects/include/Utilities.h"
#include <thread>  // Added for std::thread

namespace fftconvolver
{ 

/**
* @class TwoStageFFTConvolverParallel
* @brief FFT convolver using two different block sizes with parallel tail processing.
*
* This class is similar to TwoStageFFTConvolver but has been modified to process the tail
* convolution in parallel. The tail block is split into two halves that are processed concurrently.
*
* The convolver consists of:
* - A head convolver for the beginning of the impulse response.
* - A tail convolver for the remaining (usually longer) portion of the impulse response.
*
* The virtual methods startBackgroundProcessing()/waitForBackgroundProcessing() have been
* overridden to spawn and manage a background thread that further divides the tail processing
* into two parallel tasks.
*
* All time-critical operations (the head convolution) are performed on the real-time thread,
* while the tail convolution is offloaded to background threads.
*/
class TwoStageFFTConvolverParallel
{  
public:
  TwoStageFFTConvolverParallel();  
  virtual ~TwoStageFFTConvolverParallel();
  
  /**
  * @brief Initializes the convolver.
  * @param headBlockSize The head block size.
  * @param tailBlockSize The tail block size.
  * @param ir The impulse response.
  * @param irLen Length of the impulse response in samples.
  * @return true if initialization was successful; false otherwise.
  */
  bool init(size_t headBlockSize, size_t tailBlockSize, const Sample* ir, size_t irLen);

  /**
  * @brief Convolves the given input samples and outputs the result immediately.
  * @param input The input samples.
  * @param output The convolution result.
  * @param len Number of input/output samples.
  */
  void process(const Sample* input, Sample* output, size_t len);

  /**
  * @brief Resets the convolver and discards the set impulse response.
  */
  void reset();
  
protected:
  /**
  * @brief Called when background processing work is available.
  *
  * The default implementation spawns a background thread that, in turn, spawns two worker
  * threads to process the tail block concurrently.
  */
  virtual void startBackgroundProcessing();

  /**
  * @brief Called to ensure that any background processing has completed.
  *
  * This method should block until the background processing thread finishes.
  */
  virtual void waitForBackgroundProcessing();

  /**
  * @brief Actually performs the background processing work.
  *
  * In this parallel version, the tail block is split into two halves and processed concurrently.
  */
  void doBackgroundProcessing();

private:
  size_t _headBlockSize;
  size_t _tailBlockSize;
  FFTConvolver _headConvolver;
  FFTConvolver _tailConvolver0;
  SampleBuffer _tailOutput0;
  SampleBuffer _tailPrecalculated0;
  FFTConvolver _tailConvolver;
  SampleBuffer _tailOutput;
  SampleBuffer _tailPrecalculated;
  SampleBuffer _tailInput;
  size_t _tailInputFill;
  size_t _precalculatedPos;
  SampleBuffer _backgroundProcessingInput;

  // Added to manage the background processing thread.
  std::thread _backgroundThread;

  // Prevent uncontrolled usage
  TwoStageFFTConvolverParallel(const TwoStageFFTConvolverParallel&);
  TwoStageFFTConvolverParallel& operator=(const TwoStageFFTConvolverParallel&);
};
  
} // End of namespace fftconvolver

#endif // _FFTCONVOLVER_TWOSTAGEFFTCONVOLVERPARALLEL_H
