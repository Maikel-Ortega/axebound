#pragma bank 2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "..\res\src\tiles.h"
#include "..\res\src\map.h"
#include "..\res\src\knight.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Palette.h"

const UINT16 bg_palette[]		= { PALETTE_FROM_HEADER(tiles) };
//UINT16 sprites_palette[]	= { PALETTE_FROM_HEADER(knight) };
UINT16 sprites_palette[] = {
	PALETTE_INDEX(knight, 0),
	PALETTE_INDEX(knight, 1),
	PALETTE_INDEX(knight,  2),
	PALETTE_INDEX(knight, 3),
	PALETTE_INDEX(knight, 4),
	PALETTE_INDEX(knight, 5),
	PALETTE_INDEX(knight, 6),
	PALETTE_INDEX(knight, 7),
};

extern UINT8 n_sprite_types;
extern UINT8* template_mod_Data[];

UINT8 collision_tiles[] = { 1, 4,5,6,7,0 };

void Start_STATE_GAME() {
	UINT8 i;
	
	SetPalette(SPRITES_PALETTE, 0, 8, sprites_palette, bank_STATE_GAME);
	SetPalette(BG_PALETTE, 0, 8, bg_palette, bank_STATE_GAME); 
	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;


	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 50, 50);	
	
	InitScrollTilesColor(0, 16, tiles, 3);
	InitScroll(mapWidth, mapHeight, map, collision_tiles, 0, 3);
	SHOW_BKG;	
	PlayMusic(template_mod_Data, 4, 1);

}

void Update_STATE_GAME() {
}