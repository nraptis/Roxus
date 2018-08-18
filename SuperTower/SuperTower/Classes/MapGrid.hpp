//
//  MapGrid.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef MapGrid_hpp
#define MapGrid_hpp

#include "FList.hpp"
#include "MapTile.hpp"
#include "LevelPath.hpp"
#include "FXML.h"

class PathNode;
class MapGrid {
public:
    MapGrid();
    ~MapGrid();

    void                                        Update();

    void                                        DrawAllNodes();
    void                                        DrawOccupiedNodes();
    void                                        DrawOccupiedTiles();
    void                                        DrawAllConnections();
    void                                        DrawLevelPathConnections();

    //Our main "grid" of tiles...
    MapTile                                     ****mTile;
    int                                         mTileGridWidthTotal;
    int                                         mTileGridHeightTotal;
    int                                         mTileGridWidthActive;
    int                                         mTileGridHeightActive;
    int                                         mTileGridBufferH;
    int                                         mTileGridBufferV;
    bool                                        mTileVisible[GRID_DEPTH];
    float                                       mTileOpacity[GRID_DEPTH];

    //The grid that we use for pathfinding, etc - these are clones of the objects in mUnitGridBase...
    PathNode                                    ****mUnitGrid;
    PathNode                                    ****mUnitGridBase;
    int                                         mUnitGridWidth;
    int                                         mUnitGridHeight;

    bool                                        ***mWalkAllowed;

    bool                                        **mTowerAllowed;



    FList                                       mDeletedTileList;
    FList                                       mDeletedNodeList;
    FList                                       mTileList;


    ////////////////////////////////////////////////
    ////                                        ////
    ////             Grid Size Stuff            ////
    ////                                        ////
    void                                        SizeGrid(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);
    void                                        ClearGrid();
    void                                        Generate(int pWidth, int pHeight, int pGridBufferH, int pGridBufferV);

    void                                        GenerateUnitGrid();
    void                                        ClearWalkableChunk(int pGridX, int pGridY, int pGridZ, int pRingSize);


    void                                        ClearTiles(int pDepth);
    void                                        ClearTiles();
    void                                        Flood(int pDepth);
    void                                        IncreaseBuffer();
    void                                        DecreaseBuffer();
    void                                        IncreaseWidth();
    void                                        DecreaseWidth();
    void                                        IncreaseHeight();
    void                                        DecreaseHeight();
    ////                                        ////
    ////                                        ////
    ////////////////////////////////////////////////




    ////////////////////////////////////////////////
    ////                                        ////
    ////              Touch Support             ////
    ////                                        ////

    //Get the closest valid node to a particular screen location....
    //There is one rule always enforce - the node must be on a tile...
    PathNode                                    *GetClosestNode(float pX, float pY, bool pAllowBlocked, bool pAllowOccupied, bool pAllowRamps);

    //Takes into consideration the actual tiles of the arena to determine exactly
    //which x, y, and z grid positions the user's finger has landed on...
    void                                        GetGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ);
    //Editor only: this determines which grid position our fingers would land at
    //for a given depth...
    void                                        GetEditorGridPosAtDepth(float pX, float pY, int pDepth, int &pGridX, int &pGridY);
    void                                        GetEditorGridPos(float pX, float pY, int &pGridX, int &pGridY, int &pGridZ);
    ////                                        ////
    ////                                        ////
    ////////////////////////////////////////////////


    ////////////////////////////////////////////////
    ////                                        ////
    ////          Connection Stuff...           ////
    ////                                        ////

    //Assumption: Grid nodes already exist.
    //If, for example, we change a tile or place a tower, we should REFRESH the nodes.
    //This will assign nodes to tiles, compute node positions, and figure out which
    //nodes are "blocked" by default...
    void                                        RefreshUnitGridNodes();
    void                                        ComputePathConnections();


    //Basically un-occupy all tiles and reset our connections...
    //Then, re-occupy all nodes covered by tower tiles, and anything that
    //is not a moving unit...
    void                                        ResetGridConnections();

    //Assumed that ComputePathConnections() was called...
    //Assumed that we have OCCUPIED the desired tiles that will
    //be occupied for this twist of the pepper dispenser.
    void                                        ComputeGridConnections();

    ///                                         ////
    ////                                        ////
    ////////////////////////////////////////////////


    ////////////////////////////////////////////////
    ////                                        ////
    ////           Unit Grid Helpers            ////
    ////                                        ////

    PathNode                                    *GetGridNode(int pGridX, int pGridY, int pGridZ);
    float                                       GetUnitGridX(int pGridX, int pGridY, int pGridZ);
    float                                       GetUnitGridY(int pGridX, int pGridY, int pGridZ);
    bool                                        UnitGridPositionsAreAdjacent(int pGridX1, int pGridY1, int pGridZ1, int pGridX2, int pGridY2, int pGridZ2);
    bool                                        UnitGridPositionsAreAdjacentAndNotEqual(int pGridX1, int pGridY1, int pGridZ1, int pGridX2, int pGridY2, int pGridZ2);

    FRect                                       GetRectForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ);

    ///                                         ////
    ////                                        ////
    ////////////////////////////////////////////////


    ////////////////////////////////////////////////
    ////                                        ////
    ////          Tile Grid Helpers             ////
    ////                                        ////

    MapTile                                     *GetTile(int pGridX, int pGridY, int pGridZ);
    void                                        DeleteTile(int pGridX, int pGridY, int pGridZ);

    ///                                         ////
    ////                                        ////
    ////////////////////////////////////////////////


    ////////////////////////////////////////////////
    ////                                        ////
    ////       Tile / Unit Grid Bridging        ////
    ////                                        ////

    bool                                        IsNodeOnTile(PathNode *pNode, MapTile *pTile);


    PathNode                                    *GetEndNodeForTile(MapTile *pTile);

    //Used when we deploy a group, so that there are not collisions on the end-tile...
    void                                        UnblockAllNodesForTile(MapTile *pTile);
    

    //If there are multiple tiles for a particular node, we get all of the tiles
    // (max of 2) for the given node...
    void                                        GetAllTilesForNode(int pUnitGridX, int pUnitGridY, int pUnitGridZ, FList *pList);

    ///                                         ////
    ////                                        ////
    ////////////////////////////////////////////////


    ////////////////////////////////////////////////
    ////                                        ////
    ////              Path Helpers              ////
    ////                                        ////
    PathNode                                    *GetEndNodeForPath(LevelPath *pPath);
    PathNode                                    *GetStartNodeForPath(LevelPath *pPath);

    void                                        DumpLevelPathToTileList(LevelPath *pPath);
    MapTile                                     *GetEndTileForPath(LevelPath *pPath);
    MapTile                                     *GetStartTileForPath(LevelPath *pPath);
    

    ///                                         ////
    ////                                        ////
    ////////////////////////////////////////////////

    //...There can only be one tower at ANY level along the grid, assumed top level...
    //TODO: Make special grid locations election function for TOWERS which select the top
    //available colliding tile with click position...
    void                                        ComputeTowerAllowedPlacements();

    void                                        Save(FXMLTag *pTag);
    void                                        Load(FXMLTag *pTag);
    
};

extern MapGrid *gGrid;

#endif /* MapGrid_hpp */
