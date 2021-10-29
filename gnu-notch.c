#include <assert.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xfixes.h>

#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

#include <glib/gprintf.h>
#include <librsvg/rsvg.h>

#include <termios.h>
#include <stdbool.h>
#include <unistd.h>

#define NOTCH_LIGHT_ON "<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 543 94'> <defs> <radialGradient id='radial-gradient' cx='424' cy='452.15' r='11.56' gradientTransform='matrix(1 0 0 1.08 -90 -462.32)' gradientUnits='userSpaceOnUse'> <stop offset='0' stop-color='#00ff34'/> <stop offset='.2' stop-color='#00fc33' stop-opacity='.99'/> <stop offset='.34' stop-color='#00f332' stop-opacity='.95'/> <stop offset='.45' stop-color='#00e42f' stop-opacity='.9'/> <stop offset='.55' stop-color='#00cf2a' stop-opacity='.81'/> <stop offset='.65' stop-color='#00b325' stop-opacity='.7'/> <stop offset='.74' stop-color='#00911e' stop-opacity='.57'/> <stop offset='.83' stop-color='#006915' stop-opacity='.41'/> <stop offset='.91' stop-color='#003a0c' stop-opacity='.23'/> <stop offset='.99' stop-color='#000601' stop-opacity='.02'/> <stop offset='1' stop-opacity='0'/> </radialGradient> <radialGradient id='radial-gradient-2' cx='271.25' cy='27.25' r='20.75' gradientUnits='userSpaceOnUse'> <stop offset='0' stop-color='#1d1d1d'/> <stop offset='.62' stop-color='#1d1d1d' stop-opacity='.94'/> <stop offset='.84' stop-color='#1d1d1d' stop-opacity='.7'/> <stop offset='1' stop-color='#1d1d1d' stop-opacity='.3'/> </radialGradient> <radialGradient id='radial-gradient-3' cx='271.5' cy='27.5' r='6.5' gradientUnits='userSpaceOnUse'> <stop offset='0' stop-color='#101f25'/> <stop offset='.55' stop-color='#0f1d23' stop-opacity='.95'/> <stop offset='.75' stop-color='#0c181c' stop-opacity='.77'/> <stop offset='.89' stop-color='#070e11' stop-opacity='.45'/> <stop offset='1' stop-opacity='0'/> </radialGradient> <radialGradient id='radial-gradient-4' cx='361.11' cy='452.15' r='3.02' gradientTransform='matrix(1.13 0 0 .67 -135.75 -276.93)' gradientUnits='userSpaceOnUse'> <stop offset='0' stop-color='#c1c4de' stop-opacity='.5'/> <stop offset='.21' stop-color='#bbbed7' stop-opacity='.48'/> <stop offset='.4' stop-color='#a8abc1' stop-opacity='.44'/> <stop offset='.57' stop-color='#898b9d' stop-opacity='.35'/> <stop offset='.75' stop-color='#5c5e6a' stop-opacity='.24'/> <stop offset='.91' stop-color='#242429' stop-opacity='.09'/> <stop offset='1' stop-opacity='0'/> </radialGradient> <radialGradient id='radial-gradient-5' cx='362' cy='455.75' r='3.02' gradientTransform='matrix(1.13 0 0 .8 -135.75 -335.6)' gradientUnits='userSpaceOnUse'> <stop offset='0' stop-color='#c1c4de' stop-opacity='.5'/> <stop offset='.16' stop-color='#b1b4cc' stop-opacity='.46'/> <stop offset='.42' stop-color='#86889a' stop-opacity='.35'/> <stop offset='.74' stop-color='#40414a' stop-opacity='.17'/> <stop offset='1' stop-opacity='0'/> </radialGradient> <style> .cls-1{fill:none;stroke:#000;stroke-miterlimit:10} </style> </defs> <g id='Layer_2' data-name='Layer 2'> <rect x='.5' y='.5' width='542' height='93' rx='30.24' ry='30.24'/> <path d='M602.26 431A29.77 29.77 0 0 1 632 460.74v32.52A29.77 29.77 0 0 1 602.26 523H120.74A29.77 29.77 0 0 1 91 493.26v-32.52A29.77 29.77 0 0 1 120.74 431h481.52m0-1H120.74A30.74 30.74 0 0 0 90 460.74v32.52A30.74 30.74 0 0 0 120.74 524h481.52A30.74 30.74 0 0 0 633 493.26v-32.52A30.74 30.74 0 0 0 602.26 430Z' transform='translate(-90 -430)'/> <path d='M.5.5h542v34H.5z'/> <path d='M632 431v33H91v-33h541m1-1H90v35h543v-35Z' transform='translate(-90 -430)'/> </g> <circle cx='334' cy='26' r='12' style='fill:url(#radial-gradient)' id='Layer_5' data-name='Layer 5'/> <circle cx='271.25' cy='27.25' r='20.75' style='fill:url(#radial-gradient-2)' id='Layer_4' data-name='Layer 4'/> <circle cx='271.5' cy='27.5' r='6.5' style='fill:url(#radial-gradient-3)' id='Layer_6' data-name='Layer 6'/> <g id='Layer_7' data-name='Layer 7'> <ellipse cx='270.5' cy='24.5' rx='4.5' ry='2.5' style='fill:url(#radial-gradient-4);opacity:.2'/> <ellipse cx='271.5' cy='29' rx='4.5' ry='3' style='fill:url(#radial-gradient-5);opacity:.2'/> </g></svg>"
#define NOTCH_LIGHT_OFF "<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' viewBox='0 0 543 94'><defs><style>.cls-1{fill:none;stroke:#000;stroke-miterlimit:10;}.cls-2{fill:url(#radial-gradient);}.cls-3{fill:url(#radial-gradient-2);}.cls-4,.cls-5{opacity:0.2;}.cls-4{fill:url(#radial-gradient-3);}.cls-5{fill:url(#radial-gradient-4);}</style><radialGradient id='radial-gradient' cx='271.25' cy='27.25' r='20.75' gradientUnits='userSpaceOnUse'><stop offset='0' stop-color='#1d1d1d'/><stop offset='0.62' stop-color='#1d1d1d' stop-opacity='0.94'/><stop offset='0.84' stop-color='#1d1d1d' stop-opacity='0.7'/><stop offset='1' stop-color='#1d1d1d' stop-opacity='0.3'/></radialGradient><radialGradient id='radial-gradient-2' cx='271.5' cy='27.5' r='6.5' gradientUnits='userSpaceOnUse'><stop offset='0' stop-color='#101f25'/><stop offset='0.55' stop-color='#0f1d23' stop-opacity='0.95'/><stop offset='0.75' stop-color='#0c181c' stop-opacity='0.77'/><stop offset='0.89' stop-color='#070e11' stop-opacity='0.45'/><stop offset='1' stop-opacity='0'/></radialGradient><radialGradient id='radial-gradient-3' cx='361.11' cy='452.15' r='3.02' gradientTransform='translate(-135.75 -276.93) scale(1.13 0.67)' gradientUnits='userSpaceOnUse'><stop offset='0' stop-color='#c1c4de' stop-opacity='0.5'/><stop offset='0.21' stop-color='#bbbed7' stop-opacity='0.48'/><stop offset='0.4' stop-color='#a8abc1' stop-opacity='0.44'/><stop offset='0.57' stop-color='#898b9d' stop-opacity='0.35'/><stop offset='0.75' stop-color='#5c5e6a' stop-opacity='0.24'/><stop offset='0.91' stop-color='#242429' stop-opacity='0.09'/><stop offset='1' stop-opacity='0'/></radialGradient><radialGradient id='radial-gradient-4' cx='362' cy='455.75' r='3.02' gradientTransform='translate(-135.75 -335.6) scale(1.13 0.8)' gradientUnits='userSpaceOnUse'><stop offset='0' stop-color='#c1c4de' stop-opacity='0.5'/><stop offset='0.16' stop-color='#b1b4cc' stop-opacity='0.46'/><stop offset='0.42' stop-color='#86889a' stop-opacity='0.35'/><stop offset='0.74' stop-color='#40414a' stop-opacity='0.17'/><stop offset='1' stop-opacity='0'/></radialGradient></defs><title>gnu-notch-light-off</title><g id='Layer_2' data-name='Layer 2'><rect x='0.5' y='0.5' width='542' height='93' rx='30.24' ry='30.24'/><path d='M602.26,431A29.77,29.77,0,0,1,632,460.74v32.52A29.77,29.77,0,0,1,602.26,523H120.74A29.77,29.77,0,0,1,91,493.26V460.74A29.77,29.77,0,0,1,120.74,431H602.26m0-1H120.74A30.74,30.74,0,0,0,90,460.74v32.52A30.74,30.74,0,0,0,120.74,524H602.26A30.74,30.74,0,0,0,633,493.26V460.74A30.74,30.74,0,0,0,602.26,430Z' transform='translate(-90 -430)'/><rect x='0.5' y='0.5' width='542' height='34'/><path d='M632,431v33H91V431H632m1-1H90v35H633V430Z' transform='translate(-90 -430)'/><path class='cls-1' d='M741.5,464.5' transform='translate(-90 -430)'/><path class='cls-1' d='M711.5,464.5' transform='translate(-90 -430)'/><path class='cls-1' d='M741.5,485.5' transform='translate(-90 -430)'/></g><g id='Layer_4' data-name='Layer 4'><circle class='cls-2' cx='271.25' cy='27.25' r='20.75'/></g><g id='Layer_6' data-name='Layer 6'><circle class='cls-3' cx='271.5' cy='27.5' r='6.5'/></g><g id='Layer_7' data-name='Layer 7'><ellipse class='cls-4' cx='270.5' cy='24.5' rx='4.5' ry='2.5'/><ellipse class='cls-5' cx='271.5' cy='29' rx='4.5' ry='3'/></g></svg>"
typedef struct
{
    float ratio;
    int light;
    int screen_widths[64];
    int screens_number;

} Arguments;

void handle_arguments(int argc, char **argv, Arguments *arguments)
{
    arguments->screens_number = 0;
    arguments->ratio = 0.5;
    arguments->light = 0;
    for (int i = 1; i < argc; i++)
    {
        if (i + 1 < argc)
        {
            if (strcmp(argv[i], "-l") == 0)
            {
                arguments->light = atof(argv[i + 1]);
            }
            else if (strcmp(argv[i], "-r") == 0)
            {
                arguments->ratio = atof(argv[i + 1]);
            }
            else if (strcmp(argv[i], "-w") == 0)
            {
                arguments->screen_widths[arguments->screens_number] = atoi(argv[i + 1]);
                arguments->screens_number += 1;
            }
        }
    }
}

void wait_for_key()
{
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void hide_cursor(Display *display, Window window)
{
    Cursor invisibleCursor;
    Pixmap bitmapNoData;
    XColor black;
    static char noData[] = {0, 0, 0, 0, 0, 0, 0, 0};
    black.red = black.green = black.blue = 0;

    bitmapNoData = XCreateBitmapFromData(display, window, noData, 8, 8);
    invisibleCursor = XCreatePixmapCursor(display, bitmapNoData, bitmapNoData,
                                          &black, &black, 0, 0);
    XDefineCursor(display, window, invisibleCursor);
    XFreeCursor(display, invisibleCursor);
    XFreePixmap(display, bitmapNoData);
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Usage: gnu-notch -l [light on (0/1)] -w [screen width] (-w [screen width]) -r [ratio for notch size]\n");
        exit(EXIT_FAILURE);
    }
    Arguments arguments;
    handle_arguments(argc, argv, &arguments);

    if (arguments.screens_number == 0) {
        printf("You must specify at least one screen width with `-w` flag.");
        exit(EXIT_FAILURE);
    }

    Display *disp = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(disp);

    XSetWindowAttributes attrs;
    attrs.override_redirect = true;

    XVisualInfo vinfo;
    if (!XMatchVisualInfo(disp, DefaultScreen(disp), 32, TrueColor, &vinfo))
    {
        printf("No visual found supporting 32 bit color, terminating\n");
        exit(EXIT_FAILURE);
    }

    attrs.colormap = XCreateColormap(disp, root, vinfo.visual, AllocNone);
    attrs.background_pixel = 0;
    attrs.border_pixel = 0;

    GError *pError = NULL;
    RsvgDimensionData dimensions;
    RsvgHandle *handle;
    //handle = rsvg_handle_new_from_file("gnu-notch-light-on.svg", &pError);

    if (arguments.light)
        handle = rsvg_handle_new_from_data(NOTCH_LIGHT_ON, sizeof(NOTCH_LIGHT_ON), &pError);
    else
        handle = rsvg_handle_new_from_data(NOTCH_LIGHT_OFF, sizeof(NOTCH_LIGHT_OFF), &pError);

    rsvg_handle_get_dimensions(handle, &dimensions);
    RsvgRectangle viewport;
    viewport.height = arguments.ratio * dimensions.height;
    viewport.width = arguments.ratio * dimensions.width;
    viewport.x = 0;
    viewport.y = 0;

    cairo_surface_t *surf;
    cairo_t *cr;
    Window overlay;

    int offset = 0;
    for (int i = 0; i < arguments.screens_number; i++)
    {
        int screen_width = arguments.screen_widths[i];
        if (viewport.width >= screen_width) {
            printf("Your notch is too big, even Apple would think so!\n");
            exit(EXIT_FAILURE);
        }

        overlay = XCreateWindow(
            disp, root,
            offset + screen_width / 2 - viewport.width / 2, 0, viewport.width, viewport.height, 0,
            vinfo.depth, InputOutput,
            vinfo.visual,
            CWOverrideRedirect | CWColormap | CWBackPixel | CWBorderPixel, &attrs);
        XMapWindow(disp, overlay);
        hide_cursor(disp, overlay);

        surf = cairo_xlib_surface_create(disp, overlay,
                                         vinfo.visual,
                                         viewport.width, viewport.height);
        cr = cairo_create(surf);

        rsvg_handle_render_document(handle, cr, &viewport, &pError);
        cairo_fill(cr);
        XFlush(disp);
        offset += screen_width;
    }

    wait_for_key();

    cairo_destroy(cr);
    cairo_surface_destroy(surf);

    XUnmapWindow(disp, overlay);
    XCloseDisplay(disp);
    return 0;
}