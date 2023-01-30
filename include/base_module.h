/*
    This class defines the base module in which all other modules would need to integrate with
*/
#ifndef _BASE_MODULE_h
#define _BASE_MODULE_h
/**
 * @brief Enumeration of possible statuses that the module can return
 * @note SUCCESS - The module has completed function
 * @note FAILED - The module has encountered an error
 */
enum class Status
{
    SUCCESS,
    FAILED
}; 

class BaseModule
{
public:
    /**
     * @brief Setup function for the BaseModule.
     * @note This function should be overridden by derived classes to perform any necessary setup for the module
     * @note This function should NOT be blocking
     * @retval Status - Enumeration indicating if the setup was successful or not
     */
    virtual Status setup();
    /**
     * @brief Loop function for the BaseModule.
     * @note This function should be overridden by derived classes to perform any necessary tasks for the module
     * @note This function should NOT be blocking
     * @retval Status - Enumeration indicating if the loop was successful or not
     */
    virtual Status loop();
    /**
     * @brief Cleanup function for the BaseModule.
     * @note This function should be overridden by derived classes to perform any necessary cleanup for the module
     * @note This function should NOT be blocking
     * @retval Status - Enumeration indicating if the cleanup was successful or not
     */
    virtual Status cleanup();
};
#endif //_BASE_MODULE_h