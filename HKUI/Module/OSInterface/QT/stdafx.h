#ifndef _os_interface_qt_h__
#define _os_interface_qt_h__

#include "CString_QT.h"
#include "stdio.h"
#include "wchar.h"
#include "stdlib.h"

#include "CXDraw_QT.h"

#include "CXCtrl_QT_CWnd.h"
#include "CXCtrl_QT_CWinApp.h"
#include "CXCtrl_QT.h"

#include "CXArray_QT.h"
#include "CFile_QT.h"
#include "CTime_QT.h"
#include "../../Log/LogPrint.h"

#ifdef _PSX_IDE_QT_
#include "CWinThread_QT.h"
#endif

#ifdef _PSX_QT_LINUX_
#include "std_api_linux.h"
#endif

#ifdef USE_Custom_CDateTime
#include "CDateTime_QT.h"
#endif

#endif   //_os_interface_qt_h__
