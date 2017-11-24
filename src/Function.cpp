#include "NauModular.hpp"

struct Function : Module{
   enum ParamIds {
	A_PARAM,
	NUM_PARAMS
    };
    enum InputIds {
	X_INPUT,
    	NUM_INPUTS
    }; 	
    enum OutputIds{
	ELLIPSE_OUTPUT,
	PARABOLA_OUTPUT,
	HYPERBOLA_OUTPUT,
	NUM_OUTPUTS
    };
    enum LightIds {
    	NUM_LIGHTS
    };

    Function() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS){}

    void step() override;
};

void Function::step(){
    float v = inputs[X_INPUT].value;

    float a = params[A_PARAM].value;

    outputs[ELLIPSE_OUTPUT].value = sqrt((a*a)-(v*v));
    outputs[HYPERBOLA_OUTPUT].value = a/v;
    outputs[PARABOLA_OUTPUT].value = v*v*a;
}

FunctionWidget::FunctionWidget(){
    Function * module = new Function();
    setModule(module);
    box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

    {
	SVGPanel *panel = new SVGPanel();
	panel->box.size = box.size;
	panel->setBackground(SVG::load(assetPlugin(plugin, "res/Function.svg")));
	addChild(panel);
    }

    addChild(createScrew<ScrewSilver>(Vec(15, 0)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
    addChild(createScrew<ScrewSilver>(Vec(15, 365)));
    addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));
   
    addParam(createParam<Davies1900hBlackKnob>(Vec(50, 87), module, Function::A_PARAM, -5.0, 5.0, 0.0));
   
    addInput(createInput<PJ301MPort>(Vec(15, 87), module, Function::X_INPUT));

    addOutput(createOutput<PJ301MPort>(Vec(15,150), module, Function::HYPERBOLA_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(15,220), module, Function::PARABOLA_OUTPUT));
    addOutput(createOutput<PJ301MPort>(Vec(15,300), module, Function::ELLIPSE_OUTPUT));
};
