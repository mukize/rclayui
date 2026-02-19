#ifndef RCLAYUI_TEXTINPUT_H
#define RCLAYUI_TEXTINPUT_H

#include "clay.h"
#include "raylib.h"
#include <string.h>

typedef struct {
  uint16_t fontSize;
  uint16_t fontId;
  Clay_SizingAxis width;
  Clay_SizingAxis height;
  Clay_Padding padding;
  Clay_CornerRadius cornerRadius;
  uint16_t borderWidth;
  Clay_Color borderColor;
  Clay_Color backgroundColor;
  Clay_Color textColor;
  Clay_TextAlignment textAlignment;
  uint16_t lineSpacing;
} RC_TextInputTheme;

typedef struct {
  Clay_ElementId id;
  int length;
  char *text;
  Clay_Vector2 scrollOverflow;
  bool isDisabled;
} RC_TextInputState;

void rClayTextInput(const Clay_ElementId id, RC_TextInputState *state, RC_TextInputTheme theme);
#endif

#ifdef RCLAYUI_IMPLEMENTATION
void rClayTextInput(const Clay_ElementId id, RC_TextInputState *state, RC_TextInputTheme theme) {

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (Clay_PointerOver(id))
      rc_currentFocusedElementId = id;
    else if (rc_currentFocusedElementId.id == id.id)
      rc_currentFocusedElementId = (Clay_ElementId){0};
  }
  bool focused = rc_currentFocusedElementId.id == id.id;
  Clay_SizingAxis textHeight = CLAY_SIZING_FIT((float)theme.fontSize);

  int textlen = strlen(state->text);

  if (focused) {
    int key = GetCharPressed();
    if (key != 0 && textlen <= (state->length - 1)) {
      state->text[textlen] = (char)key;
      state->text[textlen + 1] = '\0';
    }
    if ((textlen > 0) && IsKeyDown(KEY_BACKSPACE)) {
      state->text[textlen - 1] = '\0';
    }
  }

  Clay_String clayText = (Clay_String){
      .isStaticallyAllocated = false, .length = textlen, .chars = state->text};
  CLAY(id,
       {
           .layout = {.sizing = {.width = theme.width,
                                 .height = CLAY_SIZING_FIT(32)},
                      .padding = theme.padding},
           .backgroundColor = theme.backgroundColor,
           .cornerRadius = theme.cornerRadius,
           .clip = {.horizontal = true, .childOffset = state->scrollOverflow},
           .border =
               {
                   .color = theme.borderColor,
                   .width = CLAY_BORDER_OUTSIDE(theme.borderWidth),
               },
       }) {
    CLAY_TEXT(clayText, CLAY_TEXT_CONFIG({
                            .textColor = theme.textColor,
                            .fontId = theme.fontId,
                            .fontSize = theme.fontSize,
                            .textAlignment = theme.textAlignment,
                        }));

    // TODO: accurately position this cursor
    if (focused) {
      CLAY_AUTO_ID({
          .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                .height = textHeight}},
          .backgroundColor = {0, 0, 0, 0},
      }) {
        CLAY_TEXT(CLAY_STRING("|"), CLAY_TEXT_CONFIG({
                                        .textColor = theme.textColor,
                                        .fontId = theme.fontId,
                                        .fontSize = theme.fontSize,
                                        .textAlignment = theme.textAlignment,
                                    }));
      };
    }
  }
}

#endif
