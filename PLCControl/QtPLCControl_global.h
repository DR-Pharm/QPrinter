#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QtPLCControl_LIB)
#  define QtPLCControl_EXPORT Q_DECL_EXPORT
# else
#  define QtPLCControl_EXPORT Q_DECL_IMPORT
# endif
#else
# define QtPLCControl_EXPORT
#endif
