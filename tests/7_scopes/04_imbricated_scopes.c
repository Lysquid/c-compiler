int main() {
    int a = 1;
    int b = 1;
    int c = 1;
    int d = 1;
    {
        a = 2;
        int b = 2;
        c = 2;
        int d = 2;
        {
            a = 3;
            b = 3;
            int c = 2;
            int d = 2;
        }
    }
    return a + b + c + d;
}