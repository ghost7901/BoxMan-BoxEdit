// MIDI.h: interface for the CMIDI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIDI_H__9FAFD8F9_E605_4EC7_855A_B4AF0A782E16__INCLUDED_)
#define AFX_MIDI_H__9FAFD8F9_E605_4EC7_855A_B4AF0A782E16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MMSYSTEM.h"
#pragma comment(lib,"winmm.lib")



class CMIDI  
{
public:
	CMIDI();
	CMIDI(LPCSTR);
	virtual ~CMIDI();

public:
	MCI_OPEN_PARMS m_OpenParms;

public:
	DWORD GetMIDILength();
	void SetVolume(HMIDIOUT,DWORD);
	static void m_funcPlaySound(LPCSTR,bool=FALSE);
	BOOL IsPlaying();
	void ResumeMIDI();
	void PlayFrom(int,int);
	void SetFormat();
	DWORD ReturnInfo();
	LPCSTR m_lpstrFileName;
	BOOL StopMIDI();
	void PauseMIDI();
	BOOL PlayMIDI(HWND hWnd);
	BOOL OpenMCI();
	void SetMIDIFile(LPCSTR);
};

#endif // !defined(AFX_MIDI_H__9FAFD8F9_E605_4EC7_855A_B4AF0A782E16__INCLUDED_)
