//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfTextLine.h  CPdfTextLine

#pragma once

#include "PdfTextData.h"

class CPdfTextLine : public CExBaseList
{
public:
	CPdfTextLine(char *pszLine);
	CPdfTextLine();
	virtual ~CPdfTextLine();

	char *m_pBeginPos;
	char *m_pEndPos;

public:
	void Formart();

protected:
	void FormatBuffer(char *pBuffBegin,char *pBuffEnd,char ch,char chReplace);
};

