#include <stdint.h>
#include <stdio.h>

#include "src/rclayui.c"
#define CLAY_IMPLEMENTATION
#include "src/clay.h"
#include "vendor/clay/renderers/raylib/clay_renderer_raylib.c"

void HandleClayErrors(Clay_ErrorData errorData) {
  printf("%s", errorData.errorText.chars);
}

Clay_RenderCommandArray RenderLayout() {
  Clay_BeginLayout();
  CLAY(CLAY_ID("Body"), {.layout = {.padding = CLAY_PADDING_ALL(100),
                                    .sizing = {
                                        .width = CLAY_SIZING_GROW(),
                                        .height = CLAY_SIZING_GROW(),
                                    }}}) {
    rClayButton(CLAY_ID("Button"), CLAY_STRING("Click me!"));
  }
  return Clay_EndLayout();
}

int main(void) {
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(
      totalMemorySize, malloc(totalMemorySize));
  Clay_Initialize(
      clayMemory,
      (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()},
      (Clay_ErrorHandler){HandleClayErrors, 0});
  Clay_Raylib_Initialize(1024, 768, "Raylib Clay Components",
                         FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE |
                             FLAG_MSAA_4X_HINT);

  Font fonts[1];
  fonts[0] = GetFontDefault();
  SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
  Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

  while (!WindowShouldClose()) {
    Vector2 mousePos = GetMousePosition();
    Clay_SetLayoutDimensions(
        (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()});
    Clay_SetPointerState((Clay_Vector2){mousePos.x, mousePos.y},
                         IsMouseButtonDown(MOUSE_LEFT_BUTTON));

    if (IsKeyPressed(KEY_F1)) {
      Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
    }

    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    Clay_RenderCommandArray commands = RenderLayout();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Clay_Raylib_Render(commands, fonts);
    EndDrawing();
  }

  return 0;
}
