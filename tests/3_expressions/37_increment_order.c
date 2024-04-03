int main() {
    int a = 0;
    int i = 1;
    a += i++;
    a *= 10;
    a += ++i;
    a *= 10;
    a += 1+1*++i+1;
    return a;
}