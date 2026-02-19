#ifndef RCLAYUI_H
#define RCLAYUI_H

#include <stdint.h>
#include "clay.h"
#include "raylib.h"
#include "raymath.h"

#define RCLAY_ON_HOVER(t, f) (Clay_Hovered() ? (t) : (f))
#define RCLAY_ON_PRESS(t, f)                                                   \
  ((Clay_Hovered() && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) ? (t) : (f))

#define RCLAY_PADDING_XY(x, y) (Clay_Padding){x, x, y, y}

#define CLAY_TO_RAYLIB_COLOR(color)                                            \
  ((Color){(unsigned char)color.r, (unsigned char)color.g,                     \
           (unsigned char)color.b, (unsigned char)color.a})

#define RAYLIB_TO_CLAY_COLOR(c) ((Clay_Color){(c).r, (c).g, (c).b, (c).a})
#define CTR(c) CLAY_TO_RAYLIB_COLOR(c)
#define RTC(c) RAYLIB_TO_CLAY_COLOR(c)


#endif


#ifdef RCLAYUI_IMPLEMENTATION

Clay_ElementId rc_currentFocusedElementId = {0};

#endif
