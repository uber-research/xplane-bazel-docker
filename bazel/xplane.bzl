
_LAUNCH_SCRIPT = "@atcp_mono//bazel/xplane:launch.sh"

def xplane(name, env={}, **kwargs):
    """Setup and launch X-Plane

    Args:
        name: an unique name for the rule.
        **kwargs: other arguments accepted by the rule.
    """
    native.filegroup(
        name = "{}.plugins".format(name),
        srcs =  kwargs.get("plugins"),
    )
    native.sh_binary(
        name = name,
        srcs = [_LAUNCH_SCRIPT],
        data = ["{}.plugins".format(name)],
        args = [
            " ".join([k+"="+v for k, v in env.items()]),
            "$(locations :{}.plugins)".format(name),
        ],
    )
