#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannels.h"

class CSttTestResource_4U3I :public CSttTestResourceBase
{
public:
	CSttTestResource_4U3I(void);
	virtual ~CSttTestResource_4U3I(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_4U3I;}//��ȡ��ǰ�����Դ����
	virtual void CreateSoftResource();//���������Դ
	virtual CString GetChMapsFilePostfix(){return _T("4u3i");}
	virtual void InitAfterCreated();//�ڴ����������Դ��,��Ҫ���еĳ�ʼ������
};
