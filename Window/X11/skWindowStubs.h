#pragma once
// Temporary stubs have been copied from:
// https://tronche.com/gui/x/xlib
// https://www.khronos.org/registry/OpenGL-Refpages

#if WIN32

typedef int Window;
struct XVisualInfo;

struct Display;
typedef int Window;
typedef int Bool;
typedef int Atom;

#define GLX_RGBA 0
#define GLX_DEPTH_SIZE 0
#define GLX_DOUBLEBUFFER 0
#define None 0
#define AllocNone 0
#define InputOutput 1
#define True 1
#define False 1
#define PropModeReplace 0

#define ExposureMask 1
#define KeyPressMask 1
#define KeyReleaseMask 1
#define StructureNotifyMask 1
#define ResizeRedirectMask 1
#define PointerMotionMask 1
#define SubstructureNotifyMask 1
#define VisibilityChangeMask 1
#define ButtonPressMask 1
#define ButtonReleaseMask 1

#define Expose 1
#define ConfigureNotify 2
#define DestroyNotify 3
#define MotionNotify 4
#define ClientMessage 5
#define ButtonPress 6
#define ButtonRelease 7
#define KeyPress 8
#define KeyRelease 9

#define VisualNoMask 0x0
#define VisualIDMask 0x1
#define VisualScreenMask 0x2
#define VisualDepthMask 0x4
#define VisualClassMask 0x8
#define VisualRedMaskMask 0x10
#define VisualGreenMaskMask 0x20
#define VisualBlueMaskMask 0x40
#define VisualColormapSizeMask 0x80
#define VisualBitsPerRGBMask 0x100
#define VisualAllMask 0x1FF

/* Window attribute value mask bits */

#define CWBackPixmap (1L << 0)
#define CWBackPixel (1L << 1)
#define CWBorderPixmap (1L << 2)
#define CWBorderPixel (1L << 3)
#define CWBitGravity (1L << 4)
#define CWWinGravity (1L << 5)
#define CWBackingStore (1L << 6)
#define CWBackingPlanes (1L << 7)
#define CWBackingPixel (1L << 8)
#define CWOverrideRedirect (1L << 9)
#define CWSaveUnder (1L << 10)
#define CWEventMask (1L << 11)
#define CWDontPropagate (1L << 12)
#define CWColormap (1L << 13)
#define CWCursor (1L << 14)
#define StaticGravity 0
#define PPosition 2
#define PSize 1
#define PMinSize 1
#define PMaxSize 1
#define GL_TRUE 1
#define GLXDrawable Window

/* Values */

typedef struct XVisualInfo
{
    XVisualInfo*  visual;
    int           visualid;
    int           screen;
    int           depth;
    int           cls;
    unsigned long red_mask;
    unsigned long green_mask;
    unsigned long blue_mask;
    int           colormap_size;
    int           bits_per_rgb;
} XVisualInfo;

typedef struct Pixmap
{
    int x;
} Pixmap;

typedef struct Colormap
{
    int x;
} Colormap;
typedef struct Cursor
{
    int x;
} Cursor;

typedef int* GLXContext;
typedef int  Status;

/* Values */

typedef struct
{
    Pixmap        background_pixmap;     /* background, None, or ParentRelative */
    unsigned long background_pixel;      /* background pixel */
    Pixmap        border_pixmap;         /* border of the window or CopyFromParent */
    unsigned long border_pixel;          /* border pixel value */
    int           bit_gravity;           /* one of bit gravity values */
    int           win_gravity;           /* one of the window gravity values */
    int           backing_store;         /* NotUseful, WhenMapped, Always */
    unsigned long backing_planes;        /* planes to be preserved if possible */
    unsigned long backing_pixel;         /* value to use in restoring planes */
    Bool          save_under;            /* should bits under be saved? (popups) */
    long          event_mask;            /* set of events that should be saved */
    long          do_not_propagate_mask; /* set of events that should not propagate */
    Bool          override_redirect;     /* boolean value for override_redirect */
    Colormap      colormap;              /* color map to be associated with window */
    Cursor        cursor;                /* cursor to be displayed (or None) */
} XSetWindowAttributes;

struct XErrorEvent;

// https://tronche.com/gui/x/xlib/events/structures.html#XEvent

typedef struct
{
    int           type;       /* Expose */
    unsigned long serial;     /* # of last request processed by server */
    Bool          send_event; /* true if this came from a SendEvent request */
    Display*      display;    /* Display the event was read from */
    Window        window;
    int           x, y;
    int           width, height;
    int           count; /* if nonzero, at least this many more */
} XExposeEvent;

typedef struct
{
    int           type;       /* ConfigureNotify */
    unsigned long serial;     /* # of last request processed by server */
    Bool          send_event; /* true if this came from a SendEvent request */
    Display*      display;    /* Display the event was read from */
    Window        event;
    Window        window;
    int           x, y;
    int           width, height;
    int           border_width;
    Window        above;
    Bool          override_redirect;
} XConfigureEvent;

typedef struct
{
    int           type;       /* DestroyNotify */
    unsigned long serial;     /* # of last request processed by server */
    Bool          send_event; /* true if this came from a SendEvent request */
    Display*      display;    /* Display the event was read from */
    Window        event;
    Window        window;
} XDestroyWindowEvent;

typedef int Time;

typedef struct
{
    int           type;           /* MotionNotify */
    unsigned long serial;         /* # of last request processed by server */
    Bool          send_event;     /* true if this came from a SendEvent request */
    Display*      display;        /* Display the event was read from */
    Window        window;         /* ``event'' window reported relative to */
    Window        root;           /* root window that the event occurred on */
    Window        subwindow;      /* child window */
    Time          time;           /* milliseconds */
    int           x, y;           /* pointer x, y coordinates in event window */
    int           x_root, y_root; /* coordinates relative to root */
    unsigned int  state;          /* key or button mask */
    char          is_hint;        /* detail */
    Bool          same_screen;    /* same screen flag */
} XMotionEvent;

typedef struct
{
    int           type;       /* ClientMessage */
    unsigned long serial;     /* # of last request processed by server */
    Bool          send_event; /* true if this came from a SendEvent request */
    Display*      display;    /* Display the event was read from */
    Window        window;
    Atom          message_type;
    int           format;
    union
    {
        char  b[20];
        short s[10];
        long  l[5];
    } data;
} XClientMessageEvent;

typedef struct
{
    int           type;           /* of event */
    unsigned long serial;         /* # of last request processed by server */
    Bool          send_event;     /* true if this came from a SendEvent request */
    Display*      display;        /* Display the event was read from */
    Window        window;         /* "event" window it is reported relative to */
    Window        root;           /* root window that the event occurred on */
    Window        subwindow;      /* child window */
    Time          time;           /* milliseconds */
    int           x, y;           /* pointer x, y coordinates in event window */
    int           x_root, y_root; /* coordinates relative to root */
    unsigned int  state;          /* key or button mask */
    unsigned int  button;         /* detail */
    Bool          same_screen;    /* same screen flag */
} XButtonEvent;

typedef struct
{
    int           type;           /* KeyPress or KeyRelease */
    unsigned long serial;         /* # of last request processed by server */
    Bool          send_event;     /* true if this came from a SendEvent request */
    Display*      display;        /* Display the event was read from */
    Window        window;         /* ``event'' window it is reported relative to */
    Window        root;           /* root window that the event occurred on */
    Window        subwindow;      /* child window */
    Time          time;           /* milliseconds */
    int           x, y;           /* pointer x, y coordinates in event window */
    int           x_root, y_root; /* coordinates relative to root */
    unsigned int  state;          /* key or button mask */
    unsigned int  keycode;        /* detail */
    Bool          same_screen;    /* same screen flag */
} XKeyEvent;
typedef XKeyEvent XKeyPressedEvent;
typedef XKeyEvent XKeyReleasedEvent;


typedef union _XEvent
{
    int type; /* must not be changed */
    //XAnyEvent              xany;
    XKeyEvent              xkey;
    XButtonEvent xbutton;
    XMotionEvent xmotion;
    //XCrossingEvent         xcrossing;
    //XFocusChangeEvent      xfocus;
    XExposeEvent xexpose;
    //XGraphicsExposeEvent   xgraphicsexpose;
    //XNoExposeEvent         xnoexpose;
    //XVisibilityEvent       xvisibility;
    //XCreateWindowEvent     xcreatewindow;
    XDestroyWindowEvent xdestroywindow;
    //XUnmapEvent            xunmap;
    //XMapEvent              xmap;
    //XMapRequestEvent       xmaprequest;
    //XReparentEvent         xreparent;
    XConfigureEvent xconfigure;
    //XGravityEvent          xgravity;
    //XResizeRequestEvent    xresizerequest;
    //XConfigureRequestEvent xconfigurerequest;
    //XCirculateEvent        xcirculate;
    //XCirculateRequestEvent xcirculaterequest;
    //XPropertyEvent         xproperty;
    //XSelectionClearEvent   xselectionclear;
    //XSelectionRequestEvent xselectionrequest;
    //XSelectionEvent        xselection;
    //XColormapEvent         xcolormap;
    XClientMessageEvent xclient;
    //XMappingEvent          xmapping;
    //XErrorEvent            xerror;
    //XKeymapEvent           xkeymap;
    //long                   pad[24];
} XEvent;

typedef struct
{
    unsigned char* value;    /* property data */
    Atom           encoding; /* type of property */
    int            format;   /* 8, 16, or 32 */
    unsigned long  nitems;   /* number of items in value */
} XTextProperty;

Window   XDefaultRootWindow(Display*);
void     XNextEvent(Display* display, XEvent* event_return);
Display* XOpenDisplay(char*);
Bool     XPending(Display*);
void     XCloseDisplay(Display* display);
void     XFlush(Display* dpy);

Colormap XCreateColormap(Display* display, int w, XVisualInfo* visual, int alloc);
void     XMapWindow(Display* display, Window w);
int      XUnmapWindow(register Display* dpy, Window w);
Status   XWithdrawWindow(
      Display* dpy,
      Window   w,
      int      screen);

void XClearWindow(Display* display, Window w);
void XDestroyWindow(Display* display, Window w);

#define DefaultScreen(dpy) 0

int XDisplayWidth(Display* dpy, int scr);
int XDisplayHeight(Display* dpy, int scr);


typedef int KeySym;

KeySym XLookupKeysym(XKeyEvent* key_event, int index);

/*
Application Window Properties
https://specifications.freedesktop.org/wm-spec/wm-spec-1.3.html#idm45805407982976

    
_NET_WM_NAME

_NET_WM_VISIBLE_NAME
_NET_WM_ICON_NAME
_NET_WM_VISIBLE_ICON_NAME
_NET_WM_DESKTOP
_NET_WM_WINDOW_TYPE

_NET_WM_STATE
    _NET_WM_STATE_MODAL, ATOM
    _NET_WM_STATE_STICKY, ATOM
    _NET_WM_STATE_MAXIMIZED_VERT, ATOM
    _NET_WM_STATE_MAXIMIZED_HORZ, ATOM
    _NET_WM_STATE_SHADED, ATOM
    _NET_WM_STATE_SKIP_TASKBAR, ATOM
    _NET_WM_STATE_SKIP_PAGER, ATOM
    _NET_WM_STATE_HIDDEN, ATOM
    _NET_WM_STATE_FULLSCREEN, ATOM
    _NET_WM_STATE_ABOVE, ATOM
    _NET_WM_STATE_BELOW, ATOM
    _NET_WM_STATE_DEMANDS_ATTENTION, ATOM

_NET_WM_ALLOWED_ACTIONS
_NET_WM_STRUT
_NET_WM_STRUT_PARTIAL
_NET_WM_ICON_GEOMETRY
_NET_WM_ICON
_NET_WM_PID
_NET_WM_HANDLED_ICONS
_NET_WM_USER_TIME
_NET_FRAME_EXTENTS
*/

Atom XInternAtom(Display*, const char*, Bool);

typedef struct
{
    long flags;         /* marks which fields in this structure are defined */
    int  x, y;          /* obsolete for new window mgrs, but clients */
    int  width, height; /* should set so old wm's don't mess up */
    int  min_width, min_height;
    int  max_width, max_height;
    int  width_inc, height_inc;
    struct
    {
        int x; /* numerator */
        int y; /* denominator */
    } min_aspect, max_aspect;
    int base_width, base_height; /* added by ICCCM version 1 */
    int win_gravity;             /* added by ICCCM version 1 */
} XSizeHints;

int XSetNormalHints(Display*    dpy,
                    Window      w,
                    XSizeHints* hints);

void XSetWMName(Display* display, Window w, XTextProperty* text_prop);

Window XCreateWindow(
    Display*              display,
    Window                parent,
    int                   x,
    int                   y,
    unsigned int          width,
    unsigned int          height,
    unsigned int          border_width,
    int                   depth,
    unsigned int          cla,
    XVisualInfo*          visual,
    unsigned long         valuemask,
    XSetWindowAttributes* attributes);

Status XSendEvent(Display* display,
                  Window   w,
                  Bool     propagate,
                  long     event_mask,
                  XEvent*  event_send);
Status XSetWMProtocols(Display* display,
                       Window   w,
                       Atom*    protocols,
                       int      count);

XVisualInfo* glXChooseVisual(Display*, int, int*);
GLXContext   glXCreateContext(Display*     dpy,
                              XVisualInfo* vis,
                              GLXContext   shareList,
                              Bool         direct);

Bool glXMakeCurrent(Display*    dpy,
                    GLXDrawable drawable,
                    GLXContext  ctx);

void glXSwapBuffers(Display* disp, Window window);

#define XA_PRIMARY ((Atom)1)
#define XA_SECONDARY ((Atom)2)
#define XA_ARC ((Atom)3)
#define XA_ATOM ((Atom)4)
#define XA_BITMAP ((Atom)5)
#define XA_CARDINAL ((Atom)6)
#define XA_COLORMAP ((Atom)7)
#define XA_CURSOR ((Atom)8)
#define XA_CUT_BUFFER0 ((Atom)9)
#define XA_CUT_BUFFER1 ((Atom)10)
#define XA_CUT_BUFFER2 ((Atom)11)
#define XA_CUT_BUFFER3 ((Atom)12)
#define XA_CUT_BUFFER4 ((Atom)13)
#define XA_CUT_BUFFER5 ((Atom)14)
#define XA_CUT_BUFFER6 ((Atom)15)
#define XA_CUT_BUFFER7 ((Atom)16)
#define XA_DRAWABLE ((Atom)17)
#define XA_FONT ((Atom)18)
#define XA_INTEGER ((Atom)19)
#define XA_PIXMAP ((Atom)20)
#define XA_POINT ((Atom)21)
#define XA_RECTANGLE ((Atom)22)
#define XA_RESOURCE_MANAGER ((Atom)23)
#define XA_RGB_COLOR_MAP ((Atom)24)
#define XA_RGB_BEST_MAP ((Atom)25)
#define XA_RGB_BLUE_MAP ((Atom)26)
#define XA_RGB_DEFAULT_MAP ((Atom)27)
#define XA_RGB_GRAY_MAP ((Atom)28)
#define XA_RGB_GREEN_MAP ((Atom)29)
#define XA_RGB_RED_MAP ((Atom)30)
#define XA_STRING ((Atom)31)
#define XA_VISUALID ((Atom)32)
#define XA_WINDOW ((Atom)33)
#define XA_WM_COMMAND ((Atom)34)
#define XA_WM_HINTS ((Atom)35)
#define XA_WM_CLIENT_MACHINE ((Atom)36)
#define XA_WM_ICON_NAME ((Atom)37)
#define XA_WM_ICON_SIZE ((Atom)38)
#define XA_WM_NAME ((Atom)39)
#define XA_WM_NORMAL_HINTS ((Atom)40)
#define XA_WM_SIZE_HINTS ((Atom)41)
#define XA_WM_ZOOM_HINTS ((Atom)42)
#define XA_MIN_SPACE ((Atom)43)
#define XA_NORM_SPACE ((Atom)44)
#define XA_MAX_SPACE ((Atom)45)
#define XA_END_SPACE ((Atom)46)
#define XA_SUPERSCRIPT_X ((Atom)47)
#define XA_SUPERSCRIPT_Y ((Atom)48)
#define XA_SUBSCRIPT_X ((Atom)49)
#define XA_SUBSCRIPT_Y ((Atom)50)
#define XA_UNDERLINE_POSITION ((Atom)51)
#define XA_UNDERLINE_THICKNESS ((Atom)52)
#define XA_STRIKEOUT_ASCENT ((Atom)53)
#define XA_STRIKEOUT_DESCENT ((Atom)54)
#define XA_ITALIC_ANGLE ((Atom)55)
#define XA_X_HEIGHT ((Atom)56)
#define XA_QUAD_WIDTH ((Atom)57)
#define XA_WEIGHT ((Atom)58)
#define XA_POINT_SIZE ((Atom)59)
#define XA_RESOLUTION ((Atom)60)
#define XA_COPYRIGHT ((Atom)61)
#define XA_NOTICE ((Atom)62)
#define XA_FONT_NAME ((Atom)63)
#define XA_FAMILY_NAME ((Atom)64)
#define XA_FULL_NAME ((Atom)65)
#define XA_CAP_HEIGHT ((Atom)66)
#define XA_WM_CLASS ((Atom)67)
#define XA_WM_TRANSIENT_FOR ((Atom)68)
#define XA_LAST_PREDEFINED ((Atom)68)

int usleep(int usec);
#define XK_BackSpace                     0xff08  
#define XK_Tab                           0xff09
#define XK_Linefeed                      0xff0a  
#define XK_Clear                         0xff0b
#define XK_Return                        0xff0d  
#define XK_Pause                         0xff13  
#define XK_Scroll_Lock                   0xff14
#define XK_Sys_Req                       0xff15
#define XK_Escape                        0xff1b
#define XK_Delete                        0xffff  
#define XK_Home                          0xff50
#define XK_Left                          0xff51  
#define XK_Up                            0xff52  
#define XK_Right                         0xff53  
#define XK_Down                          0xff54  
#define XK_Prior                         0xff55  
#define XK_Page_Up                       0xff55
#define XK_Next                          0xff56  
#define XK_Page_Down                     0xff56
#define XK_End                           0xff57  
#define XK_Begin                         0xff58  
#define XK_Select                        0xff60  
#define XK_Print                         0xff61
#define XK_Execute                       0xff62  
#define XK_Insert                        0xff63  
#define XK_Undo                          0xff65
#define XK_Redo                          0xff66  
#define XK_Menu                          0xff67
#define XK_Find                          0xff68  
#define XK_Cancel                        0xff69  
#define XK_Help                          0xff6a  
#define XK_Break                         0xff6b
#define XK_Mode_switch                   0xff7e  
#define XK_script_switch                 0xff7e  
#define XK_Num_Lock                      0xff7f
#define XK_KP_Space                      0xff80  
#define XK_KP_Tab                        0xff89
#define XK_KP_Enter                      0xff8d  
#define XK_KP_F1                         0xff91  
#define XK_KP_F2                         0xff92
#define XK_KP_F3                         0xff93
#define XK_KP_F4                         0xff94
#define XK_KP_Home                       0xff95
#define XK_KP_Left                       0xff96
#define XK_KP_Up                         0xff97
#define XK_KP_Right                      0xff98
#define XK_KP_Down                       0xff99
#define XK_KP_Prior                      0xff9a
#define XK_KP_Page_Up                    0xff9a
#define XK_KP_Next                       0xff9b
#define XK_KP_Page_Down                  0xff9b
#define XK_KP_End                        0xff9c
#define XK_KP_Begin                      0xff9d
#define XK_KP_Insert                     0xff9e
#define XK_KP_Delete                     0xff9f
#define XK_KP_Equal                      0xffbd  
#define XK_KP_Multiply                   0xffaa
#define XK_KP_Add                        0xffab
#define XK_KP_Separator                  0xffac  
#define XK_KP_Subtract                   0xffad
#define XK_KP_Decimal                    0xffae
#define XK_KP_Divide                     0xffaf
#define XK_KP_0                          0xffb0
#define XK_KP_1                          0xffb1
#define XK_KP_2                          0xffb2
#define XK_KP_3                          0xffb3
#define XK_KP_4                          0xffb4
#define XK_KP_5                          0xffb5
#define XK_KP_6                          0xffb6
#define XK_KP_7                          0xffb7
#define XK_KP_8                          0xffb8
#define XK_KP_9                          0xffb9
#define XK_F1                            0xffbe
#define XK_F2                            0xffbf
#define XK_F3                            0xffc0
#define XK_F4                            0xffc1
#define XK_F5                            0xffc2
#define XK_F6                            0xffc3
#define XK_F7                            0xffc4
#define XK_F8                            0xffc5
#define XK_F9                            0xffc6
#define XK_F10                           0xffc7
#define XK_F11                           0xffc8
#define XK_F12                           0xffc9
#define XK_Shift_L                       0xffe1  
#define XK_Shift_R                       0xffe2  
#define XK_Control_L                     0xffe3  
#define XK_Control_R                     0xffe4  
#define XK_Caps_Lock                     0xffe5  
#define XK_Shift_Lock                    0xffe6  
#define XK_Meta_L                        0xffe7  
#define XK_Meta_R                        0xffe8  
#define XK_Alt_L                         0xffe9  
#define XK_Alt_R                         0xffea  
#define XK_Super_L                       0xffeb  
#define XK_Super_R                       0xffec  
#define XK_Hyper_L                       0xffed  
#define XK_Hyper_R                       0xffee  
#define XK_space                         0x0020  
#define XK_exclam                        0x0021  
#define XK_quotedbl                      0x0022  
#define XK_numbersign                    0x0023  
#define XK_dollar                        0x0024  
#define XK_percent                       0x0025  
#define XK_ampersand                     0x0026  
#define XK_apostrophe                    0x0027  
#define XK_quoteright                    0x0027  
#define XK_parenleft                     0x0028  
#define XK_parenright                    0x0029  
#define XK_asterisk                      0x002a  
#define XK_plus                          0x002b  
#define XK_comma                         0x002c  
#define XK_minus                         0x002d  
#define XK_period                        0x002e  
#define XK_slash                         0x002f  
#define XK_0                             0x0030  
#define XK_1                             0x0031  
#define XK_2                             0x0032  
#define XK_3                             0x0033  
#define XK_4                             0x0034  
#define XK_5                             0x0035  
#define XK_6                             0x0036  
#define XK_7                             0x0037  
#define XK_8                             0x0038  
#define XK_9                             0x0039  
#define XK_colon                         0x003a  
#define XK_semicolon                     0x003b  
#define XK_less                          0x003c  
#define XK_equal                         0x003d  
#define XK_greater                       0x003e  
#define XK_question                      0x003f  
#define XK_at                            0x0040  
#define XK_A                             0x0041  
#define XK_B                             0x0042  
#define XK_C                             0x0043  
#define XK_D                             0x0044  
#define XK_E                             0x0045  
#define XK_F                             0x0046  
#define XK_G                             0x0047  
#define XK_H                             0x0048  
#define XK_I                             0x0049  
#define XK_J                             0x004a  
#define XK_K                             0x004b  
#define XK_L                             0x004c  
#define XK_M                             0x004d  
#define XK_N                             0x004e  
#define XK_O                             0x004f  
#define XK_P                             0x0050  
#define XK_Q                             0x0051  
#define XK_R                             0x0052  
#define XK_S                             0x0053  
#define XK_T                             0x0054  
#define XK_U                             0x0055  
#define XK_V                             0x0056  
#define XK_W                             0x0057  
#define XK_X                             0x0058  
#define XK_Y                             0x0059  
#define XK_Z                             0x005a  
#define XK_bracketleft                   0x005b  
#define XK_backslash                     0x005c  
#define XK_bracketright                  0x005d  
#define XK_asciicircum                   0x005e  
#define XK_underscore                    0x005f  
#define XK_grave                         0x0060  
#define XK_quoteleft                     0x0060  
#define XK_a                             0x0061  
#define XK_b                             0x0062  
#define XK_c                             0x0063  
#define XK_d                             0x0064  
#define XK_e                             0x0065  
#define XK_f                             0x0066  
#define XK_g                             0x0067  
#define XK_h                             0x0068  
#define XK_i                             0x0069  
#define XK_j                             0x006a  
#define XK_k                             0x006b  
#define XK_l                             0x006c  
#define XK_m                             0x006d  
#define XK_n                             0x006e  
#define XK_o                             0x006f  
#define XK_p                             0x0070  
#define XK_q                             0x0071  
#define XK_r                             0x0072  
#define XK_s                             0x0073  
#define XK_t                             0x0074  
#define XK_u                             0x0075  
#define XK_v                             0x0076  
#define XK_w                             0x0077  
#define XK_x                             0x0078  
#define XK_y                             0x0079  
#define XK_z                             0x007a  
#define XK_braceleft                     0x007b  
#define XK_bar                           0x007c  
#define XK_braceright                    0x007d  
#define XK_asciitilde                    0x007e  


#endif

#define MessageFormatByte 8
#define MessageFormatShort 16
#define MessageFormatLong 32
#define XNullWindow -1
