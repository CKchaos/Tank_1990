#include "missile.h"

missile::missile()
{
    //ctor
}

missile::missile(int xx,int yy,int num)
{
    x=xx;
    y=yy;
    direct_num=num;
    state=1;
    if(num==0)
    {
        x+=20;
        y+=40;
        dx=0;
        dy=20;
    }
    if(num==1)
    {
        y+=20;
        dx=-20;
        dy=0;
    }
    if(num==2)
    {
        x+=20;
        dx=0;
        dy=-20;
    }
    if(num==3)
    {
        x+=40;
        y+=20;
        dx=20;
        dy=0;
    }
}

int missile::GetX()
{
    return x;
}

int missile::GetY()
{
    return y;
}

void missile::SetState(int a)
{
    state=a;
}

int missile::GetState()
{
    return state;
}

int missile::GetDirect()
{
    return direct_num;
}

void missile::UpdateXY()
{
    if(x<=0||x>=600||y<=0||y>=600)
        state=0;
    else
    {
        x+=dx;
        y+=dy;
    }
}

missile::~missile()
{
    //dtor
}
