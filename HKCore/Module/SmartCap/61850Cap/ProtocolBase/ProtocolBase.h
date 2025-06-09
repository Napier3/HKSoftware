// ProtocolBase.h: interface for the CProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_StPROTOCOLBASE_H__)
#define _StPROTOCOLBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameBaseList.h"

//���Ļ��࣬���졢������ƥ�䱨��
class CProtocolBase : public CExBaseList
{
public:
	CProtocolBase();
	virtual ~CProtocolBase();

//����
public:
	CFrameBaseList  *m_pParseFrames;   //����֡����
	long m_nFrameMaxLength;
	long m_nFrameMinLength;

	 //��Լ������ϣ�����������ݵĽṹ��
	//����ʱ����Ϊm_bufPos->pDatas���󴫵ݸ���Լ��������
	//¼������ͨ��CCapDeviceBase::AddCapDataBuffer������ӵ���Ҫ¼����ͨ����
	EPCAPPARSEDATAS m_oCapParseDatas;
	EPBUFFERPOS m_bufPos;  //��Լ�����õĻ������
	DWORD m_dwPrototcol;   //��Լ������

public:
	UINT GetClassID()	{	return STPROTOCOLCLASSID_PROTOCOL;	}
	void InitBufPos()
	{
		ZeroMemory(&m_bufPos, sizeof(EPBUFFERPOS));
		m_bufPos.pDatas = &m_oCapParseDatas;
	}

public:
	virtual CExBaseObject* Parse(CFrameMemBuffer *pBuffer, CFrameDetail *pDetailList, DWORD dwPara)
	{
		InitBufPos();
		m_bufPos.dwPara = dwPara;
		pBuffer->GetBufferPos(m_bufPos);
		CExBaseObject *p = Parse(&m_bufPos, pDetailList);
		return p;
	}
	virtual CExBaseObject* Parse(CXSmMemBuffer *pBuffer, DWORD dwPara)
	{
		InitBufPos();
		m_bufPos.dwPara = dwPara;
		pBuffer->GetBufferPos(m_bufPos);
		CExBaseObject *p = Parse(&m_bufPos);
		return p;
	}

	void AddParseFrame(CFrameBase *pFrame);

	CFrameBase* Match(PEPBUFFERPOS pBufferPos);
	CFrameBase* Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	CFrameBase* Parse(PEPBUFFERPOS pBufferPos);

	CFrameBase* FindFrameByID(DWORD dwClassID);

//////////////////////////////////////////////////////////////////////////
//ͨѶͨ������
protected:
	CExBaseObject *m_pDevice;
	//CStDeviceCmmChannel *m_pDeviceCmmChannel;    //�������豸ͨѶ����
	
public:
	void AttachDevice(CExBaseObject *pDevice);

};


#endif // !defined(_StPROTOCOLBASE_H__)
