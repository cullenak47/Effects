import("filter.lib");
import("stdfaust.lib");

// ---------------------------------------
// MAIN REVERB FUNCTION (DUAL LFO)
// ---------------------------------------

reverb(fb1, fb2, damp, pdTime, modFreq1, modDepth1, modFreq2, modDepth2) =
    _ : sdelay(8192, 1024, int(pdTime))
      <: par(i,8, lpcf(combtuningL(i), fb1, damp))
       :> seq(i,4,apcf(allpasstuningL(i), -fb2)) 
with {
    // ============== DUAL MODULATION ==============
    modSignal = 
        (os.osc(modFreq1) * modDepth1) +  // LFO 1
        (os.osc(modFreq2) * modDepth2);   // LFO 2

    // Low-pass Feedback Comb Filter
    lpcf(dt, fb, damp) =
        (+:sdelay(2048, 1024, float(dt))) ~ (*(1 - damp) : (+ ~ *(damp)) : *(fb));

    // allpass filter, where a is the feedback coefficient
    apcf(dt, a) = 
        ( ( *(a), delay(1024, dt) ) : + )
        ~ ( *( -a ) : delay(1024, dt) );


    origSR  = 44100;
    cTuning = (1116,1188,1277,1356,1422,1491,1557,1617);
    aTuning = (131, 19, 349, 719);

    combtuningL(i) = 
        take(i+1, cTuning) * SR/origSR
        : +(modSignal)
        : int;

    allpasstuningL(i) = 
        take(i+1, aTuning)*SR/origSR : int;
};

// ---------------------------------------
// UPDATED UI WITH DUAL MODULATION CONTROLS
// ---------------------------------------
reverbDemo = _,_
    <: (
        *(g)*fixedgain
        : reverb(combfeed, allpassfeed, damping, preDelay, 
                modFreq1, modDepth1, modFreq2, modDepth2)
      ),
       *(1 - g)
    :> _
with {
    // Original constants remain unchanged
    origSR     = 44100;
    scaleroom  = 0.28;
    offsetroom = 0.7;
    allpassfeed= -0.5;
    scaledamp  = 0.4;
    fixedgain  = 0.1;

    // UI groups
    mainGroup(x)  = vgroup("Reverb", x);
    knobsGroup(x) = mainGroup(hgroup("[0]", x));

    // Existing controls
    combfeed  = knobsGroup(hslider("[0]Room Size [style:knob]",0.9,0,1,0.01) 
                  * scaleroom*SR/origSR + offsetroom);

    damping   = knobsGroup(hslider("[1]Damping [style:knob]",0.2,0,1,0.01) 
                  * scaledamp*SR/origSR);

    preDelay  = knobsGroup(hslider("[3]Pre Delay [style:knob]",0,0,0.1,0.001) * SR);

    // Dual modulation controls
    modFreq1  = knobsGroup(hslider("[4]LFO1 Freq [style:knob]",0,0,5,0.01));
    modDepth1 = knobsGroup(hslider("[5]LFO1 Depth [style:knob]",0,0,100,1));
    modFreq2  = knobsGroup(hslider("[6]LFO2 Freq [style:knob]",0,0,5,0.01));
    modDepth2 = knobsGroup(hslider("[7]LFO2 Depth [style:knob]",0,0,100,1));

    // Dry/wet remains in main group
    g = mainGroup(hslider("[8]Dry/Wet",0.2,0,1,0.01));
};

process = +<:reverbDemo, reverbDemo;
