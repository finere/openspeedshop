echo expcreate -f ../../../../executables/mutatee/64bit/f77_version/mutatee pcsamp >> input.script
echo expgo >> input.script
echo expview vtop5 >>input.script
openss -batch < input.script
