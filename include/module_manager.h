/**
 * @file ModuleManager.h
 *
 * @brief This class manages the lifecycle of all modules.
 * It is responsible for initializing and running each module.
 *
 * @author Michael Wu
 *
 * @date 1/29/2023
 */

#ifndef _MODULE_MANAGER_H
#define _MODULE_MANAGER_H

#include <Arduino.h>
// https://stackoverflow.com/questions/41093090/esp8266-error-macro-min-passed-3-arguments-but-takes-just-2
#undef max
#undef min
#include <vector>
#include "base_module.h"

/**
 * @brief The class that manages the lifecycle of all modules.
 */
class ModuleManager
{
public:
    /**
     * @brief Constructs the ModuleManager.
     */
    ModuleManager();

    /**
     * @brief This function loops over all modules and calls their loop() functions.
     *
     * @return Returns the status of the last executed module's loop() function.
     */
    Status loop();

    /**
     * @brief This function initializes a module by calling its setup() function.
     *
     * @param module The module to be initialized.
     *
     * @return Returns the status of the module's setup() function.
     */
    Status setupModule(BaseModule *module);

private:
    /**
     * @brief The list of all modules managed by this class.
     */
    std::vector<BaseModule *> modules;
};

#endif //_MODULE_MANAGER_H