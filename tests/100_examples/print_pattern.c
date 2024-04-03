
void printPattern(int rows) {
    int i = 0;
    while (i++ <= rows) {
        int j = 1;
        while (j++ <= i) {
            putchar('*');
        }
        putchar(' ');
    }
}

int main() {
    int num_rows = 5;

    printPattern(num_rows);
    return 0;
}