load("//bazel/xplane:plugins.bzl", "xplane_plugin")
load("//bazel/xplane:xplane.bzl", "xplane")

xplane_plugin(
    name = "dream_collector",
    srcs = ["plugin.cpp", "plugin.h"],
    deps = [
        "//src/plugins/xplane:common",
    ]
)

xplane(
    name = "xplane",
    plugins = [":dream_collector"],
    headless = False,
    env = {
        "OUTDIR": "/repo",
    },
)
