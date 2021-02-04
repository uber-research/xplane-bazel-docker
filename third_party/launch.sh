#!/bin/bash
( sleep 1.5 ; xdotool search --name "X-System" key Escape && xdotool search --name "X-System" key Escape ) &
/xplane/X-Plane-x86_64 --window=640x480
