#ifndef MISSILE_H
#define MISSILE_H


class missile
{
    public:
        missile();
        missile(int xx,int yy,int num);
        int GetX();
        int GetY();
        void SetState(int a);
        int GetState();
        int GetDirect();
        void UpdateXY();
        virtual ~missile();
    protected:
    private:
        int x=-10,y=-10,dx,dy,state=0,direct_num;
};

#endif // MISSILE_H
