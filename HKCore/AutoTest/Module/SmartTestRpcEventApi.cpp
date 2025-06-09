#include "stdafx.h"
#include "SmartTestRpcEventApi.h"

#ifdef _PSX_QT_LINUX_
#include "SmartTestRpcEventApi_Linux.cpp"
#else
#include "SmartTestRpcEventApi_Win.cpp"
#endif

