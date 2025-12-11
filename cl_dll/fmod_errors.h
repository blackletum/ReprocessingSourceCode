#ifndef _FMOD_ERRORS_H
#define _FMOD_ERRORS_H

enum FMOD_ERRORS
{
	FMOD_ERR_NONE,             /* No errors */
	FMOD_ERR_BUSY,             /* Cannot call this command after FSOUND_Init.  Call FSOUND_Close first. */
	FMOD_ERR_UNINITIALIZED,    /* This command failed because FSOUND_Init or FSOUND_SetOutput was not called */
	FMOD_ERR_INIT,             /* Error initializing output device. */
	FMOD_ERR_ALLOCATED,        /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
	FMOD_ERR_PLAY,             /* Playing the sound failed. */
	FMOD_ERR_OUTPUT_FORMAT,    /* Soundcard does not support the features needed for this soundsystem (16bit stereo output) */
	FMOD_ERR_COOPERATIVELEVEL, /* Error setting cooperative level for hardware. */
	FMOD_ERR_CREATEBUFFER,     /* Error creating hardware sound buffer. */
	FMOD_ERR_FILE_NOTFOUND,    /* File not found */
	FMOD_ERR_FILE_FORMAT,      /* Unknown file format */
	FMOD_ERR_FILE_BAD,         /* Error loading file */
	FMOD_ERR_MEMORY,           /* Not enough memory or resources */
	FMOD_ERR_VERSION,          /* The version number of this file format is not supported */
	FMOD_ERR_INVALID_PARAM,    /* An invalid parameter was passed to this function */
	FMOD_ERR_NO_EAX,           /* Tried to use an EAX command on a non EAX enabled channel or output. */
	FMOD_ERR_CHANNEL_ALLOC,    /* Failed to allocate a new channel */
	FMOD_ERR_RECORD,           /* Recording is not supported on this machine */
	FMOD_ERR_MEDIAPLAYER,      /* Windows Media Player not installed so cannot play wma or use internet streaming. */
	FMOD_ERR_CDDEVICE          /* An error occured trying to open the specified CD device */
};

static char *FMOD_ErrorString(int errcode)
{
	switch (errcode)
	{
		case FMOD_ERR_NONE:				return "No errors";
		case FMOD_ERR_BUSY:				return "Cannot call this command after FSOUND_Init.  Call FSOUND_Close first.";
		case FMOD_ERR_UNINITIALIZED:	return "This command failed because FSOUND_Init was not called";
		case FMOD_ERR_PLAY:				return "Playing the sound failed.";
		case FMOD_ERR_INIT:				return "Error initializing output device.";
		case FMOD_ERR_ALLOCATED:		return "The output device is already in use and cannot be reused.";
		case FMOD_ERR_OUTPUT_FORMAT:	return "Soundcard does not support the features needed for this soundsystem (16bit stereo output)";
		case FMOD_ERR_COOPERATIVELEVEL:	return "Error setting cooperative level for hardware.";
		case FMOD_ERR_CREATEBUFFER:		return "Error creating hardware sound buffer.";
		case FMOD_ERR_FILE_NOTFOUND:	return "File not found";
		case FMOD_ERR_FILE_FORMAT:		return "Unknown file format";
		case FMOD_ERR_FILE_BAD:			return "Error loading file";
		case FMOD_ERR_MEMORY:			return "Not enough memory ";
		case FMOD_ERR_VERSION:			return "The version number of this file format is not supported";
		case FMOD_ERR_INVALID_PARAM:	return "An invalid parameter was passed to this function";
		case FMOD_ERR_NO_EAX:			return "Tried to use an EAX command on a non EAX enabled channel or output.";
		case FMOD_ERR_CHANNEL_ALLOC:	return "Failed to allocate a new channel";
		case FMOD_ERR_RECORD:			return "Recording not supported on this device";
		case FMOD_ERR_MEDIAPLAYER:		return "Required Mediaplayer codec is not installed";

		default :						return "Unknown error";
	};
}

#endif
