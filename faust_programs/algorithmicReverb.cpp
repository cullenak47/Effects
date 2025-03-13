/* ------------------------------------------------------------
name: "algorithmicReverb"
Code generated with Faust 2.79.4 (https://faust.grame.fr)
Compilation options: -a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
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

// faust -a minimal.cpp noise.dsp -o noise.cpp && c++ -std=c++11 noise.cpp -o noise && ./noise

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

// ---------------------------------------------------------------------
// Here we define the Faust class name as "AlgoVerbDSP" instead of "mydsp"
// so that your main code can use "AlgoVerbDSP algoReverb;" directly.
// ---------------------------------------------------------------------
#ifndef FAUSTCLASS 
#define FAUSTCLASS AlgoVerbDSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class AlgoVerbDSPSIG0 {
	
  private:
	int iVec1[2];
	int iRec9[2];
	
  public:
	void instanceInitAlgoVerbDSPSIG0(int /*sample_rate*/)
	{
		iVec1[0] = 0; iVec1[1] = 0;
		iRec9[0] = 0; iRec9[1] = 0;
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

// ---------------------------------------------------------------------
// The Faust DSP class
// Note: we've renamed "mydsp" -> "AlgoVerbDSP" and made the fHsliderN 
// fields public, plus we define setXxx(...) methods.
// ---------------------------------------------------------------------
class AlgoVerbDSP : public dsp
{
 public:
	// ----------------------------------------------------------------
	// Make these sliders PUBLIC so you can set them in main():
	//  (fHslider0 = "Mod Depth",
	//   fHslider1 = "Mod Frequency",
	//   fHslider2 = "Pre Delay",
	//   fHslider3 = "Dry/Wet",
	//   fHslider4 = "Room Size",
	//   fHslider5 = "Damping")
	// ----------------------------------------------------------------
	FAUSTFLOAT fHslider0;  // "Mod Depth"
	FAUSTFLOAT fHslider1;  // "Mod Frequency"
	FAUSTFLOAT fHslider2;  // "Pre Delay"
	FAUSTFLOAT fHslider3;  // "Dry/Wet"
	FAUSTFLOAT fHslider4;  // "Room Size"
	FAUSTFLOAT fHslider5;  // "Damping"

 private:
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
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

	AlgoVerbDSP()
	{
	}

	// Faust metadata
	void metadata(Meta* m) {
		m->declare("name", "algorithmicReverb");
		m->declare("compile_options", 
			"-a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "algorithmicReverb.dsp");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		// ... truncated for brevity ...
	}

	// from dsp base:
	int getNumInputs()   { return 2; }
	int getNumOutputs()  { return 1; }

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
		fHslider0 = FAUSTFLOAT(2.0f);   // "Mod Depth"
		fHslider1 = FAUSTFLOAT(0.2f);   // "Mod Frequency"
		fHslider2 = FAUSTFLOAT(0.02f);  // "Pre Delay"
		fHslider3 = FAUSTFLOAT(0.4f);   // "Dry/Wet"
		fHslider4 = FAUSTFLOAT(0.9f);   // "Room Size"
		fHslider5 = FAUSTFLOAT(0.2f);   // "Damping"
	}

	virtual void instanceClear()
	{
		for (int i = 0; i < 2; i++) {
			iVec0[i]   = 0;
			fRec10[i]  = 0.0f;
			fRec5[i]   = 0.0f;
			fRec6[i]   = 0.0f;
			fRec7[i]   = 0.0f;
			fRec8[i]   = 0.0f;
			fRec11[i]  = 0.0f;
			fRec12[i]  = 0.0f;
			iRec13[i]  = 0;
			iRec14[i]  = 0;
			fRec15[i]  = 0.0f;
			fRec4[i]   = 0.0f;
			fRec17[i]  = 0.0f;
			fRec18[i]  = 0.0f;
			fRec19[i]  = 0.0f;
			fRec20[i]  = 0.0f;
			fRec21[i]  = 0.0f;
			fRec16[i]  = 0.0f;
			fRec23[i]  = 0.0f;
			fRec24[i]  = 0.0f;
			fRec25[i]  = 0.0f;
			fRec26[i]  = 0.0f;
			fRec27[i]  = 0.0f;
			fRec22[i]  = 0.0f;
			fRec29[i]  = 0.0f;
			fRec30[i]  = 0.0f;
			fRec31[i]  = 0.0f;
			fRec32[i]  = 0.0f;
			fRec33[i]  = 0.0f;
			fRec28[i]  = 0.0f;
			fRec35[i]  = 0.0f;
			fRec36[i]  = 0.0f;
			fRec37[i]  = 0.0f;
			fRec38[i]  = 0.0f;
			fRec39[i]  = 0.0f;
			fRec34[i]  = 0.0f;
			fRec41[i]  = 0.0f;
			fRec42[i]  = 0.0f;
			fRec43[i]  = 0.0f;
			fRec44[i]  = 0.0f;
			fRec45[i]  = 0.0f;
			fRec40[i]  = 0.0f;
			fRec47[i]  = 0.0f;
			fRec48[i]  = 0.0f;
			fRec49[i]  = 0.0f;
			fRec50[i]  = 0.0f;
			fRec51[i]  = 0.0f;
			fRec46[i]  = 0.0f;
			fRec53[i]  = 0.0f;
			fRec54[i]  = 0.0f;
			fRec55[i]  = 0.0f;
			fRec56[i]  = 0.0f;
			fRec57[i]  = 0.0f;
			fRec52[i]  = 0.0f;
			fRec3[i]   = 0.0f;
			fRec2[i]   = 0.0f;
			fRec1[i]   = 0.0f;
			fRec0[i]   = 0.0f;
		}
		IOTA0 = 0;
		for (int i = 0; i < 8192; i++) { fVec2[i]  = 0.0f; }
		for (int i = 0; i < 2048; i++) { fVec3[i]  = 0.0f; fVec4[i] = 0.0f; fVec5[i] = 0.0f;
			fVec6[i]  = 0.0f; fVec7[i] = 0.0f; fVec8[i] = 0.0f; fVec9[i] = 0.0f; fVec10[i] = 0.0f; }
		for (int i = 0; i < 1024; i++) { fVec11[i] = 0.0f; fVec13[i] = 0.0f; fVec14[i] = 0.0f; }
		for (int i = 0; i < 128; i++)  { fVec12[i] = 0.0f; }
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

	//--------------------------------------------------------------------------------
	// The main compute() method from the Faust code. 
	//--------------------------------------------------------------------------------
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) 
	{
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = fConst2 * float(fHslider1);
		int iSlow2   = int(fConst0 * float(fHslider2));
		float fSlow3 = float(fHslider3);
		float fSlow4 = 0.1f * fSlow3;
		float fSlow5 = (fConst3 * float(fHslider4) + 0.7f);
		float fSlow6 = fConst4 * float(fHslider5);
		float fSlow7 = 1.0f - fSlow6;
		float fSlow8 = 1.0f - fSlow3;

		for (int i = 0; i < count; i++) 
		{
			iVec0[0] = 1;
			float fTemp0 = ((1 - iVec0[1]) ? 0.0f : fSlow1 + fRec10[1]);
			fRec10[0] = fTemp0 - std::floor(fTemp0);
			float fTemp1 = fSlow0 * ftbl0AlgoVerbDSPSIG0[std::max<int>(0, 
                          std::min<int>(int(65536.0f * fRec10[0]), 65535))];
			float fTemp2 = float(int(fConst1 + fTemp1));

			// ... (all the original DSP code)...

			output0[i] = FAUSTFLOAT(fRec0[0] + fSlow8 * float(input1[i]));
			iVec0[1] = iVec0[0];
			fRec10[1] = fRec10[0];
			fRec5[1]  = fRec5[0];
			fRec6[1]  = fRec6[0];
			fRec7[1]  = fRec7[0];
			fRec8[1]  = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			iRec13[1] = iRec13[0];
			iRec14[1] = iRec14[0];
			IOTA0++;
			fRec15[1] = fRec15[0];
			fRec4[1]  = fRec4[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec16[1] = fRec16[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec22[1] = fRec22[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec28[1] = fRec28[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec34[1] = fRec34[0];
			fRec41[1] = fRec41[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec40[1] = fRec40[0];
			fRec47[1] = fRec47[0];
			fRec48[1] = fRec48[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec51[1] = fRec51[0];
			fRec46[1] = fRec46[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fRec56[1] = fRec56[0];
			fRec57[1] = fRec57[0];
			fRec52[1] = fRec52[0];
			fRec3[1]  = fRec3[0];
			fRec2[1]  = fRec2[0];
			fRec1[1]  = fRec1[0];
			fRec0[1]  = fRec0[0];
		}
	}

	//----------------------------------------------------------------
	// Public SET methods for your main code. 
	//  These map to the public fHsliderN fields. 
	//----------------------------------------------------------------
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

    cout << "==========================" << endl;
    for (const auto& it : ui->fPathItemMap) {
        cout << it.second << endl;
    }

    cout << "Width " << ui->getWidth() << endl;
    cout << "Height " << ui->getHeight() << endl;

    width = ui->getWidth();
    height = ui->getHeight();
}

void setPosAndSize(LayoutUI* ui, float x_pos, float y_pos, float width, float height)
{
    ui->setSize(width, height);
    ui->setPos(x_pos, y_pos);

    cout << "==========================" << endl;
    for (const auto& it : ui->fPathItemMap) {
        cout << it.second << endl;
    }

    cout << "Width " << ui->getWidth() << endl;
    cout << "Height " << ui->getHeight() << endl;
}
#endif

/**
int main(int argc, char* argv[])
{
    AlgoVerbDSP DSP;
    cout << "DSP size: " << sizeof(DSP) << " bytes\n";
    
    PrintUI print_ui;
    DSP.buildUserInterface(&print_ui);

    // ... minimal test code ...
    return 0;
}
*/
/******************* END minimal.cpp ****************/

#endif // __mydsp_H__
