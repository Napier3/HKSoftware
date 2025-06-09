
// StationTestOptrBase.h : CStationTestOptrBase ��Ľӿ�
//


#pragma once
#include "..\..\..\61850\Module\scl\SclIecCfgDatas.h"
#include "..\..\..\61850\Module\ScdDraw\XScdDrawViewStationThumbnail.h"
#include "..\..\Module\BaseClass\MemBufferDC.H"
#include "..\..\..\61850\Module\ScdDraw\XscdViewMain.h"

#include "..\..\..\StationTest\Module\StationIedTest.h"


class CStationTestOptrBase
{
protected: // �������л�����
	CStationTestOptrBase();
	virtual ~CStationTestOptrBase();

public:
	BOOL IsIedNeedTest(CString &strIedId);
	CStationIedTest* GetCurrIedTest();
	CXScdDrawViewBase *m_pXScdDrawViewRef;

public:
	void Optr_OnStationTest_Iec61850Config();
	void Optr_OnStationTest_DvmTest();
	void Optr_OnStationTest_VTermTest();
	void Optr_OnStationTest_ProtTest();
	void Optr_OnStationTest_LinkTest();
	void Optr_OnStationTest_ExportRpt();
	void Optr_OnStationTest_UploadRpt();

};
