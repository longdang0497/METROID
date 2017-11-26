#pragma once

#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define SPRITE_PER_ROW 1
#define SAMUS_SPEED 0.3f

#define BACKGROUND_FILE L"map_demo.png"
#define METROID_EFFECT L"metroid_explode.png"
#define SAMUS_SPRITES_PATH L"sprite_sheet_samus.png"
#define ENEMIES_SPRITES_PATH L"Enemies_metroid.png"

#define APPEARING L"Samus_movement\\appearing.txt"

#define JUMP_LEFT L"Samus_movement\\jump_left.txt"
#define JUMP_RIGHT L"Samus_movement\\jump_right.txt"

#define RUN_SHOOTING_LEFT L"Samus_movement\\RUN_SHOOTING_LEFT.txt"
#define RUN_SHOOTING_RIGHT L"Samus_movement\\RUN_SHOOTING_RIGHT.txt"
#define RUN_AIM_UP_LEFT L"Samus_movement\\RUN_AIM_UP_LEFT.txt"
#define RUN_AIM_UP_RIGHT L"Samus_movement\\RUN_AIM_UP_RIGHT.txt"

#define IDLE_AIM_UP_LEFT L"Samus_movement\\IDLE_AIM_UP_LEFT.txt"
#define IDLE_AIM_UP_RIGHT L"Samus_movement\\IDLE_AIM_UP_RIGHT.txt"

#define RUNNING_LEFT L"Samus_movement\\running_left.txt"
#define RUNNING_RIGHT L"Samus_movement\\running_right.txt"

#define STANDING_LEFT L"Samus_movement\\standing_left.txt"
#define STANDING_RIGHT L"Samus_movement\\standing_right.txt"

#define APPEARING_WIDTH 16
#define APPEARING_HEIGHT 32
#define RUNNING_WIDTH 18
#define RUNNING_HEIGHT 32
#define JUMP_WIDTH 18
#define JUMP_HEIGHT 25
#define RUN_SHOOTING_WIDTH 25
#define RUN_SHOOTING_HEIGHT 31
#define RUN_AIM_UP_WIDTH 19
#define RUN_AIM_UP_HEIGHT 38
#define IDLE_AIM_UP_WIDTH 14
#define IDLE_AIM_UP_HEIGHT 38
#define STANDING_WIDTH 21
#define STANDING_HEIGHT 32

#define APPEARING_COUNT 5
#define RUNNING_COUNT 3
#define JUMP_COUNT 1
#define RUN_SHOOTING_COUNT 3
#define RUN_AIM_UP_COUNT 3
#define IDLE_AIM_UP_COUNT 1
#define STANDING_COUNT 1

#define BAT_MOVEMENT L"Enemies\\Bat.txt"
#define BAT_WIDTH 18
#define BAT_HEIGHT 26
#define BAT_COUNT 3

#define SPIDER_SPEED 0.05f
#define SPIDER_MOVEMENT L"Enemies\\Spider_Bug.txt"
#define SPIDER_WIDTH 18
#define SPIDER_HEIGHT 16

#define SPIDER_WALL_RIGHT_MOVEMENT L"Enemies\\Spider_Bug_LEFT.txt"
#define SPIDER_WALL_LEFT_MOVEMENT L"Enemies\\Spider_Bug_RIGHT.txt"
#define SPIDER_WALL_WIDTH 16
#define SPIDER_WALL_HEIGHT 18
#define SPIDER_COUNT 2

#define MAX_BULLETS 100
#define BULLET_SPEED 4.0f
#define BULLET L"bullet.txt"
#define BULLET_WIDTH 4
#define BULLET_HEIGHT 5
#define BULLET_COUNT 1

#define GROUND_ROCK L"brick.png"

#define GROUND_Y 95
#define ANIMATE_RATE 25
#define JUMP_VELOCITY_BOOST 2.5f
#define FALLDOWN_VELOCITY_DECREASE 0.5f

#define VIEW_PORT_Y  600

enum ObjectType
{
	typeSIMON,
	typeBAT,
	typeSpiderBug,
	typeOBJECT
};