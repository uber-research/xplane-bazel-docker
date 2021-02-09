//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//

#include <string>

#include "src/plugins/xplane/common/graphics.h"

using namespace atcp::plugins::xplane;

struct PluginCtx
{
    graphics::save_frame_ctx_t save_frame_ctx;
    bool initialized            = false;
};
