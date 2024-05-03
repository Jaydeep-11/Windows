#include<Windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

void DrawCircle(HDC hdc, int centerX, int centerY, int radius);
void DrawRectangle(HDC hdc, int left, int top, int right, int bottom);
void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3);
void DrawSquare(HDC hdc, int left, int top, int size);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPSTR lpCmdLine, int nShowCmd)
{
   static TCHAR szClassName[]=TEXT("The Standard Windows");
   static TCHAR szTitleOfWindows[]=TEXT("Hello World_2");

   HWND hwnd = NULL;
    
   WNDCLASSEX wnd;
   MSG msg;

   wnd.cbSize = sizeof(WNDCLASSEX);
   wnd.cbClsExtra = 0;
   wnd.cbWndExtra = 0;
   wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wnd.hCursor = LoadCursor(NULL , IDC_ARROW);
   wnd.hIcon = LoadIcon(NULL , IDI_APPLICATION);
   wnd.hIconSm = LoadIcon(NULL , IDI_APPLICATION);
   wnd.hInstance = hInstance;
   wnd.lpfnWndProc = WndProc;
   wnd.lpszClassName = szClassName;
   wnd.lpszMenuName = NULL; 
   wnd.style = CS_HREDRAW | CS_VREDRAW;


   if(!RegisterClassEx(&wnd))
   {
     MessageBox(NULL,TEXT("Fail to register window"),
                TEXT("ResgisterClassEx"),MB_ICONERROR |MB_TOPMOST );
     ExitProcess(EXIT_FAILURE);
   }

   hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                         szClassName,
                         szTitleOfWindows,
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         NULL,
                         NULL,
                         hInstance,
                         NULL
                         );


                    
   if(hwnd == NULL)
   {
    MessageBox(NULL,TEXT("FAIL TO CREAT A WINDOW"),
                TEXT("CREATWINDOWEX"),MB_ICONERROR | MB_TOPMOST);
    ExitProcess(EXIT_FAILURE);            
   }

   ShowWindow(hwnd, nShowCmd);
   UpdateWindow(hwnd);

   while(GetMessage(&msg,NULL,0,0))
   {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   }
  
   return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd , UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;
    static int midX, midY;

   switch (uMsg) {

    case WM_CREATE:
        GetClientRect(hwnd, &rect);
        midX = (rect.right - rect.left) / 2;
        midY = (rect.bottom - rect.top) / 2;
        break;
    
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Get the client area dimensions
        RECT rect;
        GetClientRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;


        // Draw horizontal line in the middle
        MoveToEx(hdc, 0, midY, NULL);
        LineTo(hdc, width, midY);

        // Draw vertical line in the middle
        MoveToEx(hdc, midX, 0, NULL);
        LineTo(hdc, midX, height);
        

        // Draw shapes in each section
        DrawCircle(hdc, 250, 120, 50);
        DrawRectangle(hdc, midX+350, 200, midX + 150, 100);
        DrawTriangle(hdc, 100, midY+200, 350, midY +200, 220, midY +100);
        DrawSquare(hdc, midX +200, midY+100, 100);

        EndPaint(hwnd, &ps);
        break;
    }

     case WM_RBUTTONDOWN: {
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);

        if (xPos < midX) {
            if (yPos < midY) {
                MessageBox(hwnd, "A circle is also termed as the locus of the points drawn at an equidistant from the centre. The distance from the centre of the circle to the outer line is its radius. Diameter is the line which divides the circle into two equal parts and is also equal to twice of the radius.", "CIRCLE", MB_OK|MB_ICONINFORMATION );
            } else {
                MessageBox(hwnd, "In Geometry, a triangle is a three-sided polygon that consists of three edges and three vertices. The most important property of a triangle is that the sum of the internal angles of a triangle is equal to 180 degrees.", "TRIANGLE", MB_OK | MB_ICONINFORMATION);
            }
        } else {
            if (yPos < midY) {
                MessageBox(hwnd, "A rectangle is a closed 2-D shape, having 4 sides, 4 corners, and 4 right angles (90°). The opposite sides of a rectangle are equal and parallel. Since, a rectangle is a 2-D shape, it is characterized by two dimensions, length, and width. Length is the longer side of the rectangle and width is the shorter side.", "RECTANGLE", MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(hwnd, "A square is a two-dimensional closed shape with 4 equal sides and 4 vertices. Its opposite sides are parallel to each other. We can also think of a square as a rectangle with equal length and breadth. Looking around, you can find many things that resemble the square shape.", "SQUARE", MB_OK | MB_ICONINFORMATION);
            }
        }
        break;
    }

    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void DrawCircle(HDC hdc, int centerX, int centerY, int radius) {
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
}

void DrawRectangle(HDC hdc, int left, int top, int right, int bottom) {
    Rectangle(hdc, left, top, right, bottom);
}

void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3) {
    POINT points[] = { {x1, y1}, {x2, y2}, {x3, y3} };
    Polygon(hdc, points, 3);
}

void DrawSquare(HDC hdc, int left, int top, int size) {
    Rectangle(hdc, left, top, left + size, top + size);
}