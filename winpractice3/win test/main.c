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
	LPCWSTR strtemp =L"�ʴ� ������ ������ ��͵� �ƴϴ�"
		L"�ʴ� 1�� 2�� ��� ���� 3���μ�"
		L"�ʴ� ������ �ʰ� ������ �ʴ� ���̴�"
		L"�׳� �ʴ� �׿���";
	RECT rect0 = {100,100,500,500};
	LPCWSTR strtemp1=L"����Ŷ�, ���� ���̾�, �׸��� ���� Ÿ�� ������ �޾Ƶ��̰Ŷ�."
		L"���� ������ ������ ������ �ʿ�ü��°���, �׸��� �ʴ� ���� ����� ���� ��������ٴ°��� �˰ų�."
		L"�ʸ� ���� ����ü�� ���̿��� ���� �������� �� ���� ���Ŷ�, �ʴ� �׵��� ������ �������κ��� ���� ������ ��� �� ���̴�."
		L"�׷��� ���� ������ Ư���ϴ�. �׵��� ���� ������ ������ �����鿡�� �����ϴµ� ����, �ʿ��Դ� �ϳ��� å�Ӹ��� �ð��� �ִ�."
		L"���� �븮�ε��� ���� ������ ���� �ɸ��� ����ü�� ã�Ҵ�. ���ݵ� �װ��� ��ȣ�޴� ������ �ӿ��� ���������� ��ź���� ��ٸ��� �ִ�."
		L"�ʴ� �� �������� ���Ѻ���, �� ���� ����ü���� ��� �ض� ��ġ�� �ʵ��� å������. ���� ���� ���� �����Ѱ��� ������ ���Ѷ�.";

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
		if(MessageBox(hWnd,L"���� �����Ͻðڽ��ϱ�?",L"Ȯ��",MB_YESNO|MB_DEFBUTTON1)==IDNO)
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