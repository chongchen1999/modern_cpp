// calculator_plugin.cpp
#include "plugin_interface.h"
#include <iostream>

class CalculatorPlugin : public PluginInterface {
public:
    std::string getName() const override { return "Calculator Plugin"; }

    void execute() override { std::cout << "5 + 7 = " << (5 + 7) << std::endl; }
};

extern "C" {
    PluginInterface* createPlugin() {
        return new CalculatorPlugin();
    }

    void destroyPlugin(PluginInterface* p) {
        delete p;
    }
}