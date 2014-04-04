
// ConvertFormatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertFormat.h"
#include "ConvertFormatDlg.h"
#include "afxdialogex.h"
#include "Coordinate.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CConvertFormatDlg dialog




CConvertFormatDlg::CConvertFormatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConvertFormatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvertFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvertFormatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CConvertFormatDlg::OnBnClickedButtonConvert)
END_MESSAGE_MAP()


// CConvertFormatDlg message handlers

BOOL CConvertFormatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConvertFormatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConvertFormatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConvertFormatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool LessCoordinate (CCoordinate i, CCoordinate j) 
{ 
	return (i<j); 
}

void CConvertFormatDlg::OnBnClickedButtonConvert()
{
	CStdioFile myFile;
	CString strLine, str;

	MAPPOINTS mpts;
	mpts.clear();
	
	if(myFile.Open(TEXT("D:\\Richard\\Documents\\GitHub\\ConvertFormat\\gr7.csv"), CFile::modeRead) == TRUE)
	{
		int nLine = 0;
		double dX = 0, dY = 0, dZ = 0;
		while(myFile.ReadString(strLine) != FALSE)
		{
			LPCTSTR szToken(_T(","));
			int curPos = 0;
			CString strTmp(_T(""));
			
			strTmp = strLine.Tokenize(szToken, curPos);
			dX = _ttof(strTmp);
			
			strTmp = strLine.Tokenize(szToken, curPos);
			dY = _ttof(strTmp);

			strTmp = strLine.Tokenize(szToken, curPos);
			dZ = _ttof(strTmp);

			CCoordinate con(dX, dY, dZ);	

			VECPOINTS vecList;
			vecList.clear();
			MAPPOINTS::iterator iter = mpts.find( dX );
			if( iter != mpts.end() )
			{
				vecList = iter->second;	

			}

			vecList.push_back(con);
			std::sort( vecList.begin(), vecList.end(), LessCoordinate);
			//mpts[con] = dZ;
			mpts[dX] = vecList;
			//mpts.insert(std::make_pair(dX, vecList));
			nLine++;
		}

		//

		CStdioFile mFile;
		CFileException mExcept;
		mFile.Open(TEXT("D:\\Richard\\Documents\\GitHub\\ConvertFormat\\gr7.mgl"), CFile::modeCreate |CFile::modeWrite, &mExcept);
		
		dX = 0;
		strLine = TEXT("");
		for( MAPPOINTS::iterator iter = mpts.begin();
			iter != mpts.end();
			iter ++ )
		{
			VECPOINTS& vecPoints = iter->second;

			if( iter == mpts.begin() )
			{
				strLine.Format(TEXT("%lf\t"), iter->first);
				for( VECPOINTS::iterator vi = vecPoints.begin();
					vi != vecPoints.end();
					vi ++ )
				{
					str.Format(TEXT("%lf\t"), vi->GetY());
					strLine += str;
				}

				strLine += TEXT("\n");
				mFile.WriteString(strLine);
			}

			strLine.Format(TEXT("%lf\t"), iter->first);
			for( VECPOINTS::iterator vi = vecPoints.begin();
				vi != vecPoints.end();
				vi ++ )
			{
				str.Format(TEXT("%lf\t"), vi->GetZ());
				strLine += str;
			}

			strLine += TEXT("\n");
			mFile.WriteString(strLine);

		}

		mFile.Close();
	}
}
