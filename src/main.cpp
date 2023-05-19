#include <GL/glut.h>
#include "class.h"
#include "keyboard_mouse.h"
#include <Windows.h>
#include <Shellapi.h>

// Global variables
static int windowWidth = 800;
static int windowHeight = 600;

static Grid* grid;
static Cube* cube;
Game* game = nullptr;

// Reshape function
void reshape(int width, int height) {
    // Update the window width and height
    windowWidth = width;
    windowHeight = height;

    // Set the viewport and projection matrix
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Display function
void display() {
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    grid->draw();
    cube->draw();

    // Swap buffers
    glutSwapBuffers();
    glutPostRedisplay();
}

// Function to minimize the window to the system tray
void MinimizeToTray(HWND hWnd) {
    NOTIFYICONDATAA nid; // Use the ANSI version of NOTIFYICONDATA
    memset(&nid, 0, sizeof(nid));

    nid.cbSize = sizeof(nid);
    nid.hWnd = hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    strcpy_s(nid.szTip, "My Application"); // Use strcpy_s to copy the ANSI string

    // Add the system tray icon
    Shell_NotifyIconA(NIM_ADD, &nid);

    // Set up the right-click menu
    HMENU hMenu = CreatePopupMenu();
    AppendMenuA(hMenu, MF_STRING, WM_USER + 2, "Close");
    AppendMenuA(hMenu, MF_STRING, WM_USER + 3, "Open New Instance");

    // Show the system tray icon with the menu
    Shell_NotifyIconA(NIM_SETVERSION, &nid);
    Shell_NotifyIconA(NIM_SETFOCUS, &nid);

    // Hide the console window
    ShowWindow(hWnd, SW_HIDE);
}

// Window procedure for handling system tray messages
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_USER + 1) {
        switch (lParam) {
            case WM_RBUTTONUP: {
                POINT pt;
                GetCursorPos(&pt);

                HMENU hMenu = CreatePopupMenu();
                AppendMenuA(hMenu, MF_STRING, WM_USER + 2, "Close");
                AppendMenuA(hMenu, MF_STRING, WM_USER + 3, "Open New Instance");

                SetForegroundWindow(hWnd);
                TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, nullptr);

                DestroyMenu(hMenu);
                break;
            }
        }
    }
    else if (uMsg == WM_COMMAND) {
        switch (LOWORD(wParam)) {
            case WM_USER + 2: // Close
                DestroyWindow(hWnd);
                break;

            case WM_USER + 3: // Open New Instance
                ShellExecuteA(nullptr, "open", "myprogram.exe", nullptr, nullptr, SW_SHOW);
                break;
        }
    }
    else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Initialize function
void initialize(Grid& gridObj, Cube& cubeObj) {
    grid = &gridObj;
    cube = &cubeObj;
    game = new Game(gridObj);

    // Set the grid size
    int numRows = 10;
    int numCols = 10;
    float cellSize = 50.0f;
    grid->setGridSize(numRows, numCols, cellSize);

    // Convert the window title to a C-style string
    const char* WindowTitle = "Blah";

    // Set up the display mode and window
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WindowTitle);

    // Minimize the command console window
    HWND hWndConsole = GetConsoleWindow();
    MinimizeToTray(hWndConsole);

    // Maximize the game window
    HWND hWndGame = FindWindowA(nullptr, WindowTitle);
    ShowWindow(hWndGame, SW_MAXIMIZE);

    // Register a window class for the tray icon messages
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "TrayWindowClass";
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    RegisterClassExA(&wcex);

    // Create a hidden window for receiving tray icon messages
    HWND hWndTray = CreateWindowExA(
        0,
        "TrayWindowClass",
        "TrayWindow",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Set the callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Create a grid
    int numRows = 10;
    int numCols = 10;
    float cellSize = 50.0f;
    Grid grid;
    grid.setGridSize(numRows, numCols, cellSize);

    Cube cube(grid);
    initialize(grid, cube);

    glutMainLoop();

    return 0;
}
