#ifndef SttIecGooseGrid_PkgStc_H
#define SttIecGooseGrid_PkgStc_H

#include "SttIecSmvGrid_PkgError.h"

//GOOSE   ����ͳ��
class CSttIecGooseGrid_PkgError :  public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecGooseGrid_PkgError(QWidget* pparent);
	virtual ~CSttIecGooseGrid_PkgError();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Config();//ҳ�湦������
	virtual BOOL NeedConfig(){return TRUE;}
	virtual BOOL NeedAddToSubPub(){return TRUE;}
	virtual void Release();
private:
	int m_nGridWidth[2];

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
};

#endif // SttIecGooseGrid_PkgStc_H
