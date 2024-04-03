int main() {
    int i = 3;
    
    while (i < 10) {
        if (i == 5) {
            i++;
            continue;
        }
        if (i == 8) {
            break;
        }
        i++;
    }
    
    
    return i;
}