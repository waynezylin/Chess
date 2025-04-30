// Chess.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Chess.h"
#include <iostream>
#include <String>
#include "Sprite.h"
#include "Game.h"
#include "winuser.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
bool first = true;
Game gameHandler = Game();
POINT mousePos;
int clickOutput = -1;
bool stale = false;
bool complete = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Check(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Checkmate(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHESS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 816, 859, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDD_CHECK:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CHECK), hWnd, Check);
            break;

        case IDD_CHECKMATE:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CHECKMATE), hWnd, Checkmate);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {

        RECT window;
        window.top = 0;
        window.left = 0;
        window.bottom = 800;
        window.right = 800;
        InvalidateRect(hWnd, &window, true);

        //OutputDebugStringA("paint\n");
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);


        //HDC bb = CreateCompatibleDC(hdc);
        //HBRUSH blk = (HBRUSH) SelectObject(hdc, GetStockObject(BLACK_BRUSH));



        //// TODO: Add any drawing code that uses hdc here...
        if (first || gameHandler.checkTC() || clickOutput == 1)
        {
            clickOutput = -1;

            //ValidateRect(hWnd, &window);


            for (int i = 0; i < 8; i++)
            {
                bool a = ((i % 2) == 0) ? true : false;
                for (int j = 0; j < 8; j++)
                {
                    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
                    if (a)
                    {
                        //OutputDebugStringA(("a " + std::to_string(i) + "\n").c_str());
                        if ((j % 2) != 0)
                        {

                            Rectangle(hdc, (i * 100), (j * 100), (i * 100) + 100, (j * 100) + 100);
                        }
                    }
                    else
                    {
                        if ((j % 2) == 0)
                        {
                            //OutputDebugString(L"end");
                            Rectangle(hdc, (i * 100), (j * 100), (i * 100) + 100, (j * 100) + 100);
                        }
                    }
                }
            }
            first = false;


            //if (gameHandler.checkTC())
            {
                //OutputDebugStringA("bleep\n");

                /*RECT pr;
                pr.left = gameHandler.getPrevTile().x * 100;
                pr.top = gameHandler.getPrevTile().y * 100;
                pr.right = pr.left + 100;
                pr.bottom = pr.top + 100;
                InvalidateRect(hWnd, &pr, true);
                HBRUSH p1 = ((gameHandler.getPrevTile().x + gameHandler.getPrevTile().y) % 2 == 0) ? CreateSolidBrush(RGB(255, 255, 255)) : CreateSolidBrush(RGB(0, 0, 0));*/

                //Rectangle(hdc, pr.left, pr.top, pr.right, pr.bottom);

                HBRUSH p = CreateSolidBrush(RGB(255, 0, 0));

                RECT r;
                r.left = gameHandler.getSelectedTile().x * 100;
                r.top = gameHandler.getSelectedTile().y * 100;
                r.right = r.left + 100;
                r.bottom = r.top + 100;
                //InvalidateRect(hWnd, &r, false);

                //SelectObject(hdc, p1);
                //FillRect(hdc, &pr, p1);

                SelectObject(hdc, p);
                FrameRect(hdc, &r, p);

                DeleteObject(p);
                //DeleteObject(p1);
                gameHandler.resetTile();
            }

            for (POINT pt : gameHandler.getPotential())
            {
                HBRUSH p = CreateSolidBrush(RGB(255, 0, 0));

                RECT r;
                r.left = pt.x * 100;
                r.top = pt.y * 100;
                r.right = r.left + 100;
                r.bottom = r.top + 100;

                SelectObject(hdc, p);
                FillRect(hdc, &r, p);
                DeleteObject(p);
            }

            //if (gameHandler.checkPC())
            {
                Sprite sp;
                Piece temp;
                int bgc = 0;
                for (int b = 0; b < gameHandler.getBL(); b++)
                {
                    temp = gameHandler.getBlackPieces()[b];
                    bgc = (temp.isBgBlk()) ? 1 : 0;
                    for (POINT pot : gameHandler.getPotential())
                    {
                        if (pot.x == temp.getX() && pot.y == temp.getY())
                        {
                            bgc = 2;
                        }
                    }
                    sp = Sprite::getSprite(temp.getType(), temp.isBlack(), bgc);
                    sp.drawSprite(temp.getX(), temp.getY(), hdc);
                }
                for (int w = 0; w < gameHandler.getWL(); w++)
                {
                    temp = gameHandler.getWhitePieces()[w];
                    bgc = (temp.isBgBlk()) ? 1 : 0;
                    for (POINT pot : gameHandler.getPotential())
                    {
                        if (pot.x == temp.getX() && pot.y == temp.getY())
                        {
                            bgc = 2;
                        }
                    }
                    sp = Sprite::getSprite(temp.getType(), temp.isBlack(), bgc);
                    sp.drawSprite(temp.getX(), temp.getY(), hdc);
                }
                gameHandler.resetPC();

            }

        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOUSEMOVE:
        mousePos.x = LOWORD(lParam);
        mousePos.y = HIWORD(lParam);
        //ScreenToClient(hWnd, &mousePos);
        //OutputDebugStringA(("mPosX: " + std::to_string(mousePos.x) + " | mPosY: " + std::to_string(mousePos.y) + "\n").c_str());
        //OutputDebugStringA(("LmPosX: " + std::to_string(LOWORD(lParam)) + " | HmPosY: " + std::to_string(HIWORD(lParam)) + "\n").c_str());
        if (gameHandler.updateTile(mousePos))
        {
            //OutputDebugStringA("updated");
            PostMessage(hWnd, WM_PAINT, wParam, lParam);
        }

        break;

    case WM_LBUTTONDOWN:
        if (!complete)
        {
            switch (gameHandler.click())
            {
            case 0:
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                break;

            case 1:
                clickOutput = 1;
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                break;
            case 2:
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                clickOutput = -1;
                break;

            case 3:
                clickOutput = 1;
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                if (gameHandler.getCurCheck())
                {
                    PostMessage(hWnd, WM_COMMAND, IDD_CHECK, lParam);
                }
                else
                {
                    gameHandler.nextTurn();
                }
                break;

            case 4:
                clickOutput = 1;
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                if (gameHandler.getCurCheck())
                {
                    PostMessage(hWnd, WM_COMMAND, IDD_CHECK, lParam);
                }
                else
                {
                    gameHandler.nextTurn();
                }
                break;
            case 5:
                clickOutput = 1;
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                PostMessage(hWnd, WM_COMMAND, IDD_CHECKMATE, lParam);
                break;

            case 6:
                clickOutput = 1;
                stale = true;
                PostMessage(hWnd, WM_PAINT, wParam, lParam);
                PostMessage(hWnd, WM_COMMAND, IDD_CHECKMATE, lParam);

            default: break;
            }
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Check(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Checkmate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    complete = true;
    UNREFERENCED_PARAMETER(lParam);
    LPCSTR text;
    if (!stale)
    {
        text = (gameHandler.getBlkTurn()) ? "Black has checkmated White" : "White has checkmated Black";
    }
    else
    {
        text = "Stalemate";
    }
    SetDlgItemTextA(hDlg, checkmate_text, text);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            //PostQuitMessage(0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
