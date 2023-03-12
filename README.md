# cef_hooking_demo
Demo trying to get CEF offscreen rendering for usage in modding OpenGL games (Geometry Dash)

# Building
Just build with cmake. It will download cef build from Spotify CDN. There are two targets. `lotus` and `lotus_sub` which will produce `lotus.dll` and `lotus_sub.exe` which is a subproccess needed by CEF to handle tasks.  
You must move the files from `Release/` and `Resources/` from `vendor/cef_binary_75.1.4+g4210896+chromium-75.0.3770.100_windows32` into the GeometryDash.exe directory (sorry its a mess).
