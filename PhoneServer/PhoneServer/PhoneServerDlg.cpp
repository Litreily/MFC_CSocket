
// PhoneServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneServer.h"
#include "PhoneServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhoneServerDlg �Ի���



CPhoneServerDlg::CPhoneServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhoneServerDlg::IDD, pParent)
	, m_port(8000)
	, m_userCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_connect = false;
}

void CPhoneServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Control(pDX, IDC_EventRecord, m_event);
	DDX_Text(pDX, IDC_UserCount, m_userCount);
}

BEGIN_MESSAGE_MAP(CPhoneServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_StartServer, &CPhoneServerDlg::OnBnClickedStartserver)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPhoneServerDlg ��Ϣ�������

BOOL CPhoneServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPhoneServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPhoneServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPhoneServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhoneServerDlg::OnBnClickedStartserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
		m_connect = false;
		SetDlgItemText(IDC_StartServer, _T("�򿪷�����"));
		UpdateEvent(_T("ϵͳ�رշ�����."));
		return;
	}
	listenSocket = new CServerSocket();
	listenSocket->m_pDlg = this;
	if (!listenSocket)
	{
		AfxMessageBox(_T("�����׽��ֳ���"));
		return;
	}
	UpdateData(true);
	if (!listenSocket->Create(m_port))
	{
		AfxMessageBox(_T("�����׽��ִ���"));
		listenSocket->Close();
		return;
	}
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
		listenSocket->Close();
		return;
	}
	m_connect = true;
	SetDlgItemText(IDC_StartServer, _T("�رշ�����"));
	UpdateEvent(_T("ϵͳ�򿪷�����."));
}


BOOL CPhoneServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPhoneServerDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();
	str += _T("\r\n");
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;
	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);
	m_event.SetSel(lastLine+1,lastLine+2,0);
	m_event.ReplaceSel(string);
}

void CPhoneServerDlg::AddClient()
{
	CServerSocket *pSocket = new CServerSocket;
	pSocket->m_pDlg = this;
	if (!pSocket)
	{
		AfxMessageBox(_T("�ڴ治��,�ͻ����ӷ�����ʧ�ܣ�"));
		delete pSocket;
		return;
	}
	listenSocket->Accept(*pSocket);

	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_clientList.AddTail(pSocket);
	m_userCount = m_clientList.GetCount();
	UpdateData(false);
	UpdateEvent(_T("�û����ӷ�����."));
	SendMSG(_T("���!"));
}

void CPhoneServerDlg::RemoveClient(CServerSocket* pSocket)
{
	POSITION nPos = m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		CServerSocket* pSockItem = (CServerSocket*)m_clientList.GetNext(nPos);
		if (pSockItem->m_hSocket == pSocket->m_hSocket)
		{			
			pSockItem->Close();
			delete pSockItem;
			m_clientList.RemoveAt(nTmpPos);
			m_userCount = m_clientList.GetCount();
			UpdateData(false);
			UpdateEvent(_T("�û��뿪."));
			return;
		}
		nTmpPos = nPos;
	}
}

void CPhoneServerDlg::RecvData(CServerSocket* pSocket)
{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)
	{
		str = pData;
		ControlPC(str);
		SendMSG(str);
		//CString IPadd;
		//UINT port;
		//pSocket->GetPeerName(IPadd, port);
		//str = _T("����") + IPadd + _T("���ݣ�") + str;
		//str = _T("�������ݣ�") + str;
		//UpdateEvent(str);
	}
	delete pData;
	pData = NULL;
}

BOOL CPhoneServerDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (nlen<n)
		return FALSE;

	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);

	return TRUE;
}

void CPhoneServerDlg::SendMSG(CString str)
{
	//����Э��ͷ
	int length = str.GetLength() * 2 + 1;
	char *pSend = new char[length];
	memset(pSend, 0, length);
	if (!WChar2MByte(str.GetBuffer(0), pSend, length))
	{
		AfxMessageBox(_T("�ַ�ת��ʧ��"));
		delete pSend;
		return;
	}
	POSITION nPos = m_clientList.GetHeadPosition();
	while (nPos)
	{
		CServerSocket* pTemp = (CServerSocket*)m_clientList.GetNext(nPos);
		pTemp->Send(pSend, length);
	}

	delete pSend;
}

void CPhoneServerDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
	}
	CDialogEx::OnClose();
}

void CPhoneServerDlg::ControlPC(CString AndroidControl)
{
	/**************************** ���ƿṷ���� ************************/
	if (AndroidControl == "mop")									//�򿪿ṷ������
	{
		ShellExecute(NULL, _T("open"), _T("C:\\Program Files (x86)\\KuGou\\KGMusic\\KuGou.exe"), NULL, NULL, SW_SHOWNORMAL);
	}
	else if (AndroidControl == "mcl")								//�رղ�����
	{
		DWORD id_num;
		HWND hWnd = ::FindWindow(_T("kugou_ui"), NULL);
		GetWindowThreadProcessId(hWnd, &id_num);					//ע�⣺�ڶ��������ǽ��̵�ID������ֵ���̵߳�ID��
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id_num);
		TerminateProcess(hd, 0);
	}
	else if (AndroidControl == "mpl" || AndroidControl == "mpa")	//����/��ͣ
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mbf")								//ǰһ��
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_LEFT, 0, 0, 0);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mne")								//��һ��
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_RIGHT, 0, 0, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mvu")								//����+
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_UP, 0, 0, 0);
		keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mvd")								//����-
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_DOWN, 0, 0, 0);
		keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	/**************************** ���Ƶ��Կ��ػ� ************************/
	else if (AndroidControl == "ssd")	//	�ػ�system shutdown
	{
		system("shutdown -s -t 0");
	}
	else if (AndroidControl == "srb")	//	����system reboot
	{
		system("shutdown -r -t 0");
	}
	else if (AndroidControl == "slo")	//	ע��system logoff
	{
		ExitWindowsEx(EWX_LOGOFF, NULL);
	}
	else if (AndroidControl == "slk")	//	����system lock
	{
		typedef BOOL(*LOCKFUN)(VOID);
		HINSTANCE hInstance = ::LoadLibrary(_T("user32.dll"));
		LOCKFUN pFun = (LOCKFUN)::GetProcAddress(hInstance, "LockWorkStation");
		pFun();
	}
	/**************************** ����PPT���� ************************/
	else if (AndroidControl == "ppl")
	{
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "pne")
	{
		keybd_event('N', 0, 0, 0);
		keybd_event('N', 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "pbf")
	{
		keybd_event('P', 0, 0, 0);
		keybd_event('p', 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "esc")
	{
		keybd_event(VK_ESCAPE, 0, 0, 0);
		keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
	}

}
