#include "player.h"

player::player()
{
    //dtor
}

player::player(int xx,int yy,int num)
{
    x=xx;
    y=yy;
    direct_num=num;
}

wxIcon player::GetIcon()
{
    return direct[direct_num];
}

void player::SetX(int xx)
{
    x=xx;
}

void player::SetY(int yy)
{
    y=yy;
}

void player::AddX(int dx)
{

    x+=dx;
}

void player::AddY(int dy)
{

    y+=dy;
}

int player::GetX()
{
    return x;
}

int player::GetY()
{
    return y;
}

void player::SetDirect(int num)
{
    direct_num=num;
}

int player::GetDirect()
{
    return direct_num;
}

int player::GetBlood()
{
    return blood;
}

void player::SetBlood(int bl)
{
    blood=bl;
}

void player::CutBlood(int db)
{
    blood-=db;
}

player::~player()
{
    //dtor
}
