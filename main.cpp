#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

ofstream fout;
ifstream fin;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hwnd;               /* This is the handle for our window */
HWND button[5];
HWND banda[100];
HWND tip[100];
HWND lungime[100];
HWND latime[100];
HWND data1[100];
HWND button_valideaza[100];

int button_index[100];

int i = 0, counter = 1;
char buffer[10];
char textEP[20];
char textTip[20];
char textLungime[20];
char textLatime[20];
char textData[20];
char textAll[101];




/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");


int getIndex(){

    fin.open("record.txt", std::ios_base::in);
    string line1;
    string line;
    while(getline(fin, line1)) {
        line = line1;
    }
    char save[line.size()];
    strcpy(save, line.c_str());
    char *p = strtok(save, " ");
    fin.close();

    return atoi(p);
}

void refresh() {
    
}


int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{

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
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Flux Artego"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            700,                 /* The programs width */
            300,                 /* and height in pixels */
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

void scrie() {
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WORD cmd = LOWORD(wParam);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:   // fac butoane, label etc

            counter = getIndex();
            counter++;
            fout.open("record.txt", std::ios_base::app);
            std::fill_n(button_index, 100, -1);

            button[0] = CreateWindow("BUTTON",
                                     "Iesire",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     560, 220, 100, 20,
                                     hwnd, (HMENU)1, NULL, NULL);   // (HMENU) 1 reprezinta care case din switch se executa
            button[1] = CreateWindow("BUTTON",
                                     "Adauga",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     450, 220, 100, 20,
                                     hwnd, (HMENU)2, NULL, NULL);

            button[2] = CreateWindow("BUTTON",
                                     "Refresh",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     340, 220, 100, 20,
                                     hwnd, (HMENU)3, NULL, NULL);


            break;

        case WM_COMMAND:  // fac instructiuni butoane
            switch (cmd)
            {
                case 1:
                    //::MessageBeep(MB_ICONERROR);
                    //::MessageBox(hwnd, "Ai salvat ?", "atentie", MB_OKCANCEL);
                    cout << "GoodBye!";
                    PostQuitMessage(0);
                    break;

                case 2:   // Adaug nou record

                    banda[i] = CreateWindow("EDIT",
                                            "EP",
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            20, 30 * i, 30, 25,
                                            hwnd, NULL, NULL, NULL);
                    tip[i] = CreateWindow("EDIT",
                                          "100",
                                          WS_BORDER | WS_CHILD | WS_VISIBLE,
                                          55, 30 * i, 100, 25,
                                          hwnd, NULL, NULL, NULL);
                    lungime[i] = CreateWindow("EDIT",
                                              "Lungime",
                                              WS_BORDER | WS_CHILD | WS_VISIBLE,
                                              160, 30 * i, 100, 25,
                                              hwnd, NULL, NULL, NULL);
                    latime[i] = CreateWindow("EDIT",
                                             "Latime",
                                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                                             265, 30 * i, 100, 25,
                                             hwnd, NULL, NULL, NULL);

                    data1[i] = CreateWindow("EDIT",
                                            "Data",
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            370, 30 * i, 100, 25,
                                            hwnd, NULL, NULL, NULL);
                    button_valideaza[i] = CreateWindow("BUTTON",
                                                       "Scrie",
                                                       WS_VISIBLE | WS_CHILD | WS_BORDER,
                                                       475, 30 * i, 80, 20,
                                                       hwnd, (HMENU)(i+5), NULL, NULL);
                    i++;
                    break;
                case 3:         // Refresh

                    refresh();

                    break;
                case 4:         // Compute
                    break;
                default:
                    if (cmd > 4 && cmd < 103)
                    {
                        int index;
                        if (button_index[cmd-3] == -1){   // daca buton index nu a fost setata
                            button_index[cmd-3] = counter;
                            index = counter;
                            //cout << "Prima apasare a butinului " << cmd-3 << " si primeste index "<<counter<<endl;
                            counter++;
                        } else {                       // a fost setat
                            index = button_index[cmd-3];
                            //cout << "Deja apasat butonul "<< cmd-3 << " si are vechiul index " << button_index[cmd-3] << endl;
                            ::MessageBox(hwnd, "Pentru a rescrie apasa pe REFRESH","Suprascriere", MB_OK);
                        }

                        int gwtstat = 0;
                        gwtstat = GetWindowText(banda[cmd-5], &textEP[0], 20);
                        gwtstat = 0;
                        gwtstat = GetWindowText(tip[cmd-5], &textTip[0], 20);
                        gwtstat = 0;
                        gwtstat = GetWindowText(lungime[cmd-5], &textLungime[0], 20);
                        gwtstat = 0;
                        gwtstat = GetWindowText(latime[cmd-5], &textLatime[0], 20);
                        gwtstat = 0;
                        gwtstat = GetWindowText(data1[cmd-5], &textData[0], 20);
                        itoa(index, buffer, 10);
                        strcpy(textAll, buffer);
                        strcat(textAll," ");
                        strcat(textAll,textEP);
                        strcat(textAll, " ");
                        strcat(textAll,textTip);
                        strcat(textAll, " ");
                        strcat(textAll, textLungime);
                        strcat(textAll, " ");
                        strcat(textAll, textLatime);
                        strcat(textAll, " ");
                        strcat(textAll, textData);
                        fout << textAll << "\n";
                        ::MessageBox(hwnd, textAll,"text", MB_OKCANCEL);

                    }
                    break;
            }

            break;
        case WM_DESTROY:
            fout.close();
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }


    return 0;
}