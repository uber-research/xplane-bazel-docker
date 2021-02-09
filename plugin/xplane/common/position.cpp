//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//

#include "position.h"
#include <cstring>

namespace atcp::plugins::xplane::position
{
void deactivate_flightloop()
{
    int vals[20];
    memset(vals, 1, sizeof(vals));
    XPLMSetDatavi(DREF_PATH_OVERRIDE, vals, 0, sizeof(vals));
}

void move_ac_to(float altitude_m)
{
    XPLMSetDatad(DREF_LOCAL_Y, altitude_m);
}
}
