// plugin_interface.h
#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <string>

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual std::string getName() const = 0;
    virtual void execute() = 0;
};

// 插件创建和销毁函数的类型定义
extern "C" {
    typedef PluginInterface* (*CreatePluginFunc)();
    typedef void (*DestroyPluginFunc)(PluginInterface*);
}

#endif // PLUGIN_INTERFACE_H