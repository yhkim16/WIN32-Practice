#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPWSTR lpszClass=L"TextOut";

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
	RECT rect = {100,100,400,400};
	LPCWSTR strtemp =L"너는 죽지도 않으며 산것도 아니다"
		L"너는 1과 2를 모두 가진 3으로서"
		L"너는 죽지도 않고 살지도 않는 자이다"
		L"그냥 너는 잉여다";
	RECT rect0 = {100,100,500,500};
	LPCWSTR strtemp1=L"깨어나거라, 나의 아이야, 그리고 너의 타고난 영광을 받아들이거라."
		L"내가 군단의 영원한 의지인 초월체라는것을, 그리고 너는 나를 섬기기 위해 만들어졌다는것을 알거나."
		L"너를 나의 정신체들 사이에서 가장 높은곳에 둔 것을 보거라, 너는 그들의 지혜와 경험으로부터 많은 도움을 얻게 될 것이다."
		L"그러나 너의 목적은 특별하다. 그들은 나의 의지를 수많은 종족들에게 전달하는데 비해, 너에게는 하나의 책임만이 맡겨져 있다."
		L"나의 대리인들중 가장 위대한 것이 될만한 생명체를 찾았다. 지금도 그것은 보호받는 번데기 속에서 군단으로의 재탄생을 기다리고 있다."
		L"너는 그 번데리를 지켜보며, 그 속의 생명체에게 어떠한 해라도 끼치지 않도록 책임져라. 이제 가서 나의 귀중한것을 안전히 지켜라.";

	RECT rectnull = {500,500,500,500};
	LPCWSTR clear=L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    "
		L"                                                    ";
	switch(iMessage)
	{
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,L"Hello Win friends!",18);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_LBUTTONDOWN:
		hdc=GetDC(hWnd);
		DrawText(hdc,strtemp,wcslen(strtemp),&rect,DT_WORDBREAK | DT_LEFT | DT_RIGHT | DT_BOTTOM);
		ReleaseDC(hWnd,hdc);
		return 0;
	case WM_RBUTTONDOWN:
		hdc=GetDC(hWnd);
		DrawText(hdc,strtemp1,wcslen(strtemp1),&rect0,DT_WORDBREAK | DT_TOP | DT_CENTER | DT_VCENTER);
		ReleaseDC(hWnd,hdc);
		return 0;
	case WM_LBUTTONDBLCLK:
		hdc=GetDC(hWnd);
		DrawText(hdc,clear,wcslen(clear),&rectnull,DT_WORDBREAK | DT_LEFT);
		ReleaseDC(hWnd,hdc);
		return 0;
	case WM_CLOSE:
		if(MessageBox(hWnd,L"정말 종료하시겠습니까?",L"확인",MB_YESNO|MB_DEFBUTTON1)==IDNO)
		{
			return 0;
		}
		else{
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}