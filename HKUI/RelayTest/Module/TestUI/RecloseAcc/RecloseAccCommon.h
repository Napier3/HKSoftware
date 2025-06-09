#ifndef RECLOSEACCCOMMON_H
#define RECLOSEACCCOMMON_H

#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

CString RecloseAccValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint);
void RecloseAccCheckParaExist(CExBaseList *pParas,CString strID);

#endif //RECLOSEACCCOMMON_H