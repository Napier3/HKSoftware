#pragma once

#include <QObject>
#include "SettingInterface.h"
#include "../SttLineEdit.h"

class QSettingLineEdit : public QSttLineEdit, public CSettingInterface
{ 
	Q_OBJECT
public:
	explicit QSettingLineEdit(QWidget *parent = 0);
	virtual ~QSettingLineEdit();

protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void focusInEvent(QFocusEvent *event);
	void ShowSettingDlg();

	virtual void SetProperty(const CString &sFormat);
	virtual void connectSetting();
	virtual void Disconnect();

protected:
	QTime m_StartTime;		//记录不显示定值关联界面时间
	QTime m_SettingCloseTime;		//20240903 huangliang 记录定值框关闭时间
	bool m_bEditState;

public slots:
	void slot_Setting();
	void slot_Clear();
	void slot_Cannel(bool bHide);	//20240731 huangliang 添加隐藏标记

	void slot_textChanged(const QString &);

public:
	virtual void UpdateText(const QString &strText);	//实现原控件更新值功能
	virtual void RefushData();	//刷新显示当前关联名称或值

	virtual BOOL IsSetting();	//依据属性"SettingIdPath"为空则非关联

	virtual CString GetText();	//20240722 huangliang 获取对象值
};
