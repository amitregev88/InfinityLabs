
typedef struct
{
    int m_x;
    int m_y;
}Point;



Point point(int x, int y)
{
    Point p;

    p.m_x = 0;
    p.m_y = 0;

    return p;
}

typedef struct
{
    char dummy;
}A;

typedef struct
{
    int x;
    int y;
    Point p;
}B;


B ctorB()
{
    B b;
    b.p = point(0,0);

    return b;
}

B Bctor(const B *const ptr)
{
    B bb = *ptr;
    
    return bb;
}



int main()
{
    A a ;   

    B b = ctorB();


    B b2 = Bctor(&b);
    b2 = b;
    return 0;
}