#pragma once

#include <d3d9.h>
#include <d3dx9.h>
using namespace std;
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEYBOARD_BUFFER_SIZE	1024
#define NODE_FACTOR 8
#define QUADTREE_FILE "Quadtree\\map(update)quadtree.txt";

//================ SCREEN RESOLUTION ================
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12
//================ END RESOLUTION ====================

#define SPRITE_PER_ROW 1
#define INTRO_SCENE L"Scene_Stuff\\intro.png"
#define BACKGROUND_FILE L"Map\\map_demo.png"
#define METROID_EFFECT L"Enemies\\metroid_explode.png"
#define ENEMIES_SPRITES_PATH L"Enemies\\Enemies_metroid.png"

//================== SAMUS ===================
#define SAMUS_SPRITES_PATH L"Samus_movement\\samus_sprites.png"
#define SAMUS_SPEED 0.15f

#define APPEARING L"Samus_movement\\APPEARING.txt"

#define RUNNING_LEFT L"Samus_movement\\RUNNING_LEFT.txt"
#define RUNNING_RIGHT L"Samus_movement\\RUNNING_RIGHT.txt"

#define JUMP_LEFT L"Samus_movement\\JUMP_LEFT.txt"
#define JUMP_RIGHT L"Samus_movement\\JUMP_RIGHT.txt"

#define RUN_SHOOTING_LEFT L"Samus_movement\\RUN_SHOOTING_LEFT.txt"
#define RUN_SHOOTING_RIGHT L"Samus_movement\\RUN_SHOOTING_RIGHT.txt"

#define RUN_AIM_UP_LEFT L"Samus_movement\\RUN_AIM_UP_LEFT.txt"
#define RUN_AIM_UP_RIGHT L"Samus_movement\\RUN_AIM_UP_RIGHT.txt"

#define IDLE_AIM_UP_LEFT L"Samus_movement\\IDLE_AIM_UP_LEFT.txt"
#define IDLE_AIM_UP_RIGHT L"Samus_movement\\IDLE_AIM_UP_RIGHT.txt"

#define STANDING_LEFT L"Samus_movement\\STANDING_LEFT.txt"
#define STANDING_RIGHT L"Samus_movement\\STANDING_RIGHT.txt"

#define MORPH_BALL_LEFT L"Samus_movement\\MORPH_BALL_LEFT.txt"
#define MORPH_BALL_RIGHT L"Samus_movement\\MORPH_BALL_RIGHT.txt"

#define _LEFT_SOMERSAULT L"Samus_movement\\SOMERSAULT_LEFT.txt"
#define _RIGHT_SOMERSAULT L"Samus_movement\\SOMERSAULT_RIGHT.txt"

#define _LEFT_JUMP_SHOOT L"Samus_movement\\JUMP_SHOOTING_LEFT.txt"
#define _RIGHT_JUMP_SHOOT L"Samus_movement\\JUMP_SHOOTING_RIGHT.txt"

#define _LEFT_JUMP_SHOOT_AIM_UP L"Samus_movement\\JUMP_AIM_UP_LEFT.txt"
#define _RIGHT_JUMP_SHOOT_AIM_UP L"Samus_movement\\JUMP_AIM_UP_RIGHT.txt"

#define APPEARING_WIDTH 32
#define APPEARING_HEIGHT 64
#define RUNNING_WIDTH 36
#define RUNNING_HEIGHT 64
#define JUMP_WIDTH 36
#define JUMP_HEIGHT 50
#define RUN_SHOOTING_WIDTH 50
#define RUN_SHOOTING_HEIGHT 62
#define RUN_AIM_UP_WIDTH 34
#define RUN_AIM_UP_HEIGHT 76
#define IDLE_AIM_UP_WIDTH 28
#define IDLE_AIM_UP_HEIGHT 76
#define STANDING_WIDTH 42
#define STANDING_HEIGHT 64
#define MORPH_BALL_WIDTH 24
#define MORPH_BALL_HEIGHT 26
#define SOMERSAULT_WIDTH 37
#define SOMERSAULT_HEIGHT 46
#define JUMPING_SHOOTING_WIDTH 46
#define JUMPING_SHOOTING_HEIGHT 50
#define JUMP_AIM_UP_WIDTH 36
#define JUMP_AIM_UP_HEIGHT 64

#define APPEARING_COUNT 5
#define RUNNING_COUNT 3
#define JUMP_COUNT 1
#define RUN_SHOOTING_COUNT 3
#define RUN_AIM_UP_COUNT 3
#define IDLE_AIM_UP_COUNT 1
#define STANDING_COUNT 1
#define MORPH_BALL_COUNT 4
#define SPRITE_PER_ROW 1
#define SOMERSAULT_COUNT 4
#define JUMPING_SHOOTING_COUNT 1
#define JUMP_AIM_UP_COUNT 1

#define ANIMATE_RATE 20
#define JUMP_VELOCITY_BOOST 0.05f
#define JUMP_VELOCITY_BOOST_FIRST 1.0f
#define FALLDOWN_VELOCITY_DECREASE 0.3f
//================== END SAMUS ====================

//================= FLYING BAT ===========
#define BAT_MOVEMENT L"Enemies\\Bat.txt"
#define BAT_WIDTH 18
#define BAT_HEIGHT 26
#define BAT_COUNT 3
//================= FLYING BAT ===========

//================= SPIDER BUG ===========
#define SPIDER_SPEED 0.05f
#define SPIDER_MOVEMENT L"Enemies\\Spider_Bug.txt"
#define SPIDER_WIDTH 18
#define SPIDER_HEIGHT 16

#define SPIDER_WALL_RIGHT_MOVEMENT L"Enemies\\Spider_Bug_LEFT.txt"
#define SPIDER_WALL_LEFT_MOVEMENT L"Enemies\\Spider_Bug_RIGHT.txt"
#define SPIDER_WALL_WIDTH 16
#define SPIDER_WALL_HEIGHT 18
#define SPIDER_COUNT 2
//================= END SPIDER BUG ===========

//================= SAMUS BULLET ===========
#define MAX_BULLETS 100
#define BULLET_PATH L"Scene_Stuff\\bullet.png"
#define BULLET_SPEED 4.0f
#define BULLET L"Scene_Stuff\\bullet.txt"
#define BULLET_WIDTH 12
#define BULLET_HEIGHT 14
#define BULLET_COUNT 1
//================= END SAMUS BULLET ===========

//================= TILES BRICK ===========
#define MAP_ROCK L"map_brick_sprite.png"
#define MAP_ROCK_WIDTH 16
#define MAP_ROCK_HEIGHT 16
#define BRICK L"brick.txt"
//================= END TILES BRICK ===========

//================ METROID SAMUS ===============
#define REGISTER_SOUND L"Audio\\Register_Sound.wav"
#define APPEARING_SOUND L"Audio\\Enter_samus.wav"
#define POWER_UP_SOUND L"Audio\\Power_Up.wav"
#define ROOMA_SOUND L"Audio\\Brinstar.wav"
//================= END METROID SOUND ===========

#define GROUND_Y 395
#define VIEW_PORT_Y  600

enum ObjectType
{
	typeSAMUS,
	typeBAT,
	typeSpiderBug
};

//================ FONT ===============
#define FONT L"Scene_Stuff\\font.png"
#define FONT_SIZE 7
//================= END FONT ===========