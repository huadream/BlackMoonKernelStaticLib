#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
#include <stdio.h>

LPBYTE __cdecl krnln_fnRpSubBin(int a2, int a3)
{
  int v3; // ecx@1
  int v4; // ebx@1
  int v5; // ebp@1
  int v6; // edi@1
  int v7; // esi@1
  LPBYTE v8; // ebx@16
  int v9; // ebp@16
  int v10; // edi@16
  int v11; // eax@19
  int v12; // esi@19
  char v13; // zf@21
  int v14; // edx@21
  int v15; // ecx@21
  int v16; // edi@21
  LPBYTE v17; // esi@21
  int v18; // eax@26
  LPBYTE v20; // eax@33
  LPBYTE v21; // [sp+0h] [bp-40h]@31
  int v22; // [sp+4h] [bp-3Ch]@31
  int v23; // [sp+18h] [bp-28h]@1
  int v24; // [sp+1Ch] [bp-24h]@1
  int v25; // [sp+20h] [bp-20h]@5
  int v26; // [sp+24h] [bp-1Ch]@2
  BYTE v27; // [sp+28h] [bp-18h]@16
  //void **v28; // [sp+2Ch] [bp-14h]@12
  //int v29; // [sp+34h] [bp-Ch]@33
  //int v30; // [sp+3Ch] [bp-4h]@33
  int v31; // [sp+4Ch] [bp+Ch]@10

  v5 = *(int*)(*(int*)a3 + 4);
  v24 = *(int*)(a3 + 12) + 8;
  v4 = *(int*)(*(int*)(a3 + 12) + 4);
  v3 = *(int*)(a3 + 32);
  v7 = *(int*)a3 + 8;
  v6 = 0;
  v23 = *(int*)(*(int*)(a3 + 12) + 4);
  if ( v3 )
    v26 = *(int*)(a3 + 24) + 8;
  else
    v26 = 0;
  if ( v3 )
    v25 = *(int*)(*(int*)(a3 + 24) + 4);
  else
    v25 = 0;
  if ( *(int*)(a3 + 44) )
    v6 = (*(int*)(a3 + 36) - 1) & ((*(int*)(a3 + 36) - 1 < 0) - 1);
  if ( *(int*)(a3 + 56) )
    v31 = *(int*)(a3 + 48) & ((*(int*)(a3 + 48) < 0) - 1);
  else
    v31 = -1;
  CFreqMem v28;
  if ( v5 && v4 && v6 < v5 && v31 )
  {
    v28.Append((LPBYTE) v7, v6);
    v8 = (LPBYTE)(v6 + v7);
    v9 = v5 - v6;
    v10 = v23;
    v27 = *(BYTE*)v24;
    if ( v9 >= v23 )
    {
      while ( 1 )
      {
        v11 = FindByte(v8, v9, v27);
        v12 = v11;
        if ( v11 == -1 )
          break;
        v28.Append( v8, v11);
        v9 -= v12;
        v8 += v12;
        if ( v9 < v10 )
          break;
        v15 = v10;
        v16 = v24;
        v17 = v8;
        v14 = 0;
        v13 = 1;
        do
        {
          if ( !v15 )
            break;
          v13 = *v17++ == *(LPBYTE)(v16++);
          --v15;
        }
        while ( v13 );
        if ( v13 )
        {
          v28.Append((LPBYTE) v26, v25);
          v18 = v23;
          v8 += v23;
          v9 -= v23;
          if ( v31 != -1 )
          {
            --v31;
            if ( !v31 )
              break;
          }
        }
        else
        {
          v14 =(BYTE) *v8;//(LOBYTE)
          v28.AddByte( v14);
          v18 = v23;
          ++v8;
          --v9;
        }
        if ( v9 < v18 )
          break;
        v10 = v23;
      }
    }
    v22 = v9;
    v21 = v8;
  }
  else
  {
    v22 = v5;
    v21 = (LPBYTE)v7;
  }
  v28.Append( v21, v22);
  v20 = CloneBinData(v28.GetPtr(), v28.GetSize());
 // v28 = &CFreqMem___vftable_;
  v28.Free();
  return v20;
}

//�ֽڼ����� - ���ֽڼ��滻
/*
    ���ø�ʽ�� ���ֽڼ��� ���ֽڼ��滻 ���ֽڼ� �����滻���ֽڼ����ֽڼ� �����滻�����ֽڼ������ֽڼ� �����滻�����ֽڼ��ݣ��������� �����滻����ʼλ�ãݣ��������� �滻���еĴ����ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�RpSubBin
    ����һ���ֽڼ������ֽڼ���ָ�������ֽڼ��ѱ��滻����һ���ֽڼ��������滻�����Ĵ���Ҳ�Ǳ�ָ���ġ�������Ϊ�������
    ����<1>������Ϊ�������滻���ֽڼ���������Ϊ���ֽڼ���bin������
    ����<2>������Ϊ�������滻�����ֽڼ���������Ϊ���ֽڼ���bin������
    ����<3>������Ϊ�������滻�����ֽڼ���������Ϊ���ֽڼ���bin���������Ա�ʡ�ԡ����ʡ�Ա���������Ĭ��Ϊ���ֽڼ���
    ����<4>������Ϊ�������滻����ʼλ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ����滻���ֽڼ�����ʼ����λ�á����ʡ�ԣ�Ĭ�ϴ�1��ʼ��
    ����<5>������Ϊ���滻���еĴ�����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ֽڼ������滻�Ĵ��������ʡ�ԣ�Ĭ�Ͻ������п��ܵ��滻��
*/

LIBAPI(void*, krnln_RpSubBin)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;

	LPBYTE pSrc = pArgInf[0].m_pBin;
	INT nSLen = pArgInf[0].m_pInt[1];
	if (nSLen <= 0 || !pSrc) return NULL;

	LPBYTE pDes = pArgInf[1].m_pBin;
	INT nDLen = pArgInf[1].m_pInt[1];

	pSrc += 2*sizeof(INT);
	INT nCount = pArgInf[4].m_int;
	if (pArgInf[4].m_dtDataType == _SDT_NULL) 
		nCount = 0x7FFFFFFF; // ����滻����21��

	INT nStart;
	if (pArgInf[3].m_dtDataType == _SDT_NULL || pArgInf[3].m_int <= 1)
		nStart = 0;
	else
		nStart = pArgInf[3].m_int - 1;

	if (nDLen <= 0 || !pDes || nCount <=0 || nStart >= nSLen || nDLen > nSLen) // �ؼ��������Ϸ���ֱ�ӷ���ԭ�ֽڼ�
		return CloneBinData(pSrc, nSLen);
	
	pDes += 2*sizeof(INT);
	LPBYTE pSub = NULL;
	INT nSubLen = 0;
	if (pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		nSubLen = pArgInf[2].m_pInt[1];
		if (nSubLen < 0)
			nSubLen = 0;
		else
			pSub = pArgInf[2].m_pBin + 2*sizeof(INT);
	}

	// ��ʼ����
	PTB pTb = initSubTb();
	if (!pTb)
		return CloneBinData(pSrc, nSLen);

	INT nPos;
	LPBYTE pFirst = pSrc;
	LPBYTE pSearch = pSrc + nStart;
	INT nSYLen = nSLen;
	LPBYTE pLast = pSrc + nSLen;
	//char* pMsg = (char*)malloc(256);
	//sprintf(pMsg,"addr:%x",pTb);
	//MessageBox(NULL,pMsg,"432",MB_OK);
	for (; nCount > 0; nCount--)
	{
		nPos = myinstring(pSearch, nSYLen, pDes, nDLen);
		if (nPos == -1)
			break;
		if (pSearch + nPos - pFirst > 0)
			recSub(&pTb, pFirst, pSearch + nPos - pFirst);

		if (nSubLen > 0)
			recSub(&pTb, pSub, nSubLen);

		pSearch += nPos + nDLen;
		pFirst = pSearch;
		nSYLen -= nPos + nDLen;
	}
	//MessageBox(NULL,"4","432",MB_OK);
	if (pLast - pFirst > 0)
		recSub(&pTb, pFirst, pLast - pFirst);

	//MessageBox(NULL,"5","432",MB_OK);
	// ���Ƽ�����
	LPBYTE pRetn = (LPBYTE)E_MAlloc_Nzero(pTb->len + 2*sizeof(INT));
	LPBYTE pRetnTmp = pRetn;
	*(LPINT)pRetnTmp = 1;
	pRetnTmp += sizeof(INT);
	*(LPINT)pRetnTmp = pTb->len;
	pRetnTmp += sizeof(INT);

	nCount = pTb->count;
	PTBRECORD pRec = &pTb->rec[0];
	//sprintf(pMsg,"nCount:%d,addr:%x",nCount,pTb);
	//MessageBox(NULL,pMsg,"432",MB_OK);
	for (int i = 0; i < nCount; i++)
	{
		//sprintf(pMsg,"addr:%x,nTLen:%d",pTbtmp[0],nTLen);
		//MessageBox(NULL,pMsg,"432",MB_OK);
		memcpy(pRetnTmp, pRec[i].addr, pRec[i].len);
		pRetnTmp += pRec[i].len;
	}
	if (pTb)
		free(pTb);

	return pRetn;
}
// {
// 
// 	return krnln_fnRpSubBin(nArgCount,(INT)&ArgInf);
// }
/*
extern "C" void* _cdecl krnln_RpSubBin (INT nArgCount,MDATA_INF ArgInf,...)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_pBin==NULL)
		return NULL;
	INT nLen = pArgInf[0].m_pInt [1];
	LPBYTE pData = pArgInf[0].m_pBin + 2*sizeof(INT);
	if(nLen==0)return NULL;
	if(pArgInf[1].m_pBin==NULL)//��Ҫ�滻���ֽڼ�
		return CloneBinData (pData, nLen);

	INT nSubLen = pArgInf[1].m_pInt [1];
	if(nSubLen > nLen)return NULL;
	if(nSubLen==0)
		return CloneBinData (pData, nLen);
	LPBYTE pObj = pArgInf[1].m_pBin + 2*sizeof(INT);
	
	LPBYTE pStrRpl = NULL;
	INT nStrRpl = 0;
	if(pArgInf[2].m_dtDataType !=_SDT_NULL && pArgInf[2].m_pBin)
	{
		pStrRpl = pArgInf[2].m_pBin + 2*sizeof(INT);
		nStrRpl = pArgInf[2].m_pInt [1];
	}

	INT nStart;
	if(pArgInf[3].m_dtDataType ==_SDT_NULL)
		nStart = 1;
	else
		nStart = pArgInf[3].m_int;

	INT nRplCount;
	if(pArgInf[4].m_dtDataType ==_SDT_NULL)
		nRplCount = 0x7fffffff;
	else
		nRplCount = pArgInf[4].m_int;

	INT nEnd = nLen - nSubLen;
	if(nStart > nEnd || nRplCount <= 0  || nStart <= 0)//Ѱ�ҵ��ı����ڿ�ʼѰ��λ�� �� û���滻����
		return CloneBinData (pData, nLen);

//ͳ���ҵ��Ĵ����ͻ��峤��
	LPBYTE pSrc = pData;
	LPBYTE pStart = pSrc + nStart -1;
	LPBYTE pEnd = pSrc + nEnd+1;
	INT nFind = 0;

	while(pStart < pEnd)
	{
		if(memcmp(pStart,pObj,nSubLen)==0)
		{
			nFind++;
			if(nFind == nRplCount)
				break;
			pStart+=nSubLen;
		}
		else
			pStart++;
	}


	if(nFind==0)//һ��Ҳû�ҵ�
		return CloneBinData (pData, nLen);

	INT nBuf = nLen + (nStrRpl - nSubLen) * nFind;
	LPBYTE pText = (LPBYTE)E_MAlloc(nBuf+2*sizeof(INT));
	LPBYTE pDest = pText;
	*(LPINT)pDest=1;
	pDest+=sizeof(INT);
	*(LPINT)pDest=nBuf;
	pDest+=sizeof(INT);

//��ʼ�滻

	pStart = pSrc + nStart -1;
	pEnd = pSrc + nEnd+1;

	while(pStart < pEnd)
	{
		if(memcmp(pStart,pObj,nSubLen)==0)
		{
			INT nStr = pStart - pSrc;
			memcpy(pDest,pSrc,nStr);//�����ϴζ�
			pDest+=nStr;
			if(pStrRpl)
			{
				memcpy(pDest,pStrRpl,nStrRpl);//�����滻�ı�
				pDest+=nStrRpl;
			}
			pStart+=nSubLen;
			pSrc = pStart; //����һ��;
			nFind--;
			if(nFind == 0)
			{
				if(pStart - pData <=nLen)
				{
					nStr = pEnd - pSrc+nSubLen-1;
					memcpy(pDest,pSrc,nStr);//�����滻�ı�
				}
				break;
			}
		}
		else
			pStart++;

	}

	return pText;
}
*/