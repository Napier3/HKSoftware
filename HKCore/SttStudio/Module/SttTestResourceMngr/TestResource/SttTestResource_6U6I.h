#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannels.h"

class CSttTestResource_6U6I :public CSttTestResourceBase
{
public:
	CSttTestResource_6U6I(void);
	virtual ~CSttTestResource_6U6I(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_6U6I;}//��ȡ��ǰ�����Դ����
	virtual void CreateSoftResource();//���������Դ
	virtual CString GetChMapsFilePostfix(){return _T("6u6i");}
	virtual void InitAfterCreated();//�ڴ����������Դ��,��Ҫ���еĳ�ʼ������
};
