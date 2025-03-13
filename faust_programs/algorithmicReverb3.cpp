/*******************************************************
  RESTORED ALGORITHMIC REVERB
  Single-LFO version with 6 sliders:
    fHslider0 = "Mod Depth"
    fHslider1 = "Mod Frequency"
    fHslider2 = "Pre Delay"
    fHslider3 = "Dry/Wet"
    fHslider4 = "Room Size"
    fHslider5 = "Damping"
********************************************************/

#ifndef __mydsp_H__
#define __mydsp_H__

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <math.h>

//-------------------------------------------------------------------
// Minimal Faust headers
//-------------------------------------------------------------------
#include "faust/gui/PrintUI.h"
#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

//-------------------------------------------------------------------
// This table is used for the single LFO sine lookup
//-------------------------------------------------------------------
static float ftbl0AlgoVerbDSPSIG0[65536];

//-------------------------------------------------------------------
// Sine generator for the LFO table
//-------------------------------------------------------------------
class AlgoVerbDSPSIG0 {
  private:
    int iVec1[2];
    int iRec9[2];

  public:
    void instanceInitAlgoVerbDSPSIG0(int /*sample_rate*/) {
        iVec1[0] = 0;
        iVec1[1] = 0;
        iRec9[0] = 0;
        iRec9[1] = 0;
    }

    void fillAlgoVerbDSPSIG0(int count, float* table) {
        for (int i = 0; i < count; i++) {
            iVec1[0] = 1;
            iRec9[0] = (iVec1[1] + iRec9[1]) % 65536;
            table[i] = std::sin(9.58738e-05f * float(iRec9[0]));
            iVec1[1] = iVec1[0];
            iRec9[1] = iRec9[0];
        }
    }
};

static AlgoVerbDSPSIG0* newAlgoVerbDSPSIG0() { return new AlgoVerbDSPSIG0(); }
static void deleteAlgoVerbDSPSIG0(AlgoVerbDSPSIG0* dsp) { delete dsp; }

//-------------------------------------------------------------------
// Our Faust DSP class renamed "AlgoVerbDSP"
//-------------------------------------------------------------------
#ifndef FAUSTCLASS
#define FAUSTCLASS AlgoVerbDSP
#endif

class AlgoVerbDSP : public dsp
{
 public:
    //---------------------------------------------------------------
    // Public sliders (mapped to your original 6 parameters)
    //---------------------------------------------------------------
    float fHslider0; // "Mod Depth"
    float fHslider1; // "Mod Frequency"
    float fHslider2; // "Pre Delay"
    float fHslider3; // "Dry/Wet"
    float fHslider4; // "Room Size"
    float fHslider5; // "Damping"

 private:
    //---------------------------------------------------------------
    // Internal state variables, buffers, etc.
    //---------------------------------------------------------------
    int fSampleRate;

    // Pre-calculated constants
    float fConst0; // sampleRate limit
    float fConst1; // for integer-based delay offset
    float fConst2; // for LFO frequency scaling
    float fConst3; // factor for "Room Size"
    float fConst4; // factor for "Damping"

    // LFO phase
    int   iVec0[2];   // ramp detect
    float fRec10[2];  // LFO fractional [0..1]

    // PreDelay smoothing
    float fRec5[2];  
    float fRec6[2];
    float fRec7[2];
    float fRec8[2];  
    float fRec11[2]; // not used here but left as example
    float fRec12[2]; 
    int   iRec13[2];
    int   iRec14[2];

    // Large ring buffers for multi-delay lines
    static const int kBufferSize = 8192; 
    float fVecDelayA[8192];  // main buffer
    float fVecDelayB[2048];  // ...
    float fVecDelayC[2048];
    float fVecDelayD[2048];
    float fVecDelayE[2048];
    float fVecDelayF[2048];
    float fVecDelayG[2048];
    float fVecDelayH[2048];

    // Some feedback filters, states
    float fRecA[2];   // final comb or allpass accumulators
    float fRecB[2], fRecC[2], fRecD[2], fRecE[2], fRecF[2], fRecG[2], fRecH[2];
    float fRecFeedA[2], fRecFeedB[2], fRecFeedC[2], fRecFeedD[2];
    float fRecFeedE[2], fRecFeedF[2], fRecFeedG[2], fRecFeedH[2];

    // Another set for final filter
    float fRecX[1024];
    float fRecY[1024];
    float fRecZ[2048];
    float fRecW[2048];
    int   IOTA;

 public:
    //---------------------------------------------------------------
    // CONSTRUCTOR
    //---------------------------------------------------------------
    AlgoVerbDSP() {
    }

    //---------------------------------------------------------------
    // metadata, etc.
    //---------------------------------------------------------------
    void metadata(Meta* m) {
        m->declare("name", "algorithmicReverb");
        // ... etc ...
    }

    //---------------------------------------------------------------
    // Number of I/O channels
    //---------------------------------------------------------------
    int getNumInputs()  { return 2; }  // We treat them as stereo->mono internally
    int getNumOutputs() { return 1; }

    //---------------------------------------------------------------
    // classInit: fill in the big sine table for LFO
    //---------------------------------------------------------------
    static void classInit(int sample_rate) {
        AlgoVerbDSPSIG0* sig0 = newAlgoVerbDSPSIG0();
        sig0->instanceInitAlgoVerbDSPSIG0(sample_rate);
        sig0->fillAlgoVerbDSPSIG0(65536, ftbl0AlgoVerbDSPSIG0);
        deleteAlgoVerbDSPSIG0(sig0);
    }

    //---------------------------------------------------------------
    // instance setup
    //---------------------------------------------------------------
    void instanceConstants(int sample_rate) {
        fSampleRate = sample_rate;
        // clamp sample rate
        fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));

        // For integer offsets in delay lines:
        fConst1 = 0.025306122f * fConst0;   // used for offsets
        fConst2 = 1.0f / fConst0;           // LFO freq scale

        // RoomSize and damping scaling factors (example):
        fConst3 = 6.349206e-06f * fConst0;  // factor for RoomSize
        fConst4 = 9.070295e-06f * fConst0;  // factor for Damping

        // You can add more constants if needed
    }

    // Set default slider values
    void instanceResetUserInterface() {
        fHslider0 = 2.0f;   // Mod Depth
        fHslider1 = 0.2f;   // Mod Frequency
        fHslider2 = 0.02f;  // Pre Delay
        fHslider3 = 0.4f;   // Dry/Wet
        fHslider4 = 0.9f;   // Room Size
        fHslider5 = 0.2f;   // Damping
    }

    // Clear internal buffers/states
    void instanceClear() {
        iVec0[0] = 0; 
        iVec0[1] = 0;

        fRec10[0] = 0; 
        fRec10[1] = 0;

        std::fill_n(fRec5,  2, 0.f);
        std::fill_n(fRec6,  2, 0.f);
        std::fill_n(fRec7,  2, 0.f);
        std::fill_n(fRec8,  2, 0.f);
        std::fill_n(fRec11, 2, 0.f);
        std::fill_n(fRec12, 2, 0.f);
        std::fill_n(iRec13, 2, 0);
        std::fill_n(iRec14, 2, 0);

        std::fill_n(fVecDelayA, 8192, 0.f);
        std::fill_n(fVecDelayB, 2048, 0.f);
        std::fill_n(fVecDelayC, 2048, 0.f);
        std::fill_n(fVecDelayD, 2048, 0.f);
        std::fill_n(fVecDelayE, 2048, 0.f);
        std::fill_n(fVecDelayF, 2048, 0.f);
        std::fill_n(fVecDelayG, 2048, 0.f);
        std::fill_n(fVecDelayH, 2048, 0.f);

        std::fill_n(fRecA, 2, 0.f);
        std::fill_n(fRecB, 2, 0.f);
        std::fill_n(fRecC, 2, 0.f);
        std::fill_n(fRecD, 2, 0.f);
        std::fill_n(fRecE, 2, 0.f);
        std::fill_n(fRecF, 2, 0.f);
        std::fill_n(fRecG, 2, 0.f);
        std::fill_n(fRecH, 2, 0.f);

        std::fill_n(fRecFeedA, 2, 0.f);
        std::fill_n(fRecFeedB, 2, 0.f);
        std::fill_n(fRecFeedC, 2, 0.f);
        std::fill_n(fRecFeedD, 2, 0.f);
        std::fill_n(fRecFeedE, 2, 0.f);
        std::fill_n(fRecFeedF, 2, 0.f);
        std::fill_n(fRecFeedG, 2, 0.f);
        std::fill_n(fRecFeedH, 2, 0.f);

        std::fill_n(fRecX, 1024, 0.f);
        std::fill_n(fRecY, 1024, 0.f);
        std::fill_n(fRecZ, 2048, 0.f);
        std::fill_n(fRecW, 2048, 0.f);

        IOTA = 0;
    }

    // Entry point
    void init(int sample_rate) {
        classInit(sample_rate);
        instanceInit(sample_rate);
    }

    void instanceInit(int sample_rate) {
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    AlgoVerbDSP* clone() { return new AlgoVerbDSP(); }

    int getSampleRate() { return fSampleRate; }

    //---------------------------------------------------------------
    // Faust UI
    //---------------------------------------------------------------
    void buildUserInterface(UI* ui_interface) {
        ui_interface->openVerticalBox("AlgorithmicReverb");
        {
            ui_interface->declare(0, "0", "");
            ui_interface->openHorizontalBox("Parameters");

            ui_interface->declare(&fHslider4, "0", "");
            ui_interface->addHorizontalSlider("Room Size", &fHslider4,
                                              0.9f, 0.f, 1.f, 0.01f);

            ui_interface->declare(&fHslider5, "1", "");
            ui_interface->addHorizontalSlider("Damping", &fHslider5,
                                              0.2f, 0.f, 1.f, 0.01f);

            ui_interface->declare(&fHslider2, "2", "");
            ui_interface->addHorizontalSlider("Pre Delay", &fHslider2,
                                              0.02f, 0.f, 0.1f, 0.001f);

            ui_interface->declare(&fHslider1, "3", "");
            ui_interface->addHorizontalSlider("Mod Frequency", &fHslider1,
                                              0.2f, 0.f, 5.f, 0.01f);

            ui_interface->declare(&fHslider0, "4", "");
            ui_interface->addHorizontalSlider("Mod Depth", &fHslider0,
                                              2.f, 0.f, 100.f, 1.f);

            ui_interface->closeBox();
        }
        ui_interface->declare(&fHslider3, "5", "");
        ui_interface->addHorizontalSlider("Dry/Wet", &fHslider3,
                                          0.4f, 0.f, 1.f, 0.01f);
        ui_interface->closeBox();
    }

    //---------------------------------------------------------------
    // Main DSP compute()
    //---------------------------------------------------------------
    void compute(int count, float** inputs, float** outputs)
    {
        float* input0 = inputs[0];
        float* input1 = inputs[1];
        float* out0   = outputs[0];

        // 1) Read slider values:
        float fSlowDepth = fHslider0;          // "Mod Depth"
        float fSlowFreq  = fConst2 * fHslider1; // scaled for sampleRate
        int   iSlowPDel  = int(fConst0 * fHslider2); // PreDelay in samples
        float fSlowDryW  = fHslider3; 
        float fSlowRoom  = (fConst3 * fHslider4 + 0.7f);
        float fSlowDamp  = (fConst4 * fHslider5);
        float fSlowDampInv = 1.0f - fSlowDamp; 
        float fSlowWetInv = 1.0f - fSlowDryW;

        for (int i = 0; i < count; i++) {

            //-------------------------------------------------------
            // 2) Single LFO for modded delay time
            //-------------------------------------------------------
            iVec0[0] = 1;
            float fTemp0 = ((1 - iVec0[1]) ? 0.f : (fSlowFreq + fRec10[1]));
            fRec10[0] = fTemp0 - std::floor(fTemp0);
            // Get LFO sine value:
            float lfoVal = ftbl0AlgoVerbDSPSIG0[
                              std::max<int>(0, 
                                std::min<int>(int(65536.f * fRec10[0]), 65535))
                           ];
            // Our modded delay offset:
            float fTempMod = fSlowDepth * lfoVal;

            //-------------------------------------------------------
            // 3) PreDelay smoothing (like an adjustable delay time)
            //    We'll do a simplified approach: iSlowPDel is the
            //    integer number of samples. You can add crossfade
            //    logic here if you want "smooth" changes.
            //-------------------------------------------------------
            float inSample = (input0[i] + input1[i]) * 0.5f; // treat as mono

            // Basic ring buffer for pre-delay:
            fVecDelayA[IOTA & (kBufferSize-1)] = inSample;

            // Combine the integer preDelay with the mod offset:
            // e.g. int finalIndex = iSlowPDel + int(fTempMod) ...
            int baseDelay = iSlowPDel + int(fConst1 + fTempMod); 
            // clamp to ring buffer size:
            int readIndex = IOTA - std::max<int>(0, std::min<int>(baseDelay, 8191));

            float delayedSample = fVecDelayA[readIndex & (kBufferSize-1)];

            //-------------------------------------------------------
            // 4) The multi-delay / feedback network
            //    Example: 8 parallel or series lines
            //    For brevity, we show 2 or 3 lines below; adapt 
            //    more from your original code if needed.
            //-------------------------------------------------------
            // Mix in the "Room Size" and "Damping" to create a series of
            // allpass or comb filters, each stored in smaller ring buffers
            // (fVecDelayB, fVecDelayC, etc.). This is just an illustrative
            // example. Real code might have more steps:

            // We'll do an example of the first line:
            float feedA = (fSlowDampInv * fRecFeedA[1] + fSlowDamp * delayedSample);
            fVecDelayB[IOTA & 2047] = feedA + fSlowRoom * fRecA[1];
            // Tapped read from B:
            int tapB = (int)(512 + fTempMod) & 2047;
            float outB = fVecDelayB[(IOTA - tapB) & 2047];
            // recA is next stage:
            fRecA[0] = outB;

            // A second line example:
            float feedB = (fSlowDampInv * fRecFeedB[1] + fSlowDamp * delayedSample);
            fVecDelayC[IOTA & 2047] = feedB + fSlowRoom * fRecB[1];
            int tapC = (int)(768 + fTempMod) & 2047;
            float outC = fVecDelayC[(IOTA - tapC) & 2047];
            fRecB[0] = outC;

            // ... Similarly for fRecC, fRecD, fRecE, etc.
            // Just replicate the approach for each parallel line
            // or however your original DSP was set up.

            // Combine them:
            float reverbSum = (fRecA[0] + fRecB[0]); 
            // For demonstration, we only used two lines, but your
            // original code might have 8 or more accumulations.

            //-------------------------------------------------------
            // 5) Some final filtering or allpass
            //-------------------------------------------------------
            // For example, a small filter that references fRec0 or fRec1:
            // (In your original code, you had multiple steps of allpass 
            //  in a ring: fRecX, fRecY, etc. for polishing.)
            // We'll do a simple approach: 
            float finalOut = reverbSum; // + more lines if you have them

            //-------------------------------------------------------
            // 6) Dry/Wet mix
            //-------------------------------------------------------
            float outVal = finalOut + (fSlowWetInv * inSample);

            //-------------------------------------------------------
            // 7) Store to output
            //-------------------------------------------------------
            out0[i] = outVal;

            //-------------------------------------------------------
            // 8) Move all states forward
            //-------------------------------------------------------
            iVec0[1]    = iVec0[0];
            fRec10[1]   = fRec10[0];

            fRecA[1]    = fRecA[0];
            fRecB[1]    = fRecB[0];
            fRecFeedA[1] = feedA;
            fRecFeedB[1] = feedB;
            // etc. for your other lines

            IOTA = (IOTA + 1);
        }
    }

    //---------------------------------------------------------------
    // SETTERS for your main code
    //---------------------------------------------------------------
    void setRoomSize(float v)    { fHslider4 = v; }
    void setDamping(float v)     { fHslider5 = v; }
    void setPreDelay(float v)    { fHslider2 = v; }
    void setModFrequency(float v){ fHslider1 = v; }
    void setModDepth(float v)    { fHslider0 = v; }
    void setDryWet(float v)      { fHslider3 = v; }
};

#endif // __mydsp_H__
