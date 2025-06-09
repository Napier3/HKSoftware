//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IeCXBinaryDrawGlobal.h

#pragma once

#include "../../../Module/XDrawBase/XDrawElements.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../Module/BaseClass/XDrawBaseInterface.h"

#define WM_BINARYOUT_CHANGED         (WM_USER + 1705)
#define WM_BINARYOUT_CAN_CHANGE    (WM_USER + 1706)

#define XBINARYDRAW_BASECLASS          (XDRAW_BASECLASS   + 0X00100000)
#define XBINARYDRAW_EXLISTCLASS        (XDRAW_EXLISTCLASS + 0X00100000)
#define XBINARYDRAW_BINARY                (XBINARYDRAW_EXLISTCLASS + 0X00000001)
#define XBINARYDRAW_BINARYOUT          (XBINARYDRAW_EXLISTCLASS + 0X00000002)
#define XBINARYDRAW_BINARYOUT_SET   (XBINARYDRAW_EXLISTCLASS + 0X00000003)
#define XBINARYDRAW_BINARYS              (XDRAW_BASECLASS + 0X00000004)
#define XBINARYDRAW_BINARYDRAWVIEW             (XDRAW_BASECLASS + 0X00000005)


class CXBinaryDrawXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CXBinaryDrawXmlRWKeys();
	virtual ~CXBinaryDrawXmlRWKeys();
	static long g_nCFGRef;

public:
	static CXBinaryDrawXmlRWKeys* g_pXmlKeys;
	static CXBinaryDrawXmlRWKeys* Create();
	static void Release();


public:


public:
	

};



class CXBinaryDrawConstGlobal
{
private:
	CXBinaryDrawConstGlobal();
	virtual ~CXBinaryDrawConstGlobal();

public:
	static CXBinaryDrawConstGlobal* Create();
	static void Release();


private:
	static long g_nGlobalRef;
	static CXBinaryDrawConstGlobal *g_pGlobal;

	void InitGlobal();

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};


extern long g_nBinaryDrawColsCalUseHex_16;
long binary_draw_cal_cols(long nWidth, long nBinaryWidth);
long binary_draw_cal_cols_rows(long nButtons, long nWidth, long nBinaryWidth, long &nCols, long &nRows);

