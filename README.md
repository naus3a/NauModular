
# NauModular VCV plugin

This is my personal collection of modules for [VCV Rack](https://vcvrack.com/): feel free to use them and modify them as you wish. If you find them useful, feel free to get me a beer.

### Tension
![alt_text](https://raw.githubusercontent.com/naus3a/NauModular/master/tension.png "tension")
**Tension** is a fixed voltage generator: you turn the knob, you change the voltage. Useful when playing with logic chains or if you need to power up a virtual lamp ;) .

### Function
![alt_text](https://raw.githubusercontent.com/naus3a/NauModular/master/function.png "function")
**Function** is a function generator; it outputs the 3 conic section functions you learned in high school: ellipse, parabola and hyperbola. Input voltage acts as the x variable, while the knob is a constant parameter.

### Perlin
![alt_text](https://raw.githubusercontent.com/naus3a/NauModular/master/perlin.png "perlin")
**Perlin** is a [Perlin noise](https://en.wikipedia.org/wiki/Perlin_noise) generator. 

The *speed knob* controls how much nervous the noise is. On its side you have a CV control input and a smaller knob to balance the final speed between the main knob's value and the CV input.

The *amp knob* controls noise amplitude. On its side threre's a CV control input and a balancing knob, just like for the speed control.

The lower 4 knobs are a *frequency mixer*: the module constantly calculates 4 noise octaves and each of these knobs controls how much of a specific octaves goes into the final mix.

The 4 outputs positioned in a square shape are *single octave outputs*; they are in the same order as the frequency mixer knobs: the top left one outputs the slowest noise, the bottom right one outputs the fastest noise.

The lowest, central output is the *mix output*, giving you a mix of the noise octaves based on your frequency mixer settings.

### S&H(it)
![alt_text](https://raw.githubusercontent.com/naus3a/NauModular/master/shit.png "S&Hit")
**S&H(it)** is a sampler and hold module. The *time knob* controls how often it samples the input signal; the *divider knob* scales the other knob's value, so yu can range from very quick lo-fi sampling to >1s periods;

