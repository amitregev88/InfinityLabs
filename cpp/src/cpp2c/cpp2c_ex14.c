typedef struct 
{

    int x_;
    int y_;


}Base;

typedef struct 
{

    Base b;
    int z_;
    


}Derived;

void CBase(Base *b, int inX, int inY)
{
    b->x_ = inX;
    b->y_ = inY;
}

void CDerived(Derived *d, int inX, int inY, int inZ)
{
    CBase(&(d->b),inX,inY);
    d->z_ = inZ;
}

int main()
{


    return 0;
}

