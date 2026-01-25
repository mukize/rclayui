
#include "clay.h"
#include "raylib.h"
#include <string.h>

#ifndef RCLAY_ON_HOVER
#define RCLAY_ON_HOVER(t, f) (Clay_Hovered() ? (t) : (f))
#endif

#ifndef RCLAY_ON_PRESS
#define RCLAY_ON_PRESS(t, f)                                                   \
  ((Clay_Hovered() && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) ? (t) : (f))
#endif

typedef struct {
  // sizing
  Clay_SizingAxis width;
  Clay_SizingAxis height;
  uint16_t paddingX;
  uint16_t paddingY;
  uint16_t cornerRadius;
  // border
  Clay_Color borderColor;
  uint16_t borderWidth;
  // cursor
  Clay_Color cursorColor;
  // background
  Clay_Color backgroundColor;
  Clay_Color backgroundColorHover;
  Clay_Color backgroundColorPressed;
  Clay_Color backgroundColorDisabled;
  // text
  Clay_Color textColor;
  Clay_TextAlignment textAlignment;
  Font font;
  uint16_t fontId;
  uint16_t lineSpacing;
  uint16_t fontSize;
} RClayTextInputTheme;

typedef struct {
} RClayTextInputState;

RClayTextInputTheme rClayTextInputTheme = (RClayTextInputTheme){0};
Clay_ElementId rClayCurrentFocusedTextInputId = (Clay_ElementId){0};

void rClayTextInputInitialize(void) {
  rClayTextInputTheme = (RClayTextInputTheme){
      .cursorColor = {0, 0, 0, 255},
      .borderColor = {0, 0, 0, 255},
      .backgroundColor = {0, 0, 0, 50},
      .backgroundColorHover = {50, 50, 50, 255},
      .backgroundColorPressed = {100, 100, 100, 255},
      .backgroundColorDisabled = {150, 150, 150, 255},
      .textColor = {0, 0, 0, 255},
      .fontId = 0,
      .lineSpacing = 1,
      .font = GetFontDefault(),
      .fontSize = 16,
      .textAlignment = CLAY_TEXT_ALIGN_CENTER,
      .paddingX = 16,
      .paddingY = 8,
      .cornerRadius = 4,
      .width = CLAY_SIZING_GROW(0),
      .height = CLAY_SIZING_FIT(0),
      .borderWidth = 1,
  };
}

void rClayTextInput(const Clay_ElementId id, int length, char text[]) {
  static double lastTime = 0;

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (Clay_PointerOver(id))
      rClayCurrentFocusedTextInputId = id;
    else if (rClayCurrentFocusedTextInputId.id == id.id)
      rClayCurrentFocusedTextInputId = (Clay_ElementId){0};
  }
  bool focused = rClayCurrentFocusedTextInputId.id == id.id;
  Clay_SizingAxis textHeight = CLAY_SIZING_FIT(rClayTextInputTheme.fontSize);

  int textlen = strlen(text);

  if (focused) {
    int key = GetCharPressed();
    if (key != 0 && textlen <= (length - 1)) {
      text[textlen] = (char)key;
      text[textlen + 1] = '\0';
    }
    if ((textlen > 0) && IsKeyDown(KEY_BACKSPACE)) {
      text[textlen - 1] = '\0';
      lastTime = GetTime();
    }
  }

  Clay_String clayText = (Clay_String){
      .isStaticallyAllocated = false, .length = textlen, .chars = text};
  CLAY(id,
       {.layout = {.padding = {.top = rClayTextInputTheme.paddingY,
                               .bottom = rClayTextInputTheme.paddingY,
                               .left = rClayTextInputTheme.paddingX,
                               .right = rClayTextInputTheme.paddingX},
                   .sizing =
                       {
                           .width = rClayTextInputTheme.width,
                           .height = CLAY_SIZING_FIT(32),
                       }},
        .backgroundColor = rClayTextInputTheme.backgroundColor,
        .border =
            {
                .color = rClayTextInputTheme.borderColor,
                .width = CLAY_BORDER_OUTSIDE(rClayTextInputTheme.borderWidth),
            },
        // .clip = {.vertical = true},
        .cornerRadius = CLAY_CORNER_RADIUS(rClayTextInputTheme.cornerRadius)}) {
    CLAY_TEXT(clayText, CLAY_TEXT_CONFIG({
                            .fontId = rClayTextInputTheme.fontId,
                            .fontSize = rClayTextInputTheme.fontSize,
                            .textAlignment = rClayTextInputTheme.textAlignment,
                            .textColor = rClayTextInputTheme.textColor,
                        }));

    // TODO: accurately position this cursor
    if (focused) {
      CLAY_AUTO_ID({
          .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                .height = textHeight}},
          .backgroundColor = {0, 0, 0, 0},
      }) {
        CLAY_TEXT(CLAY_STRING("|"),
                  CLAY_TEXT_CONFIG({
                      .fontId = rClayTextInputTheme.fontId,
                      .fontSize = rClayTextInputTheme.fontSize,
                      .textAlignment = rClayTextInputTheme.textAlignment,
                      .textColor = rClayTextInputTheme.textColor,
                  }));
      };
    }
  }
}
