/* ------------------------------------------------------------
name: "untitled"
Code generated with Faust 2.79.0 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

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
	
	int iVec3[2];
	int iRec14[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iVec3[l8] = 0;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			iRec14[l9] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec3[0] = 1;
			iRec14[0] = (iVec3[1] + iRec14[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * float(iRec14[0]));
			iVec3[1] = iVec3[0];
			iRec14[1] = iRec14[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int IOTA0;
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	int iConst1;
	int iConst2;
	int iConst3;
	int iConst4;
	int iConst5;
	int iConst6;
	int iConst7;
	int iConst8;
	FAUSTFLOAT fHslider1;
	float fConst9;
	float fRec5[2];
	FAUSTFLOAT fHslider2;
	float fConst10;
	float fVec1[8192];
	FAUSTFLOAT fHslider3;
	float fRec6[2];
	float fRec7[2];
	int iRec8[2];
	int iRec9[2];
	float fVec2[2048];
	FAUSTFLOAT fHslider4;
	float fConst11;
	float fRec15[2];
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fRec16[2];
	FAUSTFLOAT fHslider7;
	float fConst12;
	float fRec10[2];
	float fRec11[2];
	float fRec12[2];
	float fRec13[2];
	float fRec4[2];
	float fRec18[2];
	float fVec4[2048];
	float fConst13;
	float fRec19[2];
	float fRec20[2];
	float fRec21[2];
	float fRec22[2];
	float fRec17[2];
	float fRec24[2];
	float fVec5[2048];
	float fConst14;
	float fRec25[2];
	float fRec26[2];
	float fRec27[2];
	float fRec28[2];
	float fRec23[2];
	float fRec30[2];
	float fVec6[2048];
	float fConst15;
	float fRec31[2];
	float fRec32[2];
	float fRec33[2];
	float fRec34[2];
	float fRec29[2];
	float fRec36[2];
	float fVec7[2048];
	float fConst16;
	float fRec37[2];
	float fRec38[2];
	float fRec39[2];
	float fRec40[2];
	float fRec35[2];
	float fRec42[2];
	float fVec8[2048];
	float fConst17;
	float fRec43[2];
	float fRec44[2];
	float fRec45[2];
	float fRec46[2];
	float fRec41[2];
	float fRec48[2];
	float fVec9[2048];
	float fConst18;
	float fRec49[2];
	float fRec50[2];
	float fRec51[2];
	float fRec52[2];
	float fRec47[2];
	float fRec54[2];
	float fVec10[2048];
	float fConst19;
	float fRec55[2];
	float fRec56[2];
	float fRec57[2];
	float fRec58[2];
	float fRec53[2];
	float fVec11[1024];
	float fRec3[1024];
	float fRec2[1024];
	float fRec1[2048];
	float fRec0[2048];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "untitled.dsp");
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
		m->declare("name", "untitled");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.5.1");
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
		iConst1 = int(0.016303854f * fConst0) & 1023;
		iConst2 = iConst1 + 1;
		iConst3 = int(0.007913833f * fConst0) & 1023;
		iConst4 = iConst3 + 1;
		iConst5 = int(0.000430839f * fConst0) & 1023;
		iConst6 = iConst5 + 1;
		iConst7 = int(0.0029705216f * fConst0) & 1023;
		iConst8 = iConst7 + 1;
		fConst9 = 9.070295e-06f * fConst0;
		fConst10 = 6.349206e-06f * fConst0;
		fConst11 = 1.0f / fConst0;
		fConst12 = 0.036666665f * fConst0;
		fConst13 = 0.035306122f * fConst0;
		fConst14 = 0.033809524f * fConst0;
		fConst15 = 0.0322449f * fConst0;
		fConst16 = 0.030748298f * fConst0;
		fConst17 = 0.028956916f * fConst0;
		fConst18 = 0.026938776f * fConst0;
		fConst19 = 0.025306122f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.2f);
		fHslider1 = FAUSTFLOAT(0.2f);
		fHslider2 = FAUSTFLOAT(0.9f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 8192; l2 = l2 + 1) {
			fVec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec8[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec9[l6] = 0;
		}
		for (int l7 = 0; l7 < 2048; l7 = l7 + 1) {
			fVec2[l7] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec15[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec16[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec10[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fRec11[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec13[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec4[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec18[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2048; l18 = l18 + 1) {
			fVec4[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			fRec19[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec20[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fRec21[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec22[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec17[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fRec24[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2048; l25 = l25 + 1) {
			fVec5[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec25[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			fRec26[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			fRec27[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			fRec28[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			fRec23[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fRec30[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2048; l32 = l32 + 1) {
			fVec6[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec31[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec32[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec33[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			fRec34[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			fRec29[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			fRec36[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 2048; l39 = l39 + 1) {
			fVec7[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fRec37[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec38[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec39[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec40[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec35[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 2; l45 = l45 + 1) {
			fRec42[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 2048; l46 = l46 + 1) {
			fVec8[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 2; l47 = l47 + 1) {
			fRec43[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 2; l48 = l48 + 1) {
			fRec44[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fRec45[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec46[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 2; l51 = l51 + 1) {
			fRec41[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec48[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2048; l53 = l53 + 1) {
			fVec9[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 2; l54 = l54 + 1) {
			fRec49[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 2; l55 = l55 + 1) {
			fRec50[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 2; l56 = l56 + 1) {
			fRec51[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 2; l57 = l57 + 1) {
			fRec52[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fRec47[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec54[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 2048; l60 = l60 + 1) {
			fVec10[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec55[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec56[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 2; l63 = l63 + 1) {
			fRec57[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 2; l64 = l64 + 1) {
			fRec58[l64] = 0.0f;
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
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Room Size", &fHslider2, FAUSTFLOAT(0.9f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Damping", &fHslider1, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Pre Delay", &fHslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(0.001f));
		ui_interface->declare(&fHslider6, "4", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("LFO1 Freq", &fHslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider7, "5", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("LFO1 Depth", &fHslider7, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider4, "6", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("LFO2 Freq", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider5, "7", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("LFO2 Depth", &fHslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "8", "");
		ui_interface->addHorizontalSlider("Dry/Wet", &fHslider0, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = 1.0f - fSlow0;
		float fSlow2 = fConst9 * float(fHslider1);
		float fSlow3 = 1.0f - fSlow2;
		float fSlow4 = fConst10 * float(fHslider2) + 0.7f;
		float fSlow5 = 0.1f * fSlow0;
		int iSlow6 = int(fConst0 * float(fHslider3));
		float fSlow7 = fConst11 * float(fHslider4);
		float fSlow8 = float(fHslider5);
		float fSlow9 = fConst11 * float(fHslider6);
		float fSlow10 = float(fHslider7);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]) + float(input1[i0]);
			iVec0[0] = 1;
			fRec5[0] = fSlow2 * fRec5[1] + fSlow3 * fRec4[1];
			float fTemp1 = fSlow5 * fTemp0;
			fVec1[IOTA0 & 8191] = fTemp1;
			float fTemp2 = ((fRec6[1] != 0.0f) ? (((fRec7[1] > 0.0f) & (fRec7[1] < 1.0f)) ? fRec6[1] : 0.0f) : (((fRec7[1] == 0.0f) & (iSlow6 != iRec8[1])) ? 0.0009765625f : (((fRec7[1] == 1.0f) & (iSlow6 != iRec9[1])) ? -0.0009765625f : 0.0f)));
			fRec6[0] = fTemp2;
			fRec7[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec7[1] + fTemp2));
			iRec8[0] = (((fRec7[1] >= 1.0f) & (iRec9[1] != iSlow6)) ? iSlow6 : iRec8[1]);
			iRec9[0] = (((fRec7[1] <= 0.0f) & (iRec8[1] != iSlow6)) ? iSlow6 : iRec9[1]);
			float fTemp3 = fRec7[0] * fVec1[(IOTA0 - (iRec9[0] & 8191)) & 8191];
			float fTemp4 = (1.0f - fRec7[0]) * fVec1[(IOTA0 - (iRec8[0] & 8191)) & 8191];
			float fTemp5 = fTemp4 + fTemp3;
			float fTemp6 = fTemp5 + fSlow4 * fRec5[0];
			fVec2[IOTA0 & 2047] = fTemp6;
			int iTemp7 = 1 - iVec0[1];
			float fTemp8 = ((iTemp7) ? 0.0f : fSlow7 + fRec15[1]);
			fRec15[0] = fTemp8 - std::floor(fTemp8);
			float fTemp9 = ((iTemp7) ? 0.0f : fSlow9 + fRec16[1]);
			fRec16[0] = fTemp9 - std::floor(fTemp9);
			float fTemp10 = fSlow10 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec16[0]), 65535))] + fSlow8 * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec15[0]), 65535))];
			float fTemp11 = float(int(fConst12 + fTemp10));
			float fTemp12 = ((fRec10[1] != 0.0f) ? (((fRec11[1] > 0.0f) & (fRec11[1] < 1.0f)) ? fRec10[1] : 0.0f) : (((fRec11[1] == 0.0f) & (fTemp11 != fRec12[1])) ? 0.0009765625f : (((fRec11[1] == 1.0f) & (fTemp11 != fRec13[1])) ? -0.0009765625f : 0.0f)));
			fRec10[0] = fTemp12;
			fRec11[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec11[1] + fTemp12));
			fRec12[0] = (((fRec11[1] >= 1.0f) & (fRec13[1] != fTemp11)) ? fTemp11 : fRec12[1]);
			fRec13[0] = (((fRec11[1] <= 0.0f) & (fRec12[1] != fTemp11)) ? fTemp11 : fRec13[1]);
			fRec4[0] = (1.0f - fRec11[0]) * fVec2[(IOTA0 - (int(fRec12[0]) & 2047)) & 2047] + fRec11[0] * fVec2[(IOTA0 - (int(fRec13[0]) & 2047)) & 2047];
			fRec18[0] = fSlow2 * fRec18[1] + fSlow3 * fRec17[1];
			float fTemp13 = fTemp5 + fSlow4 * fRec18[0];
			fVec4[IOTA0 & 2047] = fTemp13;
			float fTemp14 = float(int(fConst13 + fTemp10));
			float fTemp15 = ((fRec19[1] != 0.0f) ? (((fRec20[1] > 0.0f) & (fRec20[1] < 1.0f)) ? fRec19[1] : 0.0f) : (((fRec20[1] == 0.0f) & (fTemp14 != fRec21[1])) ? 0.0009765625f : (((fRec20[1] == 1.0f) & (fTemp14 != fRec22[1])) ? -0.0009765625f : 0.0f)));
			fRec19[0] = fTemp15;
			fRec20[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec20[1] + fTemp15));
			fRec21[0] = (((fRec20[1] >= 1.0f) & (fRec22[1] != fTemp14)) ? fTemp14 : fRec21[1]);
			fRec22[0] = (((fRec20[1] <= 0.0f) & (fRec21[1] != fTemp14)) ? fTemp14 : fRec22[1]);
			fRec17[0] = (1.0f - fRec20[0]) * fVec4[(IOTA0 - (int(fRec21[0]) & 2047)) & 2047] + fRec20[0] * fVec4[(IOTA0 - (int(fRec22[0]) & 2047)) & 2047];
			fRec24[0] = fSlow2 * fRec24[1] + fSlow3 * fRec23[1];
			float fTemp16 = fTemp5 + fSlow4 * fRec24[0];
			fVec5[IOTA0 & 2047] = fTemp16;
			float fTemp17 = float(int(fConst14 + fTemp10));
			float fTemp18 = ((fRec25[1] != 0.0f) ? (((fRec26[1] > 0.0f) & (fRec26[1] < 1.0f)) ? fRec25[1] : 0.0f) : (((fRec26[1] == 0.0f) & (fTemp17 != fRec27[1])) ? 0.0009765625f : (((fRec26[1] == 1.0f) & (fTemp17 != fRec28[1])) ? -0.0009765625f : 0.0f)));
			fRec25[0] = fTemp18;
			fRec26[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec26[1] + fTemp18));
			fRec27[0] = (((fRec26[1] >= 1.0f) & (fRec28[1] != fTemp17)) ? fTemp17 : fRec27[1]);
			fRec28[0] = (((fRec26[1] <= 0.0f) & (fRec27[1] != fTemp17)) ? fTemp17 : fRec28[1]);
			fRec23[0] = (1.0f - fRec26[0]) * fVec5[(IOTA0 - (int(fRec27[0]) & 2047)) & 2047] + fRec26[0] * fVec5[(IOTA0 - (int(fRec28[0]) & 2047)) & 2047];
			fRec30[0] = fSlow2 * fRec30[1] + fSlow3 * fRec29[1];
			float fTemp19 = fTemp5 + fSlow4 * fRec30[0];
			fVec6[IOTA0 & 2047] = fTemp19;
			float fTemp20 = float(int(fConst15 + fTemp10));
			float fTemp21 = ((fRec31[1] != 0.0f) ? (((fRec32[1] > 0.0f) & (fRec32[1] < 1.0f)) ? fRec31[1] : 0.0f) : (((fRec32[1] == 0.0f) & (fTemp20 != fRec33[1])) ? 0.0009765625f : (((fRec32[1] == 1.0f) & (fTemp20 != fRec34[1])) ? -0.0009765625f : 0.0f)));
			fRec31[0] = fTemp21;
			fRec32[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec32[1] + fTemp21));
			fRec33[0] = (((fRec32[1] >= 1.0f) & (fRec34[1] != fTemp20)) ? fTemp20 : fRec33[1]);
			fRec34[0] = (((fRec32[1] <= 0.0f) & (fRec33[1] != fTemp20)) ? fTemp20 : fRec34[1]);
			fRec29[0] = (1.0f - fRec32[0]) * fVec6[(IOTA0 - (int(fRec33[0]) & 2047)) & 2047] + fRec32[0] * fVec6[(IOTA0 - (int(fRec34[0]) & 2047)) & 2047];
			fRec36[0] = fSlow2 * fRec36[1] + fSlow3 * fRec35[1];
			float fTemp22 = fTemp5 + fSlow4 * fRec36[0];
			fVec7[IOTA0 & 2047] = fTemp22;
			float fTemp23 = float(int(fConst16 + fTemp10));
			float fTemp24 = ((fRec37[1] != 0.0f) ? (((fRec38[1] > 0.0f) & (fRec38[1] < 1.0f)) ? fRec37[1] : 0.0f) : (((fRec38[1] == 0.0f) & (fTemp23 != fRec39[1])) ? 0.0009765625f : (((fRec38[1] == 1.0f) & (fTemp23 != fRec40[1])) ? -0.0009765625f : 0.0f)));
			fRec37[0] = fTemp24;
			fRec38[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec38[1] + fTemp24));
			fRec39[0] = (((fRec38[1] >= 1.0f) & (fRec40[1] != fTemp23)) ? fTemp23 : fRec39[1]);
			fRec40[0] = (((fRec38[1] <= 0.0f) & (fRec39[1] != fTemp23)) ? fTemp23 : fRec40[1]);
			fRec35[0] = (1.0f - fRec38[0]) * fVec7[(IOTA0 - (int(fRec39[0]) & 2047)) & 2047] + fRec38[0] * fVec7[(IOTA0 - (int(fRec40[0]) & 2047)) & 2047];
			fRec42[0] = fSlow2 * fRec42[1] + fSlow3 * fRec41[1];
			float fTemp25 = fTemp5 + fSlow4 * fRec42[0];
			fVec8[IOTA0 & 2047] = fTemp25;
			float fTemp26 = float(int(fConst17 + fTemp10));
			float fTemp27 = ((fRec43[1] != 0.0f) ? (((fRec44[1] > 0.0f) & (fRec44[1] < 1.0f)) ? fRec43[1] : 0.0f) : (((fRec44[1] == 0.0f) & (fTemp26 != fRec45[1])) ? 0.0009765625f : (((fRec44[1] == 1.0f) & (fTemp26 != fRec46[1])) ? -0.0009765625f : 0.0f)));
			fRec43[0] = fTemp27;
			fRec44[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec44[1] + fTemp27));
			fRec45[0] = (((fRec44[1] >= 1.0f) & (fRec46[1] != fTemp26)) ? fTemp26 : fRec45[1]);
			fRec46[0] = (((fRec44[1] <= 0.0f) & (fRec45[1] != fTemp26)) ? fTemp26 : fRec46[1]);
			fRec41[0] = (1.0f - fRec44[0]) * fVec8[(IOTA0 - (int(fRec45[0]) & 2047)) & 2047] + fRec44[0] * fVec8[(IOTA0 - (int(fRec46[0]) & 2047)) & 2047];
			fRec48[0] = fSlow2 * fRec48[1] + fSlow3 * fRec47[1];
			float fTemp28 = fTemp5 + fSlow4 * fRec48[0];
			fVec9[IOTA0 & 2047] = fTemp28;
			float fTemp29 = float(int(fConst18 + fTemp10));
			float fTemp30 = ((fRec49[1] != 0.0f) ? (((fRec50[1] > 0.0f) & (fRec50[1] < 1.0f)) ? fRec49[1] : 0.0f) : (((fRec50[1] == 0.0f) & (fTemp29 != fRec51[1])) ? 0.0009765625f : (((fRec50[1] == 1.0f) & (fTemp29 != fRec52[1])) ? -0.0009765625f : 0.0f)));
			fRec49[0] = fTemp30;
			fRec50[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec50[1] + fTemp30));
			fRec51[0] = (((fRec50[1] >= 1.0f) & (fRec52[1] != fTemp29)) ? fTemp29 : fRec51[1]);
			fRec52[0] = (((fRec50[1] <= 0.0f) & (fRec51[1] != fTemp29)) ? fTemp29 : fRec52[1]);
			fRec47[0] = (1.0f - fRec50[0]) * fVec9[(IOTA0 - (int(fRec51[0]) & 2047)) & 2047] + fRec50[0] * fVec9[(IOTA0 - (int(fRec52[0]) & 2047)) & 2047];
			fRec54[0] = fSlow2 * fRec54[1] + fSlow3 * fRec53[1];
			float fTemp31 = fTemp3 + fSlow4 * fRec54[0] + fTemp4;
			fVec10[IOTA0 & 2047] = fTemp31;
			float fTemp32 = float(int(fConst19 + fTemp10));
			float fTemp33 = ((fRec55[1] != 0.0f) ? (((fRec56[1] > 0.0f) & (fRec56[1] < 1.0f)) ? fRec55[1] : 0.0f) : (((fRec56[1] == 0.0f) & (fTemp32 != fRec57[1])) ? 0.0009765625f : (((fRec56[1] == 1.0f) & (fTemp32 != fRec58[1])) ? -0.0009765625f : 0.0f)));
			fRec55[0] = fTemp33;
			fRec56[0] = std::max<float>(0.0f, std::min<float>(1.0f, fRec56[1] + fTemp33));
			fRec57[0] = (((fRec56[1] >= 1.0f) & (fRec58[1] != fTemp32)) ? fTemp32 : fRec57[1]);
			fRec58[0] = (((fRec56[1] <= 0.0f) & (fRec57[1] != fTemp32)) ? fTemp32 : fRec58[1]);
			fRec53[0] = (1.0f - fRec56[0]) * fVec10[(IOTA0 - (int(fRec57[0]) & 2047)) & 2047] + fRec56[0] * fVec10[(IOTA0 - (int(fRec58[0]) & 2047)) & 2047];
			fVec11[IOTA0 & 1023] = fRec53[0] + fRec47[0] + fRec41[0] + fRec35[0] + fRec29[0] + fRec23[0] + fRec17[0] + fRec4[0];
			fRec3[IOTA0 & 1023] = fVec11[(IOTA0 - iConst7) & 1023] - 0.25f * fRec3[(IOTA0 - iConst8) & 1023];
			fRec2[IOTA0 & 1023] = fRec3[(IOTA0 - iConst5) & 1023] - 0.25f * fRec2[(IOTA0 - iConst6) & 1023];
			fRec1[IOTA0 & 2047] = fRec2[(IOTA0 - iConst3) & 1023] - 0.25f * fRec1[(IOTA0 - iConst4) & 2047];
			fRec0[IOTA0 & 2047] = fRec1[(IOTA0 - iConst1) & 2047] - 0.25f * fRec0[(IOTA0 - iConst2) & 2047];
			float fTemp34 = fRec0[IOTA0 & 2047] + fSlow1 * fTemp0;
			output0[i0] = FAUSTFLOAT(fTemp34);
			output1[i0] = FAUSTFLOAT(fTemp34);
			IOTA0 = IOTA0 + 1;
			iVec0[1] = iVec0[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[1] = fRec7[0];
			iRec8[1] = iRec8[0];
			iRec9[1] = iRec9[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
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

#endif
