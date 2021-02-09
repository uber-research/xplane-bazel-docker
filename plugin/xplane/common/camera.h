//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//
#pragma once

#include "position.h"
#include "XPLMCamera.h"

namespace atcp::plugins::xplane::camera
{
/**
 * @brief Moves from cockpit view to freeview
 * 
 */
void activate_freeview();

/**
 * @brief Sets the camera control to a custom callback
 * 
 * @param control_fn Function that controls the camera
 */
void set_camera_control(XPLMCameraControl_f  control_fn);

/**
 * @brief Namespace class for static camera control callbacks
 * 
 */
class CameraControls
{
    public:
    /**
     * @brief Predefined callback that moves together with the AC
     * 
     * @param outCameraPosition 
     * @param inIsLosingControl 
     * @param inRefcon 
     * @return int 
     */
    static int external_follower(XPLMCameraPosition_t*   outCameraPosition,   
                                 int                     inIsLosingControl,    
                                 void *                  inRefcon);
};
}
