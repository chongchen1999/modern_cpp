// main.cpp
#include "plugin_interface.h"
#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::vector<std::string> pluginPaths = {"./libgreeting_plugin.so",
                                            "./libcalculator_plugin.so"};

    std::vector<std::unique_ptr<PluginInterface>> plugins;

    for (const auto& path : pluginPaths) {
        // 加载动态库
        void* handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot load library: " << dlerror() << std::endl;
            continue;
        }

        // 获取创建和销毁函数
        auto createFunc = (CreatePluginFunc)dlsym(handle, "createPlugin");
        auto destroyFunc = (DestroyPluginFunc)dlsym(handle, "destroyPlugin");

        if (!createFunc || !destroyFunc) {
            std::cerr << "Cannot load symbols: " << dlerror() << std::endl;
            dlclose(handle);
            continue;
        }

        // 创建插件实例
        PluginInterface* plugin = createFunc();
        plugins.emplace_back(plugin);

        // 使用插件
        std::cout << "Loaded plugin: " << plugin->getName() << std::endl;
        plugin->execute();

        // 注意：这里不关闭handle，因为插件还在使用
        // 实际应用中需要更复杂的内存管理
    }

    return 0;
}