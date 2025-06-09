#ifndef ATSLIB_GLOBAL_H
#define ATSLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ATSLIB_LIBRARY)
#  define ATSLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ATSLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ATSLIB_GLOBAL_H
