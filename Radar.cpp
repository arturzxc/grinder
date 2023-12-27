#pragma once
struct Radar {
    ConfigLoader* cl;
    XDisplay* xDisplay;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;

    const int RADAR_ZOOM = 20;
    const int WINDOW_INIT_WIDTH = 300;
    const int WINDOW_INIT_HEIGHT = 300;
    const int ENEMY_SCALE_DIVIDER = 35; //This is the inverse of the size of the enemies on the radar. Smaller number means bigger enemies!

    Display* display;
    GC gc; //Graphics context (our drawing pen!)
    int counter;

    //UI components
    Window window;

    int windowWidth;
    int windowWidthHalf;
    int windowHeight;
    int windowHeightHalf;

    //enemy vars
    int enemyWidth;
    int enemyWidthHalf;
    int enemyHeight;
    int enemyHeightHalf;

    Radar(ConfigLoader* cl, XDisplay* xDisplay, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->xDisplay = xDisplay;
        this->display = xDisplay->display;
        gc = DefaultGC(this->display, DefaultScreen(this->display));
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;

        createRootWindow();
    }

    void createRootWindow() {
        int screen = DefaultScreen(display);
        Window root = RootWindow(display, screen);
        window = XCreateSimpleWindow(display, root, 0, 0, WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT, 0,
            BlackPixel(display, screen),
            WhitePixel(display, screen));

        //only capture event that we care about: expose(show window) and resizing
        XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);

        //Redirect & move top left
        XSetWindowAttributes attrib;
        attrib.override_redirect = True;
        XChangeWindowAttributes(display, window, CWOverrideRedirect, &attrib);
        XMoveWindow(display, window, 0, 0);

        //always stay on top
        Atom netWmState = XInternAtom(display, "_NET_WM_STATE", False);
        Atom netWmStateAbove = XInternAtom(display, "_NET_WM_STATE_ABOVE", False);
        XChangeProperty(display, window, netWmState, XA_ATOM, 32, PropModeAppend, (unsigned char*)&netWmStateAbove, 1);

        //remove decoration
        Atom motif_hints = XInternAtom(display, "_MOTIF_WM_HINTS", False);
        struct {
            unsigned long flags;
            unsigned long functions;
            unsigned long decorations;
            long input_mode;
            unsigned long status;
        } MWMHints = { 2, 0, 0, 0, 0 };
        XChangeProperty(display, window, motif_hints, motif_hints, 32, PropModeReplace, (unsigned char*)&MWMHints, 5);

        //show the window 
        XMapWindow(display, window);
        XFlush(display);
    }

    void RotateCartessianCoords(int x, int y, int* newX, int* newY, float angleDegrees) {
        float angleRadians = M_PI / 180.0 * angleDegrees;
        *newX = x * std::cos(angleRadians) + y * std::sin(angleRadians);
        *newY = -x * std::sin(angleRadians) + y * std::cos(angleRadians);
    }

    void ScaleCartesianCoords(int x, int y, int* newX, int* newY) {
        *newX = x * std::max(windowWidth, 1) / WINDOW_INIT_WIDTH / RADAR_ZOOM;
        *newY = y * std::max(windowHeight, 1) / WINDOW_INIT_HEIGHT / RADAR_ZOOM;
    }

    void CartesianCoordsToX11Coords(int cartX, int cartY, int* x11X, int* x11Y, int shapeWidth, int shapeWeight) {
        *x11X = cartX + windowWidthHalf;
        *x11X -= shapeWidth / 2;
        *x11Y = windowHeightHalf - cartY;
        *x11Y -= shapeWeight / 2;
    }

    void drawEnemy(int x, int y, float angle) {
        RotateCartessianCoords(x, y, &x, &y, angle);
        ScaleCartesianCoords(x, y, &x, &y);
        CartesianCoordsToX11Coords(x, y, &x, &y, enemyWidth, enemyHeight);
        XFillArc(display, window, gc, x, y, enemyWidth, enemyHeight, 0, 360 * 64);
    }

    void handleWindowExposeOrResize() {
        //grab window's current attributes
        XWindowAttributes windowAttributes;
        XGetWindowAttributes(display, window, &windowAttributes);

        //save window dimensions
        windowWidth = windowAttributes.width;
        windowWidthHalf = windowWidth / 2;
        windowHeight = windowAttributes.height;
        windowHeightHalf = windowHeight / 2;

        //save enemy dimensions
        enemyWidth = windowWidth / ENEMY_SCALE_DIVIDER;
        enemyWidthHalf = enemyWidth / 2;

        enemyHeight = windowHeight / ENEMY_SCALE_DIVIDER;
        enemyHeightHalf = enemyHeight / 2;
    }

    void processEvents(int in_counter) {
        counter = in_counter;
        while (XPending(display) > 0) {
            XEvent event;
            XNextEvent(display, &event);
            if (event.type == Expose)
                handleWindowExposeOrResize();

            else if (event.type == ConfigureNotify)
                handleWindowExposeOrResize();
        }
    }

    void repaint() {
        //bg
        XSetForeground(display, gc, 0x020617);
        XFillRectangle(display, window, gc, 0, 0, windowWidth, windowHeight);

        //draw crosshairs
        XSetForeground(display, gc, 0x80ADD8FF);
        XDrawLine(display, window, gc, windowWidthHalf, 0, windowWidthHalf, windowHeight);
        XDrawLine(display, window, gc, 0, windowHeightHalf, windowWidth, windowHeightHalf);
        XDrawArc(display, window, gc, 1, 1, windowWidth - 2, windowHeight - 2, 0, 360 * 64);
        XDrawArc(display, window, gc, 2, 2, windowWidth - 3, windowHeight - 3, 0, 360 * 64);


        XSetForeground(display, gc, 0xFF00FF);
        if (localPlayer->isValid())
            for (int i = 0;i < players->size();i++) {
                Player* p = players->at(i);
                if (!p->isCombatReady())continue;
                if (p->local)continue;

                int lpX = localPlayer->localOrigin.x;
                int lpY = localPlayer->localOrigin.y;

                int enX = p->localOrigin.x;
                int enY = p->localOrigin.y;

                int deltaX = enX - lpX;
                int deltaY = enY - lpY;

                if (p->friendly)
                    XSetForeground(display, gc, 0x00FF00);
                else
                    XSetForeground(display, gc, 0xFF0000);
                drawEnemy(deltaX, deltaY, localPlayer->viewAngles.y - 90);
            }

        //push the changes
        XFlush(display);
    }
};
