#ifndef POWERDIRCOMMON_H
#define POWERDIRCOMMON_H

#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

CString PowerDirValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint);
void PowerDirCheckParaExist(CExBaseList *pParas,CString strID);

#endif //POWERDIRCOMMON_H