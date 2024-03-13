
int func1(int a, int b)
{
    return a + b;
}

int func2(int a, int b)
{
    return func1(a,b);
}

int func3(int a, int b)
{
    return func2(a, b);
}

int main()
{
    int a = getchar();
    return func3(1, a);
}
