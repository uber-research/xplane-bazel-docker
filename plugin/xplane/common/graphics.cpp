//
// Advanced Technologies Center - Paris - 2020
// Uber France Software & Development
//

#include "graphics.h"

#include "GL/gl.h"
#include "GL/glext.h"

#include "opencv2/opencv.hpp"

#include <cstdlib>
#include <chrono>
#include <experimental/filesystem>
#include <functional>
#include <iostream>
#include <sstream>

using namespace std::chrono;
using namespace std::placeholders;
using namespace std::experimental;

namespace atcp::plugins::xplane::graphics
{
filesystem::path save_image(const cv::Mat &img,
                            const filesystem::path &folder_path,
                            const std::string &name,
                            const std::string &extension,
                            bool add_timestamp)
{
    auto filename = name;

    if (add_timestamp){
        milliseconds ms = duration_cast<milliseconds>(
               system_clock::now().time_since_epoch());

        filename = name + std::to_string(ms.count());
    }

    auto path = folder_path / filename;
    cv::imwrite(path.replace_extension(extension), img);

    return path;
}

int DrawCallbacks::save_frame_cb(XPLMDrawingPhase   inPhase,    
                                 int                inIsBefore,    
                                 void*              inRefcon)
{
    // Checking if shooting is needed
    auto ctx = (save_frame_ctx_t *)inRefcon;
    if (!ctx->should_shoot){
        return 1;
    }

    // Save previously bound buffer name
    GLint   buffer;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER, &buffer);

    // We unbind GL_PIXEL_PACK_BUFFER to prevent readPixels from reading
    // to a PBO (instead it will read to CPU memory)
    // If we want this to be faster (like for streaming), we should use 
    // PBOs instead for async retrieval
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

    // Allocate memory on the CPU
    // (TODO: smamessier) only reallocate when screesize changes
    // Initializing cv matrices with element size: unsigned byte x 3 channels 
    int width, height;
    XPLMGetScreenSize(&width, &height);
    cv::Mat img(height, width, CV_8UC3);
    cv::Mat flipped(height, width, CV_8UC3);


    // Set GL_PACK_ALIGNMENT to opencv's default alignment (4 bytes)
    // Check https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glPixelStore.xhtml
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.cols);

    // Selects GL_BACK (default openGL color buffer) as the source color Buffer
    // when using glReadPixels
    glReadBuffer(GL_BACK);

    // Reads pixels from color buffer to cpu memory (img.data)
    glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);

    // Cleaning after ourselves
    glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer);

    // Need to flip the image before saving
    cv::flip(img, flipped, 0);

    // Saving cv image to jpg file
    save_image(flipped, ctx->outdir, "img", ".jpg", true);

    // Marking shot has been done
    ctx->should_shoot = false;

    return 1;
}
}
