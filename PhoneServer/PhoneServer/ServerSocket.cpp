// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneServer.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket ��Ա����


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_pDlg->RecvData(this);
	CSocket::OnReceive(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_pDlg->RemoveClient(this);
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_pDlg->AddClient();
	CSocket::OnAccept(nErrorCode);
}
