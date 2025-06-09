#pragma once

#include <QObject>
#include <QTableWidget>
#include "SettingInterface.h"
#include "../../Module/QExBaseListGridBase/QGridDefine.h"

class QSettingItem : public QObject, public QGV_ITEM, public CSettingInterface
{
	Q_OBJECT
public:
	//explicit QSettingItem(const QString &text);
	explicit QSettingItem(QTableWidget *parent);
	virtual ~QSettingItem(void);

	void ShowSettingDlg();	//20240806 huangliang 单击事件被过滤后调用

protected:
	QTableWidget *m_pTableWidget;

public slots:
	void slot_itemPressed(QTableWidgetItem *item);

	void slot_Setting();
	void slot_Clear();
	void slot_Cannel(bool bHide);	//20240731 huangliang 添加隐藏标记

public:
	virtual void UpdateText(const QString &strText);	//实现原控件更新值功能
	virtual void RefushData();	//刷新显示当前关联名称或值

	virtual BOOL IsSetting();	//依据属性"SettingIdPath"为空则非关联

	virtual CString GetText();	//20240722 huangliang 获取对象值

protected:
	virtual void SetProperty(const CString &sFormat);
	virtual void connectSetting();
	virtual void Disconnect();
};
