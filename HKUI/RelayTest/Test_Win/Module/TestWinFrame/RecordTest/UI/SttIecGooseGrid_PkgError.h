#ifndef SttIecGooseGrid_PkgStc_H
#define SttIecGooseGrid_PkgStc_H

#include "SttIecSmvGrid_PkgError.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//GOOSE   报文统计
class CSttIecGooseGrid_PkgError : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecGooseGrid_PkgError(QWidget* pparent);
	virtual ~CSttIecGooseGrid_PkgError();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Config();//页面功能配置
	virtual BOOL NeedConfig(){return TRUE;}
	virtual BOOL NeedAddToSubPub(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
};

#endif // SttIecGooseGrid_PkgStc_H
