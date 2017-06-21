#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <tchar.h>
#include <windows.h>
#include <fstream>
#include <string>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("essay writer");

HWND textField, infoText, infoText2, submitButton, nameFile;
HINSTANCE hInstance;


int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

							 /* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
											   /* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
		return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		_T("essay writer"),       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		544,                 /* The programs width */
		375,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	/* Make the window visible on the screen */
	ShowWindow(hwnd, nCmdShow);

	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR info[] = _T("Write your essay in the field to the left\nthen press submit.");
	TCHAR info2[] = _T("dont forget to add\n.txt at the end of the name.");
	TCHAR text[100];
	TCHAR messageText[10000];
	std::basic_fstream<TCHAR> file;

	switch (message)                  /* handle the messages */
	{
	case WM_CREATE:
		textField = CreateWindowEx(WS_EX_WINDOWEDGE, _T("Edit"), _T("write here, supports 10.000 words, supports appending"), WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | WS_BORDER, 10, 10, 250, 250, hwnd, NULL, hInstance, (LPVOID)lParam);
		infoText = CreateWindowEx(WS_EX_WINDOWEDGE, _T("Static"), info, WS_CHILD | WS_VISIBLE, 300, 10, 130, 50, hwnd, NULL, hInstance, (LPVOID)lParam);
		infoText2 = CreateWindowEx(WS_EX_WINDOWEDGE, _T("Static"), info2, WS_CHILD | WS_VISIBLE, 300, 100, 130, 50, hwnd, NULL, hInstance, (LPVOID)lParam);
		nameFile = CreateWindowEx(NULL, _T("Edit"), _T("nameOfFile.txt"), WS_CHILD | WS_VISIBLE | WS_BORDER, 300, 70, 100, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		submitButton = CreateWindowEx(WS_EX_WINDOWEDGE, _T("Button"), _T("SUBMIT"), WS_CHILD | WS_VISIBLE, 300, 170, 60, 20, hwnd, NULL, hInstance, (LPVOID)lParam);
		
		break;
	case WM_COMMAND:
		if (message == WM_COMMAND && (HWND)lParam == submitButton)
		{
			GetWindowText(nameFile, text, _countof(text));
			GetWindowText(textField, messageText, _countof(messageText));
			file.open(text, std::fstream::app);
			for (int i = 0; i < sizeof(messageText) / sizeof(messageText[0]); i++)
			{
				file <<	messageText[i];
			}
			file.close();
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
