#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DONGLE_LIB)
#  define DONGLE_EXPORT Q_DECL_EXPORT
# else
#  define DONGLE_EXPORT Q_DECL_IMPORT
# endif
#else
# define DONGLE_EXPORT
#endif
