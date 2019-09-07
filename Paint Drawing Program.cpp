#define OEMRESOURCE
#define WINVER 0x501
#define _WIN32_WINNT 0x501
#include <windows.h> 
#include <string> 
#include <vector> 
#include "Shape.h"
#include "resource.h"
#include <iostream>
#include <mmsystem.h>
#include <tchar.h>

using namespace std; 


RECT rect, rect1;

POINT point1;

int a, b = 0;
int Reso1 = 1920, Reso2 = 1080;

HBITMAP ghBitMap = 0, ghBitMap1 = 0;

static int bmWidth = 0, bmWidth1 = 0;
static int bmHeight = 0, bmHeight1 = 0;

HWND      ghMainWnd = 0; 
HINSTANCE ghAppInst = 0; 
HMENU     ghMenu = 0;
vector<Shape*> gShapes; 
Shape* gShape = 0;

bool gMouseDown = false;

int gCurrFileSel = ID_FILE_EXIT;
int gCurrImageSel = ID_IMAGE_IMAGE1;
int gCurrMusicSel = ID_MUSIC_MYSOUL;
int gCurrResoSel = ID_RESOLUTION_1920X1080;
int gCurrGameSel = ID_GAME_ANGELBEATS;
int gCurrCursorSel = ID_CURSOR_SHIINA;
int gCurrToolSel = ID_TOOL_RLTOOL1;

LOGPEN gLogPen; 
LOGBRUSH gLogBrush;

LRESULT CALLBACK MusicDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char msgText[256];
	HANDLE hMyIcon, hMyIcon1, hMyIcon2, hMyIcon3, hMyIcon4;
	HWAVEOUT  m_hWave = 0;
	HBITMAP myBitMap = 0;
	vector<char*> CharVec;
	CharVec.resize(5);
	CharVec[0] = _strdup("D://My Soul,Your Beats!.wav");
	CharVec[1] = _strdup("D://EP.wav");
	CharVec[2] = _strdup("D://Heartily-Song-Lia.wav");
	CharVec[3] = _strdup("D://CrowSong.wav");
	CharVec[4] = _strdup("D://LastSong.wav");

	static int classSelection = IDC_RADIO1;
	static HWND hComboBox = 0;  
	static int choose = 1;
	static int index = 0;
	
	switch (msg)
	{
	case WM_INITDIALOG:
		
		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		hComboBox = GetDlgItem(hDlg, IDC_COMBO1);        
		myBitMap = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP12));
		SendDlgItemMessage(hDlg, IDC_STATIC, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)myBitMap);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)CharVec[0]);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)CharVec[1]);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)CharVec[2]);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)CharVec[3]);
		SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)CharVec[4]);
		hMyIcon = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_STOP), IMAGE_BITMAP, 75, 21, NULL);
		hMyIcon1 = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PAUSE), IMAGE_BITMAP, 75, 21, NULL);
		hMyIcon2 = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_PREV), IMAGE_BITMAP, 75, 21, NULL);
		hMyIcon3 = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_EXIT), IMAGE_BITMAP, 75, 21, NULL);
		hMyIcon4 = LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NEXT), IMAGE_BITMAP, 75, 21, NULL);
		SendDlgItemMessage(hDlg, IDC_STOP, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hMyIcon);
		SendDlgItemMessage(hDlg, IDC_PAUSE, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hMyIcon1);
		SendDlgItemMessage(hDlg, IDC_PREV, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hMyIcon2);
		SendDlgItemMessage(hDlg, IDC_EXIT, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hMyIcon3);
		SendDlgItemMessage(hDlg, IDC_NEXT, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hMyIcon4);
		return true;
	
	case WM_COMMAND:
		
		switch (HIWORD(wParam))
		{
		    case  CBN_SELENDOK:
			    index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
			    SendMessage(hComboBox, CB_GETLBTEXT, (WPARAM)index, (LPARAM)msgText);
				PlaySound((LPCSTR)msgText, GetModuleHandle(NULL),  SND_LOOP | SND_ASYNC);
			    return true;
		}       

		switch (LOWORD(wParam))
		{
		    case IDC_RADIO1:
			case IDC_RADIO2:

				CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO2, LOWORD(wParam));
				classSelection = LOWORD(wParam);

				return true;
		
			case IDC_BUTTON4:
				--choose;
				if (choose < 0)
					choose = 0;
				SetWindowText(hComboBox, CharVec[choose]);
					PlaySound((LPCSTR)CharVec[choose], GetModuleHandle(NULL), SND_LOOP | SND_ASYNC);
					
				return 0;


			case IDC_BUTTON3:
				++choose;
				if (choose >= CharVec.size())
					choose = (CharVec.size() - 1);
				SetWindowText(hComboBox, CharVec[choose]);
					PlaySound((LPCSTR)CharVec[choose], GetModuleHandle(NULL), SND_LOOP | SND_ASYNC);
				return 0;
				
		
		    case IDC_BUTTON1:
				PlaySound(TEXT("MyAppSound"), NULL, NULL);
				return 0;
			
			case IDC_EXIT:
				EndDialog(hDlg, 0);
				CheckMenuItem(ghMenu, gCurrMusicSel, MF_UNCHECKED);
				PlaySound(TEXT("MyAppSound"), NULL, NULL);
				return true; 


		}
		return false;
	}
    return DefWindowProc(hDlg, msg, wParam, lParam);
}

LRESULT CALLBACK AboutDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, 0);
			return true;
		}
		return false;
	}
	return DefWindowProc(hDlg, msg, wParam, lParam);
}

LRESULT CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	
	HDC hdc = 0, hdc1 = 0;
	PAINTSTRUCT ps, ps1;


	HDC bmHDC = 0, bmHDC1 = 0;

	BITMAP bitmap = { 0 }, bitmap1 = { 0 };
	HBITMAP oldBM = 0, oldBM1 = 0;

	POINT p0;  
	POINT p1;

	int width, height, width1, height1;

	if (GetWindowRect(ghMainWnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	if (GetWindowRect(ghMainWnd, &rect1))
	{
		width1 = rect1.right - rect1.left;
		height1 = rect1.bottom - rect1.top;
	}




switch (msg) 
{
case WM_CREATE:   
	CheckMenuItem(ghMenu, ID_FILE_EXIT, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_IMAGE_IMAGE1, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_MUSIC_MYSOUL, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_RESOLUTION_1920X1080, MF_CHECKED);
	CheckMenuItem(ghMenu, ID_GAME_ANGELBEATS, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_CURSOR_SHIINA, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_TOOL_RLTOOL1, MF_UNCHECKED);
	
	ghBitMap1 = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP9));
	GetObject(ghBitMap1, sizeof(BITMAP), &bitmap1);

	bmWidth1 = bitmap1.bmWidth;
	bmHeight1 = bitmap1.bmHeight;
	PlaySound((LPCSTR)"D://EP.wav", GetModuleHandle(NULL), SND_LOOP | SND_ASYNC);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return 0;

case WM_COMMAND:   

switch (LOWORD(wParam)) 
{       
   case ID_MUSIC_MUSICPLAYER:
	   InvalidateRect(hWnd, 0, false);
	   CheckMenuItem(ghMenu, ID_MUSIC_MUSICPLAYER, MF_CHECKED);
	   CheckMenuItem(ghMenu, gCurrMusicSel, MF_UNCHECKED);
	   gCurrMusicSel = ID_MUSIC_MUSICPLAYER;
	   DialogBox(ghAppInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, (DLGPROC)MusicDlgProc);
	   return 0;

   case ID_TOOL_RLTOOL1:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_TOOL_RLTOOL1, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrToolSel, MF_UNCHECKED);
		gCurrToolSel = ID_TOOL_RLTOOL1;
		ShellExecute(ghMainWnd, "open", "C://Users//Admin//source//repos//RLTool1//Debug//RLTool1.exe", NULL, NULL, SW_SHOWDEFAULT);
		return 0;

	case ID_TOOL_RLTOOL2:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_TOOL_RLTOOL2, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrToolSel, MF_UNCHECKED);
		gCurrToolSel = ID_TOOL_RLTOOL2;
		ShellExecute(ghMainWnd, "open", "C://Users//Admin//source//repos//GoTiengViet//Debug//GoTiengViet.exe", NULL, NULL, SW_SHOWDEFAULT);
		return 0;


    case ID_CURSOR_SHIINA:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_CURSOR_SHIINA, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrCursorSel, MF_UNCHECKED);
		gCurrCursorSel = ID_CURSOR_SHIINA;
		b = 140;
		SetCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(140)));
		SetSystemCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(140)), OCR_NORMAL);
		return 0;

	case ID_CURSOR_SHIINA32832:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_CURSOR_SHIINA32832, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrCursorSel, MF_UNCHECKED);
		gCurrCursorSel = ID_CURSOR_SHIINA32832;
		b = 142;
		SetCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(IDC_CURSOR2)));
		SetSystemCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(140)), OCR_NORMAL);
		return 0;

	case ID_CURSOR_IWASAWA:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_CURSOR_IWASAWA, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrCursorSel, MF_UNCHECKED);
		gCurrCursorSel = ID_CURSOR_IWASAWA;
		b = 143;
		SetCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(IDC_CURSOR3)));
		SetSystemCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(140)), OCR_NORMAL);
		return 0;
		

    case ID_GAME_ANGELBEATS:
		CheckMenuItem(ghMenu, ID_GAME_ANGELBEATS, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrGameSel, MF_UNCHECKED);
		gCurrGameSel = ID_GAME_ANGELBEATS;
		ShellExecute(ghMainWnd, "open", "D://Angel beats!//Key//AngelBeats!//SiglusEngine.exe.lnk", NULL, NULL, SW_SHOWDEFAULT);
		return 0;

    case ID_RESOLUTION_640X360:
		InvalidateRect(hWnd, 0, true);
		CheckMenuItem(ghMenu, ID_RESOLUTION_640X360, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrResoSel, MF_UNCHECKED);
		gCurrResoSel = ID_RESOLUTION_640X360;
		Reso1 = 640, Reso2 = 360;
		SetWindowPos(ghMainWnd, 0, 0, 0, Reso1, Reso2, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		return 0;

	case ID_RESOLUTION_1280X720:
		InvalidateRect(hWnd, 0, true);
		(ghMenu, ID_RESOLUTION_640X360, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrResoSel, MF_UNCHECKED);
		gCurrResoSel = ID_RESOLUTION_1280X720;
		Reso1 = 1280, Reso2 = 720;
		SetWindowPos(ghMainWnd, 0, 0, 0, Reso1, Reso2, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		return 0;

	case ID_RESOLUTION_1920X1080:
		InvalidateRect(hWnd, 0, true);
		CheckMenuItem(ghMenu, ID_RESOLUTION_1920X1080, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrResoSel, MF_UNCHECKED);
		gCurrResoSel = ID_RESOLUTION_1920X1080;
		Reso1 = 1920, Reso2 = 1080;
		SetWindowPos(ghMainWnd, 0, 0, 0, Reso1, Reso2, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		return 0;

	case ID_FILE_EXIT:    
		CheckMenuItem(ghMenu, ID_FILE_EXIT, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrFileSel, MF_UNCHECKED);
		gCurrFileSel = ID_FILE_EXIT;
	    DestroyWindow(ghMainWnd);    
		return 0;   

	case ID_FILE_ABOUT:
		CheckMenuItem(ghMenu, ID_FILE_ABOUT, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrFileSel, MF_UNCHECKED);
		gCurrFileSel = ID_FILE_ABOUT;
        DialogBox(ghAppInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, (DLGPROC)AboutDlgProc);
		return 0;

	case ID_IMAGE_IMAGE1:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_IMAGE_IMAGE1, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrImageSel, MF_UNCHECKED);
		gCurrImageSel = ID_IMAGE_IMAGE1;
		ghBitMap = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(ghBitMap, sizeof(BITMAP), &bitmap);

		bmWidth = bitmap.bmWidth;
		bmHeight = bitmap.bmHeight;

		return 0;
	case ID_IMAGE_IMAGE2:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_IMAGE_IMAGE2, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrImageSel, MF_UNCHECKED);
		gCurrImageSel = ID_IMAGE_IMAGE2;
		ghBitMap = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP2));
		GetObject(ghBitMap, sizeof(BITMAP), &bitmap);

		bmWidth = bitmap.bmWidth;
		bmHeight = bitmap.bmHeight;

		return 0;
	case ID_IMAGE_IMAGE3:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_IMAGE_IMAGE3, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrImageSel, MF_UNCHECKED);
		gCurrImageSel = ID_IMAGE_IMAGE3;
		ghBitMap = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP3));
		GetObject(ghBitMap, sizeof(BITMAP), &bitmap);

		bmWidth = bitmap.bmWidth;
		bmHeight = bitmap.bmHeight;

		return 0;
	case ID_IMAGE_IMAGE4:
		InvalidateRect(hWnd, 0, false);
		CheckMenuItem(ghMenu, ID_IMAGE_IMAGE4, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrImageSel, MF_UNCHECKED);
		gCurrImageSel = ID_IMAGE_IMAGE4;
		ghBitMap = LoadBitmap(ghAppInst, MAKEINTRESOURCE(IDB_BITMAP7));
		GetObject(ghBitMap, sizeof(BITMAP), &bitmap);

		bmWidth = bitmap.bmWidth;
		bmHeight = bitmap.bmHeight;

		return 0;
	case ID_IMAGE_CLEARIMAGE:
		InvalidateRect(hWnd, 0, true);
		CheckMenuItem(ghMenu, ID_IMAGE_CLEARIMAGE, MF_CHECKED);
		CheckMenuItem(ghMenu, gCurrImageSel, MF_UNCHECKED);
		gCurrImageSel = ID_IMAGE_CLEARIMAGE;
		ghBitMap = 0;
		bitmap = { 0 };
		return 0;

}

case WM_PAINT:   
	
	InvalidateRect(hWnd, 0, false);
	
	hdc = BeginPaint(hWnd, &ps);

	bmHDC1 = CreateCompatibleDC(hdc);
	oldBM1 = (HBITMAP)SelectObject(bmHDC1, ghBitMap1);
	BitBlt(hdc, Reso1 / 2 - bmWidth1 / 2, Reso2 / 2 - bmHeight1 / 2, bmWidth1, bmHeight1, bmHDC1, 0, 0, SRCCOPY);
	SelectObject(bmHDC1, oldBM1);
	DeleteDC(bmHDC1);


	bmHDC = CreateCompatibleDC(hdc);
	oldBM = (HBITMAP)SelectObject(bmHDC, ghBitMap);
	BitBlt(hdc, Reso1 / 2 - bmWidth / 2, Reso2 / 2 - bmHeight / 2, bmWidth, bmHeight, bmHDC, 0, 0, SRCCOPY);
	SelectObject(bmHDC, oldBM);
	DeleteDC(bmHDC);
	
	if(gMouseDown)
	gShape->draw(hdc);
	for (int i = 0; i < gShapes.size(); ++i)    
		gShapes[i]->draw(hdc);

	    EndPaint(hWnd, &ps);

case WM_KEYDOWN:    
	if (wParam == VK_ESCAPE)
	{
		SetCursor(LoadCursor(ghAppInst, MAKEINTRESOURCE(IDC_ARROW)));
		DestroyWindow(ghMainWnd);
	}
	
	return 0;

case WM_DESTROY:     
	PostQuitMessage(0);    
	return 0;   
}
return DefWindowProc(hWnd, msg, wParam, lParam); 
}

int WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int showCmd)
{
	ghAppInst = hInstance;
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghAppInst;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "MyWndClassName";

	RegisterClass(&wc);
	ghMenu = LoadMenu(ghAppInst, MAKEINTRESOURCE(IDR_MENU1));
	ghMainWnd = ::CreateWindow("MyWndClassName", "Angel Beats! Entertainment 1.0", WS_OVERLAPPEDWINDOW, 0, 0, Reso1, Reso2, 0, ghMenu, ghAppInst, 0);

	if (ghMainWnd == 0)
	{
		::MessageBox(0, "CreateWindow - Failed", 0, 0);
		return false;
	}

	ShowWindow(ghMainWnd, showCmd);
	UpdateWindow(ghMainWnd);

	
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	for (int i = 0; i < gShapes.size(); ++i)
		delete gShapes[i];
	return (int)msg.wParam;
}


