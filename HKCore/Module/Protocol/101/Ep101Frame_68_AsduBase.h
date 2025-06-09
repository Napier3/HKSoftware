//Ep101Frame_68_AsduBase.h  
#ifndef _Ep101Frame_68_AsduBase_H__
#define _Ep101Frame_68_AsduBase_H__

#include "Ep101Frame_68.h"
#include "..\ProtocolBase\EpFrameAsdu.h"
#include "EpByteBlockData_101_Yx.h"

/*
���������������������ש�������������������������������������������
��ASDU	            ��                      ASDU����            ��
�ǩ������������������贈�������������������ש���������������������
��                  ��                    ��   ���ͱ�ʶ         ��
��                  ��   ���ݵ�Ԫ����     �ǩ���������������������
��                  ��                    ��   �ɱ�ṹ�޶���   ��
��  ���ݵ�Ԫ��ʶ    �ǩ��������������������ߩ���������������������
��                  ��   ����ԭ��                               ��
��                  �ǩ�������������������������������������������
��                  ��   ������ַ                               ��
�ǩ������������������贈������������������������������������������
��                  ��   ��Ϣ���ַ                             ��
��                  �ǩ�������������������������������������������
��    ��Ϣ��        ��   ��Ϣ��Ԫ��                             ��
��                  �ǩ�������������������������������������������
��                  ��   ��Ϣ��ʱ�꣨���б�Ҫ��                 ��
���������������������ߩ�������������������������������������������
*/

class CEp101Frame_68_AsduBase : public CEpFrameAsdu
{
public:
	CEp101Frame_68_AsduBase(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CEp101Frame_68_AsduBase();

public:
	BYTE m_byteType;    //���ͱ�ʶ
	BYTE m_byteVSQ;     //�ɱ�ṹ�޶���

	//COT
	BYTE m_byteCOT;     //����ԭ��
	BYTE m_byteAddr;    //������ַ

	long m_nSQ;         //	SQ=1��������֡�е���Ϣ���ǰ���Ϣ���ַ˳�����еġ�SQ=0��������֡�е���Ϣ�岻�ǰ���Ϣ���ַ˳�����е�
	long m_nCount;      //��Ϣ��ĸ���,С��128

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_68_ASDUBASE;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);

protected:
	// ���ݻ�ȡ
	float GetNormalizationValue(const BYTE *byASDU, int &iCursor, float fMinValue, float fMaxValue);
	float GetIEEE754Value(const BYTE *byASDU, int &iCursor);
	void GetODDRValue(const BYTE *byASDU, int &iCursor, const int iIndex, int &iODDR);																						// ��ȡ��Ϣ�����ַ��Ϣ
	void GetCP56Time2aValue(const BYTE *byASDU, int &iCursor, int &iMillSec, int &iSec
		, int &iMin, int &iHour, int &iDayOfWeek, int &iDayOfMonth, int &iMon, int &iYear);
	void GetVSQValue(BYTE byValue, int &iSQ, int &iNum);																														// ��ȡ�ɱ�ṹ�޶�����Ϣ
	void GetSIQValue(BYTE byValue, int &iSPI, int &iBL, int &iSB, int &iNT, int &iIV);																							// ��ȡ��Ʒ�������ʵĵ�����Ϣ
	void GetQDSValue(BYTE byValue, int &iOV, int &iBL, int &iSB, int &iNT, int &iIV);																							// ��ȡƷ����������Ϣ
	void GetQOSValue(BYTE byValue, int &iQL, int &iSE);																														// ��ȡ�趨�����޶�����Ϣ
	void GetDCOValue(BYTE byValue, int &iDCS, int &iQU, int &iSE);																																				// ��ȡ˫������Ϣ
	void GetRCOValue(BYTE byValue, int &iDCS, int &iQU, int &iSE);																																				// ��ȡ������������Ϣ
	void GetQOCValue(BYTE byValue, int &iQU, int &iSE);																																							// ��ȡ�����޶�����Ϣ

protected:
	void AddAsduByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail);
	void AddVsqByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteVsq, BOOL bAddDetail);
	void AddCotByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteCot, BOOL bAddDetail);
	void AddSIQByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteSIQ, BOOL bAddDetail);

	CEpByteBlockData_101_Yx* AddNewYxByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex);
};


#endif //_Ep101Frame_68_AsduBase_H__