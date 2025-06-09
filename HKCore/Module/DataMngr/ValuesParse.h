//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
public:
	void Parse(const CString &strText);

//私有成员变量
private:
	void Skip(char **ppPos);
	void InitFlags();

//私有成员变量访问方法
public:
};

