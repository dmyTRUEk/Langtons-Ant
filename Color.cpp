/*
 this file contains COLOR class

 created by dmyTRUEk 11.10.2019

 v1.0 - 11.10.2019

 */





class Color
{
public:
    int r, g, b;

    Color (int _r=0, int _g=0, int _b=0)
    {
        init(_r, _g, _b);
    }

    void init (int _r=0, int _g=0, int _b=0)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    void operator = (int arr[])
    {
        init(arr[0], arr[1], arr[2]);
    }
};
