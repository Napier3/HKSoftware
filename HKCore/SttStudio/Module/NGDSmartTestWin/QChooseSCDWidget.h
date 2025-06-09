#pragma once
#include<QWidget>
#include <QFileDialog>
#include "ui_QChooseSCDWidget.h"
#include "CString_QT.h"
#include "..\..\61850\Module\SCL\SclIecCfgDatas.h"
#include "..\DataMngr\DataGroup.h"

class QChooseSCDWidget :public QWidget
{
	Q_OBJECT
public:
	QChooseSCDWidget(QWidget *pparent = NULL);
	virtual ~QChooseSCDWidget(void);

private:
	Ui::QChooseSCDWidget ui;

public:
	CDataGroup *m_pModTypeGroup;
	CSclStation *m_pSclStation;//��Ž����õ�SCD�����ݽṹ
	CString m_strSCDFilePath;
	CString m_strModFileName;

	void InitCombo();
	void SetSCLStation(CSclStation *pSclStation);
	void GetModFileName();
	CString OpenSaveTemplateFileDlg(QWidget *parent,const CString &strTitle,const CString &strFilter,
		const CString &strFolderPath,BOOL bIsOpen);//���ļ���ѡ���ļ�

signals:

public slots:
	void slot_On_m_Btn_ChooseSCD_clicked();
};
