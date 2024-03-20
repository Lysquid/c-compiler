int main() {
    int a;
    a = -10;
    int b;
    b = 10;
    int x;
    x = 5;
    
    if(a > b){
        if(!( a == x )){
            x = a + b;
        }else{
            x = a - b;
        }
    }else{
        x = a;
    }
    return x;
}
