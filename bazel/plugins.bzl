load(":vars.bzl", "XPLANE_COPTS")

_LD_SCRIPT = "@atcp_mono//bazel/xplane:exports.ldscript"
_CP_SCRIPT = "@atcp_mono//bazel/xplane:copy_xpl.sh"

XPLANE_LINKOPTS = [
    "-m64","-static-libgcc","-shared",
    "-Wl,--version-script,$(location {})".format(_LD_SCRIPT),
]

XPLANE_DEPS = ["@xplane//:sdk", _LD_SCRIPT]

def _xplane_augment_attrs(**kwargs):
    kwargs['deps'] = kwargs.get('deps', []) + XPLANE_DEPS
    kwargs['linkopts'] = kwargs.get('linkopts', []) + XPLANE_LINKOPTS
    kwargs['copts'] = kwargs.get('copts', []) + XPLANE_COPTS
    return kwargs

def xplane_plugin(name, **kwargs):
    native.cc_binary(
        name = name,
        **_xplane_augment_attrs(**kwargs),
    )

def xplane_library(name, **kwargs):
    native.cc_library(
        name = name,
        **_xplane_augment_attrs(**kwargs)
    )
