// greeting_plugin.cpp
#include "plugin_interface.h"
#include <iostream>

class GreetingPlugin : public PluginInterface {
public:
    std::string getName() const override { return "Greeting Plugin"; }

    void execute() override {
        std::cout << "Hello from the Greeting Plugin!" << std::endl;
    }
};

extern "C" {
    PluginInterface* createPlugin() {
        return new GreetingPlugin();
    }

    void destroyPlugin(PluginInterface* p) {
        delete p;
    }
}