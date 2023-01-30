#include "module_manager.h"

ModuleManager::ModuleManager(uint32_t num_modules)
{
    this->num_modules = num_modules;
    this->modules_count = 0;
}

Status ModuleManager::loop()
{
    for (BaseModule *module : this->modules) {
        module->loop();
    }
    return Status::SUCCESS;
}

Status ModuleManager::setupModule(BaseModule *module)
{
    if (this->modules_count >= this->num_modules)
    {
        return Status::FAILED;
    }
    module->setup();
    modules.push_back(module);
    this->modules_count ++;

    return Status::SUCCESS;
}