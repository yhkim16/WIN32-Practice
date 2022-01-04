#include <windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass=L"Resources";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	HACCEL hAccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));

	while(GetMessage(&Message,0,0,0)) {
		if(!TranslateAccelerator(hWnd,hAccel,&Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR strTemp[3][256];

	HMENU popupmenu1,popupmenu2;
	POINT point;

	switch(iMessage)
	{
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		LoadString(g_hInst,IDS_STRING106,strTemp[0],256);
		TextOut(hdc,100,200,strTemp[0],wcslen(strTemp[0]));
		LoadString(g_hInst,IDS_STRING107,strTemp[1],256);
		TextOut(hdc,100,220,strTemp[1],wcslen(strTemp[1]));
		LoadString(g_hInst,IDS_STRING108,strTemp[2],256);
		TextOut(hdc,100,240,strTemp[2],wcslen(strTemp[2]));
		EndPaint(hWnd,&ps);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			return 0;
		case ID_POPUP1:
			MessageBox(hWnd,L"First!",L"POPUP",MB_OK);
			break;
		case ID_POPUP2:
			MessageBox(hWnd,L"Second!",L"POPUP",MB_OK);
			break;
		case IDR_ACCELERATOR1:
			MessageBox(hWnd,L"ACCELERATOR!",L"메시지 박스",MB_OK | MB_ICONWARNING);
			break;
		}
	case WM_CONTEXTMENU:
		point.x=LOWORD(lParam);
		point.y=HIWORD(lParam);
		popupmenu1=LoadMenu(g_hInst,MAKEINTRESOURCE(IDR_POPUP));
		popupmenu2=GetSubMenu(popupmenu1,0);
		TrackPopupMenu(popupmenu2,TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,0,hWnd,NULL);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}