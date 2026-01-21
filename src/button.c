#include "clay.h"
#include "raylib.h"

#define RCLAY_ON_HOVER(t, f) (Clay_Hovered() ? (t) : (f))

#define RCLAY_ON_PRESS(t, f)                                                   \
  ((Clay_Hovered() && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) ? (t) : (f))

typedef struct {
  Clay_Color backgroundColor;
  Clay_Color textColor;
  Clay_Color backgroundColorHover;
  Clay_Color backgroundColorPressed;
  Clay_Color backgroundColorDisabled;
  uint16_t fontId;
  uint16_t fontSize;
  Clay_TextAlignment textAlignment;
} RClayButtonTheme;

const RClayButtonTheme RCLAY_DEFAULT_BUTTON_THEME = {
    .backgroundColor = {0, 0, 0, 255},
    .textColor = {255, 255, 255, 255},
    .backgroundColorHover = {50, 50, 50, 255},
    .backgroundColorPressed = {100, 100, 100, 255},
    .backgroundColorDisabled = {150, 150, 150, 255},
    //
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
};

RClayButtonTheme rClayButtonTheme = RCLAY_DEFAULT_BUTTON_THEME;

typedef struct {
  bool isDisabled;
} RClayButtonState;

RClayButtonState RCLAY_DEFAULT_BUTTON_STATE = {
    .isDisabled = false,
};

// Button Component - returns true if the button was clicked
bool rClayButton(Clay_ElementId id, Clay_String content,
                 RClayButtonState state) {

  CLAY(id,
       {.layout = {.padding = {.top = 8, .bottom = 8, .left = 16, .right = 16}},
        .backgroundColor =
            state.isDisabled
                ? rClayButtonTheme.backgroundColorDisabled
                : RCLAY_ON_HOVER(
                      RCLAY_ON_PRESS(rClayButtonTheme.backgroundColorPressed,
                                     rClayButtonTheme.backgroundColorHover),
                      rClayButtonTheme.backgroundColor),
        .cornerRadius = CLAY_CORNER_RADIUS(8)

       }) {
    if (!state.isDisabled && Clay_Hovered())
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    CLAY_TEXT(content, CLAY_TEXT_CONFIG({
                           .fontId = rClayButtonTheme.fontId,
                           .fontSize = rClayButtonTheme.fontSize,
                           .textAlignment = rClayButtonTheme.textAlignment,
                           .textColor = rClayButtonTheme.textColor,
                       }));
  }

  if (state.isDisabled)
    return false;

  return Clay_PointerOver(id) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}
