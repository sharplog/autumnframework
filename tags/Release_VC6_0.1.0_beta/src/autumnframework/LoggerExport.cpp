
#include "BeanWrapperMacro.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

AUTUMNBEAN(ConsoleLogger)
AUTUMNBEAN_CON_PARAMS(ConsoleLogger, 1, int)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_END(ConsoleLogger)
AUTUMN_LOCALBEAN(ConsoleLogger)

AUTUMNBEAN(FileLogger)
AUTUMNBEAN_CON_PARAMS(FileLogger, 2, string)
AUTUMNBEAN_CON_PARAM(int)
AUTUMNBEAN_CON_PARAMS_END()
AUTUMNBEAN_END(FileLogger)
AUTUMN_LOCALBEAN(FileLogger)

