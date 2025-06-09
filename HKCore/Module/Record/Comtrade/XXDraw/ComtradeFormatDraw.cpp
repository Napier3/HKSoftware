// ComtradeFormatDraw.cpp: implementation of the CComtradeFormatDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeFormatDraw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComtradeFormatDraw::CComtradeFormatDraw()
{
	InitIt();
	m_iBeginIndex=0;
	m_iEndIndex=1500;
	m_pMemBuf_Point=new CMemBuffer_CPoint;
	m_pNowActElement=NULL;
	m_pTimeDataBuff = new CMemBuffer_float();
}

CComtradeFormatDraw::~CComtradeFormatDraw()
{
	EndIt();
	delete m_pTimeDataBuff;
	m_pTimeDataBuff = NULL;
}
void CComtradeFormatDraw::RegisterComtradeDrawClass()
{

}
void CComtradeFormatDraw::UnRegisterComtradeDrawClass()
{
	
}

CComtradeDrawBaseClass*CComtradeFormatDraw::GetComtradeDrawClassByName(CString strType)
{
	ASSERT(FALSE);
	return NULL;
}

void CComtradeFormatDraw::InitIt()
{
	RegisterComtradeDrawClass();
	m_bShowTagBar		=FALSE;	
	m_bShowUsedOnly		=0;	
	m_nAnalogDrawMode	= ANALOG_DRAW_MODE_SIGLE;		
	m_pNowActElement=NULL;
}

void CComtradeFormatDraw::EndIt()
{
	UnRegisterComtradeDrawClass();
	
	if(m_pMemBuf_Point)
		delete m_pMemBuf_Point;
	m_pMemBuf_Point=NULL;
}

//################################################################
//����ͼ�ӿ�����ָ��ͬ��ͼ���
DWORD CComtradeFormatDraw::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	m_pCmtrdInterface=(CComtradeMngr*)pData;
	
	m_iBeginIndex=0;
	m_iEndIndex=m_pCmtrdInterface->m_nTotalPoints-1;
	m_pMemBuf_Point->AllocMemBuffer(m_pCmtrdInterface->m_nTotalPoints);

	DeleteAll();

	if(IsAnalogDrawModeGroup())//0��ͬ��ģ����һ����ƣ�
	{
		XCreateElement_Group(pParentWnd);
	}
	else
	{
		XCreateElement_Single(pParentWnd);
	}

	XCreateElement_Binary(pParentWnd);

	////CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	////����λ��
	Layout(CPoint(0, 0));

	return XCREATE_SUCC;
}

void CComtradeFormatDraw::XCreateElement_Group(CWnd *pParentWnd)
{
	CExBaseList *pAnalogs = m_pCmtrdInterface->GetAnalogs();
	POS pos = pAnalogs->GetHeadPosition();
	CComtradeDataBase *p = NULL;
	CComtradeDrawBaseClass *pDraw = NULL;

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)pAnalogs->GetNext(pos);
		pDraw = new CComtradeAnalogDraw();
		AddNewChild(pDraw);
		pDraw->XCreateElement(p, pParentWnd);
	}
}

void CComtradeFormatDraw::XCreateElement_Single(CWnd *pParentWnd)
{
	CExBaseList *pAnalogs = m_pCmtrdInterface->GetAnalogs();
	POS pos = pAnalogs->GetHeadPosition();
	CComtradeDataBase *p = NULL;
	CComtradeDrawBaseClass *pDraw = NULL;

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)pAnalogs->GetNext(pos);
		pDraw = new CComtradeAnalogDraw();
		AddNewChild(pDraw);
		pDraw->XCreateElement(p, pParentWnd);
	}
}

void CComtradeFormatDraw::XCreateElement_Binary(CWnd *pParentWnd)
{
	CExBaseList *pBinarys = m_pCmtrdInterface->GetBinarys();
	POS pos = pBinarys->GetHeadPosition();
	CComtradeDataBase *p = NULL;
	CComtradeDrawBaseClass *pDraw = NULL;

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)pBinarys->GetNext(pos);
		pDraw = new CComtradeBinaryDraw();
		AddNewChild(pDraw);
		pDraw->XCreateElement(p, pParentWnd);
	}
}

#if 0
//����������ͼ��־���ɻ�ͼͼԪ����
void CComtradeFormatDraw::InitDrawListByFlags(CDC*pDC)
{
	DeleteAll();

	//��õ�ѹͨ��������ͨ���ĸ���
	int iAnalogCHCount[3];
	iAnalogCHCount[0]=m_bShowUsedOnly;
	iAnalogCHCount[1]=iAnalogCHCount[2]=0;
	POS pos=m_pCmtrdInterface->GetHeadPosition();

	CComtradeDataBase *pData = NULL;
	
	if(!pos)return;

	if(IsAnalogDrawModeGroup())//0��ͬ��ģ����һ����ƣ�
	{
		//��õ�ѹͨ��������ͨ���ĸ���
		while(pos)
		{
			pData=(CComtradeDataBase*)m_pCmtrdInterface->GetNext(pos);
			pData->GetCountBeforeBind(iAnalogCHCount);
		}
		int *ipVoltage	=new int[iAnalogCHCount[1]+1];
		int *ipCurrent	=new int[iAnalogCHCount[2]+1];
		ipVoltage[0]=1;ipCurrent[0]=1;
		//��ø���ʾ�ĵ�ѹͨ��������ͨ����������ipVoltage[0]��ipCurrent[0]��ʾ��������
		pos=m_pCmtrdInterface->GetHeadPosition();
	
		while(pos)
		{
			pData=(CComtradeDataBase*)m_pCmtrdInterface->GetNext(pos);
			pData->GetCHIndexBeforeBind(ipVoltage,ipCurrent,m_bShowUsedOnly);
		}
		
		//ģ��������ѹͨ�����ݵİ�
		CComtradeDrawBaseClass*pElement;

		if(iAnalogCHCount[1]>0)
		{
			pElement=new CComtradeDrawBaseClass;
			pElement->SetElementCurveType("A");
			pElement->BindCHToDrawElement(iAnalogCHCount[1],&ipVoltage[1]);
			AddTail(pElement);
			MakeCHUnitTheSame(pElement);
			pElement->InitBitmapDraw(pDC);
		}
		//ģ����������ͨ�����ݵİ�
		if(iAnalogCHCount[2]>0)
		{
			pElement=new CComtradeDrawBaseClass;
			pElement->SetElementCurveType("A");
			pElement->BindCHToDrawElement(iAnalogCHCount[2],&ipCurrent[1]);
			AddTail(pElement);
			MakeCHUnitTheSame(pElement);
			pElement->InitBitmapDraw(pDC);
		}
		delete ipVoltage;
		delete ipCurrent;
	}
	else//1��ÿ��ģ����һ��ͼ��
	{
		pos=m_pCmtrdInterface->GetHeadPosition();
		while(pos)
		{
			pData=(CComtradeDataBase*)m_pCmtrdInterface->GetNext(pos);
			if(pData->m_strCHType=="A")
			{
				BOOL bNew=FALSE;
				if(m_bShowUsedOnly==FALSE)
				{
					bNew=TRUE;
				}
				else
				{
					if(pData->m_bCHUsed)bNew=TRUE;
				}
				if(bNew)
				{
					CComtradeDrawBaseClass*pElement=new CComtradeDrawBaseClass;
					pElement->SetElementCurveType("A");
					iAnalogCHCount[0]=pData->m_nChannelIndex;
					pElement->BindCHToDrawElement(1,iAnalogCHCount);
					AddTail(pElement);
					ResumeCHUnit(pElement);
					pElement->InitBitmapDraw(pDC);
				}
			}
		}
	}

	//����ͨ��������
	if(m_bShowUsedOnly==FALSE)
	{
		if(m_pCmtrdInterface->m_cntCHDigital>0)
		{
			int *ipDigital=new int [m_pCmtrdInterface->m_cntCHDigital+1];
			iAnalogCHCount[0]=0;
			pos=m_pCmtrdInterface->GetHeadPosition();
			//�������ͨ����������������ͨ��������
			while(pos)
			{
				pData=(CComtradeDataBase*)m_pCmtrdInterface->GetNext(pos);
				if(pData->m_strCHType=="D")
				{
					ipDigital[iAnalogCHCount[0]]=pData->m_nChannelIndex;
					iAnalogCHCount[0]=iAnalogCHCount[0]+1;
				}
			}
			//������ͨ��
			CComtradeDrawBaseClass*pElement=new CComtradeDrawBaseClass;			
			pElement->SetElementCurveType("D");
			pElement->BindCHToDrawElement(m_pCmtrdInterface->m_cntCHDigital,ipDigital);
			AddTail(pElement);
			pElement->InitBitmapDraw(pDC);
			delete ipDigital;
		}
	}
}
#endif

//���ݻ�ͼ�ı�־����ͨ���ĵ�λ���ָ�ͨ��ԭ���ĵ�λ
void CComtradeFormatDraw::MakeCHUnitTheSame(CComtradeDrawBaseClass* pElement)
{
// 	if(pElement->GetElementCurveType()=="D")return;
// 	//��ð󶨵�ͨ�������ĵ�λ
// 	CString strMaxUnit="";
// 	CComtradeAnalogData*pData;
// 	int index=0;
// 	for(index=0;index<pElement->m_nTotalCHCurves;index++)
// 	{
// 		pData=(CComtradeAnalogData*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[index]);
// 		if(pData)
// 		{
// 			if(strMaxUnit.GetLength()<pData->m_strCHUnit.GetLength())
// 				strMaxUnit=pData->m_strCHUnit;
// 		}
// 	}
// 	//����ÿ��ͼԪ������ϵ�ĵ�λ
// 	pElement->SetElementUnit(strMaxUnit);
// 	//����ͨ����λ������
// 	for(index=0;index<pElement->m_nTotalCHCurves;index++)
// 	{
// 		pData=(CComtradeAnalogData*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[index]);
// 		if(pData)
// 		{
// 			pData->AdjuseCHUnitDataByUnit(strMaxUnit);
// 		}
// 	}
}
void CComtradeFormatDraw::ResumeCHUnit(CComtradeDrawBaseClass*pElement)
{
// 	//�ָ���λ������
// 	if(pElement->GetElementCurveType()=="D")return;
// 	CComtradeAnalogData*pData;
// 	int index=0;
// 	for(index=0;index<pElement->m_nTotalCHCurves;index++)
// 	{
// 		pData=(CComtradeAnalogData*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[index]);
// 		if(pData)
// 		{
// 			pData->ResumeCHUnitDataByUnit();
// 		}
// 	}
}
//�ٽ����е�ͨ�������ͼͼԪ��֮�󣬱�����������Ŀ̶ȷ�Χ
void CComtradeFormatDraw::SetElementAxisRange()
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	CComtradeDataBase*pData;
// 	float fAxisVal[4];
// 	if(!pos)return;
// 	fAxisVal[0]=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
// 	fAxisVal[1]=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);
// 	fAxisVal[2]=9999;fAxisVal[3]=-9999;
// 	int iIndex=0;
// 	while(pos)
// 	{
// 		fAxisVal[2]=9999;fAxisVal[3]=-9999;
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		for(iIndex=0;iIndex<pElement->m_nTotalCHCurves;iIndex++)
// 		{
// 			pData=(CComtradeDataBase*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[iIndex]);
// 			pData->GetCHSampMaxMiVal(fAxisVal[3],fAxisVal[2]);
// 		}
// 		float f1,f2,f;
// 		f1=(float)fabs(fAxisVal[2]);f2=(float)fabs(fAxisVal[3]);
// 		f=f1;
// 		if(f2>f1)f=f2;
// 		if(f<=0.01f)f=0.01f;
// 		f=f*1.1f;
// 		fAxisVal[2]=-f;fAxisVal[3]=f;
// 		pElement->SetAixsMaxMinVal(fAxisVal);
// 	}	
}

//�����ǻ�ͼģʽ�ı�Ľӿں���

//###################################################################
//��ͼ�ӿں���
//�����ͼ����Ĵ�С�����ø���ͼͼԪ��λ��
//����Ĳ���sizeΪ������ͼ�ͻ����Ĵ�С,
void CComtradeFormatDraw::InitDrawElement(CSize size,long &lDrift)
{
	m_pNowActElement=NULL;
	//��ø�ͨ���������󳤶�
	GetCHTitleMaxLength();
	//�Ի�ͼԪ�б�����Ű�
	TypeSetAllElement(size,lDrift);
	//������ص��ܵĸ߶�С��Size.cy����ÿ����ͼԪ���������Y��߶�����
	TypeSetAllElementAgain(size,lDrift);
	//��������Ŀ̶ȷ�Χ
	SetElementAxisRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
	//�Ű���ͨ�����ݵı���λ�ý��г�ʼ��
	InitCHTitlePosAfterTypeset();
	//��ʼ������ϵ
	InitDrawElementAxis();
}
//��ø�ͨ���������󳤶�
void CComtradeFormatDraw::GetCHTitleMaxLength()
{
// 	CComtradeDrawBaseClass*pElement;
// 	CComtradeDataBase*pData;
// 	POS pos=GetHeadPosition();
// 	long iMaxTitleLen=0;
// 	CComtradeDrawBaseClass*p=new CComtradeDrawBaseClass;
// 	LOGFONT lf=p->m_lfDrawFont;
// 	delete p;
// 	int iIndex=0;
// 
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		
// 		for(iIndex=0;iIndex<pElement->m_nTotalCHCurves;iIndex++)
// 		{
// 			pData=m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[iIndex]);
// 			if(pData)
// 				pData->GetCHTitleTextExtent(pElement->m_pMemDC,lf,iMaxTitleLen);
// 		}
// 	}
// 	pos=GetHeadPosition();
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->SetMaxTitleLenVal(iMaxTitleLen);
// 		pElement->m_iOwnDefTitleLen=iMaxTitleLen;
// 		if(IsAnalogDrawModeGroup())
// 			pElement->SetLeftGapMinVal(30);
// 	}
}
//�Ի�ͼԪ�б�����Ű�
void CComtradeFormatDraw::TypeSetAllElement(CSize size,long &lDrift)
{
// 	CComtradeDrawBaseClass*pElement;
// 	POS pos=GetHeadPosition();
// 	//�����ʾ��ͼԪ��������ͨ���������л�ͼͼԪ����߾����ó�����ͨ���������ⳤ��
// 	long iMaxTitleLen=0;
// 	CComtradeDrawBaseClass*p=new CComtradeDrawBaseClass;
// 	LOGFONT lf=p->m_lfDrawFont;
// 	delete p;
// 
// 	int index=0;
// 	BOOL bTrue=FALSE;
// 	CComtradeDataBase*pDataBase;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		if(IsAnalogDrawModeGroup())
// 		{
// 			if(pElement->GetElementCurveType()=="D")
// 			{
// 				for(index=0;index<pElement->m_nTotalCHCurves;index++)
// 				{
// 					pDataBase=(CComtradeDataBase*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[index]);
// 					pDataBase->GetCHTitleTextExtent(pElement->m_pMemDC,lf,iMaxTitleLen);
// 				}
// 				bTrue=TRUE;
// 			}
// 		}
// 	}
// 	pos=GetHeadPosition();
// 	if(bTrue)
// 	{
// 		while(pos)
// 		{
// 			pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 			pElement->SetMaxTitleLenVal(iMaxTitleLen);
// 			pElement->SetLeftGapMinVal(iMaxTitleLen);
// 		}
// 	}
// 	pos=GetHeadPosition();
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->Typeset(size,m_nAnalogDrawMode,lDrift);
// 	}
	//��������Ŀ̶ȷ�Χ
//	SetElementAxisRange();	
//	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);//���ݻ�ͼ����ʼ����ֹ�����ɻ�ͼ�ռ�
}
//�����Ű�
void CComtradeFormatDraw::TypeSetAllElementAgain(CSize size,long &lDrift)
{
// 	if(size.cy<lDrift)return;
// 	//���ģ��ͨ���ĸ���
// 	int	iAnalogs=0;
// 	CComtradeDrawBaseClass*pElement;
// 	POS pos=GetHeadPosition();
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		if(pElement->GetElementCurveType()=="A")iAnalogs++;
// 	}
// 	//����ģ��ͨ��������ϵ�����������ֵ
// 	if(iAnalogs==0)return;
// 	int iYExpand=(size.cy-lDrift) / iAnalogs;
// 	//��ģ��ͨ���Ļ�ͼͼԪ���������Ű�
// 	pos=GetHeadPosition();
// 	iAnalogs=0;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->TypesetAgain(iYExpand,m_nAnalogDrawMode,iAnalogs);
// 	}
	//��������Ŀ̶ȷ�Χ
//	SetElementAxisRange();
//	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//�Ű���ͨ�����ݵı���λ�ý��г�ʼ��
void CComtradeFormatDraw::InitCHTitlePosAfterTypeset()
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	int iIndex=0;
// 	int iTotal=0;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		CComtradeDataBase*pData;
// 		iTotal=pElement->GetCHTotalCuves();
// 		for(iIndex=0;iIndex<iTotal;iIndex++)
// 		{
// 			pData=m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[iIndex]);
// 			if(pData)
// 			{
// 				pData->SetCHPosition(pElement->pCHTitlePos[iIndex]);
// 			}
// 		}
// 	}
}
//��ʼ������ϵ
void CComtradeFormatDraw::InitDrawElementAxis()
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->InitAxisAgain();
// 	}
}

//#######################################��ͼ�ӿں���#######################################
//�ܵĻ�ͼ����
void CComtradeFormatDraw::DrawTheGraph(CDC*pDC)
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->InitBitmapDraw(pDC);
// 		pElement->DrawTheElementGraph();
// 		//pElement->DrawIt(pDC);
// 		//��������ͼ
// 		DrawTheComtradeCurve(pElement);
// 	}
}
void CComtradeFormatDraw::DrawTheGraphCurve(CDC*pDC)
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->DrawTheElementGraph();
// 		DrawTheComtradeCurve(pElement);
// 	}
}
//���ƻ�ͼͼԪ�е�ͼ��,�������ڵ�λͼ���Ƶ���Ļ��
void CComtradeFormatDraw::DrawComtrade(CDC*pDC)
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->DrawIt(pDC);
// 	}	
}
void CComtradeFormatDraw::DrawTheComtradeCurve(CComtradeDrawBaseClass*pElement,int iActiveCHIndex)
{
// 	CComtradeDrawBaseClass*pDrawBase;
// 	CComtradeDataBase*pData;
// 	int iIndex=0;
// 	int iTotal=pElement->GetCHTotalCuves();
// 	CAxisReference axisRef;
// 	//���ƻ�ͼ������
// //	CRect rect=pElement->odDef.odDisplayPara.cWorkArea;
// //	CRgn rgn;
// //	rgn.CreateRectRgnIndirect(rect);	//���ƻ��ƵĴ��ڷ�Χ
// //	pElement->m_pMemDC->SelectClipRgn(&rgn);
// 
// 	pElement->GetAxisReference(&axisRef);
// 	for(iIndex=0;iIndex<iTotal;iIndex++)
// 	{
// 		pData=(CComtradeDataBase*)m_pCmtrdInterface->GetDrawDataByCHIndex(pElement->m_ipCHIndexList[iIndex]);
// 		pDrawBase=GetComtradeDrawClassByName(pData->GetCHType());
// 		pDrawBase->DrawIt(pElement->m_pMemDC,pData,m_pMemBuf_Point,&axisRef,m_iBeginIndex,m_iEndIndex,m_nAnalogDrawMode);
// 		if(iActiveCHIndex==pElement->m_ipCHIndexList[iIndex])
// 			pDrawBase->DrawCHTitle(pElement->m_pMemDC,pData,m_nAnalogDrawMode,1,pElement->m_crViewBK);
// 		else
// 			pDrawBase->DrawCHTitle(pElement->m_pMemDC,pData,m_nAnalogDrawMode,0,pElement->m_crViewBK);
// 	}
//	pElement->m_pMemDC->SelectClipRgn(NULL);
}
void CComtradeFormatDraw::SetDrawBeginEndIndex(int iBeginIndex,int iEndIndex)
{
// 	if(GetCount()<=0)return;
// 	CComtradeDrawBaseClass*pElement;
// 	pElement=(CComtradeDrawBaseClass*)GetHead();
// 	if(!pElement)return;
// 	
// 	m_iBeginIndex=iBeginIndex;m_iEndIndex=iEndIndex;
// 
// 	CAxisReference axisRef;
// 	pElement->GetAxisReference(&axisRef);
// 
// 	float fVal=0;
// 	int iBMemBuff	=m_iBeginIndex / MEMBUFFER_MAX_ONEBUFFER ;
// 	int iEMemBuff	=m_iEndIndex   / MEMBUFFER_MAX_ONEBUFFER ;
// 	int iBMemIndex	=m_iBeginIndex - iBMemBuff * MEMBUFFER_MAX_ONEBUFFER;
// 	int iEMemIndex	=m_iEndIndex - iEMemBuff * MEMBUFFER_MAX_ONEBUFFER;
// 	CPoint	*pPoint=NULL;
// 	float	*pFloatVal=NULL;
// 
// 	if(iBMemBuff==iEMemBuff)
// 	{
// 		pPoint=m_pMemBuf_Point->m_pPointData[iBMemBuff];
// 		pFloatVal=m_pTimeDataBuff->m_pfData[iBMemBuff];
// 		for (int iIndex=iBMemIndex;iIndex<=iEMemIndex;iIndex++)
// 		{
// 			fVal=pFloatVal[iIndex] * axisRef.m_fOneXGapValue+ axisRef.m_ptCenterLogInDv.x;
// 			pPoint[iIndex].x=(int)(fVal);
// 		}
// 	}
// 	else
// 	{
// 		//��һ�������������������ݴ�iBMemIndex��MEMBUFFER_MAX_ONEBUFFER-1;
// 		pPoint=m_pMemBuf_Point->m_pPointData[iBMemBuff];
// 		pFloatVal=m_pTimeDataBuff->m_pfData[iBMemBuff];
// 		for (int iIndex=iBMemIndex;iIndex<=MEMBUFFER_MAX_ONEBUFFER-1;iIndex++)
// 		{
// 			fVal=pFloatVal[iIndex] * axisRef.m_fOneXGapValue+ axisRef.m_ptCenterLogInDv.x;
// 			pPoint[iIndex].x=(int)(fVal);
// 		}
// 		//�м�Ļ����������������iBMemBuff+1��iEMemBuff��
// 		for(int iMemBuffIndex=iBMemBuff+1;iMemBuffIndex<iEMemBuff;iMemBuffIndex++)
// 		{
// 			pPoint=m_pMemBuf_Point->m_pPointData[iMemBuffIndex];
// 			pFloatVal=m_pTimeDataBuff->m_pfData[iMemBuffIndex];
// 			for (int iIndex=0;iIndex<=MEMBUFFER_MAX_ONEBUFFER-1;iIndex++)
// 			{
// 				fVal=pFloatVal[iIndex] * axisRef.m_fOneXGapValue+ axisRef.m_ptCenterLogInDv.x;
// 				pPoint[iIndex].x=(int)(fVal);
// 			}
// 		}
// 		pPoint=m_pMemBuf_Point->m_pPointData[iEMemBuff];
// 		pFloatVal=m_pTimeDataBuff->m_pfData[iEMemBuff];
// 		for (iIndex=0;iIndex<=iEMemIndex;iIndex++)
// 		{
// 			fVal=pFloatVal[iIndex] * axisRef.m_fOneXGapValue+ axisRef.m_ptCenterLogInDv.x;
// 			pPoint[iIndex].x=(int)(fVal);
// 		}
// 	}
}

//###################################################################
//ͼ�β�����ͨ�ú���
void CComtradeFormatDraw::SetElementAxisXRange()
{
// 	POS pos=GetHeadPosition();
// 	CComtradeDrawBaseClass*pElement;
// 	float fAxisVal[4];
// 	fAxisVal[0]=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
// 	fAxisVal[1]=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		pElement->SetAixsMaxMinVal_X(fAxisVal);
// 	}
}
void CComtradeFormatDraw::FindBeginEndIndex(float fBT,float fET)
{
	int iBeginIndex=0,iEndInex=0;
	HalfSearchIndex(fBT,iBeginIndex);
	HalfSearchIndex(fET,iEndInex);
	SetDrawBeginEndIndex(iBeginIndex,iEndInex);
}
int CComtradeFormatDraw::FindTimeIndex(float fTime)
{
	int iTimeIndex=0;
	HalfSearchIndex(fTime,iTimeIndex);
	return iTimeIndex;
}
void CComtradeFormatDraw::HalfSearchIndex(float fTime,int &iTimeIndex)
{
// 	int iBegin=0;
// 	int iEnd=m_pCmtrdInterface->m_nTotalPoints-1;
// 
// 	if(fTime<0)
// 	{
// 		iTimeIndex=0;
// 		return ;
// 	}
// 	float *pFloatTime=NULL;
// 	int iBuffNum=m_pTimeDataBuff->m_iMemBuffNum;
// 	BOOL bFindBuff=FALSE;
// 	int iIndex=0;
// 	iEnd=MEMBUFFER_MAX_ONEBUFFER-1;
// 	iBegin=0;
// 	int iTimeBuffIndex=0;
// 	for(iIndex=0;iIndex<iBuffNum;iIndex++)
// 	{
// 		pFloatTime=m_pTimeDataBuff->m_pfData[iIndex];
// 		if(fTime>=pFloatTime[iBegin] && fTime<=pFloatTime[iEnd])
// 		{
// 			bFindBuff=TRUE;
// 			iTimeBuffIndex=iIndex;
// 			break;
// 		}
// 	}
// 	if(bFindBuff==FALSE)
// 	{
// 		iTimeBuffIndex=iBuffNum;
// 		pFloatTime=m_pTimeDataBuff->m_pfData[iBuffNum];
// 		iEnd=m_pTimeDataBuff->m_iLastMemBuffIndex-1;
// 	}
// 
// 	if(fTime>=pFloatTime[iEnd])
// 	{
// 		iTimeIndex=iEnd+MEMBUFFER_MAX_ONEBUFFER*iTimeBuffIndex;
// 		return;
// 	}
// 	int index=iBegin;
// 	while(1)
// 	{
// 		if(	pFloatTime[index] <=fTime && pFloatTime[index+1] >fTime)
// 		{
// 			iTimeIndex=index;
// 			break;
// 		}
// 		index=(iEnd+iBegin)/2;
// 		if(	pFloatTime[index] <=fTime && pFloatTime[index+1] >fTime)
// 		{
// 			iTimeIndex=index;
// 			break;
// 		}
// 		if(pFloatTime[index] < fTime)iBegin=index;
// 		else iEnd=index;
// 		if(iBegin==iEnd)
// 		{
// 			iTimeIndex=-1;
// 			break;
// 		}
// 	}
// 	iTimeIndex=iTimeIndex+MEMBUFFER_MAX_ONEBUFFER*iTimeBuffIndex;
}
void CComtradeFormatDraw::GetElementAxisUnit(float &fAxisUnit)
{
// 	if(GetCount()<=0)return;
// 	CComtradeDrawBaseClass*pElement;
// 	pElement=(CComtradeDrawBaseClass*)GetHead();
// 	fAxisUnit=(float)pElement->odDef.odDisplayPara.m_fXCarryOneGap;
}
//����ͼ�εĲ���������ͼ�εķŴ���С���ƶ�
//ͼ�ηŴ�
void CComtradeFormatDraw::OnCmtrdGrphOP_Zoomout()
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	float fBegin=0,fEnd=0;
	fBegin	=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
	fEnd	=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);
	float fGap=fEnd-fBegin;
	if(fGap<=0.04f)return;
	fGap/=4;
	if(fGap<0.01f)
	{
		fGap=(fEnd-fBegin-0.04f)/2;
	}
	fBegin=fBegin+fGap;
	fEnd=fEnd-fGap;
	FindBeginEndIndex(fBegin,fEnd);
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//ͼ�θ�ԭ
void CComtradeFormatDraw::OnCmtrdGrphOP_Resume()
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	m_iBeginIndex=0;
	m_iEndIndex=m_pCmtrdInterface->m_nTotalPoints-1;
	SetElementAxisXRange();	
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//ͼ�ε���С
void CComtradeFormatDraw::OnCmtrdGrphOP_Zoomin()
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	if(m_iBeginIndex==0 && m_iEndIndex==m_pCmtrdInterface->m_nTotalPoints-1)return;
	float fBegin=0,fEnd=0;
	fBegin	=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
	fEnd	=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);
	float fGap=(fEnd-fBegin)/2;

	fBegin-=fGap;fEnd+=fGap;
	FindBeginEndIndex(fBegin,fEnd);
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//�����ƶ�
void CComtradeFormatDraw::OnCmtrdGrphOP_Moveleft()
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	if(m_iBeginIndex==0)return;
	float fXAxisUnit=0;
	GetElementAxisUnit(fXAxisUnit);
	float fBegin=0,fEnd=0;
	fBegin	=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
	fEnd	=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);
	float fLen=fEnd-fBegin;
	fBegin-=fXAxisUnit;fEnd-=fXAxisUnit;
	if(fBegin<=0)
	{
		fBegin=0;
		fEnd=fLen;
	}
	FindBeginEndIndex(fBegin,fEnd);
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//�����ƶ�
void CComtradeFormatDraw::OnCmtrdGrphOP_Moveright()
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	if(m_iEndIndex==m_pCmtrdInterface->m_nTotalPoints-1)return;

	float fXAxisUnit=0;
	GetElementAxisUnit(fXAxisUnit);

	float fBegin=0,fEnd=0;
	fBegin	=m_pTimeDataBuff->GetMemBufVal(m_iBeginIndex);
	fEnd	=m_pTimeDataBuff->GetMemBufVal(m_iEndIndex);

	float fLen=fEnd-fBegin;
	fBegin+=fXAxisUnit;fEnd+=fXAxisUnit;
	float fMaxTimeVal=m_pTimeDataBuff->GetMemBufVal(m_pCmtrdInterface->m_nTotalPoints-1);
	if(fEnd>=fMaxTimeVal)
	{
		fEnd=fMaxTimeVal;
		fBegin=fEnd-fLen;
	}
	FindBeginEndIndex(fBegin,fEnd);
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
//ͼ������Ŵ�
void CComtradeFormatDraw::OnCmtrdGrphOP_RangeZoomout(int iXL,int iXR)
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	float fBegin=0,fEnd=0;
	fBegin	=m_pTimeDataBuff->GetMemBufVal(iXL);
	fEnd	=m_pTimeDataBuff->GetMemBufVal(iXR);

	float fLen=fEnd-fBegin;
	if(fLen<0.04)return;

	m_iBeginIndex=iXL;
	m_iEndIndex=iXR;
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
//	InitDrawElementAxis();
}
void CComtradeFormatDraw::OnCmtrdGrphOP_RangeZoomout(float fTime1,float fTime2)
{
	if(m_pCmtrdInterface->m_nTotalPoints<=0)return;
	float fTimeGap=fTime2-fTime1;
	if(fTimeGap<0.04)
	{
		fTime1=fTime2-0.04f;
		if(fTime1<0)
		{
			fTime1=0;fTime2=0.04f;
		}
	}
	FindBeginEndIndex(fTime1,fTime2);
	SetElementAxisXRange();
	SetDrawBeginEndIndex(m_iBeginIndex,m_iEndIndex);
}
void CComtradeFormatDraw::GetTimeByCursorPos(int iXL,int iXR,float &fTime1,float &fTime2)
{
	if(GetCount()<=0)return;
	CComtradeDrawBaseClass*pElement=(CComtradeDrawBaseClass*)GetHead();
	pElement->GetTimeByCursorPos(iXL,iXR,fTime1,fTime2);	
}
void CComtradeFormatDraw::GetXPosByTimeVal(float fTime1,int &iXPos)
{
	if(GetCount()<=0)return;
	CComtradeDrawBaseClass*pElement=(CComtradeDrawBaseClass*)GetHead();
	pElement->GetXPosByTimeVal(fTime1,iXPos);	
}
//####################################################################
//���������Ķ���ӿں���

//�������ͼԪ�Ļ�ͼ�ľ��ε�λ��
CRect* CComtradeFormatDraw::GetAllElementRectPos()
{
//	CRect rectPos;
// 	int iElements=GetCount();
// 	if(iElements==0)return NULL;
// 	CRect *pRect=new CRect[iElements];
// 	CComtradeDrawBaseClass*pElement;
// 	POS pos=GetHeadPosition();
// 	iElements=0;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		rectPos=pElement->GetElementPosition();
// 		pRect[iElements]=pElement->odDef.odDisplayPara.cWorkArea;
// 		pRect[iElements].top+=rectPos.top;
// 		pRect[iElements].bottom+=rectPos.top;
// 		iElements++;
// 	}
//	return pRect;
	return NULL;
}
int  CComtradeFormatDraw::GetTotalElement()
{
	return GetCount();
}

//�������ѡ�л��ͼԪ�е�ͨ�����Ƶ���س�Ա�ͺ���
//CComtradeDrawBaseClass*CComtradeFormatDraw::GetNowActiveElement(CPoint point)
BOOL CComtradeFormatDraw::OnLButtonDown(CPoint point)
{
	CComtradeDrawBaseClass*pElement=NULL;
	POS pos=GetHeadPosition();
	BOOL	bElement=FALSE;
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		bElement=pElement->OnLButtonDown(point);
// 		if(bElement)break;
// 	}
// 	if(bElement)
// 	{
// 		if(m_pNowActElement!=pElement)
// 		{
// 			if(m_pNowActElement==NULL)
// 			{
// 				m_pNowActElement=pElement;
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// 			}
// 			else
// 			{
// 				m_pNowActElement->KillElementActiveCH();
// 				//�ָ�ԭ���ͨ��
// 				DrawTheComtradeCurve(m_pNowActElement);
// 				//���Ƶ�ǰ��ı���
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// 			}
// 		}
// 		else
// 		{
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// 		}
// 	}
// 	else
// 	{
// 		if(m_pNowActElement)
// 		{
// 			m_pNowActElement->KillElementActiveCH();
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// 			bElement=TRUE;
// 		}
// 	}
	return bElement;
}
BOOL CComtradeFormatDraw::OnLButtonDown(CPoint point,CDC*pDC)
{
	BOOL	bElement=FALSE;
// 	CComtradeDrawBaseClass*pElement=NULL;
// 	POS pos=GetHeadPosition();
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		bElement=pElement->OnLButtonDown(point);
// 		if(bElement)break;
// 	}
// 	if(bElement)
// 	{
// 		if(m_pNowActElement!=pElement)
// 		{
// 			if(m_pNowActElement==NULL)
// 			{
// 				m_pNowActElement=pElement;
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// //				m_pNowActElement->DrawIt(pDC);
// 			}
// 			else
// 			{
// 				m_pNowActElement->KillElementActiveCH();
// 				//�ָ�ԭ���ͨ��
// 				DrawTheComtradeCurve(m_pNowActElement);
// //				m_pNowActElement->DrawIt(pDC);
// 				//���Ƶ�ǰ��ı���
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// //				m_pNowActElement->DrawIt(pDC);
// 			}
// 		}
// 		else
// 		{
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// //			m_pNowActElement->DrawIt(pDC);
// 		}
// 	}
// 	else
// 	{
// 		if(m_pNowActElement)
// 		{
// 			m_pNowActElement->KillElementActiveCH();
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// //			m_pNowActElement->DrawIt(pDC);
// 			bElement=TRUE;
// 		}
// 	}
	return bElement;
}
BOOL CComtradeFormatDraw::OnLButtonDown(CPoint point,CWnd*pParent)
{
	BOOL	bElement=FALSE;
// 	CComtradeDrawBaseClass*pElement=NULL;
// 	POS pos=GetHeadPosition();
// 	while(pos)
// 	{
// 		pElement=(CComtradeDrawBaseClass*)GetNext(pos);
// 		bElement=pElement->OnLButtonDown(point);
// 		if(bElement)break;
// 	}
// 	if(bElement)
// 	{
// 		if(m_pNowActElement!=pElement)
// 		{
// 			if(m_pNowActElement==NULL)
// 			{
// 				m_pNowActElement=pElement;
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// 				pParent->InvalidateRect(m_pNowActElement->GetElementPosition(),0);
// 			}
// 			else
// 			{
// 				m_pNowActElement->KillElementActiveCH();
// 				//�ָ�ԭ���ͨ��
// 				DrawTheComtradeCurve(m_pNowActElement);
// 				pParent->InvalidateRect(m_pNowActElement->GetElementPosition(),0);
// 				//���Ƶ�ǰ��ı���
// 				DrawTheComtradeCurve(pElement,pElement->GetElementActCHIndex());
// 				m_pNowActElement=pElement;
// 				pParent->InvalidateRect(m_pNowActElement->GetElementPosition(),0);
// 			}
// 		}
// 		else
// 		{
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// 			pParent->InvalidateRect(m_pNowActElement->GetElementPosition(),0);
// 		}
// 	}
// 	else
// 	{
// 		if(m_pNowActElement)
// 		{
// 			m_pNowActElement->KillElementActiveCH();
// 			DrawTheComtradeCurve(m_pNowActElement,m_pNowActElement->GetElementActCHIndex());
// 			pParent->InvalidateRect(m_pNowActElement->GetElementPosition(),0);
// 			bElement=TRUE;
// 		}
// 	}
	return bElement;
}
CComtradeDrawBaseClass*CComtradeFormatDraw::GetNowActiveElement(CPoint point)
{
	return m_pNowActElement;
}
CComtradeDrawBaseClass*CComtradeFormatDraw::GetNowActiveElement()
{
	return m_pNowActElement;
}
int CComtradeFormatDraw::GetNowActCHIndex()
{
// 	if(!m_pNowActElement)return -1;
// 	return m_pNowActElement->GetElementActCHIndex();
	return 0;
}
void CComtradeFormatDraw::SetNowActiveElement(CComtradeDrawBaseClass*pElement)
{

}


