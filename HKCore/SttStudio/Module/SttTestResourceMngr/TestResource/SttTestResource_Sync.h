#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannels.h"

class CSttTestResource_Sync :public CSttTestResourceBase
{
public:
	CSttTestResource_Sync(void);
	virtual ~CSttTestResource_Sync(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_SYNC;}//��ȡ��ǰ�����Դ����
	virtual void CreateSoftResource();//���������Դ
	virtual CString GetChMapsFilePostfix(){return _T("sync");}
};
