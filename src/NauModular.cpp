#include "NauModular.hpp"

Plugin * plugin;

void init(rack::Plugin * p){
    plugin = p;
    p->slug = "NauModular";
#ifdef VERSION
    p->version = TOSTRING(VERSION);
#endif
    p->website = "http://naus3a.ml";
    p->manual = "http://naus3a.ml";

    p->addModel(createModel<TensionWidget>("NauModular", 
					    "Tension", 
					    "Fixed voltage generator",
					    OSCILLATOR_TAG));
}
