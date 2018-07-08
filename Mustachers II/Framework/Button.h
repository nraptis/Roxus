
//#define BUTTON_SETUP 1

#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"
#include "Sound.h"
#include "FString.h"
#include "Include.h"

class Image;
class Sprite;
class Font;

class ButtonLayer
{
public:
    ButtonLayer();
    ~ButtonLayer();
    
    Sprite              *mSprite[3];
    float               mOffsetX;
    float               mOffsetY;
    
};

class Button : public Canvas
{
public:
	Button();
	virtual         ~Button();
	
	virtual void	Touch(int x, int y);
	virtual void	Drag(int x, int y);
	virtual void	Release(int x, int y);
    
    
    virtual void	MultiTouch(int x, int y, void *pData);
	virtual void	MultiRelease(int x, int y, void *pData);
    virtual void	MultiDrag(int x, int y, void *pData);
    virtual void    FlushMultiTouch();
    
    virtual void    BaseDraw(float pTranslateX, float pTranslateY);
    virtual void    BaseDrawOver(float pTranslateX, float pTranslateY);
    
    
	virtual void	Draw();
    virtual void	DrawUntransformed();
    
    bool            mDrawManual;
	
	virtual bool	IsOver(int x, int y);
	
	void			SetDimensions(float pWidth, float pHeight);
	
	void			Setup(int x, int y, Sprite *pSpriteArray, int pSpriteCount, Canvas *pListener);
    
    void			Setup(int x, int y, Sprite *pSprite, Canvas *pListener);
    void			Setup(int x, int y, Sprite &pSprite){Setup(x, y, &(pSprite));}
    void			Setup(int x, int y, Sprite *pSprite);
    void			Setup(int x, int y, int pWidth, int pHeight, Canvas *pListener=0);
    
    void            SetUpCentered(float pX, float pY, Canvas *pListener, bool pAutoSize=true);
    void            SetUpTopLeft(float pX, float pY, Canvas *pListener, bool pAutoSize=true);
    
    void            AddLayer(Sprite *pSprite1, Sprite *pSprite2=0, Sprite *pSprite3=0);
    void            AddLayer(Sprite &pSprite1, Sprite &pSprite2, Sprite &pSprite3);
    void            AddLayer(Sprite &pSprite1, Sprite &pSprite2);
    void            AddLayer(Sprite &pSprite1);
    
	void			AddListener(Canvas *pCanvas);
    
	Canvas			*mListener;
    
    void            *mData;
	
	Image			*mImage;
    
    bool			mDrawOver;
    
	Sprite			*mSprite[3];
	int				mSpriteCount;
	
	Sprite			*mOverSprite;
	
	Sound			*mClickSound;
    
	FPoint			mSpriteOffset;
    
	int				mClicked;
	int				mPressed;
	int				mOver;
	
	bool			mDisableSound;
    
    //By default it will "trigger" on release..
    bool            mTriggerOnDown;
    
    bool            mCheckBox;
    bool            mCheckBoxState;

    List            mLayerList;
    
    bool            mDragMode;
    
    bool            mDragModeClicked;
    
    int             mDragModeMouseX;
    int             mDragModeMouseY;
    
    int             mDragModeOffseX;
    int             mDragModeOffseY;
    
    int             mDragModeTimer;
    
    bool            mMultiTouch;
    
};

#endif
