clear
clear

emcc main.cpp \
  -O3 \
  -std=c++98 \
  -sUSE_SDL=2 \
  -sALLOW_MEMORY_GROWTH=1 \
  -sMODULARIZE=1 \
  -sEXPORT_ES6=1 \
  -sENVIRONMENT=web \
  -o ../../public/sdl_game.js
