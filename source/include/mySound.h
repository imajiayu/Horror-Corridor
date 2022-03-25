#pragma once
#include "irrKlang/irrKlang.h"
#include<vector>
#include<string>
#include<time.h>

using namespace irrklang;
using namespace std;

struct Music
{
	double start_time;
	double play_time;
	string path;
};

class mySoundEngline
{
	ISoundEngine* SoundEngine;
	vector<Music>PlayingMusic;

public:
	mySoundEngline();
	~mySoundEngline();
	void play2D(const char[], int isLoop);
	void playFewSecond(const char[], double time);
private:
};