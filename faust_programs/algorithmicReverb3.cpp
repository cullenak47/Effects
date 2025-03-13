/* ------------------------------------------------------------
name: "dual_modulation"
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
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec11[2];
	float fRec5[2];
	float fRec6[2];
	float fRec7[2];
	float fRec8[2];
	FAUSTFLOAT fHslider4;
	float fRec12[2];
	float fRec13[2];
	int iRec14[2];
	int iRec15[2];
	FAUSTFLOAT fHslider5;
	int IOTA0;
	float fVec2[8192];
	float fConst3;
	FAUSTFLOAT fHslider6;
	float fConst4;
	FAUSTFLOAT fHslider7;
	float fRec16[2];
	float fVec3[2048];
	float fRec4[2];
	float fConst5;
	float fRec18[2];
	float fRec19[2];
	float fRec20[2];
	float fRec21[2];
	float fRec22[2];
	float fVec4[2048];
	float fRec17[2];
	float fConst6;
	float fRec24[2];
	float fRec25[2];
	float fRec26[2];
	float fRec27[2];
	float fRec28[2];
	float fVec5[2048];
	float fRec23[2];
	float fConst7;
	float fRec30[2];
	float fRec31[2];
	float fRec32[2];
	float fRec33[2];
	float fRec34[2];
	float fVec6[2048];
	float fRec29[2];
	float fConst8;
	float fRec36[2];
	float fRec37[2];
	float fRec38[2];
	float fRec39[2];
	float fRec40[2];
	float fVec7[2048];
	float fRec35[2];
	float fConst9;
	float fRec42[2];
	float fRec43[2];
	float fRec44[2];
	float fRec45[2];
	float fRec46[2];
	float fVec8[2048];
	float fRec41[2];
	float fConst10;
	float fRec48[2];
	float fRec49[2];
	float fRec50[2];
	float fRec51[2];
	float fRec52[2];
	float fVec9[2048];
	float fRec47[2];
	float fConst11;
	float fRec54[2];
	float fRec55[2];
	float fRec56[2];
	float fRec57[2];
	float fRec58[2];
	float fVec10[2048];
	float fRec53[2];
	float fVec11[1024];
	int iConst12;
	int iConst13;
	float fRec3[1024];
	int iConst14;
	int iConst15;
	float fRec2[1024];
	int iConst16;
	int iConst17;
	float fRec1[2048];
	int iConst18;
	int iConst19;
	float fRec0[2048];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a minimal.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "dual_modulation.dsp");
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
		m->declare("name", "dual_modulation");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
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
		iConst13 = iConst12 + 1;
		iConst14 = int(0.000430839f * fConst0) & 1023;
		iConst15 = iConst14 + 1;
		iConst16 = int(0.007913833f * fConst0) & 1023;
		iConst17 = iConst16 + 1;
		iConst18 = int(0.016303854f * fConst0) & 1023;
		iConst19 = iConst18 + 1;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.2f);
		fHslider6 = FAUSTFLOAT(0.9f);
		fHslider7 = FAUSTFLOAT(0.2f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec10[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec11[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec8[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec12[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec13[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec14[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			iRec15[l12] = 0;
		}
		IOTA0 = 0;
		for (int l13 = 0; l13 < 8192; l13 = l13 + 1) {
			fVec2[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec16[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2048; l15 = l15 + 1) {
			fVec3[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec4[l16] = 0.0f;
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
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec22[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2048; l22 = l22 + 1) {
			fVec4[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec17[l23] = 0.0f;
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
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec28[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2048; l29 = l29 + 1) {
			fVec5[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec23[l30] = 0.0f;
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
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2048; l36 = l36 + 1) {
			fVec6[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec29[l37] = 0.0f;
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
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec40[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2048; l43 = l43 + 1) {
			fVec7[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec35[l44] = 0.0f;
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
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec46[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2048; l50 = l50 + 1) {
			fVec8[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec41[l51] = 0.0f;
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
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec52[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2048; l57 = l57 + 1) {
			fVec9[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec47[l58] = 0.0f;
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
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec58[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2048; l64 = l64 + 1) {
			fVec10[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 2; l65 = l65 + 1) {
			fRec53[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 1024; l66 = l66 + 1) {
			fVec11[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 1024; l67 = l67 + 1) {
			fRec3[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 1024; l68 = l68 + 1) {
			fRec2[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 2048; l69 = l69 + 1) {
			fRec1[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2048; l70 = l70 + 1) {
			fRec0[l70] = 0.0f;
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
		ui_interface->declare(&fHslider6, "0", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("Room Size", &fHslider6, FAUSTFLOAT(0.9f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider7, "1", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("Damping", &fHslider7, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Pre Delay", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("LFO1 Freq", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider0, "5", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("LFO1 Depth", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "6", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("LFO2 Freq", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "7", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("LFO2 Depth", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider5, "8", "");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider5, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = fConst2 * float(fHslider1);
		float fSlow2 = float(fHslider2);
		float fSlow3 = fConst2 * float(fHslider3);
		int iSlow4 = int(fConst0 * float(fHslider4));
		float fSlow5 = float(fHslider5);
		float fSlow6 = 0.1f * fSlow5;
		float fSlow7 = fConst3 * float(fHslider6) + 0.7f;
		float fSlow8 = fConst4 * float(fHslider7);
		float fSlow9 = 1.0f - fSlow8;
		float fSlow10 = 1.0f - fSlow5;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			int iTemp0 = 1 - iVec0[1];
			float fTemp1 = ((iTemp0) ? 0.0f : fSlow1 + fRec10[1]);
			fRec10[0] = fTemp1 - std::floor(fTemp1);
			float fTemp2 = ((iTemp0) ? 0.0f : fSlow3 + fRec11[1]);
			fRec11[0] = fTemp2 - std::floor(fTemp2);
			float fTemp3 = fSlow0 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec10[0]), 65535))] + fSlow2 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec11[0]), 65535))];
			float fTemp4 = float(int(fConst1 + fTemp3));
			float fTemp5 = ((fRec5[1] != 0.0f) ? (((fRec6[1] > 0.0f) & (fRec6[1] < 1.0f)) ? fRec5[1] : 0.0f) : (((fRec6[1] == 0.0f) & (fTemp4 != fRec7[1])) ? 0.0009765625f : (((fRec6[1] == 1.0f) & (fTemp4 != fRec8[1])) ? -0.0009765625f : 0.0f)));
			fRec5[0] = fTemp5;
			fRec6[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec6[1] + fTemp5));
			fRec7[0] = (((fRec6[1] >= 1.0f) & (fRec8[1] != fTemp4)) ? fTemp4 : fRec7[1]);
			fRec8[0] = (((fRec6[1] <= 0.0f) & (fRec7[1] != fTemp4)) ? fTemp4 : fRec8[1]);
			float fTemp6 = ((fRec12[1] != 0.0f) ? (((fRec13[1] > 0.0f) & (fRec13[1] < 1.0f)) ? fRec12[1] : 0.0f) : (((fRec13[1] == 0.0f) & (iSlow4 != iRec14[1])) ? 0.0009765625f : (((fRec13[1] == 1.0f) & (iSlow4 != iRec15[1])) ? -0.0009765625f : 0.0f)));
			fRec12[0] = fTemp6;
			fRec13[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec13[1] + fTemp6));
			iRec14[0] = (((fRec13[1] >= 1.0f) & (iRec15[1] != iSlow4)) ? iSlow4 : iRec14[1]);
			iRec15[0] = (((fRec13[1] <= 0.0f) & (iRec14[1] != iSlow4)) ? iSlow4 : iRec15[1]);
			float fTemp7 = float(input0[i0]) + float(input1[i0]);
			float fTemp8 = fSlow6 * fTemp7;
			fVec2[IOTA0 & 8191] = fTemp8;
			float fTemp9 = fRec13[0] * fVec2[(IOTA0 - (iRec15[0] & 8191)) & 8191];
			fRec16[0] = fSlow8 * fRec16[1] + fSlow9 * fRec4[1];
			float fTemp10 = (1.0f - fRec13[0]) * fVec2[(IOTA0 - (iRec14[0] & 8191)) & 8191];
			float fTemp11 = fTemp9 + fSlow7 * fRec16[0] + fTemp10;
			fVec3[IOTA0 & 2047] = fTemp11;
			fRec4[0] = (1.0f - fRec6[0]) * fVec3[(IOTA0 - (int(fRec7[0]) & 2047)) & 2047] + fRec6[0] * fVec3[(IOTA0 - (int(fRec8[0]) & 2047)) & 2047];
			float fTemp12 = float(int(fConst5 + fTemp3));
			float fTemp13 = ((fRec18[1] != 0.0f) ? (((fRec19[1] > 0.0f) & (fRec19[1] < 1.0f)) ? fRec18[1] : 0.0f) : (((fRec19[1] == 0.0f) & (fTemp12 != fRec20[1])) ? 0.0009765625f : (((fRec19[1] == 1.0f) & (fTemp12 != fRec21[1])) ? -0.0009765625f : 0.0f)));
			fRec18[0] = fTemp13;
			fRec19[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec19[1] + fTemp13));
			fRec20[0] = (((fRec19[1] >= 1.0f) & (fRec21[1] != fTemp12)) ? fTemp12 : fRec20[1]);
			fRec21[0] = (((fRec19[1] <= 0.0f) & (fRec20[1] != fTemp12)) ? fTemp12 : fRec21[1]);
			float fTemp14 = fTemp10 + fTemp9;
			fRec22[0] = fSlow8 * fRec22[1] + fSlow9 * fRec17[1];
			float fTemp15 = fTemp14 + fSlow7 * fRec22[0];
			fVec4[IOTA0 & 2047] = fTemp15;
			fRec17[0] = (1.0f - fRec19[0]) * fVec4[(IOTA0 - (int(fRec20[0]) & 2047)) & 2047] + fRec19[0] * fVec4[(IOTA0 - (int(fRec21[0]) & 2047)) & 2047];
			float fTemp16 = float(int(fConst6 + fTemp3));
			float fTemp17 = ((fRec24[1] != 0.0f) ? (((fRec25[1] > 0.0f) & (fRec25[1] < 1.0f)) ? fRec24[1] : 0.0f) : (((fRec25[1] == 0.0f) & (fTemp16 != fRec26[1])) ? 0.0009765625f : (((fRec25[1] == 1.0f) & (fTemp16 != fRec27[1])) ? -0.0009765625f : 0.0f)));
			fRec24[0] = fTemp17;
			fRec25[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec25[1] + fTemp17));
			fRec26[0] = (((fRec25[1] >= 1.0f) & (fRec27[1] != fTemp16)) ? fTemp16 : fRec26[1]);
			fRec27[0] = (((fRec25[1] <= 0.0f) & (fRec26[1] != fTemp16)) ? fTemp16 : fRec27[1]);
			fRec28[0] = fSlow8 * fRec28[1] + fSlow9 * fRec23[1];
			float fTemp18 = fTemp14 + fSlow7 * fRec28[0];
			fVec5[IOTA0 & 2047] = fTemp18;
			fRec23[0] = (1.0f - fRec25[0]) * fVec5[(IOTA0 - (int(fRec26[0]) & 2047)) & 2047] + fRec25[0] * fVec5[(IOTA0 - (int(fRec27[0]) & 2047)) & 2047];
			float fTemp19 = float(int(fConst7 + fTemp3));
			float fTemp20 = ((fRec30[1] != 0.0f) ? (((fRec31[1] > 0.0f) & (fRec31[1] < 1.0f)) ? fRec30[1] : 0.0f) : (((fRec31[1] == 0.0f) & (fTemp19 != fRec32[1])) ? 0.0009765625f : (((fRec31[1] == 1.0f) & (fTemp19 != fRec33[1])) ? -0.0009765625f : 0.0f)));
			fRec30[0] = fTemp20;
			fRec31[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec31[1] + fTemp20));
			fRec32[0] = (((fRec31[1] >= 1.0f) & (fRec33[1] != fTemp19)) ? fTemp19 : fRec32[1]);
			fRec33[0] = (((fRec31[1] <= 0.0f) & (fRec32[1] != fTemp19)) ? fTemp19 : fRec33[1]);
			fRec34[0] = fSlow8 * fRec34[1] + fSlow9 * fRec29[1];
			float fTemp21 = fTemp14 + fSlow7 * fRec34[0];
			fVec6[IOTA0 & 2047] = fTemp21;
			fRec29[0] = (1.0f - fRec31[0]) * fVec6[(IOTA0 - (int(fRec32[0]) & 2047)) & 2047] + fRec31[0] * fVec6[(IOTA0 - (int(fRec33[0]) & 2047)) & 2047];
			float fTemp22 = float(int(fConst8 + fTemp3));
			float fTemp23 = ((fRec36[1] != 0.0f) ? (((fRec37[1] > 0.0f) & (fRec37[1] < 1.0f)) ? fRec36[1] : 0.0f) : (((fRec37[1] == 0.0f) & (fTemp22 != fRec38[1])) ? 0.0009765625f : (((fRec37[1] == 1.0f) & (fTemp22 != fRec39[1])) ? -0.0009765625f : 0.0f)));
			fRec36[0] = fTemp23;
			fRec37[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec37[1] + fTemp23));
			fRec38[0] = (((fRec37[1] >= 1.0f) & (fRec39[1] != fTemp22)) ? fTemp22 : fRec38[1]);
			fRec39[0] = (((fRec37[1] <= 0.0f) & (fRec38[1] != fTemp22)) ? fTemp22 : fRec39[1]);
			fRec40[0] = fSlow8 * fRec40[1] + fSlow9 * fRec35[1];
			float fTemp24 = fTemp14 + fSlow7 * fRec40[0];
			fVec7[IOTA0 & 2047] = fTemp24;
			fRec35[0] = (1.0f - fRec37[0]) * fVec7[(IOTA0 - (int(fRec38[0]) & 2047)) & 2047] + fRec37[0] * fVec7[(IOTA0 - (int(fRec39[0]) & 2047)) & 2047];
			float fTemp25 = float(int(fConst9 + fTemp3));
			float fTemp26 = ((fRec42[1] != 0.0f) ? (((fRec43[1] > 0.0f) & (fRec43[1] < 1.0f)) ? fRec42[1] : 0.0f) : (((fRec43[1] == 0.0f) & (fTemp25 != fRec44[1])) ? 0.0009765625f : (((fRec43[1] == 1.0f) & (fTemp25 != fRec45[1])) ? -0.0009765625f : 0.0f)));
			fRec42[0] = fTemp26;
			fRec43[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec43[1] + fTemp26));
			fRec44[0] = (((fRec43[1] >= 1.0f) & (fRec45[1] != fTemp25)) ? fTemp25 : fRec44[1]);
			fRec45[0] = (((fRec43[1] <= 0.0f) & (fRec44[1] != fTemp25)) ? fTemp25 : fRec45[1]);
			fRec46[0] = fSlow8 * fRec46[1] + fSlow9 * fRec41[1];
			float fTemp27 = fTemp14 + fSlow7 * fRec46[0];
			fVec8[IOTA0 & 2047] = fTemp27;
			fRec41[0] = (1.0f - fRec43[0]) * fVec8[(IOTA0 - (int(fRec44[0]) & 2047)) & 2047] + fRec43[0] * fVec8[(IOTA0 - (int(fRec45[0]) & 2047)) & 2047];
			float fTemp28 = float(int(fConst10 + fTemp3));
			float fTemp29 = ((fRec48[1] != 0.0f) ? (((fRec49[1] > 0.0f) & (fRec49[1] < 1.0f)) ? fRec48[1] : 0.0f) : (((fRec49[1] == 0.0f) & (fTemp28 != fRec50[1])) ? 0.0009765625f : (((fRec49[1] == 1.0f) & (fTemp28 != fRec51[1])) ? -0.0009765625f : 0.0f)));
			fRec48[0] = fTemp29;
			fRec49[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec49[1] + fTemp29));
			fRec50[0] = (((fRec49[1] >= 1.0f) & (fRec51[1] != fTemp28)) ? fTemp28 : fRec50[1]);
			fRec51[0] = (((fRec49[1] <= 0.0f) & (fRec50[1] != fTemp28)) ? fTemp28 : fRec51[1]);
			fRec52[0] = fSlow8 * fRec52[1] + fSlow9 * fRec47[1];
			float fTemp30 = fTemp14 + fSlow7 * fRec52[0];
			fVec9[IOTA0 & 2047] = fTemp30;
			fRec47[0] = (1.0f - fRec49[0]) * fVec9[(IOTA0 - (int(fRec50[0]) & 2047)) & 2047] + fRec49[0] * fVec9[(IOTA0 - (int(fRec51[0]) & 2047)) & 2047];
			float fTemp31 = float(int(fConst11 + fTemp3));
			float fTemp32 = ((fRec54[1] != 0.0f) ? (((fRec55[1] > 0.0f) & (fRec55[1] < 1.0f)) ? fRec54[1] : 0.0f) : (((fRec55[1] == 0.0f) & (fTemp31 != fRec56[1])) ? 0.0009765625f : (((fRec55[1] == 1.0f) & (fTemp31 != fRec57[1])) ? -0.0009765625f : 0.0f)));
			fRec54[0] = fTemp32;
			fRec55[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec55[1] + fTemp32));
			fRec56[0] = (((fRec55[1] >= 1.0f) & (fRec57[1] != fTemp31)) ? fTemp31 : fRec56[1]);
			fRec57[0] = (((fRec55[1] <= 0.0f) & (fRec56[1] != fTemp31)) ? fTemp31 : fRec57[1]);
			fRec58[0] = fSlow8 * fRec58[1] + fSlow9 * fRec53[1];
			float fTemp33 = fTemp14 + fSlow7 * fRec58[0];
			fVec10[IOTA0 & 2047] = fTemp33;
			fRec53[0] = (1.0f - fRec55[0]) * fVec10[(IOTA0 - (int(fRec56[0]) & 2047)) & 2047] + fRec55[0] * fVec10[(IOTA0 - (int(fRec57[0]) & 2047)) & 2047];
			fVec11[IOTA0 & 1023] = fRec4[0] + fRec17[0] + fRec23[0] + fRec29[0] + fRec35[0] + fRec41[0] + fRec47[0] + fRec53[0];
			fRec3[IOTA0 & 1023] = fVec11[(IOTA0 - iConst12) & 1023] - 0.25f * fRec3[(IOTA0 - iConst13) & 1023];
			fRec2[IOTA0 & 1023] = fRec3[(IOTA0 - iConst14) & 1023] - 0.25f * fRec2[(IOTA0 - iConst15) & 1023];
			fRec1[IOTA0 & 2047] = fRec2[(IOTA0 - iConst16) & 1023] - 0.25f * fRec1[(IOTA0 - iConst17) & 2047];
			fRec0[IOTA0 & 2047] = fRec1[(IOTA0 - iConst18) & 2047] - 0.25f * fRec0[(IOTA0 - iConst19) & 2047];
			float fTemp34 = fRec0[IOTA0 & 2047] + fSlow10 * fTemp7;
			output0[i0] = FAUSTFLOAT(fTemp34);
			output1[i0] = FAUSTFLOAT(fTemp34);
			iVec0[1] = iVec0[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			iRec14[1] = iRec14[0];
			iRec15[1] = iRec15[0];
			IOTA0 = IOTA0 + 1;
			fRec16[1] = fRec16[0];
			fRec4[1] = fRec4[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec17[1] = fRec17[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec23[1] = fRec23[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec29[1] = fRec29[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec39[1] = fRec39[0];
			fRec40[1] = fRec40[0];
			fRec35[1] = fRec35[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec41[1] = fRec41[0];
			fRec48[1] = fRec48[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec51[1] = fRec51[0];
			fRec52[1] = fRec52[0];
			fRec47[1] = fRec47[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fRec56[1] = fRec56[0];
			fRec57[1] = fRec57[0];
			fRec58[1] = fRec58[0];
			fRec53[1] = fRec53[0];
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

/******************* END minimal.cpp ****************/


#endif
