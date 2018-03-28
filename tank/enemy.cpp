#include "enemy.h"

enemy::enemy()
{
    //ctor
}

enemy::enemy(int xx,int yy,int num,int bl)
{
    x=xx;
    y=yy;
    direct_num=num;
    blood=bl;
}

int enemy::GetBlood()
{
    return blood;
}

void enemy::SetBlood(int bl)
{
    blood=bl;
}

void enemy::CutBlood(int db)
{
    blood-=db;
}

wxIcon enemy::GetIcon()
{
    return direct[blood-1][direct_num];
}

void enemy::SetX(int xx)
{
    x=xx;
}

void enemy::SetY(int yy)
{
    y=yy;
}

void enemy::AddX(int dx)
{

    x+=dx;
}

void enemy::AddY(int dy)
{

    y+=dy;
}

int enemy::GetX()
{
    return x;
}

int enemy::GetY()
{
    return y;
}

void enemy::SetDirect(int num)
{
    direct_num=num;
}

int enemy::GetDirect()
{
    return direct_num;
}

enemy::~enemy()
{
    //dtor
}
