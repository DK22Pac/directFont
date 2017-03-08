#include <Windows.h>
#include "plugin.h"
#include "CNewFonts.h"

using namespace plugin;

class DirectFontPlugin {
public:
    DirectFontPlugin() {
        Events::initRwEvent += CNewFonts::Initialise;
        Events::shutdownRwEvent += CNewFonts::Shutdown;
        Events::d3dLostEvent += CNewFonts::Lost;
        Events::d3dResetEvent += CNewFonts::Reset;
    }
} directFontPlg;