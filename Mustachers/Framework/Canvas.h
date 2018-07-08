#include "List.h"
#include "Color.h"
#include "FPoint.h"

#ifndef CANVAS_H
#define CANVAS_H


class Canvas
{
public:
	Canvas();
	virtual						~Canvas();
    
    virtual void                GoInactive();
    virtual void                GoActive();
	
	virtual void				BaseUpdate();
	virtual void				BaseDraw(float pTranslateX, float pTranslateY);
	virtual void				BaseDrawOver(float pTranslateX, float pTranslateY);
	
	virtual void				BaseTouch(int x, int y);
	virtual void				BaseRelease(int x, int y);
	virtual void				BaseDrag(int x, int y);
	
	virtual void				Update(){}
    virtual void				Draw(){}
	virtual void				DrawOver(){}
	
	virtual void				Touch(int x, int y){}
	virtual void				Release(int x, int y){}
	virtual void				Drag(int x, int y){}
	
	
	virtual void				MultiTouch(int x, int y, void *pData){}
	virtual void				MultiRelease(int x, int y, void *pData){}
    virtual void				MultiDrag(int x, int y, void *pData){}
    virtual void				FlushMultiTouch(){}
	
	
	void						SetPos(float x, float y);
	
	bool						Exists(Canvas *pCanvas);
	
	
	virtual bool				IsOver(int x, int y);
	
	FPoint						Center(){return FPoint(mX+mWidth/2,mY+mHeight/2);}
	
	virtual void				Kill();
	
	virtual void				Notify(void *pEvent){}
	
	virtual void				Size(int x, int y, int pWidth, int pHeight);
	
	void						Fill(Color pColor);

	int							mX, mY, mWidth, mHeight, mOffsetX, mOffsetY;
	
	int							mKill;
	
	int							mMouseX, mMouseY;
	float						mMouseXf, mMouseYf;
	
	bool						mRegisterAllTouch;
	bool						mRegisterAllRelease;
	bool						mRegisterAllDrag;
	
	
	bool						mIsButton;
	bool						mIsButtonOver;
    
    bool                        mUpdateReceived;
	
	
	Canvas						*mParent;
	
	Canvas						*GetTop(int x, int y, int &pTopX, int &pTopY);

	void						AddSubcanvas(Canvas *pCanvas);
	virtual void operator		+=(Canvas *pCanvas){AddSubcanvas(pCanvas);}
	
	void						RemoveChild(Canvas *pCanvas){mChildren-=pCanvas;}
	virtual void operator		-=(Canvas *pCanvas){RemoveChild(pCanvas);pCanvas->mParent=0;}
	
	//void						DeleteCanvas(Canvas *pCanvas);
	
	bool						mRoot;
	List						mChildren;
};

#endif