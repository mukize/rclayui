#ifndef RCLAYUI_BUTTON_H
#define RCLAYUI_BUTTON_H

typedef struct {
  Font font;
  uint16_t fontClayId;
  uint16_t fontSize;
  Clay_Color textColor;
  Clay_Color backgroundColor;
  Clay_Color backgroundColorDisabled;
  Clay_Color backgroundColorPressed;
  Clay_Color backgroundColorHover;
  Clay_Padding padding;
  float cornerRadius;
} RC_ButtonTheme;

typedef struct {
  Clay_String label;
  bool isDisabled;
} RC_ButtonState;

bool rcButton(Clay_ElementId id, RC_ButtonState state, RC_ButtonTheme theme);
#endif

#ifdef RCLAYUI_IMPLEMENTATION
bool rcButton(Clay_ElementId id, RC_ButtonState state, RC_ButtonTheme theme) {
  CLAY(id, {.layout = {.padding = theme.padding},
            .backgroundColor =
                state.isDisabled
                    ? theme.backgroundColorDisabled
                    : RCLAY_ON_HOVER(
                          RCLAY_ON_PRESS(theme.backgroundColorPressed,
                                         theme.backgroundColorHover),
                          theme.backgroundColor),
            .cornerRadius = CLAY_CORNER_RADIUS(theme.cornerRadius)

           }) {
    if (!state.isDisabled && Clay_Hovered())
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    CLAY_TEXT(state.label, CLAY_TEXT_CONFIG({
                               .textColor = theme.textColor,
                               .fontId = theme.fontClayId,
                               .fontSize = theme.fontSize,
                               .textAlignment = CLAY_TEXT_ALIGN_CENTER,
                           }));
  }

  if (state.isDisabled)
    return false;
  else
    return Clay_PointerOver(id) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}
#endif
