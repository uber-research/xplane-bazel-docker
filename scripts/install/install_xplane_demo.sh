#!/usr/bin/env bash
# This script installs required packages to run XPlane 11 on Ubuntu 18.04

set -eu -o pipefail

# Require root
if [ "$EUID" -eq 0 ]; then
    echo 'Please do not run as root'
    exit 1
fi

# Install system prerequisites
sudo apt-get update --quiet
sudo apt-get install --quiet --assume-yes --no-install-recommends \
    python3-pip \
    scrot \
    wget

sudo -H pip3 install pyautogui

# Localize autogui folder
_DIR=$( cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )
AUTOGUI_DIR=$(readlink -f "${_DIR}/../autogui")

# Download Xplane installation script
TMP_DIR=$(mktemp -d)
URL='https://www.x-plane.com/update/installers11/X-Plane11InstallerLinux.zip'
cd "${TMP_DIR}"
wget "${URL}"
unzip 'X-Plane11InstallerLinux.zip'

# Run installation script and autogui script
INSTALLER='X-Plane 11 Installer Linux'
"./${INSTALLER}" &
sleep 1
cd "${AUTOGUI_DIR}/xplane"
python3 install.py
