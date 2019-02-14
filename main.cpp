#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#define citire_item(pos) in>>items[pos].index>>items[pos].eep>>items[pos].tip>>items[pos].lungime>>items[pos].latime>>items[pos].data>>items[pos].arie>>useless>>items[pos].greutate>>useless


#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <math.h>
#include <vector>


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

int i = 0, counter = 1, j = 1;
char buffer[10];
char textEP[20];
char textTip[20];
char textLungime[20];
char textLatime[20];
char textData[20];
char textAll[101];




/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

struct item {
    int index;
    char eep[3];
    int tip;
    float lungime;
    float latime;
    char data[20];
    float arie;
    float greutate;
};

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

int getLines(){
    fin.open("record.txt", std::ios_base::in);
    string line1;
    int nr = 0;
    while(getline(fin, line1)) {
        nr++;
    }
    fin.close();

    return nr;
}

float weight(char textEp[20], char textTip[20], float arie){
    float mass = 0;
    float ee[500] = {0};
    float ep[630] = {0};
    ee[80]  = 0.33;  // ee
    ee[100] = 0.38;
    ee[125] = 0.48;
    ee[150] = 0.51;
    ee[160] = 0.58;
    ee[200] = 0.717;
    ee[250] = 0.79;
    ee[300] = 0.885;
    ee[500] = 1.46;

    ep[80]  = 0.33;   // ep
    ep[100] = 0.38;
    ep[125] = 0.46;
    ep[160] = 0.57;
    ep[200] = 0.70;
    ep[250] = 0.84;
    ep[315] = 1.16;
    ep[400] = 1.30;
    ep[500] = 1.64;
    ep[630] = 1.70;
    if(strcmp(textEp,"ee") == 0)                // este ee
    {
        mass = ee[atoi(textTip)] * arie;
    }
    else                                        // este ep
    {
        mass = ep[atoi(textTip)] * arie;
    }



    return mass;
}

void refresh() {         // revad size
    ifstream in("record.txt");
    ofstream out("other.txt");
    int size = getLines();
    item items[size];
    cout << "Number of duplicates = "<< size<<endl;
    for (int k = 1; k <= size-1 ; ++k) {
        string line;
        getline(in, line);
        char save[line.size()];
        strcpy(save, line.c_str());
        char *p = strtok(save, " ");
        items[k].index = atoi(p);
        p = strtok(NULL, " ");
        strcpy(items[k].eep, p);
        p = strtok(NULL, " ");
        items[k].tip = atoi(p);
        p = strtok(NULL, " ");
        items[k].lungime = atof(p);
        p = strtok(NULL, " ");
        items[k].latime = atof(p);
        p = strtok(NULL, " ");
        strcpy(items[k].data, p);
        p = strtok(NULL, " ");
        items[k].arie = atof(p);
        p = strtok(NULL, " ");
        p = strtok(NULL, " ");
        items[k].greutate = atof(p);
        //cout << "Greutatile sunt = "<< p<< endl;
        //cout<<"Data este = "<<items[5].data<<endl;
    }

    string line;
    getline(in, line);
    char save[line.size()];
    strcpy(save, line.c_str());
    char *p = strtok(save, " ");
    items[size].index = atoi(p);
    p = strtok(NULL, " ");
    strcpy(items[size].eep, p);
    p = strtok(NULL, " ");
    items[size].tip = atoi(p);
    p = strtok(NULL, " ");
    items[size].lungime = atof(p);
    p = strtok(NULL, " ");
    items[size].latime = atof(p);
    p = strtok(NULL, " ");
    strcpy(items[size].data, p);
    char copie[20];
    strcpy(copie,items[size].data);
    p = strtok(NULL, " ");
    items[size].arie = atof(p);
    p = strtok(NULL, " ");
    p = strtok(NULL, " ");
    items[size].greutate = atof(p);
    strcpy(items[size].data,copie);
    //cout << "data din  ="<<items[size].data;



//    for (int k = 1; k <= size; ++k) {
//        cout << items[k].index<< " " <<items[k].eep<< " " <<items[k].tip<< " "<<items[k].lungime<<" "<<items[k].latime <<" " <<items[k].data<<" "<<items[k].arie <<" m^2 " <<items[k].greutate<<" kg"<<endl;
//
//
//    }

    for (int o = 1; o <= size ; ++o) {

        for (int oo = o + 1; oo <= size; ++oo) {
            if(items[o].index == items[oo].index)  // daca sunt la fel
            {

                strcpy(items[o].eep,items[oo].eep);
                strcpy(items[o].data,items[oo].data);
                items[o].tip = items[oo].tip;
                items[o].lungime = items[oo].lungime;
                items[o].latime = items[oo].latime;
                items[o].arie = items[oo].arie;
                items[o].greutate = items[oo].greutate;

            }
        }
    }

    int nr = 1;
    for (int o = 1; o <= size ; ++o) {
        if(nr == items[o].index){
            out << nr << " " << items[o].eep<< " " << items[o].tip<< " " << items[o].lungime<< " " << items[o].latime<<" "<<items[o].data<<" "<< items[o].arie<< " m^2 " << items[o].greutate<<" kg"<<"\n";
            nr++;
        }
    }
    in.close();
    out.close();
    // sterg fisier record.txt
    //redenumesc pe other.txt in record.txt
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

            static HWND hwnd_st_u, hwnd_ed_u;
            hwnd_st_u = CreateWindow("static", "ST_U",
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     15, 10, 45, 15,
                                     hwnd, (HMENU)(501),
                                     (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
            SetWindowText(hwnd_st_u, "Banda");
            hwnd_st_u = CreateWindow("static", "ST_U",
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     85, 10, 30, 15,
                                     hwnd, (HMENU)(501),
                                     (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
            SetWindowText(hwnd_st_u, "Tip");
            hwnd_st_u = CreateWindow("static", "ST_U",
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     176, 10, 60, 15,
                                     hwnd, (HMENU)(501),
                                     (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
            SetWindowText(hwnd_st_u, "Lungime");
            hwnd_st_u = CreateWindow("static", "ST_U",
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     270, 10, 90, 15,
                                     hwnd, (HMENU)(501),
                                     (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
            SetWindowText(hwnd_st_u, "Latime   (mm)");
            hwnd_st_u = CreateWindow("static", "ST_U",
                                     WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                     390, 10, 35, 15,
                                     hwnd, (HMENU)(501),
                                     (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
            SetWindowText(hwnd_st_u, "Data");





            counter = getIndex();
            counter++;
            cout << "Number of records = " << counter-1 <<endl;

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

            button[3] = CreateWindow("BUTTON",
                                     "Calculeaza",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     230, 220, 100, 20,
                                     hwnd, (HMENU)4, NULL, NULL);


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
                                            "ee",
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            20, 30 * j, 30, 25,
                                            hwnd, NULL, NULL, NULL);
                    tip[i] = CreateWindow("EDIT",
                                          NULL,
                                          WS_BORDER | WS_CHILD | WS_VISIBLE,
                                          55, 30 * j, 100, 25,
                                          hwnd, NULL, NULL, NULL);
                    lungime[i] = CreateWindow("EDIT",
                                              NULL,
                                              WS_BORDER | WS_CHILD | WS_VISIBLE,
                                              160, 30 * j, 100, 25,
                                              hwnd, NULL, NULL, NULL);
                    latime[i] = CreateWindow("EDIT",
                                             NULL,
                                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                                             265, 30 * j, 100, 25,
                                             hwnd, NULL, NULL, NULL);

                    data1[i] = CreateWindow("EDIT",
                                            NULL,
                                            WS_BORDER | WS_CHILD | WS_VISIBLE,
                                            370, 30 * j, 100, 25,
                                            hwnd, NULL, NULL, NULL);
                    button_valideaza[i] = CreateWindow("BUTTON",
                                                       "Scrie",
                                                       WS_VISIBLE | WS_CHILD | WS_BORDER,
                                                       475, 30 * j, 80, 20,
                                                       hwnd, (HMENU)(i+5), NULL, NULL);
                    i++;
                    j++;

                    break;
                case 3:         // Refresh

                    refresh();
                    std::remove("record.txt");
                    std::rename("other.txt", "record.txt");
                    for (int t = 0; t < 102; ++t) {
                        DestroyWindow(button_valideaza[t]);
                        DestroyWindow(banda[t]);
                        DestroyWindow(tip[t]);
                        DestroyWindow(lungime[t]);
                        DestroyWindow(latime[t]);
                        DestroyWindow(data1[t]);

                    }
                    j = 1;


                    Beep( 750, 300 );
                    break;
                case 4:         // Compute
                    break;
                default:
                    if (cmd > 4 && cmd < 103)
                    {

                        int index;
                        fout.open("record.txt", std::ios_base::app);
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
                        float latime = atof(textLatime);
                        float lungime = atof(textLungime);
                        latime = latime / 1000;    // conversia in metrii
                        float arie = lungime * latime;
                        float mass = 0;
                        mass = weight(textEP, textTip, arie);
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
                        strcat(textAll," ");
                        fout << textAll <<" " << arie << " m^2 ";  // arie
                        fout << mass << " kg" << "\n";
                        //::MessageBox(hwnd, textAll,"text", MB_OKCANCEL);
                        fout.close();
                        Beep( 750, 300 );
                    }
                    break;
            }

            break;
        case WM_SIZE:

            RECT rcParent;
            GetClientRect(hwnd, &rcParent);
            RECT rcButton[5];
            GetClientRect(button[0], &rcButton[0]); // Pt a completa cu butoane se adauga la primul arg - 12 - (rcButton[x].right  - rcButton[x].left) si la al doilea se schimba cu x
            SetWindowPos(button[0],
                         NULL,
                         (rcParent.right  - 12 - (rcButton[0].right  - rcButton[0].left)),
                         (rcParent.bottom - 12 - (rcButton[0].bottom - rcButton[0].top)),
                         0,
                         0,
                         SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);

            GetClientRect(button[1], &rcButton[1]);
            SetWindowPos(button[1],
                         NULL,
                         (rcParent.right  - 12 - (rcButton[0].right  - rcButton[0].left) - 12 - (rcButton[1].right  - rcButton[1].left)),
                         (rcParent.bottom - 12 - (rcButton[1].bottom - rcButton[1].top)),
                         0,
                         0,
                         SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);

            GetClientRect(button[2], &rcButton[2]);
            SetWindowPos(button[2],
                         NULL,
                         (rcParent.right  - 12 - (rcButton[0].right  - rcButton[0].left) - 12 - (rcButton[1].right  - rcButton[1].left)) - 12 - (rcButton[2].right - rcButton[2].left),
                         (rcParent.bottom - 12 - (rcButton[2].bottom - rcButton[2].top)),
                         0,
                         0,
                         SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);

            GetClientRect(button[3], &rcButton[3]);
            SetWindowPos(button[3],
                         NULL,
                         (rcParent.right  - 12 - (rcButton[0].right  - rcButton[0].left) - 12 - (rcButton[1].right  - rcButton[1].left)) - 12 - (rcButton[2].right - rcButton[2].left) - 12 - (rcButton[3].right - rcButton[3].left),
                         (rcParent.bottom - 12 - (rcButton[3].bottom - rcButton[3].top)),
                         0,
                         0,
                         SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);

            break;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }


    return 0;
}