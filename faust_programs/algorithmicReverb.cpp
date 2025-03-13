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

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
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

class mydspSIG0 {
	
  private:
	
	int iVec1[2];
	int iRec9[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iVec1[l1] = 0;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec9[l2] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec1[0] = 1;
			iRec9[0] = (iVec1[1] + iRec9[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec9[0]));
			iVec1[1] = iVec1[0];
			iRec9[1] = iRec9[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec10[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	FAUSTFLOAT fHslider2;
	float fRec11[2];
	float fRec12[2];
	int iRec13[2];
	int iRec14[2];
	FAUSTFLOAT fHslider3;
	int IOTA0;
	float fVec2[8192];
	float fConst3;
	FAUSTFLOAT fHslider4;
	float fConst4;
	FAUSTFLOAT fHslider5;
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
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "algorithmicReverb.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "algorithmicReverb");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
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
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2.0f);
		fHslider1 = FAUSTFLOAT(0.2f);
		fHslider2 = FAUSTFLOAT(0.02f);
		fHslider3 = FAUSTFLOAT(0.4f);
		fHslider4 = FAUSTFLOAT(0.9f);
		fHslider5 = FAUSTFLOAT(0.2f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec10[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec5[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec7[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec8[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec12[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			iRec13[l10] = 0;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec14[l11] = 0;
		}
		IOTA0 = 0;
		for (int l12 = 0; l12 < 8192; l12 = l12 + 1) {
			fVec2[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec15[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2048; l14 = l14 + 1) {
			fVec3[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec4[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec17[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec19[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec20[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec21[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2048; l21 = l21 + 1) {
			fVec4[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec16[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec23[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec24[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec25[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec26[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec27[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2048; l28 = l28 + 1) {
			fVec5[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec22[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec29[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec30[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec31[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec32[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec33[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2048; l35 = l35 + 1) {
			fVec6[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec28[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec35[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2; l39 = l39 + 1) {
			fRec37[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec38[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec39[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2048; l42 = l42 + 1) {
			fVec7[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec34[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec41[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec42[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2; l46 = l46 + 1) {
			fRec43[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec44[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec45[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2048; l49 = l49 + 1) {
			fVec8[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec40[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec47[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec48[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec49[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec50[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec51[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2048; l56 = l56 + 1) {
			fVec9[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec46[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec53[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec54[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2; l60 = l60 + 1) {
			fRec55[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec56[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec57[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2048; l63 = l63 + 1) {
			fVec10[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec52[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 1024; l65 = l65 + 1) {
			fVec11[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 2; l66 = l66 + 1) {
			fRec3[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 128; l67 = l67 + 1) {
			fVec12[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec2[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 1024; l69 = l69 + 1) {
			fVec13[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec1[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 1024; l71 = l71 + 1) {
			fVec14[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 2; l72 = l72 + 1) {
			fRec0[l72] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
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
		ui_interface->addHorizontalSlider("Mod Depth", &fHslider0, FAUSTFLOAT(2.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider3, "6", "");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider3, FAUSTFLOAT(0.4f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fHslider0);
		float fSlow1 = fConst2 * float(fHslider1);
		int iSlow2 = int(fConst0 * float(fHslider2));
		float fSlow3 = float(fHslider3);
		float fSlow4 = 0.1f * fSlow3;
		float fSlow5 = fConst3 * float(fHslider4) + 0.7f;
		float fSlow6 = fConst4 * float(fHslider5);
		float fSlow7 = 1.0f - fSlow6;
		float fSlow8 = 1.0f - fSlow3;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			float fTemp0 = ((1 - iVec0[1]) ? 0.0f : fSlow1 + fRec10[1]);
			fRec10[0] = fTemp0 - std::floor(fTemp0);
			float fTemp1 = fSlow0 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec10[0]), 65535))];
			float fTemp2 = float(int(fConst1 + fTemp1));
			float fTemp3 = ((fRec5[1] != 0.0f) ? (((fRec6[1] > 0.0f) & (fRec6[1] < 1.0f)) ? fRec5[1] : 0.0f) : (((fRec6[1] == 0.0f) & (fTemp2 != fRec7[1])) ? 0.0009765625f : (((fRec6[1] == 1.0f) & (fTemp2 != fRec8[1])) ? -0.0009765625f : 0.0f)));
			fRec5[0] = fTemp3;
			fRec6[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec6[1] + fTemp3));
			fRec7[0] = (((fRec6[1] >= 1.0f) & (fRec8[1] != fTemp2)) ? fTemp2 : fRec7[1]);
			fRec8[0] = (((fRec6[1] <= 0.0f) & (fRec7[1] != fTemp2)) ? fTemp2 : fRec8[1]);
			float fTemp4 = ((fRec11[1] != 0.0f) ? (((fRec12[1] > 0.0f) & (fRec12[1] < 1.0f)) ? fRec11[1] : 0.0f) : (((fRec12[1] == 0.0f) & (iSlow2 != iRec13[1])) ? 0.0009765625f : (((fRec12[1] == 1.0f) & (iSlow2 != iRec14[1])) ? -0.0009765625f : 0.0f)));
			fRec11[0] = fTemp4;
			fRec12[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec12[1] + fTemp4));
			iRec13[0] = (((fRec12[1] >= 1.0f) & (iRec14[1] != iSlow2)) ? iSlow2 : iRec13[1]);
			iRec14[0] = (((fRec12[1] <= 0.0f) & (iRec13[1] != iSlow2)) ? iSlow2 : iRec14[1]);
			float fTemp5 = fSlow4 * float(input0[i0]);
			fVec2[IOTA0 & 8191] = fTemp5;
			float fTemp6 = fRec12[0] * fVec2[(IOTA0 - (iRec14[0] & 8191)) & 8191];
			fRec15[0] = fSlow6 * fRec15[1] + fSlow7 * fRec4[1];
			float fTemp7 = (1.0f - fRec12[0]) * fVec2[(IOTA0 - (iRec13[0] & 8191)) & 8191];
			float fTemp8 = fTemp6 + fSlow5 * fRec15[0] + fTemp7;
			fVec3[IOTA0 & 2047] = fTemp8;
			fRec4[0] = (1.0f - fRec6[0]) * fVec3[(IOTA0 - (int(fRec7[0]) & 2047)) & 2047] + fRec6[0] * fVec3[(IOTA0 - (int(fRec8[0]) & 2047)) & 2047];
			float fTemp9 = float(int(fConst5 + fTemp1));
			float fTemp10 = ((fRec17[1] != 0.0f) ? (((fRec18[1] > 0.0f) & (fRec18[1] < 1.0f)) ? fRec17[1] : 0.0f) : (((fRec18[1] == 0.0f) & (fTemp9 != fRec19[1])) ? 0.0009765625f : (((fRec18[1] == 1.0f) & (fTemp9 != fRec20[1])) ? -0.0009765625f : 0.0f)));
			fRec17[0] = fTemp10;
			fRec18[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec18[1] + fTemp10));
			fRec19[0] = (((fRec18[1] >= 1.0f) & (fRec20[1] != fTemp9)) ? fTemp9 : fRec19[1]);
			fRec20[0] = (((fRec18[1] <= 0.0f) & (fRec19[1] != fTemp9)) ? fTemp9 : fRec20[1]);
			float fTemp11 = fTemp7 + fTemp6;
			fRec21[0] = fSlow6 * fRec21[1] + fSlow7 * fRec16[1];
			float fTemp12 = fTemp11 + fSlow5 * fRec21[0];
			fVec4[IOTA0 & 2047] = fTemp12;
			fRec16[0] = (1.0f - fRec18[0]) * fVec4[(IOTA0 - (int(fRec19[0]) & 2047)) & 2047] + fRec18[0] * fVec4[(IOTA0 - (int(fRec20[0]) & 2047)) & 2047];
			float fTemp13 = float(int(fConst6 + fTemp1));
			float fTemp14 = ((fRec23[1] != 0.0f) ? (((fRec24[1] > 0.0f) & (fRec24[1] < 1.0f)) ? fRec23[1] : 0.0f) : (((fRec24[1] == 0.0f) & (fTemp13 != fRec25[1])) ? 0.0009765625f : (((fRec24[1] == 1.0f) & (fTemp13 != fRec26[1])) ? -0.0009765625f : 0.0f)));
			fRec23[0] = fTemp14;
			fRec24[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec24[1] + fTemp14));
			fRec25[0] = (((fRec24[1] >= 1.0f) & (fRec26[1] != fTemp13)) ? fTemp13 : fRec25[1]);
			fRec26[0] = (((fRec24[1] <= 0.0f) & (fRec25[1] != fTemp13)) ? fTemp13 : fRec26[1]);
			fRec27[0] = fSlow6 * fRec27[1] + fSlow7 * fRec22[1];
			float fTemp15 = fTemp11 + fSlow5 * fRec27[0];
			fVec5[IOTA0 & 2047] = fTemp15;
			fRec22[0] = (1.0f - fRec24[0]) * fVec5[(IOTA0 - (int(fRec25[0]) & 2047)) & 2047] + fRec24[0] * fVec5[(IOTA0 - (int(fRec26[0]) & 2047)) & 2047];
			float fTemp16 = float(int(fConst7 + fTemp1));
			float fTemp17 = ((fRec29[1] != 0.0f) ? (((fRec30[1] > 0.0f) & (fRec30[1] < 1.0f)) ? fRec29[1] : 0.0f) : (((fRec30[1] == 0.0f) & (fTemp16 != fRec31[1])) ? 0.0009765625f : (((fRec30[1] == 1.0f) & (fTemp16 != fRec32[1])) ? -0.0009765625f : 0.0f)));
			fRec29[0] = fTemp17;
			fRec30[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec30[1] + fTemp17));
			fRec31[0] = (((fRec30[1] >= 1.0f) & (fRec32[1] != fTemp16)) ? fTemp16 : fRec31[1]);
			fRec32[0] = (((fRec30[1] <= 0.0f) & (fRec31[1] != fTemp16)) ? fTemp16 : fRec32[1]);
			fRec33[0] = fSlow6 * fRec33[1] + fSlow7 * fRec28[1];
			float fTemp18 = fTemp11 + fSlow5 * fRec33[0];
			fVec6[IOTA0 & 2047] = fTemp18;
			fRec28[0] = (1.0f - fRec30[0]) * fVec6[(IOTA0 - (int(fRec31[0]) & 2047)) & 2047] + fRec30[0] * fVec6[(IOTA0 - (int(fRec32[0]) & 2047)) & 2047];
			float fTemp19 = float(int(fConst8 + fTemp1));
			float fTemp20 = ((fRec35[1] != 0.0f) ? (((fRec36[1] > 0.0f) & (fRec36[1] < 1.0f)) ? fRec35[1] : 0.0f) : (((fRec36[1] == 0.0f) & (fTemp19 != fRec37[1])) ? 0.0009765625f : (((fRec36[1] == 1.0f) & (fTemp19 != fRec38[1])) ? -0.0009765625f : 0.0f)));
			fRec35[0] = fTemp20;
			fRec36[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec36[1] + fTemp20));
			fRec37[0] = (((fRec36[1] >= 1.0f) & (fRec38[1] != fTemp19)) ? fTemp19 : fRec37[1]);
			fRec38[0] = (((fRec36[1] <= 0.0f) & (fRec37[1] != fTemp19)) ? fTemp19 : fRec38[1]);
			fRec39[0] = fSlow6 * fRec39[1] + fSlow7 * fRec34[1];
			float fTemp21 = fTemp11 + fSlow5 * fRec39[0];
			fVec7[IOTA0 & 2047] = fTemp21;
			fRec34[0] = (1.0f - fRec36[0]) * fVec7[(IOTA0 - (int(fRec37[0]) & 2047)) & 2047] + fRec36[0] * fVec7[(IOTA0 - (int(fRec38[0]) & 2047)) & 2047];
			float fTemp22 = float(int(fConst9 + fTemp1));
			float fTemp23 = ((fRec41[1] != 0.0f) ? (((fRec42[1] > 0.0f) & (fRec42[1] < 1.0f)) ? fRec41[1] : 0.0f) : (((fRec42[1] == 0.0f) & (fTemp22 != fRec43[1])) ? 0.0009765625f : (((fRec42[1] == 1.0f) & (fTemp22 != fRec44[1])) ? -0.0009765625f : 0.0f)));
			fRec41[0] = fTemp23;
			fRec42[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec42[1] + fTemp23));
			fRec43[0] = (((fRec42[1] >= 1.0f) & (fRec44[1] != fTemp22)) ? fTemp22 : fRec43[1]);
			fRec44[0] = (((fRec42[1] <= 0.0f) & (fRec43[1] != fTemp22)) ? fTemp22 : fRec44[1]);
			fRec45[0] = fSlow6 * fRec45[1] + fSlow7 * fRec40[1];
			float fTemp24 = fTemp11 + fSlow5 * fRec45[0];
			fVec8[IOTA0 & 2047] = fTemp24;
			fRec40[0] = (1.0f - fRec42[0]) * fVec8[(IOTA0 - (int(fRec43[0]) & 2047)) & 2047] + fRec42[0] * fVec8[(IOTA0 - (int(fRec44[0]) & 2047)) & 2047];
			float fTemp25 = float(int(fConst10 + fTemp1));
			float fTemp26 = ((fRec47[1] != 0.0f) ? (((fRec48[1] > 0.0f) & (fRec48[1] < 1.0f)) ? fRec47[1] : 0.0f) : (((fRec48[1] == 0.0f) & (fTemp25 != fRec49[1])) ? 0.0009765625f : (((fRec48[1] == 1.0f) & (fTemp25 != fRec50[1])) ? -0.0009765625f : 0.0f)));
			fRec47[0] = fTemp26;
			fRec48[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec48[1] + fTemp26));
			fRec49[0] = (((fRec48[1] >= 1.0f) & (fRec50[1] != fTemp25)) ? fTemp25 : fRec49[1]);
			fRec50[0] = (((fRec48[1] <= 0.0f) & (fRec49[1] != fTemp25)) ? fTemp25 : fRec50[1]);
			fRec51[0] = fSlow6 * fRec51[1] + fSlow7 * fRec46[1];
			float fTemp27 = fTemp11 + fSlow5 * fRec51[0];
			fVec9[IOTA0 & 2047] = fTemp27;
			fRec46[0] = (1.0f - fRec48[0]) * fVec9[(IOTA0 - (int(fRec49[0]) & 2047)) & 2047] + fRec48[0] * fVec9[(IOTA0 - (int(fRec50[0]) & 2047)) & 2047];
			float fTemp28 = float(int(fConst11 + fTemp1));
			float fTemp29 = ((fRec53[1] != 0.0f) ? (((fRec54[1] > 0.0f) & (fRec54[1] < 1.0f)) ? fRec53[1] : 0.0f) : (((fRec54[1] == 0.0f) & (fTemp28 != fRec55[1])) ? 0.0009765625f : (((fRec54[1] == 1.0f) & (fTemp28 != fRec56[1])) ? -0.0009765625f : 0.0f)));
			fRec53[0] = fTemp29;
			fRec54[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec54[1] + fTemp29));
			fRec55[0] = (((fRec54[1] >= 1.0f) & (fRec56[1] != fTemp28)) ? fTemp28 : fRec55[1]);
			fRec56[0] = (((fRec54[1] <= 0.0f) & (fRec55[1] != fTemp28)) ? fTemp28 : fRec56[1]);
			fRec57[0] = fSlow6 * fRec57[1] + fSlow7 * fRec52[1];
			float fTemp30 = fTemp11 + fSlow5 * fRec57[0];
			fVec10[IOTA0 & 2047] = fTemp30;
			fRec52[0] = (1.0f - fRec54[0]) * fVec10[(IOTA0 - (int(fRec55[0]) & 2047)) & 2047] + fRec54[0] * fVec10[(IOTA0 - (int(fRec56[0]) & 2047)) & 2047];
			fVec11[IOTA0 & 1023] = fRec4[0] + fRec16[0] + fRec22[0] + fRec28[0] + fRec34[0] + fRec40[0] + fRec46[0] + fRec52[0] - 0.2f * fRec3[1];
			fRec3[0] = fVec11[(IOTA0 - iConst12) & 1023];
			fVec12[IOTA0 & 127] = fRec3[0] - 0.2f * fRec2[1];
			fRec2[0] = fVec12[(IOTA0 - iConst13) & 127];
			fVec13[IOTA0 & 1023] = fRec2[0] - 0.2f * fRec1[1];
			fRec1[0] = fVec13[(IOTA0 - iConst14) & 1023];
			fVec14[IOTA0 & 1023] = fRec1[0] - 0.2f * fRec0[1];
			fRec0[0] = fVec14[(IOTA0 - iConst15) & 1023];
			output0[i0] = FAUSTFLOAT(fRec0[0] + fSlow8 * float(input1[i0]));
			iVec0[1] = iVec0[0];
			fRec10[1] = fRec10[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			iRec13[1] = iRec13[0];
			iRec14[1] = iRec14[0];
			IOTA0 = IOTA0 + 1;
			fRec15[1] = fRec15[0];
			fRec4[1] = fRec4[0];
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
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

using namespace std;

#ifdef LAYOUT_UI
void getMinimumSize(dsp* dsp, LayoutUI* ui, float& width, float& height)
{
    // Prepare layout
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
    mydsp DSP;
    cout << "DSP size: " << sizeof(DSP) << " bytes\n";
    
    // Activate the UI, here that only print the control paths
    PrintUI print_ui;
    DSP.buildUserInterface(&print_ui);
    
    /*
    MapUI map_ui;
    DSP.buildUserInterface(&map_ui);
    for (int i = 0; i < map_ui.getParamsCount(); i++) {
        cout << "getParamAddress " << map_ui.getParamAddress(i) << endl;
        cout << "getParamShortname " << map_ui.getParamShortname(i) << endl;
        cout << "getParamLabel " << map_ui.getParamLabel(i) << endl;
    }
    */
/**    
#ifdef LAYOUT_UI
    LayoutUI layout_ui;
    float width, height;
    getMinimumSize(&DSP, &layout_ui, width, height);
    cout << "minimal_width: " << width << "\n";
    cout << "minimal_height: " << height << "\n";
    setPosAndSize(&layout_ui, 0, 0, width*1.5, height*1.5);
#else
    // Allocate the audio driver to render 5 buffers of 512 frames
    dummyaudio audio(5);
    audio.init("Test", static_cast<dsp*>(&DSP));
    
    // Render buffers...
    audio.start();
    audio.stop();
#endif
}
*/
/******************* END minimal.cpp ****************/


#endif
