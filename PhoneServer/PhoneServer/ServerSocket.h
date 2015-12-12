#pragma once

// CServerSocket ÃüÁîÄ¿±ê
#include "PhoneServerDlg.h"

class CPhoneServerDlg;

class CServerSocket : public CSocket
{
public:
	CPhoneServerDlg* m_pDlg;
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
};


