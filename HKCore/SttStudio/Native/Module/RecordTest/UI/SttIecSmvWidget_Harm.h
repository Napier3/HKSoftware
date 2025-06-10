#pragma once

#include <QWidget>
#include "SttIecRcdFuncInterface.h"
#include "../../UI/SttTestCntrFrameBase.h"


#define	IECRCD_FUNC_Smv_Harm_ValidValue          	0  //有效值
#define	IECRCD_FUNC_Smv_Harm_Content                1  //含有率
#define	IECRCD_FUNC_Smv_Harm_Histogram  	        2  //柱状图

//SMV   谐波
class CSttIecSmvWidget_Harm : public QWidget, public CSttIecRcdFuncInterface
{
	Q_OBJECT
public:
	    
	CSttIecSmvWidget_Harm(QWidget *parent = 0);
	virtual ~CSttIecSmvWidget_Harm();

	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;

public:
	void HarmFunc_Create(int index);
	virtual void Release();
};

