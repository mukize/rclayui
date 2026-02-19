#include "../src/rclayui.h"
#include "../src/rclayui_button.h"
#include "../src/rclayui_textinput.h"
#include "raylib.h"

Clay_Color rcColorPrimary = {138, 173, 244, 255};
Clay_Color rcColorSecondary = {183, 189, 248, 255};
Clay_Color rcColorSuccess = {166, 218, 149, 255};
Clay_Color rcColorWarning = {238, 212, 159, 255};
Clay_Color rcColorError = {237, 135, 150, 255};
Clay_Color rcColorText = {202, 211, 245, 255};
Clay_Color rcColorSubText = {184, 192, 224, 255};
Clay_Color rcColorTextMuted = {165, 173, 203, 255};
Clay_Color rcColorBase = {36, 39, 58, 255};
Clay_Color rcColorMantle = {30, 32, 48, 255};
Clay_Color rcColorCrust = {24, 25, 38, 255};

static Clay_Color ClayColorBrightness(Clay_Color color, float brightness) {
  return RTC(ColorBrightness(CTR(color), brightness));
}

bool myButton(Clay_ElementId i, RC_ButtonState s) {
  return rcButton(
      i, s,
      (RC_ButtonTheme){
          .backgroundColor = rcColorPrimary,
          .backgroundColorHover = ClayColorBrightness(rcColorPrimary, .2f),
          .backgroundColorPressed = ClayColorBrightness(rcColorPrimary, .3f),
          .backgroundColorDisabled = ClayColorBrightness(rcColorPrimary, -.6f),
          .textColor = rcColorBase,
          .font = GetFontDefault(),
          .fontClayId = 0,
          .fontSize = 16,
          .padding = RCLAY_PADDING_XY(16, 8),
          .cornerRadius = 8,
      });
}

// void myTextInput(Clay_ElementId i, RC_ButtonState s) {
//   return rcTextInput(i, s,
//                      (RC_TextInputTheme){
//                          .cursorColor = {0, 0, 0, 255},
//                          .borderColor = {0, 0, 0, 255},
//                          .backgroundColor = {0, 0, 0, 50},
//                          .backgroundColorHover = {50, 50, 50, 255},
//                          .backgroundColorPressed = {100, 100, 100, 255},
//                          .backgroundColorDisabled = {150, 150, 150, 255},
//                          .textColor = {0, 0, 0, 255},
//                          .fontId = 0,
//                          .lineSpacing = 1,
//                          .font = GetFontDefault(),
//                          .fontSize = 16,
//                          .textAlignment = CLAY_TEXT_ALIGN_CENTER,
//                          .paddingX = 16,
//                          .paddingY = 8,
//                          .cornerRadius = 4,
//                          .width = CLAY_SIZING_GROW(0),
//                          .height = CLAY_SIZING_FIT(0),
//                          .borderWidth = 1,
//                      });
// }
