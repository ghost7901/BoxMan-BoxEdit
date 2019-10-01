// MyMIDI.h: interface for the MyMIDI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMIDI_H__C5474CBF_FD94_4ED4_9DFC_E2350118FB16__INCLUDED_)
#define AFX_MYMIDI_H__C5474CBF_FD94_4ED4_9DFC_E2350118FB16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MIDI.h"

class MyMIDI : public CMIDI  
{
public:
	static int counter;
	static void StopAllMIDI();
	MyMIDI(LPCSTR);
	virtual ~MyMIDI();
};

#endif // !defined(AFX_MYMIDI_H__C5474CBF_FD94_4ED4_9DFC_E2350118FB16__INCLUDED_)
