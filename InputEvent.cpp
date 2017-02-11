#include "stdafx.h"
#include "InputEvent.h"

#include <stdio.h>

namespace Xylena {
    KeyCode InputEvent::keyCodeForKeyboard(int code) {

        switch (code) {

        case -1: return KEY_UNKNOWN;
        case 32: return KEY_SPACE;
        case 39: return KEY_APOSTROPHE;
        case 44: return KEY_COMMA;
        case 45: return KEY_MINUS;
        case 46: return KEY_PERIOD;
        case 47: return KEY_SLASH;
        case 48: return KEY_0;
        case 49: return KEY_1;
        case 50: return KEY_2;
        case 51: return KEY_3;
        case 52: return KEY_4;
        case 53: return KEY_5;
        case 54: return KEY_6;
        case 55: return KEY_7;
        case 56: return KEY_8;
        case 57: return KEY_9;
        case 59: return KEY_SEMICOLON;
        case 61: return KEY_EQUAL;
        case 65: return KEY_A;
        case 66: return KEY_B;
        case 67: return KEY_C;
        case 68: return KEY_D;
        case 69: return KEY_E;
        case 70: return KEY_F;
        case 71: return KEY_G;
        case 72: return KEY_H;
        case 73: return KEY_I;
        case 74: return KEY_J;
        case 75: return KEY_K;
        case 76: return KEY_L;
        case 77: return KEY_M;
        case 78: return KEY_N;
        case 79: return KEY_O;
        case 80: return KEY_P;
        case 81: return KEY_Q;
        case 82: return KEY_R;
        case 83: return KEY_S;
        case 84: return KEY_T;
        case 85: return KEY_U;
        case 86: return KEY_V;
        case 87: return KEY_W;
        case 88: return KEY_X;
        case 89: return KEY_Y;
        case 90: return KEY_Z;
        case 91: return KEY_LEFT_BRACKET;
        case 92: return KEY_BACKSLASH;
        case 93: return KEY_RIGHT_BRACKET;
        case 96: return KEY_GRAVE_ACCENT;
        case 161: return KEY_WORLD_1;
        case 162: return KEY_WORLD_2;
        case 256: return KEY_ESCAPE;
        case 257: return KEY_ENTER;
        case 258: return KEY_TAB;
        case 259: return KEY_BACKSPACE;
        case 260: return KEY_INSERT;
        case 261: return KEY_DELETE;
        case 262: return KEY_RIGHT;
        case 263: return KEY_LEFT;
        case 264: return KEY_DOWN;
        case 265: return KEY_UP;
        case 266: return KEY_PAGE_UP;
        case 267: return KEY_PAGE_DOWN;
        case 268: return KEY_HOME;
        case 269: return KEY_END;
        case 280: return KEY_CAPS_LOCK;
        case 281: return KEY_SCROLL_LOCK;
        case 282: return KEY_NUM_LOCK;
        case 283: return KEY_PRINT_SCREEN;
        case 284: return KEY_PAUSE;
        case 290: return KEY_F1;
        case 291: return KEY_F2;
        case 292: return KEY_F3;
        case 293: return KEY_F4;
        case 294: return KEY_F5;
        case 295: return KEY_F6;
        case 296: return KEY_F7;
        case 297: return KEY_F8;
        case 298: return KEY_F9;
        case 299: return KEY_F10;
        case 300: return KEY_F11;
        case 301: return KEY_F12;
        case 302: return KEY_F13;
        case 303: return KEY_F14;
        case 304: return KEY_F15;
        case 305: return KEY_F16;
        case 306: return KEY_F17;
        case 307: return KEY_F18;
        case 308: return KEY_F19;
        case 309: return KEY_F20;
        case 310: return KEY_F21;
        case 311: return KEY_F22;
        case 312: return KEY_F23;
        case 313: return KEY_F24;
        case 314: return KEY_F25;
        case 320: return KEY_KEYPAD_0;
        case 321: return KEY_KEYPAD_1;
        case 322: return KEY_KEYPAD_2;
        case 323: return KEY_KEYPAD_3;
        case 324: return KEY_KEYPAD_4;
        case 325: return KEY_KEYPAD_5;
        case 326: return KEY_KEYPAD_6;
        case 327: return KEY_KEYPAD_7;
        case 328: return KEY_KEYPAD_8;
        case 329: return KEY_KEYPAD_9;
        case 330: return KEY_KEYPAD_DECIMAL;
        case 331: return KEY_KEYPAD_DIVIDE;
        case 332: return KEY_KEYPAD_MULTIPLY;
        case 333: return KEY_KEYPAD_SUBTRACT;
        case 334: return KEY_KEYPAD_ADD;
        case 335: return KEY_KEYPAD_ENTER;
        case 336: return KEY_KEYPAD_EQUAL;
        case 340: return KEY_LEFT_SHIFT;
        case 341: return KEY_LEFT_CONTROL;
        case 342: return KEY_LEFT_ALT;
        case 343: return KEY_LEFT_SUPER;
        case 344: return KEY_RIGHT_SHIFT;
        case 345: return KEY_RIGHT_CONTROL;
        case 346: return KEY_RIGHT_ALT;
        case 347: return KEY_RIGHT_SUPER;
        case 348: return KEY_MENU;

        default:
            return KEY_UNKNOWN;
        }
    }

    KeyCode InputEvent::keyCodeForMouse(int code) {
        
        switch (code) {

        case 0: return MOUSE_BUTTON_LEFT;
        case 1: return MOUSE_BUTTON_MIDDLE;
        case 2: return MOUSE_BUTTON_RIGHT;
        case 3: return MOUSE_BUTTON_4;
        case 4: return MOUSE_BUTTON_5;
        case 5: return MOUSE_BUTTON_6;
        case 6: return MOUSE_BUTTON_7;
        case 7: return MOUSE_BUTTON_8;

        default:
            return MOUSE_BUTTON_LEFT;
        }
    }

    KeyCode InputEvent::keyCodeForJoystick(int code) {

        switch (code) {

        case 0: return JOYSTICK_1;
        case 1: return JOYSTICK_2;
        case 2: return JOYSTICK_3;
        case 3: return JOYSTICK_4;
        case 4: return JOYSTICK_5;
        case 5: return JOYSTICK_6;
        case 6: return JOYSTICK_7;
        case 7: return JOYSTICK_8;
        case 8: return JOYSTICK_9;
        case 9: return JOYSTICK_10;
        case 10: return JOYSTICK_11;
        case 11: return JOYSTICK_12;
        case 12: return JOYSTICK_13;
        case 13: return JOYSTICK_14;
        case 14: return JOYSTICK_15;
        case 15: return JOYSTICK_16;

        default:
            return JOYSTICK_1;
        }
    }

    KeyStatus InputEvent::keyStatusForAction(int action) {

        switch (action) {
            
        case 0: return KEY_RELEASE;
        case 1: return KEY_PRESS;
        case 2: return KEY_REPEAT;

        default:
            return KEY_PRESS;
        }

    }

    InputEvent InputEvent::clone() {
        InputEvent input;
        input.setKeyCode(this->getKeyCode());
        input.setKeyStatus(this->getKeyStatus());

        return input;
    }
}