//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//

#include "XPLMUtilities.h"

#include "camera.h"
#include <stddef.h>

static XPLMCommandButtonID camera_change_btn = xplm_joy_v_fr1;

namespace atcp::plugins::xplane::camera
{

void activate_freeview()
{
    XPLMCommandButtonPress(camera_change_btn);
    XPLMCommandButtonRelease(camera_change_btn);	
}

void set_camera_control(XPLMCameraControl_f  control_fn)
{
    XPLMControlCamera(xplm_ControlCameraUntilViewChanges, control_fn, NULL);
}

int CameraControls::external_follower(XPLMCameraPosition_t*  outCameraPosition,   
                                      int                    inIsLosingControl,    
                                      void *                 inRefcon)
{
    // Positioning ourselves 10m ahead of the AC center of mass
    float Z_OFFSET = 10.0;

    // Setting camera position following the AC
    outCameraPosition->x            = XPLMGetDataf(position::DREF_LOCAL_X);
    outCameraPosition->y            = XPLMGetDataf(position::DREF_LOCAL_Y);
    outCameraPosition->z            = XPLMGetDataf(position::DREF_LOCAL_Z) + Z_OFFSET;
    outCameraPosition->pitch        = XPLMGetDataf(position::DREF_TRUE_PITCH);
    outCameraPosition->heading      = XPLMGetDataf(position::DREF_TRUE_HEADING);
    outCameraPosition->roll         = XPLMGetDataf(position::DREF_TRUE_ROLL);		

    // Returning one means we still want to keep controlling the camera
    return 1;
}
}
