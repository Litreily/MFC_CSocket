
// PhoneClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "PhoneClientDlg.h"
#include "afxdialogex.h"

#define port 8000
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


// CPhoneClientDlg 对话框



CPhoneClientDlg::CPhoneClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhoneClientDlg::IDD, pParent)
	, m_DataSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_connect = false;
}

void CPhoneClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Connect, m_ConPC);
	DDX_Text(pDX, IDC_DataSend, m_DataSend);
}

BEGIN_MESSAGE_MAP(CPhoneClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Connect, &CPhoneClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_Send, &CPhoneClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CPhoneClientDlg 消息处理程序

BOOL CPhoneClientDlg::OnInitDialog()
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
	//pSock = new CClientSocket();
	//if (!pSock)
	//{
	//	AfxMessageBox(_T("内存不足！"));
	//	return false;
	//}

	//if (!pSock->Create())
	//{
	//	AfxMessageBox(_T("创建套接字失败！"));
	//	return false;
	//}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPhoneClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPhoneClientDlg::OnPaint()
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
HCURSOR CPhoneClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhoneClientDlg::OnBnClickedConnect()
{
	// TODO:  在此添加控件通知处理程序代码

	if (m_connect)
	{
		m_connect = false;
		pSock->Close();
		delete pSock;
		pSock = NULL;
		m_ConPC.SetWindowTextW(_T("连接服务器"));
		UpdateData(false);
		return;
	}
	else
	{
		pSock = new CClientSocket();
		if (!pSock)
		{
			AfxMessageBox(_T("内存不足！"));
			return;
		}

		if (!pSock->Create())
		{
			AfxMessageBox(_T("创建套接字失败！"));
			return;
		}
	}
	if (!pSock->Connect(_T("127.0.0.1"), port))
	{
		AfxMessageBox(_T("连接服务器失败！"));
		return;
	}
	else
	{
		m_connect = true;
		m_ConPC.SetWindowTextW(_T("断开服务器"));
		UpdateData(false);
	}
}


void CPhoneClientDlg::OnBnClickedSend()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_connect)return;
	UpdateData(true);
	if (m_DataSend != "")
	{
		int length = m_DataSend.GetLength() * 2 + 1;
		char* pBuff = new char[length];
		memset(pBuff, 0, length);
		WChar2MByte(m_DataSend.GetBuffer(0), pBuff, length);
		pSock->SendMSG(pBuff, length);
	}
}

BOOL CPhoneClientDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if (nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

BOOL CPhoneClientDlg::PreTranslateMessage(MSG* pMsg)
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
