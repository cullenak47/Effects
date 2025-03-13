/****************************************************
   algorithmicReverb.cpp (modified for integration)
****************************************************/

#ifndef __ALGO_REVERB_DSP__
#define __ALGO_REVERB_DSP__

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

//-----------------------------------------------------------------
// If you need these classes, you can include the minimal Faust 
// headers. For brevity, we assume the minimal architecture code 
// already includes them. 
//-----------------------------------------------------------------
#include "faust/gui/meta.h"       //  from Faust
#include "faust/gui/UI.h"         //  from Faust
#include "faust/dsp/dsp.h"        //  from Faust

//-----------------------------------------------------------------
// The rest is just the raw Faust DSP code (from minimal.cpp) 
// but with the "main()" removed, and the class renamed to 
// "AlgoVerbDSP", plus public setter methods at the bottom.
//-----------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10  __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

//-----------------------------------------
// Lookup table for LFO
//-----------------------------------------
class mydspSIG0 {
  private:
    int iVec1[2];
    int iRec9[2];
    
  public:
    void instanceInitmydspSIG0(int sample_rate) {
        (void)sample_rate; // unused
        iVec1[0] = 0; iVec1[1] = 0;
        iRec9[0] = 0; iRec9[1] = 0;
    }
    void fillmydspSIG0(int count, float* table) {
        for (int i = 0; i < count; i++) {
            iVec1[0] = 1;
            iRec9[0] = (iVec1[1] + iRec9[1]) % 65536;
            table[i] = std::sin(9.58738e-05f * float(iRec9[0]));
            iVec1[1] = iVec1[0];
            iRec9[1] = iRec9[0];
        }
    }
};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }
static float ftbl0mydspSIG0[65536];

//-----------------------------------------------------------------
// Our Faust DSP class: "AlgoVerbDSP"
// Note: originally "class mydsp : public dsp { ... }"
//-----------------------------------------------------------------
class AlgoVerbDSP : public dsp
{
  private:
    // ----------------------------------------------------------------
    // Faust code's internal fields
    // (the code you pasted, minus the main() at the end, goes here)
    // ----------------------------------------------------------------

    int iVec0[2];
    int fSampleRate;
    float fConst0;
    float fConst1;

    // Sliders (previously private). 
    // We'll keep them private but add public setters below.
    FAUSTFLOAT fHslider0; // "Mod Depth"
    FAUSTFLOAT fHslider1; // "Mod Frequency"
    FAUSTFLOAT fHslider2; // "Pre Delay"
    FAUSTFLOAT fHslider3; // "Dry/Wet"
    FAUSTFLOAT fHslider4; // "Room Size"
    FAUSTFLOAT fHslider5; // "Damping"

    // The rest of the Faust variables:
    float fConst2;
    float fRec10[2];
    float fRec5[2];
    float fRec6[2];
    float fRec7[2];
    float fRec8[2];
    float fRec11[2];
    float fRec12[2];
    int iRec13[2];
    int iRec14[2];
    int IOTA0;
    float fVec2[8192];
    float fConst3;
    float fConst4;
    float fRec15[2];
    float fVec3[2048];
    float fRec4[2];
    float fConst5;
    float fRec17[2];
    float fRec18[2];
    float fRec19[2];
    float fRec20[2];
    float fRec21[2];
    float fVec4[2048];
    float fRec16[2];
    float fConst6;
    float fRec23[2];
    float fRec24[2];
    float fRec25[2];
    float fRec26[2];
    float fRec27[2];
    float fVec5[2048];
    float fRec22[2];
    float fConst7;
    float fRec29[2];
    float fRec30[2];
    float fRec31[2];
    float fRec32[2];
    float fRec33[2];
    float fVec6[2048];
    float fRec28[2];
    float fConst8;
    float fRec35[2];
    float fRec36[2];
    float fRec37[2];
    float fRec38[2];
    float fRec39[2];
    float fVec7[2048];
    float fRec34[2];
    float fConst9;
    float fRec41[2];
    float fRec42[2];
    float fRec43[2];
    float fRec44[2];
    float fRec45[2];
    float fVec8[2048];
    float fRec40[2];
    float fConst10;
    float fRec47[2];
    float fRec48[2];
    float fRec49[2];
    float fRec50[2];
    float fRec51[2];
    float fVec9[2048];
    float fRec46[2];
    float fConst11;
    float fRec53[2];
    float fRec54[2];
    float fRec55[2];
    float fRec56[2];
    float fRec57[2];
    float fVec10[2048];
    float fRec52[2];
    float fVec11[1024];
    int iConst12;
    float fRec3[2];
    float fVec12[128];
    int iConst13;
    float fRec2[2];
    float fVec13[1024];
    int iConst14;
    float fRec1[2];
    float fVec14[1024];
    int iConst15;
    float fRec0[2];

  public:
    // ------------------------------------------------------------
    // Faust metadata method
    // ------------------------------------------------------------
    void metadata(Meta* m) {
        m->declare("name", "algorithmicReverb");
        // truncated for brevity...
    }

    // ------------------------------------------------------------
    // Overridden virtual methods from dsp base class
    // ------------------------------------------------------------
    virtual int getNumInputs()   { return 2; }
    virtual int getNumOutputs()  { return 1; }

    static void classInit(int sample_rate)
    {
        // Fill the LFO table
        mydspSIG0* sig0 = newmydspSIG0();
        sig0->instanceInitmydspSIG0(sample_rate);
        sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
        deletemydspSIG0(sig0);
    }

    virtual void instanceConstants(int sample_rate)
    {
        fSampleRate = sample_rate;
        fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
        fConst1 = 0.025306122f * fConst0;
        fConst2 = 1.0f / fConst0;
        fConst3 = 6.349206e-06f * fConst0;
        fConst4 = 9.070295e-06f * fConst0;
        fConst5 = 0.026938776f * fConst0;
        fConst6 = 0.028956916f * fConst0;
        fConst7 = 0.030748298f * fConst0;
        fConst8 = 0.0322449f * fConst0;
        fConst9 = 0.033809524f * fConst0;
        fConst10 = 0.035306122f * fConst0;
        fConst11 = 0.036666665f * fConst0;
        iConst12 = int(0.0029705216f * fConst0) & 1023;
        iConst13 = int(0.000430839f * fConst0) & 1023;
        iConst14 = int(0.007913833f * fConst0) & 1023;
        iConst15 = int(0.016303854f * fConst0) & 1023;
    }

    virtual void instanceResetUserInterface()
    {
        // Default values
        fHslider0 = FAUSTFLOAT(2.0f);  // Mod Depth
        fHslider1 = FAUSTFLOAT(0.2f);  // Mod Frequency
        fHslider2 = FAUSTFLOAT(0.02f); // Pre Delay
        fHslider3 = FAUSTFLOAT(0.4f);  // Dry/Wet
        fHslider4 = FAUSTFLOAT(0.9f);  // Room Size
        fHslider5 = FAUSTFLOAT(0.2f);  // Damping
    }

    virtual void instanceClear()
    {
        for (int i = 0; i < 2; i++) { iVec0[i] = 0; fRec10[i] = 0; fRec5[i] = 0; fRec6[i] = 0; 
            fRec7[i] = 0; fRec8[i] = 0; fRec11[i] = 0; fRec12[i] = 0; iRec13[i] = 0; iRec14[i] = 0; }
        IOTA0 = 0;
        for (int i = 0; i < 8192; i++) { fVec2[i] = 0; }
        for (int i = 0; i < 2; i++) { fRec15[i] = 0; fRec4[i] = 0; fRec17[i] = 0; fRec18[i] = 0; 
            fRec19[i] = 0; fRec20[i] = 0; fRec21[i] = 0; fRec16[i] = 0; fRec23[i] = 0; 
            fRec24[i] = 0; fRec25[i] = 0; fRec26[i] = 0; fRec27[i] = 0; fRec22[i] = 0; 
            fRec29[i] = 0; fRec30[i] = 0; fRec31[i] = 0; fRec32[i] = 0; fRec33[i] = 0; 
            fRec28[i] = 0; fRec35[i] = 0; fRec36[i] = 0; fRec37[i] = 0; fRec38[i] = 0; 
            fRec39[i] = 0; fRec34[i] = 0; fRec41[i] = 0; fRec42[i] = 0; fRec43[i] = 0; 
            fRec44[i] = 0; fRec45[i] = 0; fRec40[i] = 0; fRec47[i] = 0; fRec48[i] = 0; 
            fRec49[i] = 0; fRec50[i] = 0; fRec51[i] = 0; fRec46[i] = 0; fRec53[i] = 0; 
            fRec54[i] = 0; fRec55[i] = 0; fRec56[i] = 0; fRec57[i] = 0; fRec52[i] = 0; 
            fRec3[i] = 0; fRec2[i] = 0; fRec1[i] = 0; fRec0[i] = 0; 
        }
        for (int i = 0; i < 2048; i++) { fVec3[i] = 0; fVec4[i] = 0; fVec5[i] = 0; 
            fVec6[i] = 0; fVec7[i] = 0; fVec8[i] = 0; fVec9[i] = 0; fVec10[i] = 0; }
        for (int i = 0; i < 1024; i++) { fVec11[i] = 0; fVec13[i] = 0; fVec14[i] = 0; }
        for (int i = 0; i < 128; i++)  { fVec12[i] = 0; }
    }

    virtual void init(int sample_rate)
    {
        classInit(sample_rate);
        instanceInit(sample_rate);
    }

    virtual void instanceInit(int sample_rate)
    {
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }

    virtual AlgoVerbDSP* clone() {
        return new AlgoVerbDSP();
    }

    virtual int getSampleRate() {
        return fSampleRate;
    }

    // Build the Faust UI (we won't actually use it in code; it's here for completeness)
    virtual void buildUserInterface(UI* ui_interface)
    {
        ui_interface->openVerticalBox("Reverb");
        ui_interface->declare(0, "0", "");
        ui_interface->openHorizontalBox("0x00");
        ui_interface->declare(&fHslider4, "0", "");
        ui_interface->declare(&fHslider4, "style", "knob");
        ui_interface->addHorizontalSlider("Room Size", &fHslider4, FAUSTFLOAT(0.9f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));

        ui_interface->declare(&fHslider5, "1", "");
        ui_interface->declare(&fHslider5, "style", "knob");
        ui_interface->addHorizontalSlider("Damping", &fHslider5, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));

        ui_interface->declare(&fHslider2, "3", "");
        ui_interface->declare(&fHslider2, "style", "knob");
        ui_interface->addHorizontalSlider("Pre Delay", &fHslider2, FAUSTFLOAT(0.02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));

        ui_interface->declare(&fHslider1, "4", "");
        ui_interface->declare(&fHslider1, "style", "knob");
        ui_interface->addHorizontalSlider("Mod Frequency", &fHslider1, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));

        ui_interface->declare(&fHslider0, "5", "");
        ui_interface->declare(&fHslider0, "style", "knob");
        ui_interface->addHorizontalSlider("Mod Depth", &fHslider0, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(100.0f), FAUSTFLOAT(1.0f));
        ui_interface->closeBox();

        ui_interface->declare(&fHslider3, "6", "");
        ui_interface->addHorizontalSlider("Dry/Wet", &fHslider3, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
        ui_interface->closeBox();
    }

    // DSP compute
    void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs);

    // ------------------------------------------------------------
    // Public: expose param setters so we can adjust from main code
    // ------------------------------------------------------------
  public:
    void setModDepth(float v)    { fHslider0 = v; }
    void setModFrequency(float v){ fHslider1 = v; }
    void setPreDelay(float v)    { fHslider2 = v; }
    void setDryWet(float v)      { fHslider3 = v; }
    void setRoomSize(float v)    { fHslider4 = v; }
    void setDamping(float v)     { fHslider5 = v; }
};

#endif // __ALGO_REVERB_DSP__
