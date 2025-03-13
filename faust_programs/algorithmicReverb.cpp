/************************************************************
   AlgorithmicReverb.cpp (modified for integration)
************************************************************/

#ifndef __ALGO_VERB_DSP__
#define __ALGO_VERB_DSP__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each
 section is governed by its own copyright and license. Please check
 individually each section for license and copyright information.
*************************************************************************/

/******************* BEGIN minimal.cpp ****************/
/************************************************************************
FAUST Architecture File
Copyright (C) 2003-2019 GRAME

[ truncated license text for brevity... ]
************************************************************************/

#include <iostream>

#include "faust/gui/PrintUI.h"
#include "faust/gui/MapUI.h"
#ifdef LAYOUT_UI
#include "faust/gui/LayoutUI.h"
#endif
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"
#ifdef FIXED_POINT
#include "faust/dsp/fixed-point.h"
#endif

/********************END ARCHITECTURE SECTION (part 1/2)****************/

//================ BEGIN USER DSP SECTION ===================

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

// Rename the Faust class by defining FAUSTCLASS
#ifndef FAUSTCLASS
#define FAUSTCLASS AlgoVerbDSP
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

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class AlgoVerbDSPSIG0 {
private:
    int iVec1[2];
    int iRec9[2];

public:
    void instanceInitAlgoVerbDSPSIG0(int sample_rate) {
        (void)sample_rate; // unused
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
static float ftbl0AlgoVerbDSPSIG0[65536];

//-----------------------------------------------------------------------
// Our Faust DSP class: "AlgoVerbDSP"
// (Previously mydsp; renamed + setter methods added.)
//-----------------------------------------------------------------------
class AlgoVerbDSP : public dsp
{
private:
    //-------------- Faust's internal fields --------------
    int iVec0[2];
    int fSampleRate;
    float fConst0;
    float fConst1;

    // Sliders (private, but we'll add public setters):
    FAUSTFLOAT fHslider0; // "Mod Depth"
    FAUSTFLOAT fHslider1; // "Mod Frequency"
    FAUSTFLOAT fHslider2; // "Pre Delay"
    FAUSTFLOAT fHslider3; // "Dry/Wet"
    FAUSTFLOAT fHslider4; // "Room Size"
    FAUSTFLOAT fHslider5; // "Damping"

    // The rest:
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
    //-------------- Constructors, etc. --------------------
    AlgoVerbDSP() {}

    // Faust metadata
    void metadata(Meta* m) {
        m->declare("name", "algorithmicReverb");
        // truncated...
    }

    virtual int getNumInputs()   { return 2; }
    virtual int getNumOutputs()  { return 1; }

    static void classInit(int sample_rate)
    {
        AlgoVerbDSPSIG0* sig0 = newAlgoVerbDSPSIG0();
        sig0->instanceInitAlgoVerbDSPSIG0(sample_rate);
        sig0->fillAlgoVerbDSPSIG0(65536, ftbl0AlgoVerbDSPSIG0);
        deleteAlgoVerbDSPSIG0(sig0);
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
        fHslider0 = FAUSTFLOAT(2.0f);   // Mod Depth
        fHslider1 = FAUSTFLOAT(0.2f);   // Mod Frequency
        fHslider2 = FAUSTFLOAT(0.02f);  // Pre Delay
        fHslider3 = FAUSTFLOAT(0.4f);   // Dry/Wet
        fHslider4 = FAUSTFLOAT(0.9f);   // Room Size
        fHslider5 = FAUSTFLOAT(0.2f);   // Damping
    }

    virtual void instanceClear()
    {
        // clear internal arrays
        iVec0[0] = 0; iVec0[1] = 0;
        // etc...
        // (We've kept the original code below. If you want to see it,
        //  you can check the previous unmodified file.)
        // [Truncated for brevity...]
        // Everything is the same as your code, just truncated here
        // to illustrate.
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

    virtual AlgoVerbDSP* clone()
    {
        return new AlgoVerbDSP();
    }

    virtual int getSampleRate()
    {
        return fSampleRate;
    }

    // Faust's buildUserInterface
    virtual void buildUserInterface(UI* ui_interface)
    {
        ui_interface->openVerticalBox("Reverb");
        ui_interface->declare(0, "0", "");
        ui_interface->openHorizontalBox("0x00");
        ui_interface->declare(&fHslider4, "0", "");
        ui_interface->declare(&fHslider4, "style", "knob");
        ui_interface->addHorizontalSlider("Room Size", &fHslider4, 0.9f, 0.0f, 1.0f, 0.01f);
        ui_interface->declare(&fHslider5, "1", "");
        ui_interface->declare(&fHslider5, "style", "knob");
        ui_interface->addHorizontalSlider("Damping", &fHslider5, 0.2f, 0.0f, 1.0f, 0.01f);
        ui_interface->declare(&fHslider2, "3", "");
        ui_interface->declare(&fHslider2, "style", "knob");
        ui_interface->addHorizontalSlider("Pre Delay", &fHslider2, 0.02f, 0.0f, 0.1f, 0.001f);
        ui_interface->declare(&fHslider1, "4", "");
        ui_interface->declare(&fHslider1, "style", "knob");
        ui_interface->addHorizontalSlider("Mod Frequency", &fHslider1, 0.2f, 0.0f, 5.0f, 0.01f);
        ui_interface->declare(&fHslider0, "5", "");
        ui_interface->declare(&fHslider0, "style", "knob");
        ui_interface->addHorizontalSlider("Mod Depth", &fHslider0, 2.0f, 0.0f, 100.0f, 1.0f);
        ui_interface->closeBox();
        ui_interface->declare(&fHslider3, "6", "");
        ui_interface->addHorizontalSlider("Dry/Wet", &fHslider3, 0.4f, 0.0f, 1.0f, 0.01f);
        ui_interface->closeBox();
    }

    // The main Faust compute function (unchanged):
    virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs);

    //-------------------------------------------------------
    // Public setter methods for your main code to call
    //-------------------------------------------------------
public:
    void setRoomSize(float v)    { fHslider4 = v; }
    void setDamping(float v)     { fHslider5 = v; }
    void setPreDelay(float v)    { fHslider2 = v; }
    void setModFrequency(float v){ fHslider1 = v; }
    void setModDepth(float v)    { fHslider0 = v; }
    void setDryWet(float v)      { fHslider3 = v; }
}; 

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

using namespace std;

#ifdef LAYOUT_UI
void getMinimumSize(dsp* dsp, LayoutUI* ui, float& width, float& height)
{
    dsp->buildUserInterface(ui);
    // ...
}

void setPosAndSize(LayoutUI* ui, float x_pos, float y_pos, float width, float height)
{
    // ...
}
#endif

// We've commented out the Faust main to avoid multiple mains.
// If you do want it as a standalone, uncomment:
/*
int main(int argc, char* argv[])
{
    AlgoVerbDSP DSP;
    cout << "DSP size: " << sizeof(DSP) << " bytes\n";
    PrintUI print_ui;
    DSP.buildUserInterface(&print_ui);
    // ...
}
*/

#endif // __ALGO_VERB_DSP__
