int main() {
    int a;
    int b;
    int c;
    a = !2;
    b = !a;
    c = !(a + b * 4 / a);
    return a + b + c;
}
