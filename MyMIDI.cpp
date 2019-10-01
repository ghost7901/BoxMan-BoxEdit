// MyMIDI.cpp: implementation of the MyMIDI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BoxMan.h"
#include "MyMIDI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int MyMIDI::counter=0;

MyMIDI::MyMIDI(LPCSTR filename):CMIDI(filename)
{
	counter++;
}

MyMIDI::~MyMIDI()
{

}

void MyMIDI::StopAllMIDI()
{
	for(int i=1;i<=counter;i++)
	{
		mciSendCommand(i,MCI_STOP,NULL,NULL);
		mciSendCommand(i, MCI_CLOSE, NULL, NULL);
	}
}