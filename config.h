#ifndef inc_mw_config
#define inc_mw_config
#include <libintl.h>
#include <SFML/System.hpp>
#define _(String) gettext (String)
#define U_(String) (sf::Unicode::UTF8String)((const unsigned char*)gettext (String))
#define INSTALLDIR "/opt/magicwar"
#define PACKAGE "magicwar"
#define LOCALEDIR "/opt/magicwar/data/locale"
#define DATAPATH "/opt/magicwar/data"

#endif
