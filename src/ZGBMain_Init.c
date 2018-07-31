#pragma bank 1
#include "ZGBMain.h"
UINT8 init_bank = 1;


#include "StateGame.h"

#include "SpritePlayer.h"
#include "SpriteAxe.h"
#include "SpriteEnemy.h"

#include "../res/src/knight.h"
#include "../res/src/enemy.h"
#include "../res/src/axe.h"

UINT8 next_state = STATE_GAME;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_GAME);
}

void InitSprites() {
	INIT_SPRITE_COLOR(SPRITE_PLAYER, knight, 3, FRAME_16x16, 16);	
	INIT_SPRITE(SPRITE_AXE, axe, 3, FRAME_16x16, 3);
	INIT_SPRITE(SPRITE_ENEMY, enemy, 3, FRAME_16x16, 6);
}