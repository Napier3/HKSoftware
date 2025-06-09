// XRecordDrawComtradeDib.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRecordDrawComtradeDib_h__)
#define _XRecordDrawComtradeDib_h__

#include "Draw\XRecordDrawBase.h"
#include "Analysis\XRcdAnalysisDrawMngr.h"

//2023-7-22  lijunqing 从CXRecordDrawBase移动过来
#include "Comtrade/ComtradeMngr.h"

class CXRecordDrawComtradeDib : public CXRecordDrawBase
{
public:
	CXRecordDrawComtradeDib();
	virtual ~CXRecordDrawComtradeDib();

public:
	void InitByComtrade(CRcdComtradeFile *pComtradeFile, long nWidth, long nHeight, BOOL bUseBinary);
	void ComtradeDib(CWnd *pWnd);
	void ComtradeDib();
	void CopyToClipboard(CWnd *pWnd);
	void WriteBmpFile(const CString &strBmpFile);

	//2021-1-16  lijunqing
	void InitByRcdDrawFile(const CString &strRcdDrawFile, long nWidth, long nHeight, BOOL bUseBinary);

	CXRcdAnalysisDrawMngr* GetRcdAnalysisDrawMngr()	{	return &m_oXRcdAnalysisDrawMngr;	 }

	//调整绘图对象  2021-2-19  lijunqing
	void AdjustRcdAnalysisDrawMngr();

protected:
	void InitVariablesByComtrade(CRcdComtradeFile *pComtradeFile, BOOL bUseBinary);
	CDrawBinaryVariable* AddDrawVariable_Binary(CComtradeBinaryData* pBinary, long &nCurrentChans, PRECORDDRAWOBJECTCONTROL pDrawControl);
	CDrawAnalogVariable* AddDrawVariable_Analog(CComtradeAnalogData* pAnalogData, long &nCurrentChans, PRECORDDRAWOBJECTCONTROL pDrawControl);

	void InitRecordDraw(long nWidth, long nHeight);
	void InitByBorder(long nWidth, long nHeight);


protected:
	RECORDDRAWOBJECTCONTROL	  m_oDrawControl[MAX_DRAW_VARIABLE];
	CDibDraw m_oDibDraw;
	
	//2023-7-22  lijunqing 
	CRcdComtradeFile *m_pRcdComtradeFile;

	//2021-1-16  lijunqing
	CXRcdAnalysisDrawMngr m_oXRcdAnalysisDrawMngr;
};


#endif // !defined(_RecordGlobalDefine_h__)
