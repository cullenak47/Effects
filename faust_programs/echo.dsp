import("stdfaust.lib");

echo = _, vgroup("Echo",+~(@(delLength-1) :  *(feedback))) 
with{
    duration = hslider("[0]Duration", 500, 1, 1000, 1)*0.001;
    feedback = hslider("[1]Feedback", 0.5, 0,1, 0.01);
    delLength = ma.SR*duration;
} : select2(s);

s = nentry("Selector",0,0,1,1) : int;



process = echo;