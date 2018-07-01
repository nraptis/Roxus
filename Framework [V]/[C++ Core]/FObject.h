#ifndef FRAMEWORK_OBJECT_H
#define FRAMEWORK_OBJECT_H

#include "FList.h"

class FObject
{
public:
    
    FObject();
    virtual ~FObject();
    
    virtual void                            Update(){}
    virtual void                            Draw(){}
    
    virtual void                            Kill();
    int                                     mKill;
    
    //bool
    
};

class FObjectList : public FList
{
public:
    
    FObjectList();
    virtual ~FObjectList();
    
    
    void                                    Add(void *pObject);
    //void                                  Add(FList &pList);
    inline void operator                    +=(void *pItem){Add(pItem);}
    
    
    //virtual void                            Add(FObject *pObject);
    //inline void operator                    +=(FObject *pObject){Add(pObject);}
    
    bool                                    Empty(){return ((mCount <= 0) && (mObjectsAddedRecently.mCount <= 0));}
    

	void									ClearRecentlyAdded();
    void                                    Update();
    void                                    Draw();
    
    void                                    Free();
    void                                    KillAll();
    
    FList                                   mObjectsAddedRecently;
    //FList                                   mObjects;
    FList                                   mObjectsKillThisUpdate;
    FList                                   mObjectsKill;
    FList                                   mObjectsDelete;
    
};








#endif
