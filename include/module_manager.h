
#ifndef _MODULE_MANAGER_H
#define _MODULE_MANAGER_H
#include <Arduino.h>
// https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2
#undef max
#undef min
#include <vector>
#include "base_module.h"

class ModuleManager
{
public:
    ModuleManager();
    Status loop();
    Status setupModule(BaseModule *module);

private:
    std::vector<BaseModule *> modules;
};
#endif //_MODULE_MANAGER_H
