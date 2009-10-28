#!/bin/sh
installdir=$1
if [[ $1 = "" ]]; then
	installdir=/opt/magicwar
fi;

echo "Configurating MagicWar 0.1 alpha"
echo "Configurating for installation to $installdir"
echo "Generating Makefile"
echo "installdir = $installdir" > Makefile
cat Makefile.in >> Makefile
echo "Generating config.h"
echo "#ifndef inc_mw_config" > config.h
echo "#define inc_mw_config" >> config.h
echo "#include <libintl.h>" >> config.h
echo "#include <SFML/System.hpp>" >> config.h
echo "#define _(String) gettext (String)" >> config.h
echo "#define U_(String) (sf::Unicode::UTF8String)((const unsigned char*)gettext (String))" >> config.h
echo "#define INSTALLDIR \"$installdir\"" >> config.h
echo "#define PACKAGE \"magicwar\"" >> config.h
echo "#define LOCALEDIR \"$installdir/data/locale\"" >> config.h
echo "#define DATAPATH \"$installdir/data\"" >> config.h
echo "" >> config.h
echo "#endif" >> config.h
echo "Done. Now run 'make' and 'make install'."
