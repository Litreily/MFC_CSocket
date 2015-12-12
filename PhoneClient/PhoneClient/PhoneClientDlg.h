
// PhoneClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ClientSocket.h"

// CPhoneClientDlg 对话框
class CPhoneClientDlg : public CDialogEx
{
// 构造
public:
	CPhoneClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	bool m_connect;
	CClientSocket* pSock;
// 对话框数据
	enum { IDD = IDD_PHONECLIENT_DIALOG };
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	CButton m_ConPC;
	afx_msg void OnBnClickedSend();
	CString m_DataSend;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
