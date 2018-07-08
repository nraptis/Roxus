/*
 *  HSList.h
 *  GetLucky
 *
 *  Created by Nick Raptis on 8/10/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */


#include "stdafx.h"

#pragma once

class HSList
{
public:
	HSList();
	~HSList();
	
	void		Add(char *name, int score);
	inline void	Add(const char *name, int score){Add((char*)name,score);}
	
	bool		Exists(char *name);
	inline bool	Exists(const char *name){return Exists((char*)name);}
	
	int			NewScoreIndex(int theScore);
	bool		IsHighScore(int theScore){return NewScoreIndex(theScore)!=-1;}
	
	int 		GetHighestScore();
	int			GetHighestScore(char *pName);//gc
	
	void		PadScore(int pScore);
	
	void		Size(int size);
	void		Clear();
	
	void		Save(){Save(mFile);}
	void		Save(FString theString);
	void		Load(FString theString);
	
	void		Print();

	FString		mFile;
	int			mSize;
	int			mRecent;
	int			*mScore;
	char		**mName;

};