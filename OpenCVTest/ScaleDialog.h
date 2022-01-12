#pragma once


// ScaleDialog 대화 상자

class ScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDialog)

public:
	ScaleDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ScaleDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_scale_sld;
	CEdit m_scale_edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnClose();
//	afx_msg void OnNcDestroy();
	virtual void PostNcDestroy();
	void CalculateX();
	void CalculateY();
	CSliderCtrl m_scalex_sld;
	CSliderCtrl m_scaley_sld;
	CEdit m_scalex_edit;
	CEdit m_scaley_edit;
	CEdit m_totalx;
	CEdit m_totaly;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
};
