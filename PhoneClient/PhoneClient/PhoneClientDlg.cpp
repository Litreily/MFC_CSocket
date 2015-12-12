
// PhoneClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhoneClient.h"
#include "PhoneClientDlg.h"
#include "afxdialogex.h"

#define port 8000
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


// CPhoneClientDlg �Ի���



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


// CPhoneClientDlg ��Ϣ�������

BOOL CPhoneClientDlg::OnInitDialog()
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
	//pSock = new CClientSocket();
	//if (!pSock)
	//{
	//	AfxMessageBox(_T("�ڴ治�㣡"));
	//	return false;
	//}

	//if (!pSock->Create())
	//{
	//	AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
	//	return false;
	//}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPhoneClientDlg::OnPaint()
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
HCURSOR CPhoneClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhoneClientDlg::OnBnClickedConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_connect)
	{
		m_connect = false;
		pSock->Close();
		delete pSock;
		pSock = NULL;
		m_ConPC.SetWindowTextW(_T("���ӷ�����"));
		UpdateData(false);
		return;
	}
	else
	{
		pSock = new CClientSocket();
		if (!pSock)
		{
			AfxMessageBox(_T("�ڴ治�㣡"));
			return;
		}

		if (!pSock->Create())
		{
			AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
			return;
		}
	}
	if (!pSock->Connect(_T("127.0.0.1"), port))
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return;
	}
	else
	{
		m_connect = true;
		m_ConPC.SetWindowTextW(_T("�Ͽ�������"));
		UpdateData(false);
	}
}


void CPhoneClientDlg::OnBnClickedSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ����ר�ô����/����û���
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
