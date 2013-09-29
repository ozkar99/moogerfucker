moogerfucker
============

Square Wave Arduino Synthetizer

### Introduction:

100% Digital, aside from input/output no VCO or anything fancy.  
Just simple square waves.

### Requeriments:

1 Arduino  
4 10k Potenciometers  
1 Buzzer

### Wiring:

<image here>


#### Analog Inputs:
```

0 -> This potenciometer controls the tones (C,D,E,F,G,A,B) it acts as a discrete potenciometer.  

1 -> This potenciometer controls the octave number, also in a discrete manner. (from 2 to 7 according to the scientific pitch notation)

2 -> Este potenciómeter controls the pitch  of the tone in a continuous manner. (200Hz Range)

3 -> This potenciometer controls the time of wait between the pulsations to the buzzer/speaker.
```

#### Digital Out (pin 8):
`This is the buzzer/speaker, its our output.`



### Resources:

http://en.wikipedia.org/wiki/Scientific_pitch_notation  
http://arduino.cc/en/Tutorial/Tone

### Explanation:
We start with a table with our initial tonesfrqeuencies. (0 in the scientific pitch notation table)  


16, 18, 20, 22, 25, 28, 31  
C,  D,  E,  F,  G,  A,  B  
(This is what potenciometer 0 does)

Consider a certain tone, with its initial frequency being X.  

To calculate its central frequency one would do: X *(2^4) where 4 is the central tone.

If we want to go up a octave from there, we do a square on that frequency.  (X^2)  
If we want to go down a octave we take the square root of that frequency. (X^1/2)  
(Tis is what potenciometer 1 does)

Now the tricky part is the shift, we want to be able to have all the range so we can reach the semi-tones  
and that way have the full range of the frequencies, we accomplish that like this:  

We define a range that we can substract or add to our basic tone frequency (X), this range is X/4  
why the 4? well, with 4 we go all the way down to a semitone down, and all the way up to a semitone up.  

Meaning the range is actually: 
X - X/4 To  X+(X/4)*2  

This will give us the maximum freqency and be able to pull all the tones/semitones from here.  
(This is what potenciometer 2 does)  


The wait between pulsations its a simple wait between 0 and 250ms.  
(This is what potenciometer 3 does)
