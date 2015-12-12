
// PhoneServerDlg.h : 头文件
//

#pragma once
#include "ServerSocket.h"
#include "afxwin.h"
class CServerSocket;
// CPhoneServerDlg 对话框
class CPhoneServerDlg : public CDialogEx
{
// 构造
public:
	CPhoneServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	CServerSocket* listenSocket;			// 用于打开服务器
	CPtrList m_clientList;					// 链表用于存储用户
	bool m_connect;							
	void AddClient();						// 增加用户，响应用户请求
	void RemoveClient(CServerSocket* pSocket);	// 移除下线的用户
	void RecvData(CServerSocket* pSocket);		// 获取数据
	void UpdateEvent(CString str);				// 更新事件日志
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);	//字符转换
	void SendMSG(CString str);					// 发送消息给各个客户端
	void ControlPC(CString AndroidControl);		// 手机控制PC的响应函数
// 对话框数据
	enum { IDD = IDD_PHONESERVER_DIALOG };

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
	afx_msg void OnBnClickedStartserver();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	UINT m_port;
	CEdit m_event;
	UINT m_userCount;
	afx_msg void OnClose();
};
