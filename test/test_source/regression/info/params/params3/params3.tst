#!/bin/sh
rm -f input.script
echo expCreate  -f ../../../../../executables/mutatee/cplus_version/mutatee hwc >> input.script
echo listparams >> input.script
echo exit >> input.script
openss -batch < input.script
