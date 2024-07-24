rm -rf "builds/hypr" && cc src/*.c -Wall  -Iinclude -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o "builds/hypr"
