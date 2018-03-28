/***************************************************************
 * Name:      tankMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2016-06-30
 * Copyright:  ()
 * License:
 **************************************************************/
#include <wx/dcclient.h>
#include <wx/effects.h>
#include <wx/dcbuffer.h>
#include "tankMain.h"
#include <wx/msgdlg.h>
#include <malloc.h>

//(*InternalHeaders(tankFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(tankFrame)
const long tankFrame::idMenuQuit = wxNewId();
const long tankFrame::idMenuAbout = wxNewId();
const long tankFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(tankFrame,wxFrame)
    //(*EventTable(tankFrame)
    //*)
    EVT_TIMER(ID_TIMER,tankFrame::OnTimer)
END_EVENT_TABLE()

tankFrame::tankFrame(wxWindow* parent,wxWindowID id):m_timer(this,ID_TIMER)
{
    //(*Initialize(tankFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(600,642));
    Move(wxPoint(400,30));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&tankFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&tankFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&tankFrame::OnClose);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&tankFrame::OnPaint);
    Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&tankFrame::OnEraseBackground);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&tankFrame::OnKeyDown);
    Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&tankFrame::OnMouseMove);
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&tankFrame::OnMouseMove);
    //*)
    for(int i=0;i<30;i++)
        for(int j=0;j<30;j++)
            m_map1[i][j]=m_map[i][j];
    me=player(320,520,2);
    enemyx[0]=enemy(60,40,0,3);
    enemyx[1]=enemy(480,40,0,2);
    enemyx[2]=enemy(40,520,2,3);
    snd_fire.Create("fire1.wav");
    snd_hit.Create("hit.wav");
    snd_start.Create("start.wav");
    snd_win.Create("win.wav");
    snd_fail.Create("fail.wav");
    m_over=wxIcon(_T("fail.png"),wxBITMAP_TYPE_PNG);
    m_into=wxIcon(_T("into.png"),wxBITMAP_TYPE_PNG);
    m_win=wxIcon(_T("win.png"),wxBITMAP_TYPE_PNG);
    m_bitmap=wxBitmap(_T("black.png"), wxBITMAP_TYPE_PNG);
    m_tank=wxIcon(_T("tank.png"),wxBITMAP_TYPE_PNG);
    m_black=wxIcon(_T("black.png"), wxBITMAP_TYPE_PNG);
    m_black2=wxIcon(_T("black2.png"), wxBITMAP_TYPE_PNG);
    m_blackall=wxIcon(_T("blackall.png"), wxBITMAP_TYPE_PNG);
    m_wall=wxIcon(_T("wall.png"),wxBITMAP_TYPE_PNG);
    m_stone=wxIcon(_T("stone.png"),wxBITMAP_TYPE_PNG);
    m_start=wxIcon(_T("start.png"),wxBITMAP_TYPE_PNG);
    m_start1=wxIcon(_T("start1.png"),wxBITMAP_TYPE_PNG);
    m_start2=wxIcon(_T("start2.png"),wxBITMAP_TYPE_PNG);
    m_start3=wxIcon(_T("start3.png"),wxBITMAP_TYPE_PNG);
    me.direct[0]=wxIcon(_T("p1tankD.gif"),wxBITMAP_TYPE_GIF);
    me.direct[1]=wxIcon(_T("p1tankL.gif"),wxBITMAP_TYPE_GIF);
    me.direct[2]=wxIcon(_T("p1tankU.gif"),wxBITMAP_TYPE_GIF);
    me.direct[3]=wxIcon(_T("p1tankR.gif"),wxBITMAP_TYPE_GIF);
    m_missile=wxIcon(_T("missile.png"),wxBITMAP_TYPE_PNG);
    //enemyx[0]=enemy(60,40,0,3);
    //enemyx[1]=enemy(480,40,0,2);
    //enemyx[2]=enemy(40,520,2,3);
    for(int i=0;i<3;i++)
    {
        enemyx[i].direct[0][0]=wxIcon(_T("enemy1D.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[0][1]=wxIcon(_T("enemy1L.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[0][2]=wxIcon(_T("enemy1U.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[0][3]=wxIcon(_T("enemy1R.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[1][0]=wxIcon(_T("enemy2D.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[1][1]=wxIcon(_T("enemy2L.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[1][2]=wxIcon(_T("enemy2U.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[1][3]=wxIcon(_T("enemy2R.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[2][0]=wxIcon(_T("enemy3D.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[2][1]=wxIcon(_T("enemy3L.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[2][2]=wxIcon(_T("enemy3U.png"),wxBITMAP_TYPE_PNG);
        enemyx[i].direct[2][3]=wxIcon(_T("enemy3R.png"),wxBITMAP_TYPE_PNG);
    }
}

tankFrame::~tankFrame()
{
    //(*Destroy(tankFrame)
    //*)
}

void tankFrame::OnQuit(wxCommandEvent& event)
{
    Destroy();
}

void tankFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}

void tankFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void tankFrame::OnEraseBackground(wxEraseEvent& event)
{
    if(bool_select==false)
    {
        wxClientDC* clientDC = NULL;
        if (!event.GetDC())
            clientDC = new wxClientDC(this);
        wxDC* dc = clientDC?clientDC:event.GetDC();
        wxSize sz = GetClientSize();
        wxEffects effects ;
        effects.TileBitmap(wxRect(0, 0, sz.x, sz .y), *dc, m_bitmap);
        if (clientDC)
            delete clientDC;
    }
}

void tankFrame::OnPaint(wxPaintEvent& event)
{
    if(bool_select)
    {
        wxBufferedPaintDC dc(this);
        int i=0,j=0;
        for(i=0;i<30;i++)
            for(j=0;j<30;j++)
                if(m_map1[j][i]==1)
                {
                    if(bool_start)
                        dc.DrawIcon(m_wall,i*20,j*20);
                }
                else
                    if(m_map1[j][i]==2)
                    {
                            dc.DrawIcon(m_stone,i*20,j*20);
                    }
                    else
                        dc.DrawIcon(m_black,i*20,j*20);
        bool_start=false;
        dc.DrawIcon(me.GetIcon(),me.GetX(),me.GetY());
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()>0)
                dc.DrawIcon(enemyx[i].GetIcon(),enemyx[i].GetX(),enemyx[i].GetY());
        }
        for(int i=0;i<m_num;i++)
        if(m[i].GetState())
        {
            dc.DrawIcon(m_missile,m[i].GetX()-3,m[i].GetY()-3);
            UpdateMap(m[i].GetDirect(),m[i].GetX()/20,m[i].GetY()/20,m[i]);
        }
        if(enemyx[0].GetBlood()+enemyx[1].GetBlood()+enemyx[2].GetBlood()==0)
        {
            dc.DrawIcon(m_win,10,10);
            snd_win.Play();
            m_timer.Stop();
        }
        if(me.GetBlood()==0)
        {
            dc.DrawIcon(m_over,10,10);
            snd_fail.Play();
            m_timer.Stop();
        }
    }
    else
    {
        wxPaintDC dc(this);
        dc.DrawIcon(m_tank,100,50);
        dc.DrawIcon(m_start,225,150);
        m_timer.Stop();
    }
}
void tankFrame::OnKeyDown(wxKeyEvent& event)
{
    switch(event.GetKeyCode())
    {
        case WXK_LEFT:
            if(me.GetX()>0)
                if(m_map1[me.GetY()/20][me.GetX()/20-1]==0&&m_map1[me.GetY()/20+1][me.GetX()/20-1]==0)
                    me.AddX(-20);
            me.SetDirect(1);
            break;
        case WXK_RIGHT:
            if(me.GetX()<560)
                if(m_map1[me.GetY()/20][me.GetX()/20+2]==0&&m_map1[me.GetY()/20+1][me.GetX()/20+2]==0)
                    me.AddX(20);
            me.SetDirect(3);
            break;
        case WXK_UP:
            if(me.GetY()>0)
                if(m_map1[me.GetY()/20-1][me.GetX()/20]==0&&m_map1[me.GetY()/20-1][me.GetX()/20+1]==0)
                    me.AddY(-20);
            me.SetDirect(2);
            break;
        case WXK_DOWN:
            if(me.GetY()<560)
                if(m_map1[me.GetY()/20+2][me.GetX()/20]==0&&m_map1[me.GetY()/20+2][me.GetX()/20+1]==0)
                    me.AddY(20);
            me.SetDirect(0);
            break;
        case 83:
            m[m_num]=missile(me.GetX(),me.GetY(),me.GetDirect());
            m_num++;
            snd_fire.Play();
            break;
    }
    this->Refresh();
}

void tankFrame::OnTimer(wxTimerEvent& event)
{
    times++;
    for(int i=0;i<m_num;i++)
        if(m[i].GetState())
            m[i].UpdateXY();
    if(times%enemy_move==0&&times>25)
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            int d_x=enemyx[i].GetX()-me.GetX();
            int d_y=enemyx[i].GetY()-me.GetY();
            if(d_x>=0&&d_y>=0)
            {
                if(d_x>d_y)
                {
                    enemyx[i].SetDirect(1);
                    if(enemyx[i].GetX()>0)
                        if(m_map1[enemyx[i].GetY()/20][enemyx[i].GetX()/20-1]==0&&m_map1[enemyx[i].GetY()/20+1][enemyx[i].GetX()/20-1]==0)
                            enemyx[i].AddX(-20);
                }
                else
                {
                    enemyx[i].SetDirect(2);
                    if(enemyx[i].GetY()>0)
                        if(m_map1[enemyx[i].GetY()/20-1][enemyx[i].GetX()/20]==0&&m_map1[enemyx[i].GetY()/20-1][enemyx[i].GetX()/20+1]==0)
                            enemyx[i].AddY(-20);
                }
            }
            if(d_x<0&&d_y>=0)
            {
                if(0-d_x>d_y)
                {
                    enemyx[i].SetDirect(3);
                    if(enemyx[i].GetX()<560)
                        if(m_map1[enemyx[i].GetY()/20][enemyx[i].GetX()/20+2]==0&&m_map1[enemyx[i].GetY()/20+1][enemyx[i].GetX()/20+2]==0)
                            enemyx[i].AddX(20);
                }
                else
                {
                    enemyx[i].SetDirect(2);
                    if(enemyx[i].GetY()>0)
                        if(m_map1[enemyx[i].GetY()/20-1][enemyx[i].GetX()/20]==0&&m_map1[enemyx[i].GetY()/20-1][enemyx[i].GetX()/20+1]==0)
                            enemyx[i].AddY(-20);
                }
            }
            if(d_x>=0&&d_y<0)
            {
                if(d_x>0-d_y)
                {
                    enemyx[i].SetDirect(1);
                    if(enemyx[i].GetX()>0)
                        if(m_map1[enemyx[i].GetY()/20][enemyx[i].GetX()/20-1]==0&&m_map1[enemyx[i].GetY()/20+1][enemyx[i].GetX()/20-1]==0)
                            enemyx[i].AddX(-20);
                }
                else
                {
                    enemyx[i].SetDirect(0);
                    if(enemyx[i].GetY()<560)
                        if(m_map1[enemyx[i].GetY()/20+2][enemyx[i].GetX()/20]==0&&m_map1[enemyx[i].GetY()/20+2][enemyx[i].GetX()/20+1]==0)
                            enemyx[i].AddY(20);
                }
            }
            if(d_x<0&&d_y<0)
            {
                if(d_x<d_y)
                {
                    enemyx[i].SetDirect(3);
                    if(enemyx[i].GetX()<560)
                        if(m_map1[enemyx[i].GetY()/20][enemyx[i].GetX()/20+2]==0&&m_map1[enemyx[i].GetY()/20+1][enemyx[i].GetX()/20+2]==0)
                            enemyx[i].AddX(20);
                }
                else
                {
                    enemyx[i].SetDirect(0);
                    if(enemyx[i].GetY()<560)
                        if(m_map1[enemyx[i].GetY()/20+2][enemyx[i].GetX()/20]==0&&m_map1[enemyx[i].GetY()/20+2][enemyx[i].GetX()/20+1]==0)
                            enemyx[i].AddY(20);
                }
            }
        }
    if(times%enemy_fire==0&&times>25)
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            m[m_num]=missile(enemyx[i].GetX(),enemyx[i].GetY(),enemyx[i].GetDirect());
            m_num++;
        }
    this->Refresh();
}

void tankFrame::UpdateMap(int num,int x,int y,missile& mm)
{
    if(x==0||x>=30||y==0||y>=30)
    {
        mm.SetState(0);
        return;
    }
    bool bool_hit=false;
    if(num==0)
    {
        int me_x=me.GetX()/20;
        int me_y=me.GetY()/20;
        if(y==me_y&&(x==me_x||x-1==me_x||x-2==me_x))
        {
            me.CutBlood(1);
            bool_hit=true;
        }
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            int en_x=enemyx[i].GetX()/20;
            int en_y=enemyx[i].GetY()/20;
            if(y==en_y&&(x==en_x||x-1==en_x||x-2==en_x))
            {
                enemyx[i].CutBlood(1);
                bool_hit=true;
            }
        }

        if(m_map1[y][x-1]==1)
        {
            m_map1[y][x-1]=0;
            bool_hit=true;
        }
        if(m_map1[y][x]==1)
        {
            m_map1[y][x]=0;
            bool_hit=true;
        }
        if(m_map1[y][x-1]==2||m_map1[y][x]==2)
            bool_hit=true;
    }
    if(num==1)
    {
        int me_x=me.GetX()/20;
        int me_y=me.GetY()/20;
        if(x-2==me_x&&(y-1==me_y||y==me_y||y-2==me_y))
        {
            me.CutBlood(1);
            bool_hit=true;
        }
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            int en_x=enemyx[i].GetX()/20;
            int en_y=enemyx[i].GetY()/20;
            if(x-2==en_x&&(y-1==en_y||y==en_y||y-2==en_y))
            {
                enemyx[i].CutBlood(1);
                bool_hit=true;
            }
        }

        if(m_map1[y][x-1]==1)
        {
            m_map1[y][x-1]=0;
            bool_hit=true;
        }
        if(m_map1[y-1][x-1]==1)
        {
            m_map1[y-1][x-1]=0;
            bool_hit=true;
        }
        if(m_map1[y][x-1]==2||m_map1[y-1][x-1]==2)
            bool_hit=true;
    }
    if(num==2)
    {
        int me_x=me.GetX()/20;
        int me_y=me.GetY()/20;
        if(y-2==me_y&&(x==me_x||x==me_x+1||x==me_x+2))
        {
            me.CutBlood(1);
            bool_hit=true;
        }
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            int en_x=enemyx[i].GetX()/20;
            int en_y=enemyx[i].GetY()/20;
            if(y-2==en_y&&(x==en_x||x==en_x+1||x==en_x+2))
            {
                enemyx[i].CutBlood(1);
                bool_hit=true;
            }
        }

        if(m_map1[y-1][x-1]==1)
        {
            m_map1[y-1][x-1]=0;
            bool_hit=true;
        }
        if(m_map1[y-1][x]==1)
        {
            m_map1[y-1][x]=0;
            bool_hit=true;
        }
        if(m_map1[y-1][x-1]==2||m_map1[y-1][x]==2)
            bool_hit=true;
    }
    if(num==3)
    {
        int me_x=me.GetX()/20;
        int me_y=me.GetY()/20;
        if(x==me_x&&(y==me_y||y==me_y+1||y==me_y+2))
        {
            me.CutBlood(1);
            bool_hit=true;
        }
        for(int i=0;i<3;i++)
        {
            if(enemyx[i].GetBlood()==0) continue;
            int en_x=enemyx[i].GetX()/20;
            int en_y=enemyx[i].GetY()/20;
            if(x==en_x&&(y==en_y||y==en_y+1||y==en_y+2))
            {
                enemyx[i].CutBlood(1);
                bool_hit=true;
            }
        }

        if(m_map1[y-1][x]==1)
        {
            m_map1[y-1][x]=0;
            bool_hit=true;
        }
        if(m_map1[y][x]==1)
        {
            m_map1[y][x]=0;
            bool_hit=true;
        }
        if(m_map1[y-1][x]==2||m_map1[y][x]==2)
            bool_hit=true;
    }
    if(bool_hit==true)
    {
        mm.SetState(0);
        snd_hit.Play();
    }
}

void tankFrame::OnMouseMove(wxMouseEvent& event)
{
    if(bool_select==false)
    {
        wxClientDC dc(this);
        wxPoint pos=event.GetPosition();
        if(pos.x>=270&&pos.x<=326&&pos.y>=150&&pos.y<=206)
        {
            dc.DrawIcon(m_blackall,0,295);
            dc.DrawIcon(m_start1,225,150);
        }
        else
            if(pos.x>=225&&pos.x<=270&&pos.y>=150&&pos.y<=206)
            {
                dc.DrawIcon(m_blackall,0,295);
                dc.DrawIcon(m_start3,225,150);
                dc.DrawIcon(m_into,60,300);
            }
            else
                if(pos.x>=326&&pos.x<=375&&pos.y>=150&&pos.y<=206)
                {
                    dc.DrawIcon(m_blackall,0,295);
                    dc.DrawIcon(m_start2,225,150);
                }
                else
                {
                    dc.DrawIcon(m_blackall,0,295);
                    dc.DrawIcon(m_start,225,150);
                }
        if(pos.x>=270&&pos.x<=326&&pos.y>=150&&pos.y<=206&&event.LeftIsDown())
        {
            bool_select=true;
            snd_start.Play();
            Init();
            m_timer.Start(80);
        }
    }
    else
        if(enemyx[0].GetBlood()+enemyx[1].GetBlood()+enemyx[2].GetBlood()==0&&event.LeftIsDown())
        {
            bool_select=false;
            this->Refresh();
        }
        else
            if(me.GetBlood()==0&&event.LeftIsDown())
            {
                bool_select=false;
                this->Refresh();
            }
}

void tankFrame::Init()
{
    times=0;
    bool_start=true;
    for(int i=0;i<30;i++)
        for(int j=0;j<30;j++)
            m_map1[i][j]=m_map[i][j];
    me.SetX(320);
    me.SetY(520);
    me.SetDirect(2);
    me.SetBlood(3);
    enemyx[0].SetX(60);
    enemyx[0].SetY(40);
    enemyx[0].SetDirect(0);
    enemyx[0].SetBlood(3);
    enemyx[1].SetX(480);
    enemyx[1].SetY(40);
    enemyx[1].SetDirect(0);
    enemyx[1].SetBlood(2);
    enemyx[2].SetX(40);
    enemyx[2].SetY(520);
    enemyx[2].SetDirect(2);
    enemyx[2].SetBlood(3);
}
