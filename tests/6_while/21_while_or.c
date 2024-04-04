int main()
{
    int x  = -5;
    int y = 0;

    while (x < 0 && x < -3){
        x++;
        if(x == -2){
            y = 5;
            break;
        }
        else {
            continue;
            break;
        }
    }

    return x + y;
}
