#ifndef ACTIONTIMECOMMON_H
#define ACTIONTIMECOMMON_H

#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

CString ActTimeValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint);
void ActTimeCheckParaExist(CExBaseList *pParas,CString strID);

#endif //ACTIONTIMECOMMON_H