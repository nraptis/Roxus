#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator
{
public:
	Oscillator(int pTime);
	Oscillator();
	~Oscillator();
	
	void				Update();
	
	float				Percent(){if(mTime==0)return 1;return (float)mIndex/(float)mTime;}
	inline float		P(){return Percent()-0.5f;}
	
	int					Dir(){return mDir;}
	bool				Max(){return mIndex==mTime;}
	bool				Min(){return mIndex==0;}
	
	void				Randomize();
	
	//-1 for counting down, 1 for counting up.
	int					mDir;
	int					mIndex;
	int					mTime;
	int					mPauseTimer;
	int					mPause;
};

#endif