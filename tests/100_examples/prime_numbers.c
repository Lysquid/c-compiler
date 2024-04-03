int isPrime(int num) {
    if (num <= 1) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }
    if (num % 2 == 0) {
        return 0;
    }
    
    int i = 3;

    while(i * i <= num) {
        if (num % i == 0) {
            return 0;
        }
        i++;
    }
    
    return 1;
}

int countPrimes(int n) {
    int count = 0;
    int i = 1;
    while(i++ < n) {
        if (isPrime(i)) {
            count++;
        }
    }
    
    return count;
}

int main() {
    int n = 100;
    return countPrimes(n);
}