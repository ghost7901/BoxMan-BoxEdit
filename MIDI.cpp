// MIDI.cpp: implementation of the CMIDI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MIDI.h"
#include "mymidi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMIDI::CMIDI(LPCSTR FileName)
:m_lpstrFileName(FileName)
{
	m_OpenParms.wDeviceID=1;
}

CMIDI::~CMIDI()
{
}

BOOL CMIDI::OpenMCI()
{	
	m_OpenParms.lpstrDeviceType=(LPCSTR)MCI_DEVTYPE_SEQUENCER;
	m_OpenParms.lpstrElementName=m_lpstrFileName;
	m_OpenParms.wDeviceID=0;
	mciSendCommand(NULL,MCI_OPEN,
		MCI_WAIT|MCI_OPEN_TYPE
		|MCI_OPEN_TYPE_ID|MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&m_OpenParms);
	if(m_OpenParms.dwCallback==MOM_DONE)
		return TRUE;
	else
		return FALSE;
}

BOOL CMIDI::PlayMIDI(HWND hWnd)
{	
	MyMIDI::StopAllMIDI();//StopMIDI();
	OpenMCI();//TRACE("wDeviceID=%d\n",m_OpenParms.wDeviceID);

	MCI_PLAY_PARMS PlayParms;
	PlayParms.dwFrom=0;
	PlayParms.dwCallback=(DWORD)hWnd;
	if(mciSendCommand(m_OpenParms.wDeviceID,MCI_PLAY,
		MCI_NOTIFY,(DWORD)(LPVOID)
		&PlayParms))
		return FALSE;
	else
	{
//		SetVolume(m_OpenParms.wDeviceID,3);
		return TRUE;
	}
}

void CMIDI::PauseMIDI()
{
	MCI_PLAY_PARMS PlayParms;
	mciSendCommand(m_OpenParms.wDeviceID,MCI_PAUSE,
		MCI_WAIT,(DWORD)(LPVOID)&PlayParms);
}

BOOL CMIDI::StopMIDI()
{
	if(mciSendCommand(m_OpenParms.wDeviceID,MCI_STOP,NULL,NULL))
		return FALSE;
	else
		return TRUE;
}


DWORD CMIDI::ReturnInfo()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem=MCI_SEQ_STATUS_DIVTYPE;
	mciSendCommand(m_OpenParms.wDeviceID,MCI_STATUS,
		MCI_WAIT|MCI_STATUS_ITEM,
		(DWORD)(LPVOID)&StatusParms);
	return StatusParms.dwReturn;	/*
	返回信息存放于StatusParms.dwReturn中。
	MCI_STATUS标志
	MCI_STATUS_LENGTH  获得文件长度
	MCI_STATUS_MODE  获得文件播放的当前状态
	MCI_STATUS_POSITION  获得文件播放的当前位置
	MCI_STATUS_TIME_FORMAT  获得当前的时间格式
	MCI_SEQ_STATUS_DIVTYPE  判断文件是PPQN类型还是SMPTE类型
	MCI_SEQ_STATUS_TEMPO	  获得当前播放速度，PQRN类型，
	此值为节拍/分，SMPTE类型，此值为祯/秒*/
}

void CMIDI::SetFormat()
{
	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	//设置时间单位为毫秒
	mciSendCommand (OpenMCI(), 
		MCI_SET, MCI_SET_TIME_FORMAT,
		(DWORD)(LPVOID) &SetParms);
	//	MCI_SEQ_SET_TEMPO  设置播放速度，
	//	PQRN类型，此值为节拍/分，
	//	SMPTE类型，此值为祯/秒
}

void CMIDI::PlayFrom(int nMinute,int nSecond)
{
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = (nMinute * 60 + nSecond) * 1000;
	//跳转的目标时间，时间单位为毫秒
	mciSendCommand (OpenMCI(), MCI_SEEK, MCI_TO 
		| MCI_WAIT,(DWORD)(LPVOID)&SeekParms);/*
	*跳到文件头
	mciSendCommand (m_wDeviceID, MCI_SEEK, 
	MCI_SEEK_TO_START, NULL);
	* 跳到文件尾
	mciSendCommand (m_wDeviceID, MCI_SEEK,
	MCI_SEEK_TO_END, NULL);*/

}

void CMIDI::ResumeMIDI()
{
	MCI_PLAY_PARMS PlayParms;
	(mciSendCommand(m_OpenParms.wDeviceID,MCI_RESUME,
		MCI_WAIT,(DWORD)(LPVOID)&PlayParms));
}

BOOL CMIDI::IsPlaying()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem=MCI_SEQ_STATUS_DIVTYPE;
	mciSendCommand(1,MCI_STATUS|MCI_STATUS_MODE,
		MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms);
	//TRACE("StatusParms.dwReturn=%d\n",StatusParms.dwReturn);
	if(StatusParms.dwReturn==MCI_SEQ_OFFSET)
		return TRUE;
	else
		return FALSE;
}

void CMIDI::m_funcPlaySound(LPCSTR FileName,bool bNoStop)
{
	TCHAR exeFullPath[MAX_PATH]; 
    CString strPath; 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH); 
    strPath=(CString)exeFullPath; 
    int position=strPath.ReverseFind('\\'); 
    strPath=strPath.Left(position+1); 

	strPath+=FileName;
    /*TCHAR FilePath[MAX_PATH]; 
    GetModuleFileName(NULL,FilePath,MAX_PATH); 
    (_tcsrchr(FilePath,'\\'))[1] = 0; 
    lstrcat(FilePath,FileName); */

	DWORD flag= SND_FILENAME | SND_ASYNC;
	if(bNoStop) flag |= SND_NOSTOP;
	PlaySound(strPath, NULL, flag);
}

void CMIDI::SetVolume(HMIDIOUT hmo, DWORD dwVolume)
{
	midiOutSetVolume(hmo,dwVolume);

}

DWORD CMIDI::GetMIDILength()
{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem=MCI_SEQ_STATUS_DIVTYPE;
	mciSendCommand(m_OpenParms.wDeviceID,MCI_STATUS|MCI_STATUS_LENGTH,
		MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID)&StatusParms);
	TRACE("Length=%l\n",StatusParms.dwReturn);
	return StatusParms.dwReturn;
}