#ifndef SttIecSmvGrid_PkgStc_H
#define SttIecSmvGrid_PkgStc_H

#include <QWidget>
#include <QBoxLayout>

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"
#include "SttIecSmvDiscretCharWidget.h"

//SMV   ����ͳ��
class CSttIecSmvGrid_PkgError : public CSttIecChsGridBase
{
public:
	CSttIecSmvGrid_PkgError(QWidget* pparent);
	virtual ~CSttIecSmvGrid_PkgError();

	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	//CDvmData* GetDvmData(CDvmDataset *pSVErr);
	
private:
	int m_nGridWidth[2];
	
};

//����ͳ����������ʾ
class QSttIecSmvPkgErrorWidget : public QWidget, public CSttIecRcdFuncInterface
{
public:
	explicit QSttIecSmvPkgErrorWidget(QWidget *parent = 0);
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void Config();//ҳ�湦������
	CSttIecSmvGrid_PkgError *m_pGridPkgError;
	QSttIecSmvDiscretCharWidget *m_pWndPkgError;

private:
	void InitUI();
	QHBoxLayout *m_pLayout;
};

#endif // SttIecSmvGrid_PkgStc_H
