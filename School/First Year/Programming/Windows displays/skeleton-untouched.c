/*
 * skeleton.c
 *
 * This is a sample SKELETON C/C++ file to use with Windows desktop
 * before we switch to MFC based development
 */

#include <windows.h>
#include <stdlib.h>


/*
 * global variables
 */

char szAppName[] = "SkeletonApp";
char szTitle[] = "Skeleton Application Sample";
HINSTANCE hInst;



/*
 * function prototypes
 */

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);




/*
 * int CALLBACK WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
 *     LPSTR lpszCmdParam, int nCmdShow);
 *
 * This is the entry point for all Windows programs. It is informed
 * of the current instance handle, the previous instance handle, the
 * current commandline, and the show flag for how the window is to be
 * displayed.
 */

int CALLBACK 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	if (!hPrevInstance) {
		wndclass.style         = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc   = WndProc;
		wndclass.cbClsExtra    = 0;
		wndclass.cbWndExtra    = 0;
		wndclass.hInstance     = hInstance;
		wndclass.hIcon         = LoadIcon (NULL, NULL);
		wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
		wndclass.lpszMenuName  = NULL;
		wndclass.lpszClassName = szAppName;
		RegisterClass (&wndclass);
	}

	hInst = hInstance;

	hwnd = CreateWindow (szAppName, szTitle, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);

	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return msg.wParam;
}


/*
 * LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, 
 *     LPARAM lParam);
 *
 * This is the Window Procedure for the main window of this application.
 * It processes all messages destined for this main window.
 */

LRESULT CALLBACK
WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_CREATE:
		return 0;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);
		TextOut (hdc, 0, 0, "Hello World", 11);
		EndPaint (hwnd, &ps);
		return 0;

	case WM_CLOSE:
		/*
		 * only if user wishes to exit should we
		 * acually allow the program to stop. This
		 * avoids inadvertant terminations.
		 */

		if (MessageBox (hwnd, "Are you sure you wish to quit?",
                        szTitle, MB_ICONSTOP | MB_YESNO) == IDYES) {
			DestroyWindow (hwnd);
		}	/* endif */
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}	/* end switch */

	return DefWindowProc (hwnd, message, wParam, lParam);
}	/* end WndProc */

