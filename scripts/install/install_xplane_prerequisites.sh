#!/usr/bin/env bash
# This script installs required packages to run XPlane 11 on Ubuntu 18.04

set -eu -o pipefail

# Require root
if [ "$EUID" -ne 0 ]; then
    echo 'Please run as root'
    exit 1
fi

apt-get update --quiet
apt-get install --quiet --assume-yes --no-install-recommends \
    libatk1.0 \
    libgdk-pixbuf2.0-0 \
    libglu1-mesa \
    libgtk2.0-0 \
    libopenal-dev \
    libpangocairo-1.0-0 \
    libpangoxft-1.0-0 \
    mesa-utils \
    xdotool \
    xvfb
