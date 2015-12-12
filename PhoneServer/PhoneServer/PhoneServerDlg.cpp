
// PhoneServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhoneServer.h"
#include "PhoneServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPhoneServerDlg 对话框



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


// CPhoneServerDlg 消息处理程序

BOOL CPhoneServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPhoneServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPhoneServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhoneServerDlg::OnBnClickedStartserver()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
		m_connect = false;
		SetDlgItemText(IDC_StartServer, _T("打开服务器"));
		UpdateEvent(_T("系统关闭服务器."));
		return;
	}
	listenSocket = new CServerSocket();
	listenSocket->m_pDlg = this;
	if (!listenSocket)
	{
		AfxMessageBox(_T("创建套接字出错！"));
		return;
	}
	UpdateData(true);
	if (!listenSocket->Create(m_port))
	{
		AfxMessageBox(_T("创建套接字错误！"));
		listenSocket->Close();
		return;
	}
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("监听失败！"));
		listenSocket->Close();
		return;
	}
	m_connect = true;
	SetDlgItemText(IDC_StartServer, _T("关闭服务器"));
	UpdateEvent(_T("系统打开服务器."));
}


BOOL CPhoneServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
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
		AfxMessageBox(_T("内存不足,客户连接服务器失败！"));
		delete pSocket;
		return;
	}
	listenSocket->Accept(*pSocket);

	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_clientList.AddTail(pSocket);
	m_userCount = m_clientList.GetCount();
	UpdateData(false);
	UpdateEvent(_T("用户连接服务器."));
	SendMSG(_T("你好!"));
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
			UpdateEvent(_T("用户离开."));
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
		//str = _T("接收") + IPadd + _T("数据：") + str;
		//str = _T("接收数据：") + str;
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
	//生成协议头
	int length = str.GetLength() * 2 + 1;
	char *pSend = new char[length];
	memset(pSend, 0, length);
	if (!WChar2MByte(str.GetBuffer(0), pSend, length))
	{
		AfxMessageBox(_T("字符转换失败"));
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_connect)
	{
		delete listenSocket;
		listenSocket = NULL;
	}
	CDialogEx::OnClose();
}

void CPhoneServerDlg::ControlPC(CString AndroidControl)
{
	/**************************** 控制酷狗播放 ************************/
	if (AndroidControl == "mop")									//打开酷狗播放器
	{
		ShellExecute(NULL, _T("open"), _T("C:\\Program Files (x86)\\KuGou\\KGMusic\\KuGou.exe"), NULL, NULL, SW_SHOWNORMAL);
	}
	else if (AndroidControl == "mcl")								//关闭播放器
	{
		DWORD id_num;
		HWND hWnd = ::FindWindow(_T("kugou_ui"), NULL);
		GetWindowThreadProcessId(hWnd, &id_num);					//注意：第二个参数是进程的ID，返回值是线程的ID。
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id_num);
		TerminateProcess(hd, 0);
	}
	else if (AndroidControl == "mpl" || AndroidControl == "mpa")	//播放/暂停
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mbf")								//前一首
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_LEFT, 0, 0, 0);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mne")								//下一首
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_RIGHT, 0, 0, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mvu")								//音量+
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_UP, 0, 0, 0);
		keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (AndroidControl == "mvd")								//音量-
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_DOWN, 0, 0, 0);
		keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
	/**************************** 控制电脑开关机 ************************/
	else if (AndroidControl == "ssd")	//	关机system shutdown
	{
		system("shutdown -s -t 0");
	}
	else if (AndroidControl == "srb")	//	重启system reboot
	{
		system("shutdown -r -t 0");
	}
	else if (AndroidControl == "slo")	//	注销system logoff
	{
		ExitWindowsEx(EWX_LOGOFF, NULL);
	}
	else if (AndroidControl == "slk")	//	锁定system lock
	{
		typedef BOOL(*LOCKFUN)(VOID);
		HINSTANCE hInstance = ::LoadLibrary(_T("user32.dll"));
		LOCKFUN pFun = (LOCKFUN)::GetProcAddress(hInstance, "LockWorkStation");
		pFun();
	}
	/**************************** 控制PPT播放 ************************/
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
