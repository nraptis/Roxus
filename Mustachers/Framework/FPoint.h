#include <math.h>

#ifndef POINT_H
#define POINT_H

#define V2_DOT(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))
#define V2_CROSS(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

class FPoint
{
public:
	FPoint() {mX=0;mY=0;}
	FPoint(const float pX, const float pY) {mX=pX;mY=pY;}
	FPoint(const float pX, const int pY) {mX=pX;mY=(float)pY;}
	FPoint(const int pX, const float pY) {mX=(float)pX;mY=pY;}
	FPoint(const int pX, const int pY) {mX=(float)pX;mY=(float)pY;}
	FPoint(const FPoint &pFPoint) {*this=pFPoint;}
	
	inline FPoint &operator=(const FPoint &pFPoint) {if (this!=&pFPoint) {mX=pFPoint.mX;mY=pFPoint.mY;}return *this;}
	inline FPoint &operator=(float &pValue) {mX=pValue;mY=pValue;return *this;}
	inline FPoint &operator=(int &pValue) {mX=(float)pValue;mY=(float)pValue;return *this;}
	
	inline bool	operator==(const FPoint &pFPoint) {return (mX==pFPoint.mX)&(mY==pFPoint.mY);}
	inline bool	operator!=(const FPoint &pFPoint) {return (mX!=pFPoint.mX)|(mY!=pFPoint.mY);}
	
	inline const FPoint	operator*(const FPoint &pFPoint) const {return FPoint(mX*pFPoint.mX,mY*pFPoint.mY);}
	inline FPoint &operator*=(const FPoint &pFPoint) {mX*=pFPoint.mX;mY*=pFPoint.mY;return *this;}
	inline const FPoint operator*(const float pFloat) const {return FPoint(mX*pFloat,mY*pFloat);}
	inline FPoint &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;return *this;}
	inline const FPoint	operator/(const FPoint &pFPoint) const {return FPoint(mX/pFPoint.mX,mY/pFPoint.mY);}
	inline FPoint &operator/=(const FPoint &pFPoint) {mX/=pFPoint.mX;mY/=pFPoint.mY;return *this;}
	inline const FPoint operator/(const float pFloat) const {return FPoint(mX/pFloat,mY/pFloat);}
	inline FPoint &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;return *this;}
	inline const FPoint operator+(const FPoint &pFPoint) const {return FPoint(mX+pFPoint.mX,mY+pFPoint.mY);}
	inline FPoint &operator+=(const FPoint &pFPoint) {mX+=pFPoint.mX;mY+=pFPoint.mY;return *this;}
	inline const FPoint operator+(const float pFloat) const {return FPoint(mX+pFloat,mY+pFloat);}
	inline FPoint &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;return *this;}
	inline const FPoint operator-(const FPoint &pFPoint) const {return FPoint(mX-pFPoint.mX,mY-pFPoint.mY);}
	inline FPoint &operator-=(const FPoint &pFPoint) {mX-=pFPoint.mX;mY-=pFPoint.mY;return *this;}
	inline const FPoint operator-(const float pFloat) const {return FPoint(mX-pFloat,mY-pFloat);}
	inline FPoint & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;return *this;}
	inline const FPoint operator-() const {return FPoint(-mX,-mY);}
    
	inline float Dot(FPoint &pVector){return mX*pVector.mX+mY*pVector.mY;}
	inline const float Cross(FPoint &pVector){return mX*pVector.mY-mY*pVector.mX;}
    
	inline float LengthSquared(){return mX*mX+mY*mY;}
	inline float Length(){return sqrtf(mX*mX+mY*mY);}
	inline void SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;}
	inline void Normalize(){float aLen=Length();if(aLen>0){mX/=aLen;mY/=aLen;}}
    
	float mX;
	float mY;
};

class Vector3
{
public:
	Vector3() {mX=0;mY=0;mZ=0;}
	Vector3(const float pX, const float pY, const float pZ) {mX=pX;mY=pY;mZ=pZ;}
	Vector3(const Vector3 &pVector3) {*this=pVector3;}
	Vector3(const FPoint &pFPoint) {*this=pFPoint;}
	
	inline Vector3 &operator=(const Vector3 &pVector3) {if (this!=&pVector3) {mX=pVector3.mX;mY=pVector3.mY;mZ=pVector3.mZ;}return *this;}
	inline Vector3 &operator=(const FPoint &pFPoint) {mX=pFPoint.mX;mY=pFPoint.mY;mZ=0;return *this;}
	
	inline bool	operator==(const Vector3 &pVector3) {return (mX==pVector3.mX)&(mY==pVector3.mY)&(mZ==pVector3.mZ);}
	inline bool	operator!=(const Vector3 &pVector3) {return (mX!=pVector3.mX)|(mY!=pVector3.mY)|(mZ!=pVector3.mZ);}
	
	inline const Vector3	operator*(const Vector3 &pVector3) const {return Vector3(mX*pVector3.mX,mY*pVector3.mY,mZ*pVector3.mZ);}
	inline Vector3 &operator*=(const Vector3 &pVector3) {mX*=pVector3.mX;mY*=pVector3.mY;mZ*=pVector3.mZ;return *this;}
	inline const Vector3 operator*(const float pFloat) const {return Vector3(mX*pFloat,mY*pFloat,mZ*pFloat);}
	inline Vector3 &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;mZ*=pFloat;return *this;}
	inline const Vector3	operator/(const Vector3 &pVector3) const {return Vector3(mX/pVector3.mX,mY/pVector3.mY,mZ/pVector3.mZ);}
	inline Vector3 &operator/=(const Vector3 &pVector3) {mX/=pVector3.mX;mY/=pVector3.mY;mZ/=pVector3.mZ;return *this;}
	inline const Vector3 operator/(const float pFloat) const {return Vector3(mX/pFloat,mY/pFloat,mZ/pFloat);}
	inline Vector3 &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;mZ/=pFloat;return *this;}
	inline const Vector3 operator+(const Vector3 &pVector3) const {return Vector3(mX+pVector3.mX,mY+pVector3.mY,mZ+pVector3.mZ);}
	inline Vector3 &operator+=(const Vector3 &pVector3) {mX+=pVector3.mX;mY+=pVector3.mY;mZ+=pVector3.mZ;return *this;}
	inline const Vector3 operator+(const float pFloat) const {return Vector3(mX+pFloat,mY+pFloat,mZ+pFloat);}
	inline Vector3 &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;mZ+=pFloat;return *this;}
	inline const Vector3 operator-(const Vector3 &pVector3) const {return Vector3(mX-pVector3.mX,mY-pVector3.mY,mZ-pVector3.mZ);}
	inline Vector3 &operator-=(const Vector3 &pVector3) {mX-=pVector3.mX;mY-=pVector3.mY;mZ-=pVector3.mZ;return *this;}
	inline const Vector3 operator-(const float pFloat) const {return Vector3(mX-pFloat,mY-pFloat,mZ-pFloat);}
	inline Vector3 & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;mZ-=pFloat;return *this;}
	inline const Vector3 operator-() const {return Vector3(-mX,-mY,-mZ);}
	
    
	inline const Vector3	operator*(const FPoint &pFPoint) const {return Vector3(mX*pFPoint.mX,mY*pFPoint.mY,mZ);}
	inline Vector3 &operator*=(const FPoint &pFPoint) {mX*=pFPoint.mX;mY*=pFPoint.mY;return *this;}
	inline const Vector3	operator/(const FPoint &pFPoint) const {return Vector3(mX/pFPoint.mX,mY/pFPoint.mY,mZ);}
	inline Vector3 &operator/=(const FPoint &pFPoint) {mX/=pFPoint.mX;mY/=pFPoint.mY;;return *this;}
	inline const Vector3 operator+(const FPoint &pFPoint) const {return Vector3(mX+pFPoint.mX,mY+pFPoint.mY,mZ);}
	inline Vector3 &operator+=(const FPoint &pFPoint) {mX+=pFPoint.mX;mY+=pFPoint.mY;return *this;}
	inline const Vector3 operator-(const FPoint &pFPoint) const {return Vector3(mX-pFPoint.mX,mY-pFPoint.mY,mZ);}
	inline Vector3 &operator-=(const FPoint &pFPoint) {mX-=pFPoint.mX;mY-=pFPoint.mY;return *this;}
    
	
	
	inline float LengthSquared(){return mX*mX+mY*mY+mZ*mZ;}
	inline float Length(){return sqrtf(mX*mX+mY*mY+mZ*mZ);}
	inline void SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;mZ*=pLength;}
	inline void Normalize(){float aLen=Length();if(aLen>0){mX/=aLen;mY/=aLen;mZ/=aLen;}}
	
	float mX;
	float mY;
	float mZ;
};

class FPoint3
{
public:
	FPoint3() {mX=0;mY=0;mZ=0;}
	FPoint3(const float pX, const float pY, const float pZ) {mX=pX;mY=pY;mZ=pZ;}
	FPoint3(const FPoint3 &pFPoint3) {*this=pFPoint3;}
	FPoint3(const FPoint &pFPoint) {*this=pFPoint;}
	
	inline FPoint3 &operator=(const FPoint3 &pFPoint3) {if (this!=&pFPoint3) {mX=pFPoint3.mX;mY=pFPoint3.mY;mZ=pFPoint3.mZ;}return *this;}
	inline FPoint3 &operator=(const FPoint &pFPoint) {mX=pFPoint.mX;mY=pFPoint.mY;mZ=0;return *this;}
	
	inline bool	operator==(const FPoint3 &pFPoint3) {return (mX==pFPoint3.mX)&(mY==pFPoint3.mY)&(mZ==pFPoint3.mZ);}
	inline bool	operator!=(const FPoint3 &pFPoint3) {return (mX!=pFPoint3.mX)|(mY!=pFPoint3.mY)|(mZ!=pFPoint3.mZ);}
	
	inline const FPoint3	operator*(const FPoint3 &pFPoint3) const {return FPoint3(mX*pFPoint3.mX,mY*pFPoint3.mY,mZ*pFPoint3.mZ);}
	inline FPoint3 &operator*=(const FPoint3 &pFPoint3) {mX*=pFPoint3.mX;mY*=pFPoint3.mY;mZ*=pFPoint3.mZ;return *this;}
	inline const FPoint3 operator*(const float pFloat) const {return FPoint3(mX*pFloat,mY*pFloat,mZ*pFloat);}
	inline FPoint3 &operator*=(const float pFloat) {mX*=pFloat;mY*=pFloat;mZ*=pFloat;return *this;}
	inline const FPoint3	operator/(const FPoint3 &pFPoint3) const {return FPoint3(mX/pFPoint3.mX,mY/pFPoint3.mY,mZ/pFPoint3.mZ);}
	inline FPoint3 &operator/=(const FPoint3 &pFPoint3) {mX/=pFPoint3.mX;mY/=pFPoint3.mY;mZ/=pFPoint3.mZ;return *this;}
	inline const FPoint3 operator/(const float pFloat) const {return FPoint3(mX/pFloat,mY/pFloat,mZ/pFloat);}
	inline FPoint3 &operator/=(const float pFloat) {mX/=pFloat;mY/=pFloat;mZ/=pFloat;return *this;}
	inline const FPoint3 operator+(const FPoint3 &pFPoint3) const {return FPoint3(mX+pFPoint3.mX,mY+pFPoint3.mY,mZ+pFPoint3.mZ);}
	inline FPoint3 &operator+=(const FPoint3 &pFPoint3) {mX+=pFPoint3.mX;mY+=pFPoint3.mY;mZ+=pFPoint3.mZ;return *this;}
	inline const FPoint3 operator+(const float pFloat) const {return FPoint3(mX+pFloat,mY+pFloat,mZ+pFloat);}
	inline FPoint3 &operator+=(const float pFloat) {mX+=pFloat;mY+=pFloat;mZ+=pFloat;return *this;}
	inline const FPoint3 operator-(const FPoint3 &pFPoint3) const {return FPoint3(mX-pFPoint3.mX,mY-pFPoint3.mY,mZ-pFPoint3.mZ);}
	inline FPoint3 &operator-=(const FPoint3 &pFPoint3) {mX-=pFPoint3.mX;mY-=pFPoint3.mY;mZ-=pFPoint3.mZ;return *this;}
	inline const FPoint3 operator-(const float pFloat) const {return FPoint3(mX-pFloat,mY-pFloat,mZ-pFloat);}
	inline FPoint3 & operator-=(const float pFloat) {mX-=pFloat;mY-=pFloat;mZ-=pFloat;return *this;}
	inline const FPoint3 operator-() const {return FPoint3(-mX,-mY,-mZ);}
	
    
	inline const FPoint3	operator*(const FPoint &pFPoint) const {return FPoint3(mX*pFPoint.mX,mY*pFPoint.mY,mZ);}
	inline FPoint3 &operator*=(const FPoint &pFPoint) {mX*=pFPoint.mX;mY*=pFPoint.mY;return *this;}
	inline const FPoint3	operator/(const FPoint &pFPoint) const {return FPoint3(mX/pFPoint.mX,mY/pFPoint.mY,mZ);}
	inline FPoint3 &operator/=(const FPoint &pFPoint) {mX/=pFPoint.mX;mY/=pFPoint.mY;;return *this;}
	inline const FPoint3 operator+(const FPoint &pFPoint) const {return FPoint3(mX+pFPoint.mX,mY+pFPoint.mY,mZ);}
	inline FPoint3 &operator+=(const FPoint &pFPoint) {mX+=pFPoint.mX;mY+=pFPoint.mY;return *this;}
	inline const FPoint3 operator-(const FPoint &pFPoint) const {return FPoint3(mX-pFPoint.mX,mY-pFPoint.mY,mZ);}
	inline FPoint3 &operator-=(const FPoint &pFPoint) {mX-=pFPoint.mX;mY-=pFPoint.mY;return *this;}
    
	
	
	inline float LengthSquared(){return mX*mX+mY*mY+mZ*mZ;}
	inline float Length(){return sqrtf(mX*mX+mY*mY+mZ*mZ);}
	inline void SetLength(float pLength){Normalize();mX*=pLength;mY*=pLength;mZ*=pLength;}
	inline void Normalize(){float aLen=Length();if(aLen>0){mX/=aLen;mY/=aLen;mZ/=aLen;}}
	
	float mX;
	float mY;
	float mZ;
};

#endif