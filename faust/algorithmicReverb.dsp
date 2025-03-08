import("music.lib");
import("filter.lib");
import("stdfaust.lib");

// ---------------------------------------
// MAIN REVERB FUNCTION
// ---------------------------------------
reverb(fb1, fb2, damp, pdTime, modFreq, modDepth) =
    // Insert the predelay here:
    _ : sdelay(8192, 1024, int(pdTime))   //smooth delay to avoid zipper noise (change if causing latency)        
      <: par(i,8, lpcf(combtuningL(i), fb1, damp))
       :> seq(i,4, apcf(1024, allpasstuningL(i), fb2))
with {
    // Lowpass-comb
    lpcf(dt, fb, damp) =
        (+:sdelay(2048, 1024, float(dt)))  // Smooth delay to avoid zipper noise when modulating dt
         ~ (*(1 - damp) : (+ ~ *(damp)) : *(fb));

    // Allpass-comb
    apcf(maxDelay, dt, fb) =
        (+:delay(maxDelay, dt)) 
         ~ *(-fb);

    // Tuning arrays
    origSR  = 44100;
    cTuning = (1116,1188,1277,1356,1422,1491,1557,1617);
    aTuning = (131, 19, 349, 719);

    // The LFO signal, scaled by 'modDepth'
    // 'modFreq' is in Hz, so 'os.osc(modFreq)' is a sine wave in [-1,1].
    // Multiply by 'modDepth' to get the modulation amplitude in samples.
    modSignal = os.osc(modFreq) * modDepth;

    // Our comb tuning function, with base shift plus LFO offset
    combtuningL(i) = 
        take(i+1, cTuning) * SR/origSR  // scale for current sample rate
        : +(modSignal)      // add the static shift + LFO
        : int;                          // then truncate to integer

    // The allpass tuning remains unchanged
    allpasstuningL(i) = 
        take(i+1, aTuning)*SR/origSR : int;
};


// ---------------------------------------
// DEMO
// ---------------------------------------
reverbDemo = _,_
    <: (
        // Send into the reverb
        *(g)*fixedgain
        : reverb(combfeed, allpassfeed, damping, preDelay, modFreq, modDepth)
      ),
       // Dry/Wet
       *(1 - g)
    :> _
with {
    origSR     = 44100;
    scaleroom  = 0.28;
    offsetroom = 0.7;
    allpassfeed= 0.2;
    scaledamp  = 0.4;
    fixedgain  = 0.1;

    // Organize the UI
    mainGroup(x)  = vgroup("Reverb", x);
    knobsGroup(x) = mainGroup(hgroup("[0]", x));

    // Room Size slider
    combfeed  = knobsGroup(
       hslider("[0]Room Size [style:knob]",0.9,0,1,0.01)
       * scaleroom*SR/origSR + offsetroom
    );

    // Damping slider
    damping   = knobsGroup(
       hslider("[1]Damping [style:knob]",0.2,0,1,0.01)
       * scaledamp*SR/origSR
    );

    // PreDelay slider (0 to 0.1 seconds)
    preDelay = knobsGroup(
       hslider("[3]Pre Delay [style:knob]",0.02,0,0.1,0.001) 
       * SR
    );

    // === NEW: Modulation sliders ===
    // LFO frequency (in Hz)
    modFreq = knobsGroup(
       hslider("[4]Mod Frequency [style:knob]",0.2,0,5,0.01)
    );

    // LFO depth (in samples)
    modDepth = knobsGroup(
       hslider("[5]Mod Depth [style:knob]",2,0,100,1)
    );

    // Dry/Wet slider
    g = mainGroup(
       hslider("[6]Dry/Wet",0.4,0,1,0.01)
    );
};

process = reverbDemo;
