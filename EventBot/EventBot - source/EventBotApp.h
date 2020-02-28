//---------------------------------------------------------------------------
//
// Name:        EventBotApp.h
// Author:      Radek
// Created:     2013-06-30 14:13:17
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __EVENTBOTFRMApp_h__
#define __EVENTBOTFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class EventBotFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
