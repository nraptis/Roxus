#ifndef GAME_TILE_GOOD_EGG
#define GAME_TILE_GOOD_EGG

#include "GameTile.h"

class GameTileGoodEgg : public GameTile
{
public:
    
    GameTileGoodEgg();
    virtual ~GameTileGoodEgg();
    
    virtual void                            Update();
    virtual void                            Draw();
    
};

#endif /* defined(___015_Jeep_Arcon__GameTileGoodEgg__) */
