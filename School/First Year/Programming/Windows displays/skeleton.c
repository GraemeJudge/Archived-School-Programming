/*
 * skeleton.c
 *
 * This is a sample SKELETON C/C++ file to use with Windows desktop
 * before we switch to MFC based development
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Time.h>




/*
 * global variables
 */

#define FONT_HEIGHT  60
#define FONT_WIDTH 0
#define LINEOFFSET 100
char szAppName[] = "SkeletonApp";
char szTitle[] = "Skeleton Application Sample";

int width = 0;
int height = 0;

char textLine[] = {"I never needed anybody's help in any way"};

HINSTANCE hInst;
/*
 * function prototypes
 */

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

void delay(int sec){

	int returnTime = time(0) + sec;

	while(time(0) < returnTime);
}


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
	
	// HFONT hFont;
	

	if (!hPrevInstance) {
		wndclass.style         = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc   = WndProc;
		wndclass.cbClsExtra    = 0;
		wndclass.cbWndExtra    = 0;
		wndclass.hInstance     = hInstance;
		wndclass.hIcon         = LoadIcon (NULL, NULL);
		wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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

	HFONT hFont, hFontOld, hOldFont;
	

	char buffer[512];

	switch (message) {
	case WM_CREATE:
		SetTimer (hwnd, 1, 500, NULL);
			return 0;
					
	case WM_TIMER:
		switch(wParam){
			case 1:
				InvalidateRect (hwnd, NULL, TRUE);
				UpdateWindow(hwnd);
				break;
		}
		return 0;	
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps);
		
		hFont = CreateFont(FONT_HEIGHT, FONT_WIDTH, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
								OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");
		
		hOldFont = CreateFont(FONT_HEIGHT/2, FONT_WIDTH/2, 0, 0, FW_DONTCARE, TRUE, FALSE, FALSE, DEFAULT_CHARSET,
								OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Courier New");



		hFontOld = (HFONT)SelectObject (hdc, hFont);
		
		SetTextColor(hdc, RGB(0,0,0));
		
		
		RECT rect;
		if(GetWindowRect(hwnd, &rect))
		{
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}
			
		
		
		sprintf(buffer, "Hiya hows it going babe", 25);
		TextOut(hdc, (width/2) - (strlen(buffer) * 53)/2, (LINEOFFSET * 1),buffer, strlen(buffer));//print
		
		if(height > FONT_HEIGHT + (LINEOFFSET * 2)){
			hFontOld = (HFONT)SelectObject(hdc, hOldFont);		
			time_t timers = time(NULL);		
			TextOut(hdc, (width/2) - (strlen(ctime(&timers)) * 53)/4 , (height - FONT_HEIGHT * 1) - 10, ctime(&timers),strlen(ctime(&timers)));
		} 
		
		
		SelectObject (hdc, hFontOld);	
		DeleteObject (hFont); // <-- delete to free up memory for the rest of the program
		DeleteObject (hOldFont);
		
		EndPaint (hwnd, &ps);
		return 0;


		

	case WM_CLOSE:
	close:
		/*
		 * only if user wishes to exit should we
		 * acually allow the program to stop. This
		 * avoids inadvertant terminations.
		 */

		

		//if (MessageBox (hwnd, "Are you sure you wish to quit?",
                        // szTitle, MB_ICONSTOP | MB_YESNO) == IDYES) {
			DestroyWindow (hwnd);
		//}	/* endif */
		return 0;

	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	}	/* end switch */

	return DefWindowProc (hwnd, message, wParam, lParam);
}	/* end WndProc */


