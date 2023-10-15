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

    bool keyDown(std::string XK_keyName) {
        KeySym keyCode = XStringToKeysym(trimXKPrefix(XK_keyName).c_str());
        return keyDown(keyCode);
    }

    void mouseClickLeft() {
        XTestFakeButtonEvent(display, Button1, True, 0);
        XTestFakeButtonEvent(display, Button1, False, 0);
        XFlush(display);
    }

    bool isLeftMouseButtonDown() {
        Window root, child;
        int root_x, root_y, win_x, win_y;
        unsigned int mask;
        if (XQueryPointer(display, XRootWindow(display, DefaultScreen(display)), &root, &child, &root_x, &root_y, &win_x, &win_y, &mask))
            return (mask & Button1Mask) != 0;
        return false;
    }

    void moveMouseRelative(int pitchMovement, int yawMovement) {
        XTestFakeRelativeMotionEvent(display, yawMovement, pitchMovement, CurrentTime);
        XFlush(display);
    }

    std::string trimXKPrefix(const std::string& keyName) {
        if (keyName.compare(0, 3, "XK_") == 0)
            return keyName.substr(3);
        return keyName;
    }
};