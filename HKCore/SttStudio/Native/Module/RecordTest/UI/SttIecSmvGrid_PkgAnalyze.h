#ifndef SttIecSmvGrid_PkgAnalyze_H
#define SttIecSmvGrid_PkgAnalyze_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   ��Чֵ 
class CSttIecSmvGrid_PkgAnalyze : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_PkgAnalyze(QWidget* pparent);
	virtual ~CSttIecSmvGrid_PkgAnalyze();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
//	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
//	virtual void Config();//ҳ�湦������
};

#endif // SttIecSmvGrid_PkgAnalyze_H
