#pragma once

#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define SPRITE_PER_ROW 1
#define SAMUS_SPEED 0.2f

#define BACKGROUND_FILE L"map_demo.png"
#define SAMUS_SPRITES_PATH L"samus_sprites.png"
#define ENEMIES_SPRITES_PATH L"Metroid_Enemies.png"

#define APPEARING L"sprites\\appearing.txt"

#define JUMP_LEFT L"sprites\\jump_left.txt"
#define JUMP_RIGHT L"sprites\\jump_right.txt"

#define RUN_SHOOTING_LEFT L"sprites\\RUN_SHOOTING_LEFT.txt"
#define RUN_SHOOTING_RIGHT L"sprites\\RUN_SHOOTING_RIGHT.txt"
#define RUN_AIM_UP_LEFT L"sprites\\RUN_AIM_UP_LEFT.txt"
#define RUN_AIM_UP_RIGHT L"sprites\\RUN_AIM_UP_RIGHT.txt"

#define IDLE_AIM_UP_LEFT L"sprites\\IDLE_AIM_UP_LEFT.txt"
#define IDLE_AIM_UP_RIGHT L"sprites\\IDLE_AIM_UP_RIGHT.txt"

#define RUNNING_LEFT L"running_left.txt"
#define RUNNING_RIGHT L"running_right.txt"

#define STANDING_LEFT L"sprites\\standing_left.txt"
#define STANDING_RIGHT L"sprites\\standing_right.txt"

#define APPEARING_WIDTH 16
#define APPEARING_HEIGHT 32
#define RUNNING_WIDTH 23
#define RUNNING_HEIGHT 38
#define STANDING_WIDTH 21
#define STANDING_HEIGHT 32
#define RUN_SHOOTING_WIDTH 25
#define RUN_SHOOTING_HEIGHT 31
#define RUN_AIM_UP_WIDTH 19
#define RUN_AIM_UP_HEIGHT 38
#define JUMP_WIDTH 18
#define JUMP_HEIGHT 25
#define IDLE_AIM_UP_WIDTH 14
#define IDLE_AIM_UP_HEIGHT 38

#define APPEARING_COUNT 5
#define RUNNING_COUNT 3
#define JUMP_COUNT 1
#define RUN_SHOOTING_COUNT 3
#define RUN_AIM_UP_COUNT 3
#define IDLE_AIM_UP_COUNT 1
#define STANDING_COUNT 1

#define BAT_MOVEMENT L"Bat.txt"
#define BAT_WIDTH 16
#define BAT_HEIGHT 24
#define BAT_COUNT 2

#define SPIDER_MOVEMENT L"Spider_Bug.txt"
#define SPIDER_WIDTH 22
#define SPIDER_HEIGHT 25
#define SPIDER_COUNT 2

#define GROUND_Y 95
#define ANIMATE_RATE 25
#define JUMP_VELOCITY_BOOST 3.0f
#define FALLDOWN_VELOCITY_DECREASE 0.5f

#define VIEW_PORT_Y  600