#pragma once
struct XDisplay {
private:
    Display* display = XOpenDisplay(NULL);

public:
    XDisplay() {
        display = XOpenDisplay(NULL);
        if (!display) throw std::invalid_argument("Could not open display");
    }

    bool keyDown(int keyCode) {
        char keys_return[32];
        XQueryKeymap(display, keys_return);
        KeyCode kc2 = XKeysymToKeycode(display, keyCode);
        bool buttonDown = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
        return buttonDown;
    }

    void mouseClickLeft() {
        XTestFakeButtonEvent(display, Button1, True, 0);
        XTestFakeButtonEvent(display, Button1, False, 0);
        XFlush(display);
    }

    void spacebarClick() {
        // Simulate the key press and release events for the "W" key
        KeySym keySym = XK_p; // "w" for the "W" key
        KeyCode keyCode = XKeysymToKeycode(display, keySym);

        // for (int i = 0;i < 10;i++) {
            XTestFakeKeyEvent(display, keyCode, True, 0);
            XTestFakeKeyEvent(display, keyCode, False, 0);
            XFlush(display);
            // usleep(100);  // 100ms
        // }

        // Sleep briefly to allow the X server to process the events

    }

    bool isLeftMouseButtonDown() {
        Window root, child;
        int root_x, root_y, win_x, win_y;
        unsigned int mask;
        if (XQueryPointer(display, XRootWindow(display, DefaultScreen(display)), &root, &child, &root_x, &root_y, &win_x, &win_y, &mask))
            return (mask & Button1Mask) != 0;
        return false;
    }

    void moveControllerAimStick(int pitchMovement, int yawMovement) {
        XTestFakeRelativeMotionEvent(display, yawMovement, pitchMovement, CurrentTime);
        XFlush(display);
    }

};