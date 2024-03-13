
int func1(int a, int b)
{
    return (a-b);
}

int func2(int a, int b)
{
    return func1(a,b);
}

int func3(int a, int b)
{
    int c = func2(a, b);
    int d = -a+b+-c-(+b+c+a)+-10-+23+a;
    int e = a/-c*+b+-(a*b/c*a)-+(a+-b+c-d)*-a;
    return d-e;
}

void func4(int a, int b)
{
}

int main()
{
    func4(1, 2);
    return func1(3,4) * (func3(1, 2) + func2(2,4)) ;
}
