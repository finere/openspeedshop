#!/bin/sh
if [ "$OPENSPEEDSHOP_PLUGIN_PATH" = "" ]
then
  echo "OPENSPEEDSHOP_PLUGIN_PATH not set."
  echo "For oss developers that's usually .../GUI/plugin/lib/openspeedshop"
  exit
fi
if test -d Panels
then
  ./MC;bootstrap;configure --prefix=$OPENSPEEDSHOP_PLUGIN_PATH/../..;make uninstall;make install;
#  ./MC;bootstrap;configure --prefix=$OPENSPEEDSHOP_PLUGIN_PATH/../..;make install;
else
  echo NOTE: This must be run from the GUI directory...
fi
