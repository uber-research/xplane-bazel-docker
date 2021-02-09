//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//
#pragma once

#include "XPLMDataAccess.h"

namespace atcp::plugins::xplane::position
{

// Small macro to declutter
#define XREF(label, dataref_str) const auto label = XPLMFindDataRef(dataref_str)

// Getting handles on a bunch of useful Xplane dataref
// as XPLMFindDataRef is slow, so doing it only once
XREF(DREF_LOCAL_X,       "sim/flightmodel/position/local_x");
XREF(DREF_LOCAL_Y,       "sim/flightmodel/position/local_y");
XREF(DREF_LOCAL_Z,       "sim/flightmodel/position/local_z");

XREF(DREF_LOCAL_VX,      "sim/flightmodel/position/local_vx");
XREF(DREF_LOCAL_VY,      "sim/flightmodel/position/local_vy");
XREF(DREF_LOCAL_VZ,      "sim/flightmodel/position/local_vz");

XREF(DREF_TRUE_PITCH,    "sim/flightmodel/position/true_theta");
XREF(DREF_TRUE_ROLL,     "sim/flightmodel/position/true_phi");
XREF(DREF_TRUE_HEADING,  "sim/flightmodel/position/true_psi");

XREF(DREF_PATH_OVERRIDE, "sim/operation/override/override_planepath");

/**
 * @brief Teleport function
 * 
 * @param altitude_m Altitude to teleport to in meters
 */
void move_ac_to(float altitude_m);

/**
 * @brief Deactivates XPlane's control over the AC state
 * 
 */
void deactivate_flightloop();
}
