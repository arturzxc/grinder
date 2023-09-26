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
};