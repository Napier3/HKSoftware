// EpParseFrame.h: interface for the CEpParseFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPARSEFRAME_H__)
#define _EPPARSEFRAME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"


class CEpParseFrame : public CEpFrameBase  
{
public:
	CEpParseFrame();
	virtual ~CEpParseFrame();

public:
	//��������
	virtual UINT GetClassID()	{ return EPCLASSID_PARSE_FRAME;	}
	
	//����
	//�ֽڿ�Ľ���  ����Ľ�������������ִ�н���
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)	{ return 0;}

	//�ֽڿ��ƥ��  ��Ҫ���ڽ���
	virtual BOOL Match(PEPBUFFERPOS pBufferPos) { return FALSE;}

};

#endif // !defined(_EPPARSEFRAME_H__)
