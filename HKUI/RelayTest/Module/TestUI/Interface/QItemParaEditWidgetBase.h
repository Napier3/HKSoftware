#ifndef QITEMPARAEDITWIDGETBASE_H
#define QITEMPARAEDITWIDGETBASE_H

#include <QWidget>
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include "../../../Module/TestMacro/TestMacro.h"
#include "../../UI/Controls/SettingCtrls/qsettinglineedit.h"


class QItemParaEditWidgetBase : public QWidget
{
	Q_OBJECT

public:
	QItemParaEditWidgetBase(QWidget *parent);
	virtual ~QItemParaEditWidgetBase();

public:
	virtual void InitUI();
	virtual void InitDatas(CTestMacro *pSingleMacroRef);
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);

	virtual bool UpdateParaForLineEdit(CString strID, QObject *pObject);	//20240805 huangliang 更新外部对象数据
	CExBaseList *GetMacroTestParaDatas_Inner();
signals:
	void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);

public:
	CSttMacroTest m_oSttMacroTest_Inner;//内部数据显示对象
	CSttMacroTest *m_pCurrMacroTest_External;//外部表格选中行对象
	CTestMacro *m_pSingleMacroRef;

};

extern bool Stt_Global_IsSetting(QObject *pObject);

#endif // QITEMPARAEDITWIDGETBASE_H
