//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbBuffer.cpp  CSmDbBuffer


#include "stdafx.h"
#include "SmDbBuffer.h"

CSmDbBuffer::CSmDbBuffer()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSmDbBuffer::~CSmDbBuffer()
{
}

BOOL CSmDbBuffer::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbBuffer *p = (CSmDbBuffer*)pObj;

	return TRUE;
}

BOOL CSmDbBuffer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbBuffer *p = (CSmDbBuffer*)pDest;

	return TRUE;
}

CBaseObject* CSmDbBuffer::Clone()
{
	CSmDbBuffer *p = new CSmDbBuffer();
	Copy(p);
	return p;
}

