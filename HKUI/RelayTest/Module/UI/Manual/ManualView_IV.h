#ifndef MANUALVIEWIV_H
#define MANUALVIEWIV_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

#include "../Module/ChannelParaset/QBasicTestParaSet.h"
#include "../Module/ExSwitchSet/exswitchset.h"

class QManualView_IV
{
public:
    QManualView_IV();
    virtual ~QManualView_IV();

	QBasicTestParaSet* m_pUIParaWidget;		//电压电流设置
	QBasicTestParaSet* m_pHarmUIParaWidget;		//谐波电压电流设置

	QTabWidget* m_pTabWidget;
public:
    void InitUI(int nFuncType);

public:
	void slot_cb_DCClicked(bool bIsChecked);

};

#endif // MANUALVIEWIV_H
