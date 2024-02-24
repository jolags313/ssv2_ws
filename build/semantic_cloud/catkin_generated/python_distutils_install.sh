#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/conlab/ssv2_ws/src/semantic_slam/semantic_cloud"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/conlab/ssv2_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/conlab/ssv2_ws/install/lib/python3/dist-packages:/home/conlab/ssv2_ws/build/semantic_cloud/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/conlab/ssv2_ws/build/semantic_cloud" \
    "/usr/bin/python3" \
    "/home/conlab/ssv2_ws/src/semantic_slam/semantic_cloud/setup.py" \
     \
    build --build-base "/home/conlab/ssv2_ws/build/semantic_cloud" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/conlab/ssv2_ws/install" --install-scripts="/home/conlab/ssv2_ws/install/bin"
