#ifndef STTPOPUPOPENDIALOG_H
#define STTPOPUPOPENDIALOG_H

#include "../../../../../Module/API/GlobalConfigApi.h"
#include "SttFileDlgBase.h"
#define STT_IECCONFIG_FILE_SCALE    2//zhouhj 2024.2.3 SCD解析

class QSttPopupOpenDialog : public QSttFileDlgBase
{
	Q_OBJECT

public:
	QSttPopupOpenDialog(const CString &strFolderPath,QStringList &astrPostfix,QWidget *parent= NULL,BOOL UseCodeConversion = TRUE);
	virtual ~QSttPopupOpenDialog();
	BOOL GetFilePath(CString &strFilePath);
	long GetFileSize();

	virtual void InitUI();//
	virtual void EnableButtons();
	virtual long GetSelType(){return STT_FILE_MNGR_SEL_TYPE_FILE;}

public slots:
	
};


#endif // STTPOPUPOPENDIALOG_H
