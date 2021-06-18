#include "stdafx.h"
#include "Myfunctions.h"
#include <stdio.h>
BOOL __cdecl ReadPepi(HANDLE hFile, TBR* tbr)
{
	DWORD nSize;
	char* pBuffer = NULL;
	char* pHH = (char*)"\r\n\0";
	while(1)
	{
		nSize = 0;
		if (!PeekNamedPipe(hFile, NULL, NULL, NULL, &nSize, NULL))
			return FALSE;
		if (!nSize)
			break;
		pBuffer = (char*)malloc(0x400);
		if (!ReadFile(hFile, pBuffer, 0x400, &nSize, NULL))
		{
			if(pBuffer) free(pBuffer);
			return FALSE;
		}
		if (!nSize)
			break;
		tbr->add(pBuffer, nSize);
		tbr->add(pHH, 2);
		pBuffer = NULL;
	}
	if(pBuffer) free(pBuffer);
	return TRUE;
}
/*
// ���� - ���п���̨����
���ø�ʽ�� ���߼��͡� ���п���̨���� ���ı��� �����е������У����ı��ͱ��� ��׼������ݴ�ű����ݣ����ı��ͱ��� ����������ݴ�ű����ݣ��������ͱ��� ����ֵ��ű����ݣ� - ϵͳ����֧�ֿ�->����
Ӣ�����ƣ�RunConsoleApp
����ָ���Ŀ���̨����(����򿪿���̨����),�����Ƿ����гɹ�.������Ϊ�������
����<1>������Ϊ�������е������С�������Ϊ���ı��ͣ�text�������ṩ�����п���̨������������ı���
����<2>������Ϊ����׼������ݴ�ű�����������Ϊ���ı��ͣ�text���������Ա�ʡ�ԣ��ṩ��������ʱֻ���ṩ����������̨�����������ڼ��������׼����豸���������ݽ�����ŵ��˱����С����������ʡ�ԣ�Ĭ��ֵΪ�ޡ�
����<3>������Ϊ������������ݴ�ű�����������Ϊ���ı��ͣ�text���������Ա�ʡ�ԣ��ṩ��������ʱֻ���ṩ����������̨�����������ڼ��������׼�����豸���������ݽ�����ŵ��˱����С����������ʡ�ԣ�Ĭ��ֵΪ�ޡ�
����<4>������Ϊ������ֵ��ű�����������Ϊ�������ͣ�int���������Ա�ʡ�ԣ��ṩ��������ʱֻ���ṩ����������̨�����˳�ʱ���ṩ�ķ���ֵ������ŵ��˱����С����������ʡ�ԣ�Ĭ��ֵΪ�ޡ�

*/
LIBAPI(BOOL, krnln_RunConsoleApp)
{
	PMDATA_INF pArgInf = &ArgInf;
	char* pCMD = pArgInf[0].m_pText;

	char** pStdOut = NULL;
	char** pStdError = NULL;
	PINT pRetn = NULL;
	if (pArgInf[1].m_dtDataType != _SDT_NULL)
		pStdOut = pArgInf[1].m_ppText;
	if (pArgInf[2].m_dtDataType != _SDT_NULL)
		pStdError = pArgInf[2].m_ppText;
	if (pArgInf[3].m_dtDataType != _SDT_NULL)
		pRetn = (PINT)pArgInf[3].m_int;

	if (!pCMD || !*pCMD)
	{
		if (pRetn)
			*pRetn = 0;
		if (pStdOut && *pStdOut)
		{
			E_MFree(((void*)(*pStdOut)));
			*pStdOut = NULL;
		}
		if (pStdError && *pStdError)
		{
			E_MFree(((void*)(*pStdError)));
			*pStdError = NULL;
		}
		return FALSE;
	}

	SECURITY_ATTRIBUTES pa;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	memset(&pi, 0, sizeof(pi));
	pi.hProcess = NULL;
	pi.hThread = NULL;
	pi.dwProcessId = NULL;
	pi.dwThreadId = NULL;
	memset(&pa, 0, sizeof(pa));
	pa.lpSecurityDescriptor = NULL;
	pa.nLength = sizeof(pa);
	pa.bInheritHandle = 1;

	HANDLE hFile1 = NULL;
	HANDLE hFile2 = NULL;
	HANDLE hStdOut = NULL;
	HANDLE hStdError = NULL;
	BOOL bSucess = FALSE;
	if(CreatePipe(&hFile1, &hStdOut, &pa, NULL))
	{
		if(CreatePipe(&hFile2, &hStdError, &pa, NULL))
		{
			memset(&si, 0, sizeof(si));
			si.cb = 68;
			si.dwFlags = 257;
			si.wShowWindow = 0;
			si.hStdOutput = hStdOut;
			si.hStdError = hStdError;

			if (CreateProcess(NULL, pCMD, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
			{
				BOOL bWait = TRUE;
				TBR tbrOut;
				TBR tbrError;
				do 
				{
					if (bWait)
						if (WaitForSingleObject(pi.hProcess, 0x64) != WAIT_TIMEOUT)
							bWait = FALSE;
				} while (bWait);
				if (pRetn)
					if (!GetExitCodeProcess(pi.hProcess, (LPDWORD)pRetn))
						*pRetn = 0;
				bSucess = TRUE;
				if (pStdOut)
				{
					ReadPepi(hFile1, &tbrOut);
					if (*pStdOut) E_MFree(*pStdOut);
					*pStdOut = tbrOut.toString();
				}
				if (pStdError)
				{
					ReadPepi(hFile2, &tbrError);
					if (*pStdError) E_MFree(*pStdError);
					*pStdError = tbrError.toString();
				}
			}
		}
	}
	if (hFile1)
		CloseHandle(hFile1);
	if (hFile2)
		CloseHandle(hFile2);
	if (hStdOut)
		CloseHandle(hStdOut);
	if (hStdError)
		CloseHandle(hStdError);
	return bSucess;
}