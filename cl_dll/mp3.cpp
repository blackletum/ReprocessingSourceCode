//mp3 support added by Killar

#include "hud.h"
#include "cl_util.h"
#include "mp3.h"

int CMP3::Initialize()
{

	char fmodlib[256];

	m_iIsPlaying = 0;
	sprintf(fmodlib, "%s/fmod.dll", gEngfuncs.pfnGetGameDirectory());
	// replace forward slashes with backslashes
	for (int i = 0; i < 256; i++)
		if (fmodlib[i] == '/') fmodlib[i] = '\\';

	m_hFMod = LoadLibrary(fmodlib);

	if (m_hFMod != NULL)
	{
		// fill in the function pointers
		(FARPROC&)VER = GetProcAddress(m_hFMod, "_FSOUND_GetVersion@0");
		(FARPROC&)SCL = GetProcAddress(m_hFMod, "_FSOUND_Stream_Close@4");
		(FARPROC&)SOP = GetProcAddress(m_hFMod, "_FSOUND_SetOutput@4");
		(FARPROC&)SBS = GetProcAddress(m_hFMod, "_FSOUND_SetBufferSize@4");
		(FARPROC&)SDRV = GetProcAddress(m_hFMod, "_FSOUND_SetDriver@4");
		(FARPROC&)INIT = GetProcAddress(m_hFMod, "_FSOUND_Init@12");
		(FARPROC&)SOF = GetProcAddress(m_hFMod, "_FSOUND_Stream_OpenFile@12");
		(FARPROC&)SO = GetProcAddress(m_hFMod, "_FSOUND_Stream_Open@16");
		(FARPROC&)SPLAY = GetProcAddress(m_hFMod, "_FSOUND_Stream_Play@8");
		(FARPROC&)CLOSE = GetProcAddress(m_hFMod, "_FSOUND_Close@0");
		(FARPROC&)SVL = GetProcAddress(m_hFMod, "_FSOUND_SetVolume@8");
		(FARPROC&)SCP = GetProcAddress(m_hFMod, "_FSOUND_Stream_SetTime@8");
		(FARPROC&)GCP = GetProcAddress(m_hFMod, "_FSOUND_Stream_GetTime@4");
		(FARPROC&)SP = GetProcAddress(m_hFMod, "_FSOUND_SetPaused@8");
		if (!(SCL && SOP && SBS && SDRV && INIT && (SOF || SO) && SPLAY && CLOSE && SVL && SCP && GCP && SP))
		{
			FreeLibrary(m_hFMod);
			gEngfuncs.Con_Printf("Fatal Error: FMOD functions couldn't be loaded!\n");
			return 0;
		}
	}
	else
	{
		gEngfuncs.Con_Printf("Fatal Error: FMOD library couldn't be loaded!\n");
		return 0;
	}
	gEngfuncs.Con_Printf("FMOD.dll loaded succesfully!\n");
	return 1;
}

int CMP3::Shutdown()
{
	if (m_hFMod)
	{
		CLOSE();

		FreeLibrary(m_hFMod);
		m_hFMod = NULL;
		m_iIsPlaying = 0;
		return 1;
	}
	else
		return 0;
}

int CMP3::StopMP3(void)
{
	if (m_iIsPlaying)
	{
		SCL(m_Stream);
		m_iIsPlaying = 0;
	}
	return 1;
}

bool CMP3::Update()
{
	if (m_iIsPlaying)
	{
		float vol = CVAR_GET_FLOAT("mp3volume");
		SVL(0, vol * 100);
		//if (GCP(m_Stream) == 0)
		//{
		//	gEngfuncs.Con_Printf("end of track\n");
		//	SCL(m_Stream);
		//	m_iIsPlaying = false;
		//}
	}
	return true;
}

void CMP3::PauseMP3(bool pause)
{
	if (m_iIsPlaying && pause != m_bPaused)
	{
		//gEngfuncs.Con_Printf("paused mus %d\n", pause);
		SP(0, pause);
		m_bPaused = pause;
	}
}

int CMP3::PlayMP3(const char *pszSong)
{
	if (m_iIsPlaying)
	{	// sound system is already initialized
		SCL(m_Stream);
	}
	else
	{
		SOP(FSOUND_OUTPUT_DSOUND);
		SBS(200);
		SDRV(0);
		INIT(44100, 1, 0); // we need just one channel, multiple mp3s at a time would be, erm, strange...	
	}				//AJH not for really cool effects, say walking past cars in a street playing different tunes

	char song[256];

	sprintf(song, "%s/media/%s", gEngfuncs.pfnGetGameDirectory(), pszSong);

	// leave out the FSOUND_LOOP_NORMAL to play the mp3 only once
//	gEngfuncs.Con_Printf("Using fmod.dll version %f\n",VER());
	if (SOF) {
		m_Stream = SOF(song, FSOUND_NORMAL, 1);	//AJH old fmod load call
	}
	else if (SO) {
		//	gEngfuncs.Con_Printf("USING FSOUND_Stream_Open\n");
		m_Stream = SO(song, FSOUND_NORMAL, 0, 0);	//AJH new fmod uses more parameters
	}
	float vol = CVAR_GET_FLOAT("mp3volume");
	//gEngfuncs.Con_Printf("mp3volume =  %f\n", vol);
	if (m_Stream) {
		SPLAY(0, m_Stream);
		SVL(0, vol*100);
		m_iIsPlaying = 1;
		return 1;

	}
	else {

		m_iIsPlaying = 0;
		gEngfuncs.Con_Printf("Error: Could not load %s\n", song);
		return 0;

	}
}