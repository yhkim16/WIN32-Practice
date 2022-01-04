#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass=L"ApiBase";

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
	WndClass.style=CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,L"잉간",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	LONG dwStyle;
	LONG style;

	TCHAR strTitle[] = L"윈도우 스타일 변경";
		switch(iMessage)
	{
		case WM_CREATE:


			return 0;
		case WM_LBUTTONDBLCLK:
			style=GetWindowLong(hWnd,GWL_STYLE);
			style &= ~WS_CAPTION;
			SetWindowLong(hWnd,GWL_STYLE,style);
			return 0;

		case WM_LBUTTONDOWN:
			dwStyle =GetWindowLong(hWnd,GWL_STYLE);
			dwStyle = dwStyle | WS_VSCROLL | WS_HSCROLL;
			SetWindowLong(hWnd, GWL_STYLE, dwStyle);
			SendMessage(hWnd,WM_NCPAINT,1,0);
			MoveWindow(hWnd,100,100,500,500,TRUE);			
			return 0;
		case WM_RBUTTONDBLCLK:
			style=GetWindowLong(hWnd,GWL_STYLE);
			style &= ~WS_OVERLAPPED;
			SetWindowLong(hWnd,GWL_STYLE,style);
			return 0;
		case WM_RBUTTONDOWN:
			hdc=GetDC(hWnd);
			TextOut(hdc,100,100,L"The Programing Language C",25);
			ReleaseDC(hWnd,hdc);

			return 0;
		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
			TextOut(hdc,10,10,strTitle,wcslen(strTitle));
			TextOut(hdc,200,200,L"Hello World!",12);
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}