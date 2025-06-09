//Ep104FrameBase.h  
#ifndef _Ep104FrameBase_H__
#define _Ep104FrameBase_H__

#include "EpGlobalDefine_101.h"

class CEp104FrameBase : public CEpFrameBase
{
public:
	CEp104FrameBase(void);
	~CEp104FrameBase(void);

// 属性
public:
	CEpByteBlockControl *m_pControl;
	//BYTE m_byteControl;  //控制域（C）的定义
	BYTE m_byteLinkAddr;     //链路地址域

// 	BYTE m_byteDIR;
// 	BYTE m_bytePRM;
// 	BYTE m_byteFCB_ACD;
// 	BYTE m_byteFCV_DFC;
// 	BYTE m_byteFuncCode;


protected:
	void AddControlByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteControl);
};


#endif //_Ep104FrameBase_H__