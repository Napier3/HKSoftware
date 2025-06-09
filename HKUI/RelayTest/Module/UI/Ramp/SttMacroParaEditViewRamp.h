#ifndef STTMACROPARAEDITVIEWRAMP_H
#define STTMACROPARAEDITVIEWRAMP_H

#include <QtGui/QMainWindow>
#include "../Interface/SttMacroParaEditViewOriginal.h"

class QSttMacroParaEditViewRamp: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewRamp(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QSttMacroParaEditViewRamp();

	virtual void SysConfig(CDataGroup *pSysConfig);
	virtual void SetDatas(CDvmDataset *pParas);
	virtual void GetDatas(CDvmDataset *pParas);

public:
	void initUI();
	void initConnections();
	void initData();

	void InitTestResource();
	void OnViewTestStart();
	void OnViewTestStop();

signals:

protected slots:		
	
};

#endif // STTMACROPARAEDITVIEWRAMP_H
