// ClientSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "ClientSocket.h"
#include "PhoneClientDlg.h"

// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket ��Ա����


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;

	leng = Receive(pData, 1024, 0);
	str = pData;

	((CPhoneClientDlg*)theApp.GetMainWnd())->SetDlgItemTextW(IDC_DataReceive, str);
	delete pData;
	pData = NULL;
	CSocket::OnReceive(nErrorCode);
}

BOOL CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	//����Э��ͷ
	if (Send(lpBuff, nlen) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	}

	return  TRUE;
}