#pragma bank 2
#include "SpriteAxe.h"
#include "SpriteManager.h"
#include "ZGBMain.h"
#include "SpritePlayer.h"

UINT8 bank_SPRITE_AXE = 2;

const UINT8 anim_spin[] = { 2, 0, 1 };
const UINT8 maxHits = 3;

extern UINT8 axes;

struct AxeCustomData	 
{
	INT16 vx;
	INT16 vy;
	UINT8 hits;
};

void CreateAxe(UINT16 x, UINT16 y, INT16 vx, INT16 vy) {
	struct Sprite* spr = SpriteManagerAdd(SPRITE_AXE, x, y);
	struct AxeCustomData* data = (struct AxeCustomData*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;
	data->hits = maxHits;
	//PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

void Start_SPRITE_AXE() 
{
	struct AxeCustomData* data = (struct AxeCustomData*)THIS->custom_data;

	THIS->coll_x = 2u;
	THIS->coll_w = 4u;
	THIS->coll_y = 6u;
	THIS->coll_h = 4u;

	data->vx = 0;
	data->vy = 0;

	SetSpriteAnim(THIS, anim_spin, 16);
}

void Update_SPRITE_AXE()
{		
	struct AxeCustomData* data = (struct AxeCustomData*)THIS->custom_data;

	//THIS->x += (INT16)data->vx << delta_time;
	//THIS->y += (INT16)data->vy << delta_time;	

	
	if (TranslateSprite(THIS, data->vx, 0))
	{
		data->vx = -data->vx;		
		data->hits = data->hits -1;
	}

	if(TranslateSprite(THIS, 0, data->vy)) 
	{
		data->vy = -data->vy;		
		data->hits = data->hits - 1;
	}			

	if (data->hits <= 0)
	{
		SpriteManagerRemove(THIS_IDX);
	}
}

void Destroy_SPRITE_AXE() 
{
	axes--;
}