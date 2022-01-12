#pragma once


// RotationDialog 대화 상자

class RotationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RotationDialog)

public:
	RotationDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~RotationDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_rotate_sldi;
	CEdit m_rotateangle;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_edit_value;
};
