#pragma once

#include <QWidget>
#include "channelparaset/paratab.h"

class QTemplateWidget :public QWidget
{
	Q_OBJECT
public:
	QTemplateWidget(void);
	~QTemplateWidget(void);

	ParaTab* getParaTab(){
		return m_pParaTab;
	}

	QParaSetBase* getSyncParaSet(){
		return m_pSyncParaSet;
	}

	virtual void initUI()=0;
	
public:
	ParaTab* m_pParaTab;			//异步资源模式
	QParaSetBase* m_pSyncParaSet;	//同步资源模式(参数设置区域)
};
