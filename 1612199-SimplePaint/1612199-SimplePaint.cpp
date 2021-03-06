// 1612199-SimplePaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1612199-SimplePaint.h"
#include <windowsx.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>
#include <vector>

#include "CStyle.h"
#include "CPoint.h"
#include "CShape.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CCircle.h"
#include "CSquare.h"
#include "CDot.h"
using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY1612199SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1612199SIMPLEPAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1612199SIMPLEPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1612199SIMPLEPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// ================ Define ================
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0

#define PEN_SOLID 0
#define PEN_DASH 1
#define PEN_DOT 2
#define PEN_DASHDOT 3
#define PEN_DASHDOTDOT 4

// ================ My Global Variable ===================
HWND hComboBoxSize, hComboBoxStyle, hStatusBar;

RECT rectPaint;

CStyle g_StypePen;
vector<CShape*> g_ListShape;
bool isDrawing = false;
CPoint CP_Start = CPoint(-1, -1), CP_End = CPoint(-1, -1);

int selected = 0;
vector<CShape*> g_Prototypes;

// =======

CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(0, 0, 0); // Red
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn

// ==================== My Functions =====================

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	InitCommonControls();
	TBBUTTON tbButtons[] =
	{
		{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	};

	HWND hToolBarWnd = CreateToolbarEx(hwnd,
		WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS ,
		ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
		0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
		BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
		sizeof(TBBUTTON));

	
	// lấy kích thước của toolbar
	RECT toolBarRect;
	GetClientRect(hToolBarWnd, &toolBarRect);

	TBBUTTON userButtons[] =
	{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ 0, ID_DRAW_DOT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 1, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 2, ID_DRAW_CIRCLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 3, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 4, ID_DRAW_SQUARE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 5, ID_DRAW_LINE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};
	TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP1 };
	// Thêm danh sách ảnh vào toolbar
	int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap) / sizeof(TBADDBITMAP),
		(LPARAM)(LPTBADDBITMAP)&tbBitmap);
	// Xác định chỉ mục hình ảnh c ủa mỗi button từ ảnh bự liên hoàn nhiều tấm
	userButtons[1].iBitmap += idx;
	userButtons[2].iBitmap += idx;
	userButtons[3].iBitmap += idx;
	userButtons[4].iBitmap += idx;
	userButtons[5].iBitmap += idx;
	userButtons[6].iBitmap += idx;
	// Thêm nút bấm vào toolbar
	SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(userButtons) / sizeof(TBBUTTON),
		(LPARAM)(LPTBBUTTON)&userButtons);

	// comboBox kích thước nét vẽ
	hComboBoxSize = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_SIMPLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		185, 0, 45, 100, hToolBarWnd, NULL, lpCreateStruct->hInstance, NULL);

	SetWindowFont(hComboBoxSize, hFont, TRUE);

	// khởi tạo giá trị trong combobox
	WCHAR Planets[5][2] =
	{
		L"1", L"2", L"3", L"4", L"5"
	};

	WCHAR A[2];

	memset(&A, 0, sizeof(A));
	for (int k = 0; k < 5; k++)
	{
		wcscpy_s(A, sizeof(A) / sizeof(WCHAR), (WCHAR*)Planets[k]);

		SendMessage(hComboBoxSize, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}

	SendMessage(hComboBoxSize, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

	
	// tạo combobox set style cho pen
	hComboBoxStyle = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_SIMPLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		245, 0, 120, 100, hToolBarWnd, NULL, lpCreateStruct->hInstance, NULL);

	SetWindowFont(hComboBoxStyle, hFont, TRUE);
	// khởi tạo giá trị trong combobox
	WCHAR Styles[5][15] =
	{
		L"Solid", L"Dash", L"Dot", L"DashDot", L"DashDotDot"
	};

	WCHAR bufferSetStyle[15];

	memset(&bufferSetStyle, 0, sizeof(bufferSetStyle));
	for (int k = 0; k < 5; k++)
	{
		wcscpy_s(bufferSetStyle, sizeof(bufferSetStyle) / sizeof(WCHAR), (WCHAR*)Styles[k]);

		SendMessage(hComboBoxStyle, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)bufferSetStyle);
	}

	SendMessage(hComboBoxStyle, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	

	// tạo status bar
	hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, (PCTSTR)NULL, SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwnd, NULL, lpCreateStruct->hInstance, NULL);

	int Parts[] = { 80, 250, 420, rectPaint.right };
	SendMessage(hStatusBar, SB_SETPARTS, (WPARAM)sizeof(Parts) / sizeof(int), (LPARAM)Parts);

	// tạo kích thước cho vùng vẽ
	RECT rectStatusBar;
	GetClientRect(hStatusBar, &rectStatusBar);

	GetClientRect(hwnd, &rectPaint);
	rectPaint.top = toolBarRect.bottom + 5;
	rectPaint.bottom -= rectStatusBar.bottom;

	// tạo text cho status bar
	SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"Ready");

	WCHAR buffer[15];
	swprintf_s(buffer, 15, L"%d x %d", rectPaint.right, rectPaint.bottom);
	SendMessage(hStatusBar, SB_SETTEXT, 2, (LPARAM)buffer);

	

	// khởi tạo prototypes
	g_Prototypes.push_back(new CLine());
	g_Prototypes.push_back(new CEllipse());
	g_Prototypes.push_back(new CCircle());
	g_Prototypes.push_back(new CRectangle());
	g_Prototypes.push_back(new CSquare());
	g_Prototypes.push_back(new CDot());

	

	return true;
}
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_FILE_NEW:
		g_ListShape.clear();
		InvalidateRect(hwnd, &rectPaint, TRUE);
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
		// color
	case ID_CHOOSE_COLOR:
		ZeroMemory(&cc, sizeof(CHOOSECOLOR));
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		if (ChooseColor(&cc))
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}
		g_StypePen.SetColor(rgbCurrent);
		break;

		// button
	case ID_DRAW_LINE:
		ShowWindow(hComboBoxSize, SW_SHOW);
		ShowWindow(hComboBoxStyle, SW_SHOW);
		selected = 0;
		break;
	case ID_DRAW_ELLIPSE:
		ShowWindow(hComboBoxSize, SW_SHOW);
		ShowWindow(hComboBoxStyle, SW_SHOW);
		selected = 1;
		break;
	case ID_DRAW_CIRCLE:
		ShowWindow(hComboBoxSize, SW_SHOW);
		ShowWindow(hComboBoxStyle, SW_SHOW);
		selected = 2;
		break;
	case ID_DRAW_RECTANGLE:
		ShowWindow(hComboBoxSize, SW_SHOW);
		ShowWindow(hComboBoxStyle, SW_SHOW);
		selected = 3;
		break;
	case ID_DRAW_SQUARE:
		ShowWindow(hComboBoxSize, SW_SHOW);
		ShowWindow(hComboBoxStyle, SW_SHOW);
		selected = 4;
		break;
	case ID_DRAW_DOT:
		ShowWindow(hComboBoxSize, SW_HIDE);
		ShowWindow(hComboBoxStyle, SW_HIDE);
		selected = 5;
		break;
	}

	// notify
	if (codeNotify == CBN_SELCHANGE)
	{
		// style
		int nType = ComboBox_GetCurSel(hComboBoxStyle);
		switch (nType)
		{
		case PEN_SOLID:
			g_StypePen.SetStyle(PS_SOLID);
			break;
		case PEN_DASH:
			g_StypePen.SetStyle(PS_DASH);
			break;
		case PEN_DOT:
			g_StypePen.SetStyle(PS_DOT);
			break;
		case PEN_DASHDOT:
			g_StypePen.SetStyle(PS_DASHDOT);
			break;
		case PEN_DASHDOTDOT:
			g_StypePen.SetStyle(PS_DASHDOTDOT);
			break;
		}

		// kích thước
		WCHAR buffer[3];
		ComboBox_GetText(hComboBoxSize, buffer, 3);
		g_StypePen.SetWidth(wcstol(buffer, NULL, 10));

		if (wcstol(buffer, NULL, 10) > 1 && nType != PEN_SOLID)
		{
			MessageBox(0, L"This style is valid only when the pen width is one or less in device units. We set size to one.", 
				L"Warning", MB_ICONINFORMATION | MB_OK);
			g_StypePen.SetWidth(1);
			SendMessage(hComboBoxSize, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
		}
	}
}
LRESULT OnNotify(HWND hwnd, int idFrom, NMHDR *pnm)
{
	return 0;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	// TODO: Add any drawing code that uses hdc here...

	for (int i = 0; i < g_ListShape.size(); i++)
	{
		if (g_ListShape[i] != NULL)
		{
			g_ListShape[i]->Draw(hdc);
		}
	}
	
	// if để không bị tình trạng tự vẽ khi click vào comboBox sau đó click ra màn hình
	// mặc dù nó không lưu vào listShape nhưng nó vẫn vẽ ra màn hình
	if (isDrawing == true && selected != 5)
	{
		g_Prototypes[selected]->SetStyle(g_StypePen);
		g_Prototypes[selected]->Draw(hdc);
	}
	else
		if (selected == 5)
		{
			// vì khi không mouseMove thì prototype không được vẽ và không set được màu. LButtonDown -> LButtonUp
			// sau đó nó lưu vào listShape và chạy hàm vẽ lại ngay lập tức.
			// -> không áp dụng được màu :3
			g_Prototypes[selected]->SetStyle(g_StypePen);
			g_Prototypes[selected]->Draw(hdc);
		}

	EndPaint(hwnd, &ps);
}
void OnDestroy(HWND hwnd)
{
	g_ListShape.clear();
	g_Prototypes.clear();
	PostQuitMessage(0);
}
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	isDrawing = true;
	CP_Start.SetX(x);
	CP_Start.SetY(y);
	g_Prototypes[selected]->SetPointStart(CP_Start);
}
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	CP_End.SetX(x);
	CP_End.SetY(y);
	g_Prototypes[selected]->SetPointEnd(CP_End);

	if (CP_Start!=CPoint(-1,-1))
	{
		if (!(CP_Start.GetX() == CP_End.GetX() && CP_Start.GetY() == CP_End.GetY()) && selected != 5)
			g_ListShape.push_back(g_Prototypes[selected]->Clone());
		else
		{
			if (selected == 5)
				g_ListShape.push_back(g_Prototypes[selected]->Clone());
		}
	}
	CP_Start = CPoint(-1, -1);
	CP_End = CPoint(-1, -1);
	
	isDrawing = false;
	// Báo hiệu cần xóa đi toàn bộ màn hình & vẽ lại
	InvalidateRect(hwnd, &rectPaint, TRUE);
}
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	WCHAR buffer[15];
	swprintf_s(buffer, 15, L"%d x %d", x, y);
	SendMessage(hStatusBar, SB_SETTEXT, 1, (LPARAM)buffer);
	if (isDrawing) {

		CP_End.SetX(x);
		CP_End.SetY(y);

		g_Prototypes[selected]->SetPointEnd(CP_End);
		// Báo hiệu cần xóa đi toàn bộ màn hình
		InvalidateRect(hwnd, &rectPaint, TRUE);
	}

}