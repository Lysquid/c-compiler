int main()
{
    int x  = -5;
    int y = 0;

    while (x < 0){
        if(x == -4){
            x++;
            y = y + 5;
            continue;
        }
        if(x == -3){
            x++;
            y++;
            continue;
        }
        else {
            x++;
            continue;
        }
    }

    return x + y;
}
