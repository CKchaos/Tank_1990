/***************************************************************
 * Name:      tankMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2016-06-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include <wx/timer.h>
#include "player.h"
#include "enemy.h"
#include <wx/sound.h>
#include "missile.h"
#define ID_TIMER 1000
#define enemy_fire 9
#define enemy_move 9

#ifndef TANKMAIN_H
#define TANKMAIN_H

//(*Headers(tankFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class tankFrame: public wxFrame
{
    public:

        tankFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~tankFrame();

    private:

        //(*Handlers(tankFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnMouseMove(wxMouseEvent& event);
        //*)

        //(*Identifiers(tankFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(tankFrame)
        wxStatusBar* StatusBar1;
        //*)
        int m_map1[30][30];
        int m_map[30][30]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1},
                            {1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1},
                            {1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,2,2,0,0,1,1},
                            {1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,2,2,0,0,1,1},
                            {1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1},
                            {1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
        wxIcon m_wall,m_black,m_black2,m_missile,m_stone,m_start,m_start1,m_start2,m_start3,m_blackall,m_tank,m_into;
        wxIcon m_win,m_over;
        wxTimer m_timer;
        wxBitmap m_bitmap;
        bool bool_start=true,bool_tank=true,bool_missile=false,bool_select=false;
        player me;
        enemy enemyx[3];
        wxSound snd_fire,snd_hit,snd_start,snd_win,snd_fail;
        missile m[2000];
        int m_num=0,times=0;
        void OnTimer(wxTimerEvent& event);
        void UpdateMap(int num,int x,int y,missile& mm);
        void Init();
        DECLARE_EVENT_TABLE()
};

#endif // TANKMAIN_H
