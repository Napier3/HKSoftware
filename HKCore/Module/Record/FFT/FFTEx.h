
typedef struct ChanelInfo
{
	float famp[26];
	float fPhsor[26];
	float fFre[26];
}ChanelInfo;

#define Pi 3.1415926
float fftData[2048];

void dsp_fft(float* pindata, int lindata, float* poutdataR, float* poutdataI, float* phase_r, float *phase_i, int* pinv)
{
	int	is,N=lindata,v;
	float *xn=pindata, *XWR=poutdataR, *XWI=poutdataI;
	float	tmpXWR,tmpXWI;
	int		leni1,leni2,xui0,xui1,pxu,is1,is2;
	v = int(log((float)N)/log((float)2.0)+0.5);

	for(is=0; is<N; is++)
	{
		XWR[is]=xn[pinv[is]];
		XWI[is]=0.0;
	}
	tmpXWR=0.0;  tmpXWI=0.0; xui0=0; xui1=0;
	for(is=1; is<=v; is++)
	{
		leni1=(int)1<<(v-is);
		for(is1=1; is1<=leni1; is1++)
		{
			leni2=(int)1<<(is-1);
			for(is2=1; is2<=leni2; is2++)
			{
				xui0 =(is1-1)*(leni2<<1)+is2-1;
				xui1 =xui0+leni2;
				pxu=(is2-1)<<(v-is);
				tmpXWR=XWR[xui1];  tmpXWI=XWI[xui1];
				XWR[xui1]=tmpXWR*phase_r[pxu]-tmpXWI*phase_i[pxu];
				XWI[xui1]=tmpXWR*phase_i[pxu]+tmpXWI*phase_r[pxu];
				tmpXWR=XWR[xui0];  tmpXWI=XWI[xui0];
				XWR[xui0]=tmpXWR+XWR[xui1];
				XWI[xui0]=tmpXWI+XWI[xui1];
				XWR[xui1]=tmpXWR-XWR[xui1];
				XWI[xui1]=tmpXWI-XWI[xui1];
			}
		}
	}
}

int xbanalysis(float *rz_fzh,float *rz_xxw,float *rz_plv,float *data, float Fre,int m_DataLength,int m_FFTCount)
{

	int	is, v, it, tmp, N = m_DataLength, *pinv, index = 0, *r_ind;
	float	*phase_r, *phase_i, *XWR, *XWI, *xn;
	float	*r_pha, *r_frq, *r_amp, *winfun;
	xn=data; r_pha=rz_xxw;	r_frq=rz_plv;	r_amp=rz_fzh;
	v= int(log((double)N)/log((double)2.0)+0.5);
	r_ind=(int *)malloc(100*sizeof(int));
	pinv=(int *)malloc(N*sizeof(int));
	phase_r=(float *)malloc(N*sizeof(float));
	phase_i=(float *)malloc(N*sizeof(float));
	XWR=(float *)malloc(N*sizeof(float));
	XWI=(float *)malloc(N*sizeof(float));
	winfun=(float *)malloc(N*sizeof(float));

	memset(r_ind,0,100*sizeof(int));
	memset(pinv,0,N*sizeof(int));

	memset(phase_r,0,N*sizeof(float));
	memset(winfun,0,N*sizeof(float));
	memset(phase_i,0,N*sizeof(float));
	memset(XWR,0,N*sizeof(float));
	memset(XWI,0,N*sizeof(float));

	for(is=0; is<N; is++)
		winfun[is]=(float)0.5-(float)0.5*(float)cos(2.0*Pi*is/N);
	//DSP analysis
	pinv[0]=0; pinv[1]=1;
	for(is=1; is<v; is++)
	{
		tmp=(int)1<<is;
		for(it=0; it<tmp; it++)
		{
			pinv[it]=2*pinv[it];
			pinv[it+tmp]=pinv[it]+1;
		}
	}

	for(is=0; is<N; is++)
	{
		phase_r[is]=(float)cos(-2.0*Pi*is/N);
		phase_i[is]=(float)sin(-2.0*Pi*is/N);
	}
	for(is=0; is<N; is++)
		xn[is]=winfun[is]*xn[is];

	dsp_fft(xn, N, XWR, XWI, phase_r, phase_i, pinv);

	// 取800个点包括上面的相位；
	int is1, idtmp=0, width=4;
	float vmax=0.0, vm=0.0, vtmp=0.0;
	*(r_pha+index)=0.0; *(r_frq+index)=0.0; *(r_amp+index)=*(XWR+index)/N*2; index++;
	for(is=width; is<N/2.0; )
	{
		if(index >= m_FFTCount)
			break; //goto xend;
		vm=0.0;
		for(is1=0; is1<width*2; is1++)
		{
			// 取800个点包括上面的相位；XWR【】，XWI【】；
			vtmp = (float)sqrt(XWR[is + is1] * XWR[is+is1] + XWI[is+is1] * XWI[is+is1]);
			if(vm < vtmp)
			{
				vm=vtmp;
				idtmp=is+is1;
			}
		}
		if(vm>10*N/4.0)
		{
			vmax=0.0;
			for(is1=-width; is1<width; is1++)
			{
				vtmp=(float)sqrt(XWR[idtmp+is1]*XWR[idtmp+is1]+XWI[idtmp+is1]*XWI[idtmp+is1]);
				if(vmax<vtmp)
					vmax=vtmp;
			}
			if(fabs(vmax-vm)<1e-4)
			{
				*(r_pha+index)=(float)atan2(XWI[idtmp],XWR[idtmp]);
				*(r_ind+index)=idtmp; *(r_amp+index)=vmax;
				index++;
			}
		}
		is=is+width*2;
	}

xend:
	float xsh=0.0, qv, hv, dfrq;
	for(is=1; is<index; is++)
	{
		idtmp=r_ind[is]-1;
		qv=(float)sqrt(XWR[idtmp]*XWR[idtmp]+XWI[idtmp]*XWI[idtmp]);
		idtmp=r_ind[is]+1;
		hv=(float)sqrt(XWR[idtmp]*XWR[idtmp]+XWI[idtmp]*XWI[idtmp]);
		if(qv>=hv)
		{
			xsh=qv/r_amp[is];
			dfrq=(float)((2.0*xsh-1.0)/(1.0+xsh));
		}
		else
		{
			xsh=hv/r_amp[is];
			dfrq=(float)((1.0-2.0*xsh)/(1.0+xsh));
		}
		qv=dfrq*dfrq; hv=qv*qv; xsh=hv*qv; qv=hv*hv;
		idtmp=r_ind[is];
		*(r_frq+is)=(float)((idtmp-dfrq)*Fre/N);
		*(r_amp+is)=(float)(*(r_amp+is)/(1.0-0.644934066848226*dfrq*dfrq+0.16680835843527*hv)/N*4);
		*(r_pha+is)=(float)((*(r_pha+is)/Pi+dfrq)*180.0);
	}
	free(r_ind);
	free(pinv);
	free(phase_r);
	free(phase_i);
	free(XWR);
	free(XWI);
	free(winfun);
	return index-1;
}

int  FFTChanle(ChanelInfo& oChanelInfo,	float * pFData,	int nDataCnt,  unsigned int nSample,	int nBeginIndex)
{
	//int nSize = data.size() - nBeginIndex;
	int nSize = nDataCnt - nBeginIndex;
	int nLen;
	if(nSize>=2048)
	{
		nLen = 2048;
	}
	else if(nSize>=1024)
	{
		nLen = 1024;
	}
	else if(nSize >=512)
	{
		nLen = 512;
	}
	else if(nSize>=256)
	{
		nLen = 256;
	}
	else
	{
		return -1;
	}
	memset(fftData,0,2048*sizeof(float));

	for(int i = nBeginIndex ; i< nLen; i++)
	{
		fftData[i] = pFData[i];
	}

	return xbanalysis(oChanelInfo.famp,oChanelInfo.fPhsor,oChanelInfo.fFre,fftData,nSample,nLen,26);
}

int getChanelAttr(ChanelInfo oInfo,float& famp,float& fPhsor,float& fFre)
 {
 	famp = oInfo.famp[1]/1.414;
 	fPhsor = oInfo.fPhsor[1];
 	fFre = oInfo.fFre[1];
 	return 0;
 }

unsigned int nSample = 4000;

float Calculate(double * pBuffer, int nLength)
{
	float fAmp[4000] = {0};
	if (nLength  >  4000)
		nLength = 4000;

	for (int i = 0;i < nLength;i++)
		fAmp[i]  = (float)pBuffer[i] ;

	//memcpy(fAmp, pBuffer, nLength * sizeof(float));

	ChanelInfo oChanelInfo;
	memset(&oChanelInfo, 0, sizeof(ChanelInfo));

	int nfft = FFTChanle(oChanelInfo, fAmp, nLength,  nSample,  0);

	float fTempDC = 0;
	if (oChanelInfo.fFre[1]  ==  0)
	{
		fTempDC = oChanelInfo.famp[0]/1.414;
		fTempDC /= 2000;

	}

	return fTempDC;


	float rms_temp0 = 0, rms_temp1 = 0;

// 	oChanelInfo.famp[0];
// 	oChanelInfo.famp[1];

	rms_temp0 = oChanelInfo.famp[0]/1.414;
	rms_temp1 = oChanelInfo.famp[1]/1.414;

	float temp0 = 0, temp1 = 0;
	temp0 = 2000;//m_fSMVPTRatioInAppID[i][0]/m_fSMVPTRatioInAppID[i][1];
	temp1 = 2000;//m_fSMVPTRatioInAppID[i][0]/m_fSMVPTRatioInAppID[i][1];

	rms_temp0 = rms_temp0/temp0;
	rms_temp1 = rms_temp1/temp1;

	float  fTemp = sqrt(rms_temp0 * rms_temp0 + rms_temp1 * rms_temp1);

	float famp,  fphsor,  ffre;
	float fFactor = 1;//getRatioFactor(QString::fromStdString(pChanel->chanelmap()));//获取U I 比例因子；
	getChanelAttr(oChanelInfo,  famp,  fphsor, ffre);//  获取幅值、相位、频率

	if(fFactor != 0)
	{
		famp =  famp/ fFactor;
	}
	famp = fTemp;
	return famp;
}

//int nfft = FFTChanle(oChanelInfo, fVec_Data,  nsample,  0);

//float famp,  fphsor,  ffre;
//float fFactor = getRatioFactor(QString::fromStdString(pChanel->chanelmap()));//获取U I 比例因子；返回的都是100；

// float getRatioFactor(QString strName)
// {
// 	if (strName.contains('U')||strName.contains('u'))
// 	{
// 		return 100;
// 	}
// 	else if (strName.contains('I')||strName.contains('i'))
// 	{
// 		return 1000;
// 	}
// 	else
// 		return 100;
// }

// int getChanelAttr(ChanelInfo oInfo,float& famp,float& fPhsor,float& fFre)
// {
// 	famp = oInfo.famp[1]/1.414;
// 	fPhsor = oInfo.fPhsor[1];
// 	fFre = oInfo.fFre[1];
// 	return 0;
// }

//getChanelAttr(oChanelInfo,  famp,  fphsor, ffre);//  获取幅值、相位、频率

//if(fFactor != 0)
//{
//	famp =  famp/ fFactor;
//}

//到这里就可以获取幅值、相位、频率了;
