#pragma bank 2
#include "SpriteAxe.h"
#include "SpritePlayer.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "ZGBMain.h"


UINT8 bank_SPRITE_PLAYER = 2;

const UINT8 anim_idle_d[] = { 1, 0 };
const UINT8 anim_walk_d[] = { 2, 1, 2 };
const UINT8 anim_shot_d[] = { 2, 3, 0 };
const UINT8 anim_idle_l[] = { 1, 4 };
const UINT8 anim_walk_l[] = { 2, 5, 6};
const UINT8 anim_shot_l[] = { 2, 7, 4 };
const UINT8 anim_idle_r[] = { 1, 8 };
const UINT8 anim_walk_r[] = { 2, 9, 10 };
const UINT8 anim_shot_r[] = { 2, 11, 8 };
const UINT8 anim_idle_u[] = { 1, 12 };
const UINT8 anim_walk_u[] = { 2, 13, 14 };
const UINT8 anim_shot_u[] = { 2, 15, 12 };

const UINT8 maxAxes = 3;
const UINT8 axeSpeed = 2;
const UINT8 invTime = 10;


typedef enum {
	PLAYER_STATE_NORMAL,
	PLAYER_STATE_HIT
}PLAYER_STATE;
PLAYER_STATE player_state;


extern UINT8 axes;

INT8 shoot_cooldown = 0;
INT8 dir = 0; // 0= up, 1= right, 2=down, 3 = left

UINT8 axeVx = 0;
UINT8 axeVy = 0;
UINT8 lifes = 3;
UINT8 hitCounter = 0;

void Shoot() {
	//struct Sprite* bullet_sprite = SpriteManagerAdd(SPRITE_AXE, 0, 0);
	axeVx = 0;
	axeVy = 0;
	axes++;

	if (dir == 1)
	{
		axeVx = axeSpeed;
		SetSpriteAnim(THIS, anim_shot_r, 8);
		CreateAxe(THIS->x + 8, THIS->y, axeVx, axeVy);
	}
	else if (dir == 3)
	{
		axeVx = -axeSpeed;
		SetSpriteAnim(THIS, anim_shot_l, 8);
		CreateAxe(THIS->x - 8, THIS->y, axeVx, axeVy);

	}	
	if (dir == 0)
	{
		axeVy = -axeSpeed;
		SetSpriteAnim(THIS, anim_shot_u, 8);
		CreateAxe(THIS->x - 8, THIS->y, axeVx, axeVy);

	}
	else if (dir == 2)
	{
		axeVy = axeSpeed;
		SetSpriteAnim(THIS, anim_shot_d, 8);
		CreateAxe(THIS->x + 8, THIS->y, axeVx, axeVy);
	}
	
	shoot_cooldown = 10;
}

void Hit()
{
	player_state = PLAYER_STATE_HIT;
	hitCounter = maxAxes;
	lifes--;	
}

void CheckCols()
{
	UINT8 i;
	struct Sprite* spr;
	if (player_state != PLAYER_STATE_HIT)
	{
		//Check enemy collision
		SPRITEMANAGER_ITERATE(i, spr)
		{
			if (spr->type == SPRITE_AXE)
			{
				if (CheckCollision(THIS, spr))
				{
					Hit();
				}
			}
		}
	}
}

void Start_SPRITE_PLAYER() 
{
	axes = 0;
	player_state = PLAYER_STATE_NORMAL;
}

void Update_SPRITE_PLAYER() 
{
	if (player_state == PLAYER_STATE_NORMAL)
	{
		if (KEY_PRESSED(J_UP))
		{		
			TranslateSprite(THIS, 0, -1);
			SetSpriteAnim(THIS, anim_walk_u, 8);
			dir = 0;
		}
		if (KEY_PRESSED(J_DOWN))
		{
			TranslateSprite(THIS, 0, 1);
			SetSpriteAnim(THIS, anim_walk_d, 8);
			dir = 2;
		}
		if (KEY_PRESSED(J_LEFT))
		{
			TranslateSprite(THIS, -1, -0);
			SetSpriteAnim(THIS, anim_walk_l, 8);
			dir = 3;
		}
		if (KEY_PRESSED(J_RIGHT))
		{
			TranslateSprite(THIS, 1, 0);
			SetSpriteAnim(THIS, anim_walk_r, 8);
			dir = 1;
		}
		if (keys == 0 && shoot_cooldown == 0)
		{
			if (dir == 0)
			{
				SetSpriteAnim(THIS, anim_idle_u, 6);
			}
			else if (dir == 1)
			{
				SetSpriteAnim(THIS, anim_idle_r, 6);
			}
			else if (dir == 2)
			{
				SetSpriteAnim(THIS, anim_idle_d, 6);
			}
			else
			{
				SetSpriteAnim(THIS, anim_idle_l, 6);
			}
		}

		if (shoot_cooldown) {
			shoot_cooldown -= 1u;
		}
		else if (axes < maxAxes) {
			if (KEY_TICKED(J_B)) 
			{
				Shoot();
			}
		}
	}
	else if (player_state == PLAYER_STATE_HIT)
	{
		hitCounter--;
		if (hitCounter == 0)
		{
			player_state = PLAYER_STATE_NORMAL;
		}
	}

	CheckCols();
}



void Destroy_SPRITE_PLAYER() {
}