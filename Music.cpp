#include"music.h"

void playMusic()
{
	while (true)
	{
		PlaySound(TEXT("BackgroundMusic.wav"), NULL, SND_FILENAME | SND_LOOP);
		PlaySound(0, 0, 0);
	}
}
