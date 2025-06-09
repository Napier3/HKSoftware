#ifndef GRADIENTPARASET_H
#define GRADIENTPARASET_H

#include <QWidget>
#include <QStringList>
#include <QDate>
#include "gradientchanneltable.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "../../../../../RelayTest/Module/SttTest/Common/tmt_state_test.h"
#include "../../../../../RelayTest/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include <QGridLayout>
#include <QScrollArea>

class GradientParaSet : public QWidget
{
	Q_OBJECT

public:
	GradientParaSet(QWidget *parent = 0);
	~GradientParaSet();

	virtual void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource,tmt_StatePara *pStatePara,int nGradientObj);

	void setData(tmt_StatePara *pStatePara);
	void setMaxMinVal();
	void setUAmpMaxMinValue();
	void setIAmpMaxMinValue();
	void setUIFreMaxMinValue();
	void updateGradientType(int nType);
	void InitLinearStepGradient();

	void saveData();

public:
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	void initData();
	void Release();
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;
	int m_nGradientObj;

	CSttTestResourceBase *m_pGradientParaSetSttTestResource;
	tmt_StatePara *m_pStatePara;
	QList<GradientChannelTable *> m_UCHannelTableList;
	QList<GradientChannelTable *> m_ICHannelTableList;

	QGridLayout* m_pMainGridLayout;
	QGridLayout *m_pUVGridLayout;
	QGridLayout *m_pIVGridLayout;

	QWidget *m_pUWidget;
	QWidget *m_pIWidget;
	QScrollArea *m_pUScrollArea;
	QScrollArea *m_pIScrollArea;
};

#endif // GRADIENTPARASET_H
