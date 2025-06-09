//Ep101Frame_68_AsduBase.h  
#ifndef _Ep101Frame_68_AsduBase_H__
#define _Ep101Frame_68_AsduBase_H__

#include "Ep101Frame_68.h"
#include "..\ProtocolBase\EpFrameAsdu.h"
#include "EpByteBlockData_101_Yx.h"

/*
┏━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━┓
┃ASDU	            ┃                      ASDU的域            ┃
┣━━━━━━━━━╋━━━━━━━━━━┳━━━━━━━━━━┫
┃                  ┃                    ┃   类型标识         ┃
┃                  ┃   数据单元类型     ┣━━━━━━━━━━┫
┃                  ┃                    ┃   可变结构限定词   ┃
┃  数据单元标识    ┣━━━━━━━━━━┻━━━━━━━━━━┫
┃                  ┃   传送原因                               ┃
┃                  ┣━━━━━━━━━━━━━━━━━━━━━┫
┃                  ┃   公共地址                               ┃
┣━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━┫
┃                  ┃   信息体地址                             ┃
┃                  ┣━━━━━━━━━━━━━━━━━━━━━┫
┃    信息体        ┃   信息体元素                             ┃
┃                  ┣━━━━━━━━━━━━━━━━━━━━━┫
┃                  ┃   信息体时标（如有必要）                 ┃
┗━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┛
*/

class CEp101Frame_68_AsduBase : public CEpFrameAsdu
{
public:
	CEp101Frame_68_AsduBase(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CEp101Frame_68_AsduBase();

public:
	BYTE m_byteType;    //类型标识
	BYTE m_byteVSQ;     //可变结构限定词

	//COT
	BYTE m_byteCOT;     //传送原因
	BYTE m_byteAddr;    //公共地址

	long m_nSQ;         //	SQ=1：表明此帧中的信息体是按信息体地址顺序排列的。SQ=0：表明此帧中的信息体不是按信息体地址顺序排列的
	long m_nCount;      //信息体的个数,小于128

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
	// 数据获取
	float GetNormalizationValue(const BYTE *byASDU, int &iCursor, float fMinValue, float fMaxValue);
	float GetIEEE754Value(const BYTE *byASDU, int &iCursor);
	void GetODDRValue(const BYTE *byASDU, int &iCursor, const int iIndex, int &iODDR);																						// 获取信息对象地址信息
	void GetCP56Time2aValue(const BYTE *byASDU, int &iCursor, int &iMillSec, int &iSec
		, int &iMin, int &iHour, int &iDayOfWeek, int &iDayOfMonth, int &iMon, int &iYear);
	void GetVSQValue(BYTE byValue, int &iSQ, int &iNum);																														// 获取可变结构限定词信息
	void GetSIQValue(BYTE byValue, int &iSPI, int &iBL, int &iSB, int &iNT, int &iIV);																							// 获取带品质描述词的单点信息
	void GetQDSValue(BYTE byValue, int &iOV, int &iBL, int &iSB, int &iNT, int &iIV);																							// 获取品质描述词信息
	void GetQOSValue(BYTE byValue, int &iQL, int &iSE);																														// 获取设定命令限定词信息
	void GetDCOValue(BYTE byValue, int &iDCS, int &iQU, int &iSE);																																				// 获取双命令信息
	void GetRCOValue(BYTE byValue, int &iDCS, int &iQU, int &iSE);																																				// 获取步调节命令信息
	void GetQOCValue(BYTE byValue, int &iQU, int &iSE);																																							// 获取命令限定词信息

protected:
	void AddAsduByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail);
	void AddVsqByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteVsq, BOOL bAddDetail);
	void AddCotByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteCot, BOOL bAddDetail);
	void AddSIQByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex, BYTE byteSIQ, BOOL bAddDetail);

	CEpByteBlockData_101_Yx* AddNewYxByteBlockToDataSet(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex);
};


#endif //_Ep101Frame_68_AsduBase_H__