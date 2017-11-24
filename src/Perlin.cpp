#include "NauModular.hpp"

#define FASTFLOOR(x) ( ((x)>0) ? ((int)x) : (((int)x)-1) )

struct Perlin : Module{
    enum ParamIds {
    	SPEED_PARAM,
	SPEED_PCT_PARAM,
	MULT_PARAM,
	MULT_PCT_PARAM,
    	NUM_PARAMS
    };
    enum InputIds {
    	SPEED_INPUT,
	MULT_INPUT,
    	NUM_INPUTS
    };
    enum OutputIds {
    	NOISE_OUTPUT,
    	NUM_OUTPUTS
    };
    enum LightIds {
	NUM_LIGHTS
    };

    Perlin() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS){}
    void step() override;

    float grad(int hash, float x);
    float getNoise(float x);

    float noisePos = 0.0;

    unsigned char perm[512] = {151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
    151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 
    };
};

float Perlin::grad(int hash, float x){
    int h = hash & 15;
    float grad  =1.0+(h&7);
    if(h&8)grad=-grad;
    return (grad*x);
}

float Perlin::getNoise(float x){
    int i0 = FASTFLOOR(x);
    int i1 = i0+1;
    float x0 = x-i0;
    float x1 = x0-1.0;
    float t1 = 1.0 - x1*x1;
    float n0;
    float n1;
    float t0 = 1.0 - x0*x0;
    t0 *= t0;
    n0 = t0*t0*grad(perm[i0 & 0xff], x0);
    t1 *= t1;
    n1 = t1*t1*grad(perm[i1 & 0xff], x1);
    return 0.25 * (n0+n1);
}

void Perlin::step(){
    float noiseSpd = params[SPEED_PARAM].value;
    if(inputs[SPEED_INPUT].value!=0){
	noiseSpd = inputs[SPEED_INPUT].value/12.0*0.1 * params[SPEED_PCT_PARAM].value + noiseSpd*(1.0-params[SPEED_PCT_PARAM].value);
    }
    float n = getNoise(getNoise(noisePos));
    float m = params[MULT_PARAM].value;
    if(inputs[MULT_INPUT].value!=0){
	m *= inputs[MULT_INPUT].value/12.0 * (1.0+params[MULT_PCT_PARAM].value);
    }
    n *= m;
    outputs[NOISE_OUTPUT].value = n;

    noisePos += noiseSpd;
}

PerlinWidget::PerlinWidget(){
    Perlin *module = new Perlin();
    setModule(module);
    box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

    {
    	SVGPanel *panel = new SVGPanel();
    	panel->box.size = box.size;
    	panel->setBackground(SVG::load(assetPlugin(plugin, "res/Perlin.svg")));
    	addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(15, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
    addChild(createScrew<ScrewSilver>(Vec(15, 365)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));
    
    float minSpd = 0.00001;
    float maxSpd = 0.015;
    float startSpd = (maxSpd-minSpd)/2 + minSpd;
    addParam(createParam<Davies1900hBlackKnob>(Vec(10, 87), module, Perlin::SPEED_PARAM, minSpd, maxSpd, startSpd));
    addParam(createParam<RoundSmallBlackKnob>(Vec(55, 100), module, Perlin::SPEED_PCT_PARAM, 0.0, 1.0, 0.5)); 

    addParam(createParam<Davies1900hBlackKnob>(Vec(10, 150), module, Perlin::MULT_PARAM, 1.0, 10.0, 1.0));
    addParam(createParam<RoundSmallBlackKnob>(Vec(55, 167), module, Perlin::MULT_PCT_PARAM, 0.0, 1.0, 0.5));


    addInput(createInput<PJ301MPort>(Vec(55, 75), module, Perlin::SPEED_INPUT));
    addInput(createInput<PJ301MPort>(Vec(55, 140), module, Perlin::MULT_INPUT));

    addOutput(createOutput<PJ301MPort>(Vec(33, 275), module, Perlin::NOISE_OUTPUT));
}
