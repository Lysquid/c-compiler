int main()
{
    int x  = -5;
    int y = 0;

    while (x < 0){
        x = x+1;
        continue;
        y++;
    }

    return x + y;
}
