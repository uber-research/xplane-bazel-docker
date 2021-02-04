#!/usr/bin/env bash
# This script installs required packages to run XPlane 11 on Ubuntu 18.04

set -eu -o pipefail

# Require root
if [ "$EUID" -ne 0 ]; then
    echo 'Please run as root'
    exit 1
fi

apt-get update --quiet
apt-get install --quiet --assume-yes --no-install-recommends unzip wget

PLUGIN_DIR="/xplane/Resources/plugins"
SDK_LIB_DIR="/usr/lib/xplane"
XPLANE_GRP="xplane"

# Creating xplane sdk lib folder and downloading XPlane sdk
mkdir -p $SDK_LIB_DIR
wget http://developer.x-plane.com/wp-content/plugins/code-sample-generation/sample_templates/XPSDK303.zip -O sdk.zip
unzip sdk.zip -d /usr/lib/xplane && rm sdk.zip
mv /usr/lib/xplane/SDK /usr/lib/xplane/sdk

# Make sure plugins folder exists and is writable by xplane groups members
groupadd $XPLANE_GRP
mkdir -p $PLUGIN_DIR
chgrp $XPLANE_GRP $PLUGIN_DIR && chmod g+w $XPLANE_GRP $PLUGIN_DIR
