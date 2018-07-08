#include "stdafx.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	Object(){mKill=false;}
	virtual
	~Object(){}
	virtual void Update(){}
	virtual void Draw(){}
	inline void Kill(){mKill=20;}
	int mKill;
	FString mName;
};

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	void Update();
	void Draw();
	void Free();
    void KillAll();
    
	List mList;
	List mPurgatory;
	List mDelete;
	void operator+=(Object*pObject){mList+=pObject;}
	void operator-=(Object*pObject){mList-=pObject;mPurgatory-=pObject;mDelete-=pObject;}
};

#endif