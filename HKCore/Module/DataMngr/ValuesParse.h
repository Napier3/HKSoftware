//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ValuesParse.h  CValuesParse

#pragma once

#include "Values.h"

class CValuesParse : public CValues
{
public:
	CValuesParse(const CString &strText);
	CValuesParse();
	virtual ~CValuesParse();
	
	char m_charValFlag;
	char m_charLeftFlag;
	char m_charRightFlag;

//���غ���
public:
	void Parse(const CString &strText);

//˽�г�Ա����
private:
	void Skip(char **ppPos);
	void InitFlags();

//˽�г�Ա�������ʷ���
public:
};

