#ifndef GAME_TILE_BAD_EGG
#define GAME_TILE_BAD_EGG

//The bad eggs and good eggs will look similar at first, and then as
//we go along the bad eggs become increasingly hostile and less attractive.

#include "GameTile.h"

class GameTileBadEgg : public GameTile
{
public:
    
    GameTileBadEgg();
    virtual ~GameTileBadEgg();
    
    virtual void                            Update();
    virtual void                            Draw();
};

#endif



