int bonjour(int a, int b)
{
    return a + b;
}

int main()
{
    int a = bonjour(bonjour(5,43),bonjour(7,66));
    return a;
}
