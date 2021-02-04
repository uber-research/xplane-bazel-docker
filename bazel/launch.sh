#!/usr/bin/env bash

readonly PLUGINS='/xplane/Resources/plugins'
readonly XPLANE='/xplane/X-Plane-x86_64'
readonly WINDOW='640x480'

skip_splash_screen () {
    (
        sleep 1.5
        xdotool search --name "X-System" windowmove 200 200
        xdotool search --name "X-System" key Escape
        xdotool search --name "X-System" key Escape
        xdotool search --name "X-System" windowraise
    ) &
}

launch_xplane () {
    "${XPLANE}" "--window=${WINDOW}"
}

delete_plugins () {
    find "${PLUGINS}" -maxdepth 1 -type d \
        -not -path "${PLUGINS}" \
        -not -path "${PLUGINS}/PluginAdmin" \
        -not -path "*.framework" \
        -exec rm -rf {} \;
}

copy_plugin () {
    local path="${1}"
    local name=$(basename "${path}")
    echo "[+] setup $name"
    mkdir -p "${PLUGINS}/${name}/lin_x64"
    cp "${path}" "${PLUGINS}/${name}/lin_x64/${name}.xpl"
}

install_plugins () {
    while (($# != 0))
    do
        if [[ -s "$1" ]]
        # the argument is the path of an existing file
        then
            copy_plugin "$1"
        fi
        shift
    done
}

export_environment () {
    while (($# != 0))
    do
        if [[ "$1" == [A-Z_]*=* ]]
        # the argument is a string with the format ENV_VAR_NAME=<value>
        then
            echo "[+] set $1"
            export "$1"
        fi
        shift
    done
}

export_environment "$@"
delete_plugins
install_plugins "$@"
skip_splash_screen
launch_xplane
