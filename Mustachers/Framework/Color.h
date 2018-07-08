#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
		
	inline Color(float pRed, float pGreen, float pBlue, float pAlpha)
	{
		mRed=pRed;
		mGreen=pGreen;
		mBlue=pBlue;
		mAlpha=pAlpha;
	}
	
	inline Color(float pRed, float pGreen, float pBlue)
	{
		mRed=pRed;
		mGreen=pGreen;
		mBlue=pBlue;
		mAlpha=1.0f;
	}
	
	inline Color(float pIntensity)
	{
		mRed=1.0f;
		mGreen=1.0f;
		mBlue=1.0f;
		mAlpha=pIntensity;
	}
	
	inline Color(int pIntensity)
	{
		mRed=1.0f;
		mGreen=1.0f;
		mBlue=1.0f;
		mAlpha=(float)pIntensity;
	}
	
	Color(const char *pRGBAString)
	{
		mRed=0;
		mGreen=0;
		mBlue=0;
		mAlpha=1.0f;
		const char *aPtr=pRGBAString;
		bool aFoundHex=false;
		if(aPtr)
		{
			while(*aPtr)
			{
				if((*aPtr>='0'&&*aPtr<='9')||(*aPtr>='a'&&*aPtr<='f')||(*aPtr>='A'&&*aPtr<='F'))
				{
					aFoundHex=true;
				}
				else
				{
					if(aFoundHex)
					{
						break;
					}
					else
					{
						pRGBAString++;
					}
				}
				aPtr++;
			}
			int aLength=(int)(aPtr-pRGBAString);
			if(aLength==2||aLength==6||aLength==8)
			{
				int aNumber[8];
				for(int i=0;i<aLength;i++)
				{
					aNumber[i]=0;
					if(pRGBAString[i]>='0'&&pRGBAString[i]<='9')
					{
						aNumber[i]=pRGBAString[i]-'0';
					}
					else if(pRGBAString[i]>='a'&&pRGBAString[i]<='f')
					{
						aNumber[i]=pRGBAString[i]-('a'-10);
					}
					else if(pRGBAString[i]>='A'&&pRGBAString[i]<='F')
					{
						aNumber[i]=pRGBAString[i]-('A'-10);
					}
					if(!(i&1))
					{
						aNumber[i]=(aNumber[i]<<4);
					}
				}
				if(aLength==2)
				{
					mRed=1;
					mGreen=1;
					mBlue=1;
					mAlpha=(float)(aNumber[0]+aNumber[1])/255.0f;
				}
				else if(aLength==6)
				{
					mRed=(float)(aNumber[0]+aNumber[1])/255.0f;
					mGreen=(float)(aNumber[2]+aNumber[3])/255.0f;
					mBlue=(float)(aNumber[4]+aNumber[5])/255.0f;
					mAlpha=1.0f;
				}
				else
				{
					mRed=(float)(aNumber[0]+aNumber[1])/255.0f;
					mGreen=(float)(aNumber[2]+aNumber[3])/255.0f;
					mBlue=(float)(aNumber[4]+aNumber[5])/255.0f;
					mAlpha=(float)(aNumber[6]+aNumber[7])/255.0f;
				}
			}
		}
	}
	
	
	Color(void)
	{
		mRed=0;
		mGreen=0;
		mBlue=0;
		mAlpha=1.0f;
	}
	
	
	void operator+=(Color &pColor){mRed+=pColor.mRed;mGreen+=pColor.mGreen;mBlue+=pColor.mBlue;mAlpha+=pColor.mAlpha;}
	void operator-=(Color &pColor){mRed-=pColor.mRed;mGreen-=pColor.mGreen;mBlue-=pColor.mBlue;mAlpha-=pColor.mAlpha;}
	void operator*=(Color &pColor){mRed*=pColor.mRed;mGreen*=pColor.mGreen;mBlue*=pColor.mBlue;mAlpha*=pColor.mAlpha;}
	void operator/=(Color &pColor){mRed/=pColor.mRed;mGreen/=pColor.mGreen;mBlue/=pColor.mBlue;mAlpha/=pColor.mAlpha;}
	
	Color operator+(Color &pColor){return Color(mRed+pColor.mRed,mGreen+pColor.mGreen,mBlue+pColor.mBlue,mAlpha+pColor.mAlpha);}
	Color operator-(Color &pColor){return Color(mRed-pColor.mRed,mGreen-pColor.mGreen,mBlue-pColor.mBlue,mAlpha-pColor.mAlpha);}
	Color operator*(Color &pColor){return Color(mRed*pColor.mRed,mGreen*pColor.mGreen,mBlue*pColor.mBlue,mAlpha*pColor.mAlpha);}
	Color operator/(Color &pColor){return Color(mRed/pColor.mRed,mGreen/pColor.mGreen,mBlue/pColor.mBlue,mAlpha/pColor.mAlpha);}
	
	void operator+=(float pVal){mRed+=pVal;mGreen+=pVal;mBlue+=pVal;mAlpha+=pVal;}
	void operator-=(float pVal){mRed-=pVal;mGreen-=pVal;mBlue-=pVal;mAlpha-=pVal;}
	void operator*=(float pVal){mRed*=pVal;mGreen*=pVal;mBlue*=pVal;mAlpha*=pVal;}
	void operator/=(float pVal){mRed/=pVal;mGreen/=pVal;mBlue/=pVal;mAlpha/=pVal;}
	
	Color operator+(float pVal){return Color(mRed+pVal,mGreen+pVal,mBlue+pVal,mAlpha+pVal);}
	Color operator-(float pVal){return Color(mRed-pVal,mGreen-pVal,mBlue-pVal,mAlpha-pVal);}
	Color operator*(float pVal){return Color(mRed*pVal,mGreen*pVal,mBlue*pVal,mAlpha*pVal);}
	Color operator/(float pVal){return Color(mRed/pVal,mGreen/pVal,mBlue/pVal,mAlpha/pVal);}
	
	
	
public:
	float	mRed;
	float	mGreen;
	float	mBlue;
	float	mAlpha;
};

#endif