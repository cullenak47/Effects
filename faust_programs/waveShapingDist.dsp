
/* A simple waveshaping effect. This is based on Bram de Jong's code from
   musicdsp.org (http://www.musicdsp.org/archive.php?classid=4#41). */

declare name "waveshaper";
declare author "Cullen Toal";
declare description "Waveshaping Distortion Effect";
declare version "1.0";

import("music.lib");

// distortion parameter
dist	= vslider("distortion[style:knob]", 30, 0, 50, 0.1);
// output gain (dB)
gain	= vslider("gain[style:knob][unit:dB]", 3, -20, 20, 0.1);

// the waveshaping function
f(a,x)	= 1/1+exp(a*x);

// gain correction factor to compensate for distortion
g(a)	= 1/sqrt(a+1);

process	= hgroup("", (out, out))
with { out(x) = db2linear(gain)*g(db2linear(dist))*f(db2linear(dist),x); };