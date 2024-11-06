#include <Windows.h>
#include <stdio.h>

LPCTSTR clsName = "MyWindowClass";
LPCTSTR msgName = "MyWindow";

LRESULT CALLBACK MyWinProc(
    HWND hwnd,                  // ���ھ��
    UINT uMsg,                  // ��Ϣ����
    WPARAM wParam,              // ������Ϣ
    LPARAM lParam               // ������Ϣ
);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	/*
	 1.��������ô��ڶ���
     typedef struct tagWNDCLASS {
        UINT        style;              // ����ʽ
        WNDPROC     lpfnWndProc;        // ָ�򴰿ڹ��̵Ļص�����ָ��
        int         cbClsExtra;         // Ҫ���ݴ�����ṹ����Ķ����ֽ��� ϵͳ���ֽڳ�ʼ��Ϊ��
        int         cbWndExtra;         // �ڴ���ʵ��֮�����Ķ����ֽ��� ϵͳ���ֽڳ�ʼ��Ϊ��
        HINSTANCE   hInstance;          // ʵ���ľ������ʵ��������Ĵ��ڹ���
        HICON       hIcon;              // ��ͼ��ľ��
        HCURSOR     hCursor;            // ���α�ľ�� �˳�Ա�������α���Դ�ľ��
        HBRUSH      hbrBackground;      // �౳�����ʵľ��
        LPCWSTR     lpszMenuName;       // ��˵�����Դ����
        LPCWSTR     lpszClassName;
    } 
    */
	WNDCLASS wndcls;
    wndcls.style = CS_HREDRAW | CS_VREDRAW;     // ������ڸ߶ȺͿ�ȸı䣬�ػ���������
    wndcls.lpfnWndProc = MyWinProc;
    wndcls.cbClsExtra = NULL;
    wndcls.cbWndExtra = NULL;
    wndcls.hInstance = hInstance;
    wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.lpszMenuName = NULL;
    wndcls.lpszClassName = clsName;

    /*
    * 2. ע�ᴰ����
    */
    RegisterClass(&wndcls);

    /*
    * 3. ��������
    * HWND CreateWindow(
         LPCWSTR   lpClassName,         // ��һ�ε���RegisterClass������������ԭ��
         LPCWSTR   lpWindowName,        // ��������
         DWORD     dwStyle,             // ���ڴ����Ĵ��ڵ���ʽ
         int       x,                   // ���ڵĳ�ʼˮƽλ��
         int       y,                   // ���ڵĳ�ʼ��ֱλ��
         int       nWidth,              // ���ڵĿ��
         int       nHeight,             // ���ڵĸ߶�
         HWND      hWndParent,          // ���ڴ����Ĵ��ڵĸ����ڻ������ߴ��ڵľ��
         HMENU     hMenu,               // �˵��ľ������ݴ�����ʽָ���Ӵ��ڱ�ʶ��
         HINSTANCE hInstance,           // Ҫ�봰�ڹ�����ģ��ʵ���ľ��
         LPVOID    lpParam              // ָ��ͨ�� CREATESTRUCT �ṹ��lpCreateParams ��Ա��ָ���ֵ��ָ��
);
    */
    HWND hwnd;
    hwnd = CreateWindow(clsName, msgName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    /*
    * 4. ��ʾ��ˢ�´���
    */
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    /*
    * 5. ��Ϣѭ�� 
    *    GetMessageֻ���յ�WM_QUIT��Ϣ�Ż᷵��0
    *    TranslateMessage ������Ϣ
    */
    MSG msg;
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK MyWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int iRet;
    HDC hdc;
    switch (uMsg)
    {
    case WM_CHAR:
        char szMsg[20];
        sprintf_s(szMsg, "touch: %c", wParam);
        MessageBox(hwnd, szMsg, "char", NULL);
        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 0, 0, "www.bing.com", strlen("www.bing.com"));
        EndPaint(hwnd, &ps);
        MessageBox(hwnd, "paint", "msg", NULL);
        break;

    case WM_CLOSE:
        iRet = MessageBox(hwnd, "Really Close?", "msg", NULL);
        if (iRet == IDYES)
        {
            DestroyWindow(hwnd);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}