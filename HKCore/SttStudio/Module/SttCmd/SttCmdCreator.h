//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttCmdCreator.h  CSttCmdCreator

#pragma once

#include "SttCmdDefineGlobal.h"

class CSttCmdCreator : public CExBaseList
{
public:
	CSttCmdCreator();
	virtual ~CSttCmdCreator();

//���غ���
public:
	CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	CExBaseObject* SttCmdCreate(const CString &strCmdXml);
};

