#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ɾȫ����
/*
    ���ø�ʽ�� ���ı��͡� ɾȫ���� ���ı��� ��ɾ���ո���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�TrimAll
    ����һ���ı������а�����ɾ��������ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
    ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_TrimAll)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	register char *str1 = pSrc;
	if (!*str1) return NULL;

	// ��ʼ����
	TBR tbr;
	char* pFirst = pSrc;
	while (1)
	{
		//�׿�
		while ( *str1 )
		{
			if (*str1 == ' ')
				str1++;
			else if (*((unsigned short*)str1) == 0xA1A1)
				str1+=2;
			else
				break;
		}
		if (!*str1) break;
		pFirst = str1;
		if (*str1 < 0) {
			str1+=2;
		} else {
			str1++;
		}
		//��β
		while ( *str1 )
		{
			if (*str1 == ' ')
				break;
			else if (*((unsigned short*)str1) == 0xA1A1)
				break;
			if (*str1 < 0)
				str1+=2;
			else
				str1++;
		}
		if (str1 - pFirst > 0)
			tbr.add(pFirst, str1 - pFirst);
	}
	return tbr.toString();
}
