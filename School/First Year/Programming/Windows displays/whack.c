/*
 * whack.c
 *
 * This is a sample Whack-a-Mole game using the Win32 GUI
 * skeleton as a base. This will illustrate a number of 
 * windows GUI features such as drawing objects, selecting
 * colours, interacting with mouse and keyboard, etc.
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * global variables
 */

char szAppName[] = "WhackAMoleApp";
char szTitle[] = "ESE Whack-A-Mole";
HINSTANCE hInst;


int counter = 0;

/*
 * some declarations
 */

#define PUKE_GREEN		RGB(177,211,135)
#define TARGET_SIZE		50


/*
 * global variables
 */

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
	RECT r;
	int x, y;
	HFONT hFont, hFontOld;
	char buffer[512];

	switch (message) {
	case WM_CREATE:
		SetTimer (hwnd, 2, 1500, NULL);
		SetTimer (hwnd, 1, 500, NULL);
		return 0;

	case WM_TIMER:
		switch (wParam) {
			case 2:
				
				counter++;
				break;
					
			case 1:
				/* force client area update */
				InvalidateRect (hwnd, NULL, TRUE);
				UpdateWindow (hwnd);
				break;
			}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);


		/* create a font and select into drawing surface 
		 * visit: https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-createfonta
		 */
		// hFont = CreateFont(100, 75, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
					// CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");
						
		hFont = CreateFont (60, 0, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");
								
		hFontOld = (HFONT)SelectObject (hdc, hFont);
		
		
		sprintf (buffer, "Hits: %d Misses: %d", counter, 25);
		TextOut (hdc, 0, 0, buffer, strlen (buffer));


		hFont = CreateFont (60, 0, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                	CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");
		hFontOld = (HFONT)SelectObject (hdc, hFont);

		sprintf (buffer, "Hits: %d Misses: %d", counter, 25);
		TextOut (hdc, 0, 250, buffer, strlen (buffer));		
		
		SelectObject (hdc, hFontOld);
		DeleteObject (hFont);
		
		
		EndPaint (hwnd, &ps);
		return 0;

	case WM_CLOSE:
		/*
		 * only if user wishes to exit should we
		 * acually allow the program to stop. This
		 * avoids inadvertant terminations.
		 */

		if (MessageBox (hwnd, "Whacked Enough?",
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

