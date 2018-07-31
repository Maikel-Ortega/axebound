#pragma bank 2
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"

UINT8 bank_SPRITE_ENEMY = 2;

const UINT8 anim_idle[] = { 2, 0, 1 };
const UINT8 anim_death[] = { 5, 2, 3, 4, 5,6 };

struct EnemyCustomData 
{
	fixed tx, ty;
	fixed vx;
	fixed vy;
};

void CheckAxeCols()
{
	UINT8 i;
	struct Sprite* spr;

	//Check enemy collision
	SPRITEMANAGER_ITERATE(i, spr)
	{
		if (spr->type == SPRITE_AXE)
		{
			if (CheckCollision(THIS, spr))
			{
				struct EnemyCustomData* data = (struct EnemyCustomData*)THIS->custom_data;
				SetSpriteAnim(THIS, anim_death, 8);
			}
		}
	}
	
}

INT16 DispLeft(INT16 v, INT8 desp) {
	return v >> desp;
}


void Start_SPRITE_ENEMY() 
{
	SetSpriteAnim(THIS,anim_idle, 8);
}

void Update_SPRITE_ENEMY()
{	
	struct EnemyCustomData* data = (struct EnemyCustomData*)THIS->custom_data;

	if (THIS->anim_data == anim_idle)
	{	
		if (U_LESS_THAN(scroll_target->x, THIS->x)) {
			data->vx.w = data->vx.w - (INT16)(8 << delta_time);
		}
		else {
			data->vx.w = data->vx.w + (INT16)(8 << delta_time);
		}


		if (U_LESS_THAN(scroll_target->y, THIS->y)) {
			data->vy.w = data->vy.w - (INT16)(8 << delta_time);
		}
		else {
			data->vy.w = data->vy.w + (INT16)(8 << delta_time);
		}

		data->tx.w += data->vx.w;
		if (TranslateSprite(THIS, data->tx.b.h, 0)) {
			data->vx.w = -data->vx.w;
			data->vx.w = DispLeft(data->vx.w, 1);
		}
		data->tx.b.h = 0;


		data->ty.w += data->vy.w;
		if (TranslateSprite(THIS, 0, data->ty.b.h)) {
			data->vy.w = -data->vy.w;
			data->vy.w = DispLeft(data->vy.w, 1);
		}
		data->ty.b.h = 0;
		CheckAxeCols();

	}
	else
	{
		if (THIS->current_frame == 4)
		{
			SpriteManagerRemove(THIS_IDX);
		}
	}
}

void Destroy_SPRITE_ENEMY()
{
	
}