class B
{
public:
    void SetX();
    void SetY();

private:

    int x;
    int y;
};

void B::SetX(int inX)
{

    x = inX;

}


void B::SetY(int inY)
{
    y = inY;

}

int main()
{
    //...
    B b;

    b.Set(5);
    b.SetY(6);

    return 0;

}