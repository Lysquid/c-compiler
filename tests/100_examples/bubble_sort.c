int main() {
    int a = 7;
    int b = 4;
    int c = 5;
    int d = 3;
    int e = 1;

    int i = 0;
    while(i++ < 5){
        int tmp;
        if(a > b){
            tmp = a;
            a = b;
            b = tmp;
        }
        
        if(b > c){
            tmp = b;
            b = c;
            c = tmp;
        }

        if(c > d){
            tmp = c;
            c = d;
            d = tmp;
        }

        if(d > e){
            tmp = d;
            d = e;
            e = tmp;
        }
    }
    putchar(a + '0');
    putchar(b + '0');
    putchar(c + '0');
    putchar(d + '0');
    putchar(e + '0');
    
    return 0;
}