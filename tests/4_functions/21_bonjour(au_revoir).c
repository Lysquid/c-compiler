int bonjour(int a, int b)
{
    return a + b;
}

int au_revoir(int c){
    int a = 5;
    return a + c;
}

int main()
{
    int a = bonjour(1,au_revoir(7));
    return a;
}
