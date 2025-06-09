#pragma once

#include "SclIecCfgDatas.h"
#include "..\..\..\AutoTest\Module\GuideBookWizard\DinWzdFromSclGinChs.h"
#include "..\..\..\Module\DataMngr\DataTypes.h"

class CSclGsInCtrlsToDinWzdTools
{
public:
	CSclGsInCtrlsToDinWzdTools();
	virtual ~CSclGsInCtrlsToDinWzdTools();

public:
	//����ң���������ļ�
	void ExportDinWzdFile(const CString &strFile, CSclCtrlsGsIn *pGsInCtrls);
	void ExportDinWzdFromSclGinCh(CDinWzdFromSclGinChs *pDinWzdFromSclGinChs , CSclCtrlsGsIn *pGsInCtrls);

protected:
	CDinWzdFromSclGinChs m_oDinWzdFromSclGinChs;
	CDataTypes m_oKeyMapDataTypes;

	void InitKeyMapDataTypes();
	void Set_DinWzdFromSclGinCh(CSclCtrlGsIn *pGsInCtrl, CSclChGsIn *pGsChIn, CDinWzdFromSclGinCh *pWzdCh);
	CString GetNameKey(const CString &strGinChPath);
	void ExportDinWzdGsInCtrl(CDinWzdFromSclGinChs *pDinWzdFromSclGinChs , CSclCtrlGsIn *pGsInCtrl);
};


