#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"


//�ı����� - �ָ��ı�
/*
    ���ø�ʽ�� ���ı������页 �ָ��ı� ���ı��� ���ָ��ı������ı��� �����ָ���ı��ݣ��������� Ҫ���ص����ı���Ŀ�ݣ� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�split
    ��ָ���ı����зָ���طָ���һά�ı����顣������Ϊ�������
    ����<1>������Ϊ�����ָ��ı���������Ϊ���ı��ͣ�text�������������ֵ��һ������Ϊ����ı����򷵻�һ�������飬��û���κγ�Ա�����顣
    ����<2>������Ϊ�������ָ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�����ֵ���ڱ�ʶ���ı��߽硣�����ʡ�ԣ���Ĭ��ʹ�ð�Ƕ����ַ���Ϊ�ָ����������һ������Ϊ����ı����򷵻ص����������һ����Ա���������ġ����ָ��ı�����
    ����<3>������Ϊ��Ҫ���ص����ı���Ŀ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ʡ�ԣ���Ĭ�Ϸ������е����ı���

*/
#define IS_CC(p) p<0

LIBAPI(void*, krnln_split)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nCount = pArgInf [2].m_dtDataType == _SDT_NULL ? 0x7FFFFFFF : pArgInf [2].m_int;
	LPBYTE p;
	if (nCount <= 0) 
		return E_NULLARRAY();

	char* pSub = pArgInf [1].m_dtDataType == _SDT_NULL ? (LPSTR)"," : pArgInf [1].m_pText;
	INT nSubLen = mystrlen(pSub);

	char* pSrc = pArgInf[0].m_pText;
	if (!pSrc || !*pSrc)
		return E_NULLARRAY();

	if (nSubLen==0)
		nCount = -1;//����һ����Ա

	// ��ʼ����
	TBR tbr;
	INT nPos;
	char* pFirst = pSrc;
	char* cp = pSrc;
	for (; nCount > 0; nCount--)
	{
		nPos = mystrstr((char*)cp, (char*)pSub);
		if (nPos == -1)
			break;
		cp += nPos;
		tbr.add(pFirst, cp - pFirst);
		cp += nSubLen;
		pFirst = cp;
	}
	
	INT nSlen = mystrlen(cp) + cp - pSrc;
	char* pLast = pSrc + nSlen;
	if (pLast - pFirst > 0 && nCount != 0)
		tbr.add(pFirst, pLast - pFirst);

	// �����������ݡ�
	nCount = tbr.m_nCount;
	INT nSize = nCount * sizeof (DWORD);
	p = (LPBYTE)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = nCount;
	LPINT pp = (LPINT)(p + 2*sizeof(INT));
	for (int i=0; i < nCount; i++)
	{
		*pp = (INT)CloneTextData((char*)(tbr.m_data[i].addr), tbr.m_data[i].len);
		pp++;
	}
	return p;  // �����������顣
}

