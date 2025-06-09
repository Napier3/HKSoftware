#include "drv_record.h"

unsigned short CalCRC(tmt_RecordPara oPara)
{
	QString type="aa";
	type+=QString::number(oPara.ntype.toInt());
	type+=QString::number(oPara.port.toInt(),16);//aa1*-SV,aa2*-goose,aa3*-ft3,接收光口序号：0-15，示例为光口3收SV

	unsigned char data[10];
	bool ok;
	data[0]=oPara.dest_mac.mid(0,2).toInt(&ok,16);
	data[1]=oPara.dest_mac.mid(2,2).toInt(&ok,16);
	data[2]=oPara.dest_mac.mid(4,2).toInt(&ok,16);
	data[3]=oPara.dest_mac.mid(6,2).toInt(&ok,16);
	data[4]=oPara.dest_mac.mid(8,2).toInt(&ok,16);
	data[5]=oPara.dest_mac.mid(10,2).toInt(&ok,16);

	data[6]=type.mid(0,2).toInt(&ok,16);
	data[7]=type.mid(2,2).toInt(&ok,16);

	data[8]=oPara.appid.mid(0,2).toInt(&ok,16);
	data[9]=oPara.appid.mid(2,2).toInt(&ok,16);

	unsigned int datalen=10;

	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x3D65;
	unsigned char wChar = 0;

	for(int i=0;i<datalen;i++)
	{
		wChar = data[i];
		wCRCin ^= (wChar << 8);
		for(int i = 0;i < 8;i++)
		{
			if(wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}

	return wCRCin;
}

void tmt_to_drv(tmt_RecordTest *pTmt ,  GooseSubData *pDrv)
{
	memset(pDrv,0,sizeof(GooseSubData));
	tmt_RecordParas oParas=pTmt->m_oRecordPara;
	pDrv->ncount=oParas.m_nSubNumber;
	pDrv->nPort=4;
	for(int index=0;index<oParas.m_nSubNumber;index++)
	{
		tmt_RecordPara oPara=oParas.m_paras[index];
		pDrv->gooseSub[index].CRC=CalCRC(oPara);
	}
}
