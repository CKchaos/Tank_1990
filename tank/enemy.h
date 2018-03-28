#include "player.h"

#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
    public:
        enemy();
        enemy(int xx,int yy,int num,int bl);
        wxIcon direct[3][4];
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
        virtual ~enemy();
    protected:
    private:
        int direct_num;
        int x,y;
        int blood;
};

#endif // ENEMY_H
