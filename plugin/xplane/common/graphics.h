//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//
#pragma once

#include "XPLMDisplay.h"
#include "opencv2/core/mat.hpp"

#include <experimental/filesystem>

namespace atcp::plugins::xplane::graphics
{
/**
 * @brief Struct used to provide context data to the save_frame_cb
 * 
 */
struct save_frame_ctx_t
{
    /**
     * @brief Whether we should create a screenshot in this loop
     * 
     */
    bool should_shoot;

    /**
     * @brief In which directory on disk should the frame be written
     * 
     */
    std::experimental::filesystem::path outdir;
};

/**
 * @brief Helper function to save openCV image to disk
 * 
 * @return std::experimental::filesystem::path 
 */
std::experimental::filesystem::path save_image(
                const cv::Mat &img,
                const std::experimental::filesystem::path &folder_path,
                const std::string &name,
                const std::string &extension,
                bool add_timestamp = false);

/**
 * @brief Holder class for drawing callbacks of function type XPLMDrawCallback_f
 * 
 */
class DrawCallbacks
{
public:

/**
 * @brief XPLMDrawCallback_f callback used to write frames to the disk.
 */
static int save_frame_cb(XPLMDrawingPhase   inPhase,    
                         int                inIsBefore,    
                         void*              inRefcon);
};

}
