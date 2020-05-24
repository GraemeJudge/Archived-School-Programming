/*
 * imagetest.c
 *
 * This is a simple C based skeleton Win32 App
 * that provides a test bed for image processing
 * algorithms.
 */

#include <windows.h>
#include <stdlib.h>

/* the following constants enumerate image processing modes for the user interface */

#define IMAGE_MODE_NORMAL		0
#define IMAGE_MODE_GRAYSCALE		1
#define IMAGE_MODE_POSTERIZE		2
#define IMAGE_MODE_INVERSE		3


/*
 * global variables
 */

char szAppName[] = "ImageSkeletonApp";
char szTitle[] = "Image Processing Application";
HINSTANCE hInst;

char filename[256] = ".\\sample.bmp";

int image_processing_mode = IMAGE_MODE_NORMAL;


/*
 * function prototypes
 */

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

/* the following prototypes are for the six different image processing functions */

int ImageProcessGrayscale (unsigned long *pPixels, int width, int height);
int ImageProcessPosterize (unsigned long *pPixels, int width, int height);
int ImageProcessInverse (unsigned long *pPixels, int width, int height);




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
	HBITMAP hBMP, hBMPOld;
	HDC hdc, hdcMem;
	BITMAP bm;
	BITMAPINFO bmi = { 0 };
	unsigned long *pixels = NULL;

	switch (message) {
	case WM_CREATE:
		return 0;

	case WM_PAINT:
		/* begin process to paint window surface (client area) */

		hdc = BeginPaint (hwnd, &ps);

		/* load a bitmap from disk into memory */

		hBMP = LoadImage (NULL, filename, IMAGE_BITMAP, 0, 0, 
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBMP == NULL)
			goto endPaint;

		/* obtain bitmap details such as width / height */

		GetObject (hBMP, sizeof(BITMAP), &bm);

		/* do we apply an image processing algorithm? */

		if (image_processing_mode == IMAGE_MODE_NORMAL)
			goto doPaint;

		/* yes, we need some memory to hold the pixel data */

		pixels = (unsigned long *)malloc (bm.bmWidth * bm.bmHeight * sizeof (unsigned long));
		if (pixels == NULL)
			goto doPaint;

		/* setup to grab the 32 bit pixel data and send to processing algorithm */

		bmi.bmiHeader.biSize = sizeof (bmi.bmiHeader);
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biWidth = bm.bmWidth;
		bmi.bmiHeader.biHeight = -bm.bmHeight;

		/* grab the pixel data, if error, just display original photo */

		if (GetDIBits (hdc, hBMP, 0, bm.bmHeight, pixels, &bmi, DIB_RGB_COLORS) == 0)
			goto doPaint;

		/* select processing algorithm */
						
		switch (image_processing_mode) {
		case IMAGE_MODE_GRAYSCALE:
			ImageProcessGrayscale (pixels, bm.bmWidth, bm.bmHeight);
			break;

		case IMAGE_MODE_POSTERIZE:
			ImageProcessPosterize (pixels, bm.bmWidth, bm.bmHeight);
			break;

		case IMAGE_MODE_INVERSE:
			ImageProcessInverse (pixels, bm.bmWidth, bm.bmHeight);
			break;
		}	/* end switch */

		/* put the altered data back into bitmap */

		SetDIBits (hdc, hBMP, 0, bm.bmHeight, pixels, &bmi, DIB_RGB_COLORS);

		/* copy from memory to window surface */

		doPaint:

		/* create a device context in memory and 
		 * install loaded bitmap as its surface */

		hdcMem = CreateCompatibleDC (hdc);
		hBMPOld = (HBITMAP)SelectObject (hdcMem, hBMP);

		BitBlt (hdc, 0, 0, bm.bmWidth, bm.bmHeight,
			hdcMem, 0, 0, SRCCOPY);

		/* deallocate all loaded resources */

		SelectObject (hdcMem, hBMPOld);
		DeleteObject (hBMP);
		DeleteDC (hdcMem);

		cleanupPaint:
		if (pixels != NULL)
			free (pixels);

		/* end update of client area */

		endPaint:
		EndPaint (hwnd, &ps);
		return 0;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_F1:
			image_processing_mode = IMAGE_MODE_NORMAL;
			break;

		case VK_F2:
			image_processing_mode = IMAGE_MODE_GRAYSCALE;
			break;

		case VK_F3:
			image_processing_mode = IMAGE_MODE_POSTERIZE;
			break;

		case VK_F4:
			image_processing_mode = IMAGE_MODE_INVERSE;
			break;
		}	/* end switch */

		InvalidateRect (hwnd, NULL, TRUE);
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


/* 
 * TODO: complete the following image processing functions 
 * and move to a separate source file
 * NOTE: pixel data is organized as 32 bit values 
 * with low 8 bits holding BLUE level, next 8
 * bits holding GREEN level and next 8 bits
 * holding RED level, with top 8 bits being zero. Thus
 * the 32 bit value is organized as such:
 * [ 8 bits = 0 ][ RED 8 bits ][ GREEN 8 bits ][ BLUE 8 bits]
 */


int
ImageProcessGrayscale (unsigned long *pPixels, int width, int height)
{
	/*
	 * this algorithm computes grayscale via luminance computations.
	 * Luminance = 30% of RED value + 59% of GREEN value + 11% of BLUE value.
	 * Set the red/green/blue values of pixel to the luminance value.
	 * When the red/green/blue components are all the same value, a pixel
	 * is considered a shade of gray, and thus, a grayscale image
	 * has 256 levels of gray.
	 */

	return 0;
}	/* end ImageProcessGrayscale */


int
ImageProcessPosterize (unsigned long *pPixels, int width, int height)
{
	/*
	 * this algorithm will collapse colours into groups
	 * to reduce the number of unique colours. For example, 
	 * pixel values from 0 to 31 could be one group, 32 to 63 could be
	 * a second group, and so forth, to generate 8 groups in total. The
	 * resulting image will appear like a painted poster. Experiment
	 * with the number of groups to determine best level of 
	 * posterization. Google for algorithms to support posterization.
	 */

	return 0;
}	/* end ImageProcessPosterize */


int
ImageProcessInverse (unsigned long *pPixels, int width, int height)
{
	/*
 	 * this algorithm will invert the pixel data to create a
	 * "negative" of the original image
	 */

	return 0;
}	/* ImageProcessInverse */


