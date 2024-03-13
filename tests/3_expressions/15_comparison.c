int main() {
    int a = 1;
    int b = 2;
    int c = (a < b) + (a <= b)*2 + (a > b)*4 + (a >= b)*8 + (a == b)*16;
    return c;
}