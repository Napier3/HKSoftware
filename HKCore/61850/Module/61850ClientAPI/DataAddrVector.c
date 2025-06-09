#include "DataAddrVector.h"

 void vector_add_capacity(PMMS_ADDR_VECTOR pVector, long nCount)
 {
 	int nNewCount = nCount + pVector->numOfData;
	int nIndex = (nNewCount)/VECTOR_ADD_NUMBER +1;
	unsigned long *pNewDatas = (unsigned long*)malloc(nIndex * VECTOR_ADD_NUMBER * sizeof(unsigned long));
	unsigned long *pOld;
  	memset(pNewDatas,0,(VECTOR_ADD_NUMBER*nIndex*(sizeof(unsigned long))));
 	memcpy(pNewDatas, pVector->Datas, (pVector->numOfData) * sizeof(unsigned long));
	pOld = pVector->Datas;
	pVector->Datas = pNewDatas;
	pVector->capacity = nIndex*VECTOR_ADD_NUMBER;

	if (pOld != NULL)
	{
		free(pOld);
	}
}

 void vector_free(PMMS_ADDR_VECTOR pVector)
 {
	 if (pVector == NULL)
		 return;

	 if (pVector->Datas != NULL)
	 {
		 free(pVector->Datas); 
		 pVector->Datas = NULL;
	 }
	  
	 pVector->capacity = 0;
	 pVector->numOfData = 0;
 }

 void vector_set_add_data(PMMS_ADDR_VECTOR pVector, LPVOID *ppData, long nDataSize)//����1ָ��������ָ��;����2��new���Ŀռ䴫�ݸ���ָ��;����3ָ���������͵Ĵ�С(��new�Ŀռ�)
 {
	 if (pVector->numOfData >= pVector->capacity)
	 {
		 vector_add_capacity(pVector, VECTOR_ADD_NUMBER);
	 }

	 *ppData = malloc(nDataSize);
	 memset(*ppData,0,(nDataSize));

	 pVector->Datas[pVector->numOfData] = *ppData;
	 pVector->numOfData = pVector->numOfData + 1;
 }

 void vector_add_data(PMMS_ADDR_VECTOR pVector, LPVOID pData)
 {
	 if (pVector->numOfData >= pVector->capacity)
	 {
		 vector_add_capacity(pVector, 10);
	 }

	 pVector->Datas[pVector->numOfData] = pData;
	 pVector->numOfData = pVector->numOfData + 1;
 }