{
  stdenv,
  raylib,
  fetchFromGitHub,
}:
stdenv.mkDerivation {
  name = "rclayui-components";
  version = "0.1.0";
  src = ./.;
  buildInputs = [
    (
      (raylib.overrideAttrs (_: {
        version = "unstable-2025-01-18";
        src = fetchFromGitHub {
          owner = "raysan5";
          repo = "raylib";
          rev = "a8c75f2bc537b65c6b6621819a1445c473ec6f83";
          sha256 = "sha256-HidbA+qY7nAiCgIsjihu9QdlF1LiLKlhSeIu4gqGtXU=";
        };
      })).override
      { platform = "SDL"; }
    )
  ];
  CFLAGS = [
    ""
    "-Wall"
    "-Wextra"
  ];

  buildPhase = ''gcc debug/debug.c $CFLAGS -o rclayui-components $LDFLAGS -Idebug -lraylib -lm '';
  installPhase = ''
    install -D -m 755 rclayui-components $out/bin/rclayui-components
  '';
}
