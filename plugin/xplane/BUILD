load("//bazel/xplane:plugins.bzl", "xplane_library")

xplane_library(
    name = "common",
    hdrs = glob(["common/**/*.h"]),
    srcs = glob(["common/**/*.cpp"]),
    deps = [
        "@opengl//:lib",
        "@opencv//:lib"
    ],
    copts = ["-DGL_GLEXT_PROTOTYPES=1"],
    linkopts = ["-lstdc++fs"],
    visibility = ["//src/plugins/xplane:__subpackages__"]
)
