#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND g_hStatic1;
HWND g_hEdit;
HWND g_hList;
HWND g_hCombo;
HWND g_hScroll;

LPWSTR lpszClass=L"childwindow";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

#define ID_CHKBOX 300
#define ID_R1 401
#define ID_R2 402
#define ID_R3 403
#define ID_R4 404
#define ID_R5 405
#define ID_EDITBOX 500
#define ID_LISTBOX 600
#define ID_COMBO 700
#define ID_SCROLL 801

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	int i;

	static HWND hCheckBox;
	static BOOL bCheckBox = FALSE;

	wchar_t strEdit[128];
	wchar_t listitems[][30]={L"C++ 프로그래밍",L"Win32 프로그래밍",L"MFC 시스템프로그래밍",L"DB 프로그래밍"};
	
	static short nSelect = 0;
	static short nCombo = 0;
	static short nList = 0;
	static int nScrollMove = 0;

	switch(iMessage)
	{
	case WM_CREATE:
		CreateWindow(L"button",L"버튼1",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,20,20,100,25,hWnd,(HMENU)100,g_hInst,NULL);
		CreateWindow(L"button",L"버튼2",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,20,60,100,25,hWnd,(HMENU)200,g_hInst,NULL);
		hCheckBox=CreateWindow(L"button",L"거짓, 참",WS_CHILD | WS_VISIBLE | BS_CHECKBOX,220,220,80,50,hWnd,(HMENU)ID_CHKBOX,g_hInst,NULL);
		CreateWindow(L"button",L"선택",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,80,150,120,300,hWnd,(HMENU)1,g_hInst,NULL);
		CreateWindow(L"button",L"선택 1",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP,100,200,80,25,hWnd,(HMENU)ID_R1,g_hInst,NULL);
		CreateWindow(L"button",L"선택 2",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,100,250,80,25,hWnd,(HMENU)ID_R2,g_hInst,NULL);
		CreateWindow(L"button",L"선택 3",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,100,300,80,25,hWnd,(HMENU)ID_R3,g_hInst,NULL);
		CreateWindow(L"button",L"선택 4",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,100,350,80,25,hWnd,(HMENU)ID_R4,g_hInst,NULL);
		CreateWindow(L"button",L"선택 5",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,100,400,80,25,hWnd,(HMENU)ID_R5,g_hInst,NULL);
		CheckRadioButton(hWnd,ID_R1,ID_R5,ID_R1);
		
		g_hScroll=CreateWindow(L"scrollbar",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,280,420,200,20,hWnd,(HMENU)ID_SCROLL,g_hInst,NULL);

		SetScrollRange(g_hScroll,SB_CTL,0,255,TRUE);
		SetScrollPos(g_hScroll,SB_CTL,0,TRUE);

		g_hStatic1=CreateWindow(L"static",L"정적분",WS_CHILD|WS_VISIBLE|SS_CENTER,280,30,400,50,hWnd,(HMENU)-1,g_hInst,NULL);

		g_hEdit=CreateWindow(L"edit",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE,300,300,400,20,hWnd,(HMENU)ID_EDITBOX,g_hInst,NULL);

		g_hList=CreateWindow(L"listbox",NULL,WS_CHILD|WS_VISIBLE|LBS_STANDARD,500,100,200,80,hWnd,(HMENU)ID_LISTBOX,g_hInst,NULL);

		g_hCombo=CreateWindow(L"combobox",NULL,WS_CHILD|WS_VISIBLE|CBS_DROPDOWN,500,200,200,100,hWnd,(HMENU)ID_COMBO,g_hInst,NULL);

		for(i=0;i<4;i++)
		{
			SendMessage(g_hList,LB_ADDSTRING,0,(LPARAM)listitems[i]);
			SendMessage(g_hCombo,CB_ADDSTRING,0,(LPARAM)listitems[i]);
		}
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 100:
			MessageBox(hWnd,L"버튼 1!",L"Button Window",MB_OK);
			break;
		case 200:
			MessageBox(hWnd,L"버튼 2!",L"Vutton Window",MB_OK);
			break;
		case ID_CHKBOX:
			if(SendMessage(hCheckBox,BM_GETCHECK,0,0)==BST_UNCHECKED)
			{
				SendMessage(hCheckBox,BM_SETCHECK,BST_CHECKED,0);
				bCheckBox=TRUE;

			}
			else
			{	
				SendMessage(hCheckBox,BM_SETCHECK,BST_UNCHECKED,0);
				bCheckBox=FALSE;
			}
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_R1:
			nSelect=0;
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_R2:
			nSelect=1;
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_R3:
			nSelect=2;
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_R4:
			nSelect=3;
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_R5:
			nSelect=4;
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_EDITBOX:
			switch(HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(g_hEdit,strEdit,128);
				SetWindowText(g_hStatic1,strEdit);
				break;
			}
			break;
		case ID_LISTBOX:
			switch(HIWORD(wParam))
			{
			case LBN_DBLCLK:
				nList=SendMessage(g_hList,LB_GETCURSEL,0,0);
				SendMessage(g_hList,LB_GETTEXT,nList,(LPARAM)strEdit);
				SetWindowText(g_hStatic1,strEdit);
			}
			break;
		case ID_COMBO:
			switch(HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				nCombo=SendMessage(g_hCombo,CB_GETCURSEL,0,0);
				SendMessage(g_hCombo,CB_GETLBTEXT,nCombo,(LPARAM)strEdit);
				SetWindowText(g_hStatic1,strEdit);
			}
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		if(bCheckBox==TRUE)
		{
			TextOut(hdc, 150, 100, L"CheckBox is checked!",20);
		}
		else
		{
			TextOut(hdc, 150, 100, L"CheckBox is unchecked!",22);
		}
		switch(nSelect)
		{
		case 0:
			TextOut(hdc, 100, 100, L"Case 1",6);
			break;
		case 1:
			TextOut(hdc, 100, 100, L"Case 2",6);
			break;
		case 2:
			TextOut(hdc, 100, 100, L"Case 3",6);
			break;
		case 3:
			TextOut(hdc, 100, 100, L"Case 4",6);
			break;
		case 4:
			TextOut(hdc, 100, 100, L"Case 5",6);
			break;
		}
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_HSCROLL:
		if((HWND)lParam == g_hScroll)
		{
			switch(LOWORD(wParam))
			{
				nScrollMove = HIWORD(wParam);
			case SB_LINELEFT:
				nScrollMove=max(0,nScrollMove-1);
				break;
			case SB_LINERIGHT:
				nScrollMove=min(255,nScrollMove+1);
				break;
			case SB_PAGELEFT:
				nScrollMove=max(0,nScrollMove-10);
				break;
			case SB_PAGERIGHT:
				nScrollMove=min(255,nScrollMove+10);
				break;
			case SB_THUMBTRACK:
				nScrollMove=HIWORD(wParam);
				break;
			}
		}
		SetScrollPos(g_hScroll,SB_CTL,nScrollMove,TRUE);
		InvalidateRect(hWnd,NULL,FALSE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}