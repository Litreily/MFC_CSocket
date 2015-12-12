// ServerSocket.cpp : 实现文件
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


// CServerSocket 成员函数


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_pDlg->RecvData(this);
	CSocket::OnReceive(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_pDlg->RemoveClient(this);
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_pDlg->AddClient();
	CSocket::OnAccept(nErrorCode);
}
