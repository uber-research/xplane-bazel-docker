//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//

#include "plugin.h"

#include "src/plugins/xplane/common/camera.h"
#include "src/plugins/xplane/common/position.h"
#include "src/plugins/xplane/common/graphics.h"

#include "XPLMDataAccess.h"
#include "XPLMDefs.h"
#include "XPLMProcessing.h"

#include <experimental/filesystem>
#include <string.h>

namespace
{
constexpr auto plugin_name    = "atcp-dream-data-collector";
constexpr auto plugin_desc    = "A Plugin to create dataset for the ATCP DREAM project";
constexpr auto plugin_package = "com.uber.atcp_dream_data_collector";
constexpr double START_ALTITUDE_M = 1000.0;

// XPlane callback system forces us to use global variables
static PluginCtx ctx;

float move_ac(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop,
                            int inCounter, void *inRefcon)
{
    if (!ctx.initialized){
        // Free view camera, custom follower control
        camera::activate_freeview();
        camera::set_camera_control(camera::CameraControls::external_follower);

        // Initialize altitude, overrides XPlane's control loop
        position::move_ac_to(START_ALTITUDE_M);
        position::deactivate_flightloop();

        ctx.initialized = true;
    }

    // As an example, divide altitude by 2 every second
    position::move_ac_to(XPLMGetDataf(position::DREF_LOCAL_Y) / 2.0);
    ctx.save_frame_ctx.should_shoot = true;

    // Returning 0 means we want to trigger this callback at next iteration
    // Returning t > 0 means we want to trigger this callback in t seconds
    return 1.0;
}
}

PLUGIN_API int XPluginStart(char * outName, char * outSig, char * outDesc)
{
    strcpy(outName, plugin_name);
    strcpy(outSig,  plugin_package);
    strcpy(outDesc, plugin_desc);

    // Setting output directory to env OUTDIR if set else working directory
    using std::experimental::filesystem::path;
    auto env = std::getenv("OUTDIR");
    ctx.save_frame_ctx.outdir = path(env ? env : ".");

    // Register our hook on the flight loop to position the plane
    XPLMRegisterFlightLoopCallback(move_ac, -1, NULL);

    // Register our hook on the draw phase to capture the screen
    // Somehow xplm_Phase_LastScene is the only phase I get to spit out
    // something. (TODO: investigate previous phases)
    XPLMRegisterDrawCallback(graphics::DrawCallbacks::save_frame_cb,
                             xplm_Phase_LastScene, 0, &ctx.save_frame_ctx);

	return 1;
}

PLUGIN_API int XPluginEnable()
{
	return 1;
}

PLUGIN_API void XPluginStop()
{
}

PLUGIN_API void XPluginDisable()
{
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMessage, void * inParam )
{
}
