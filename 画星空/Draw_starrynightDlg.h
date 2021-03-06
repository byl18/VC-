
// Draw_starrynightDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDraw_starrynightDlg 对话框
class CDraw_starrynightDlg : public CDialogEx
{
// 构造
public:
	CDraw_starrynightDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAW_STARRYNIGHT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CScrollBar m_scrollbar1;
	CEdit m_disinfo;
	int ChangeDisplayInfo(int pos);
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton5();
	CEdit m_disinfo2;
	CScrollBar m_scrollbar2;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int ChangeDisplayInfo2(int pos2);
	CEdit m_disinfo3;
	int ChangeDisplayInfo3(int pos3);
	CScrollBar m_scrollbar3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
