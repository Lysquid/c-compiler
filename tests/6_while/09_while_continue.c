int main()
{
    int x  = -5;

    while (x < 0){
        if(x%2 == 0){
            x += 2;
            continue;
        }
        x += 1;
    }

    return x;
}
