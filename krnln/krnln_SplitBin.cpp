#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
//�ֽڼ����� - �ָ��ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ����页 �ָ��ֽڼ� ���ֽڼ� ���ָ��ֽڼ������ֽڼ� �����ָ���ֽڼ��ݣ��������� Ҫ���ص����ֽڼ���Ŀ�ݣ� - ϵͳ����֧�ֿ�->�ֽڼ�����
    Ӣ�����ƣ�SplitBin
    ��ָ���ֽڼ����зָ���طָ���һά�ֽڼ����顣������Ϊ�������
    ����<1>������Ϊ�����ָ��ֽڼ���������Ϊ���ֽڼ���bin�������������ֵ��һ������Ϊ����ֽڼ����򷵻�һ�������飬��û���κγ�Ա�����顣
    ����<2>������Ϊ�������ָ���ֽڼ���������Ϊ���ֽڼ���bin���������Ա�ʡ�ԡ����ڱ�ʶ���ֽڼ��߽硣�����������ʡ�ԣ���Ĭ��ʹ���ֽ� 0 ��Ϊ�ָ�����
    ����<3>������Ϊ��Ҫ���ص����ֽڼ���Ŀ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ʡ�ԣ���Ĭ�Ϸ������е����ֽڼ���
*/
LIBAPI(void*, krnln_SplitBin)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? 0x7FFFFFFF : pArgInf [2].m_int;
	if (nCount <= 0) 
		return E_NULLARRAY();
	
	LPBYTE pSrc = pArgInf[0].m_pBin ;
	if (!pSrc)
		return E_NULLARRAY();
	INT nSLen = pArgInf[0].m_pInt[1];
	if (nSLen <= 0)
		return E_NULLARRAY();
	pSrc += 2*sizeof(INT);

	LPBYTE pSub = NULL;
	INT nSubLen = 0;
	BYTE bMark [] = {0,0};
	if(pArgInf [1].m_dtDataType == _SDT_NULL)
	{
		pSub = bMark;
		nSubLen = 1;
	}
	else
	{
		if (pArgInf [1].m_pBin)
		{
			pSub = pArgInf [1].m_pBin + 2*sizeof(INT);
			nSubLen =  pArgInf [1].m_pInt[1];
		}
	}

	if (nSubLen == 0)
		nCount = -1;//����һ����Ա

	// ��ʼ����
	PTB pTb = initSubTb();
	if (!pTb)
		return E_NULLARRAY();
	
	INT nPos;
	INT nSYLen = nSLen;
	LPBYTE pFirst = pSrc;
	LPBYTE cp = pSrc;
	for (; nCount > 0; nCount--)
	{
		nPos = myinstring(cp, nSYLen, pSub, nSubLen);
		if (nPos == -1)
			break;
		cp += nPos;
		recSub(&pTb, pFirst, cp - pFirst);
		cp += nSubLen;
		nSYLen -= nPos + nSubLen;
		pFirst = cp;
	}
	LPBYTE pLast = pSrc + nSLen;
	if (pLast - pFirst > 0 && nCount != 0)
		recSub(&pTb, pFirst, pLast - pFirst);
	
	// �����������ݡ�
	nCount = pTb->count;
	PTBRECORD pRec = &pTb->rec[0];
	INT nSize = nCount * sizeof (DWORD);
	LPBYTE p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = nCount;
	LPINT pp = (LPINT)(p + 2*sizeof(INT));
	for (int i=0; i < nCount; i++)
	{
		*pp = (INT)CloneBinData((LPBYTE)(pRec[i].addr), pRec[i].len);
		pp++;
	}
	
	if (pTb)
		free(pTb);
	return p;  // �����������顣
}
