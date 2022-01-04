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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static char strChar[MAX_PATH];
	int nlen = 0;
	static pos = 0;
	SIZE size;

	switch(iMessage)
	{
	case WM_CREATE:
		strcpy(strChar,"");
		return 0;
	case WM_CHAR:
		nlen = strlen(strChar);
		strChar[nlen] = (char)wParam;
		strChar[nlen+1] = 0;
		pos++;
		hdc=GetDC(hWnd);
		GetTextExtentPoint(hdc,strChar,pos,&size);
		ReleaseDC(hWnd,hdc);
		SetCaretPos(size.cx+100,100);
		return 0;
	case WM_SETFOCUS:
		hdc=GetDC(hWnd);
		CreateCaret(hWnd,NULL,2,14);
		ShowCaret(hWnd);
		SetCaretPos(100,100);
		return 0;
	case WM_KILLFOCUS:
		HideCaret(hWnd);
		DestroyCaret();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		TextOut(hdc, 100,100,strChar,strlen(strChar));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}