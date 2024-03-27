

int func1(int a, int b, int c){
    int d = 0;
    if (a > b)
    {
        d = a;
        return 3*d;
    } else if (c == 0){
        d *= b;
        return 1;
    }
    return 2*d;

}

int main() {
    int a;
    a = -10;
    int b;
    b = 10;
    int x;
    x = 5;

    if(a > b){
        if(!( a == x )){
            x = func1(b, b, x);
            return x;
        }else{
            x = func1(a, b, x);
            return x;
        }
    }else{
       x = func1(a, b, x);
       return a+b;
    }

    x = func1(a, b, x);
    return x;
}
