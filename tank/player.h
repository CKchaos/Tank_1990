#include <wx/icon.h>

#ifndef PLAYER_H
#define PLAYER_H

class player
{
    public:
        player();
        player(int xx,int yy,int num);
        wxIcon direct[4];
        wxIcon GetIcon();
        void SetX(int xx);
        void SetY(int yy);
        void AddX(int dx);
        void AddY(int dy);
        int GetX();
        int GetY();
        void SetDirect(int num);
        int GetDirect();
        int GetBlood();
        void SetBlood(int bl);
        void CutBlood(int db);
        virtual ~player();
    protected:
    private:
        int direct_num;
        int x,y;
        int blood=3;
};

#endif // PLAYER_H
