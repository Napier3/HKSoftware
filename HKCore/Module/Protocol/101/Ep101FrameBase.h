//Ep101FrameBase.h  
#ifndef _Ep101FrameBase_H__
#define _Ep101FrameBase_H__

#include "EpGlobalDefine_101.h"

class CEp101FrameBase : public CEpFrameBase
{
public:
	CEp101FrameBase(void);
	~CEp101FrameBase(void);

// ����
public:
	CEpByteBlockControl *m_pControl;
	//BYTE m_byteControl;  //������C���Ķ���
	BYTE m_byteLinkAddr;     //��·��ַ��

// 	BYTE m_byteDIR;
// 	BYTE m_bytePRM;
// 	BYTE m_byteFCB_ACD;
// 	BYTE m_byteFCV_DFC;
// 	BYTE m_byteFuncCode;


protected:
	void AddControlByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteControl);
};


#endif //_Ep101FrameBase_H__