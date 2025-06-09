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
	QTime m_StartTime;		//��¼����ʾ��ֵ��������ʱ��
	QTime m_SettingCloseTime;		//20240903 huangliang ��¼��ֵ��ر�ʱ��
	bool m_bEditState;

public slots:
	void slot_Setting();
	void slot_Clear();
	void slot_Cannel(bool bHide);	//20240731 huangliang ������ر��

	void slot_textChanged(const QString &);

public:
	virtual void UpdateText(const QString &strText);	//ʵ��ԭ�ؼ�����ֵ����
	virtual void RefushData();	//ˢ����ʾ��ǰ�������ƻ�ֵ

	virtual BOOL IsSetting();	//��������"SettingIdPath"Ϊ����ǹ���

	virtual CString GetText();	//20240722 huangliang ��ȡ����ֵ
};
