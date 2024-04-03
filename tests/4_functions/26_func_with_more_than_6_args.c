int func3(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j){
  return a+b+c+d+e+f+g+h+i+j;
}

int func2(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j){
  return a+b+c+d+e+f+g+h+func3(i,1,2,3,4,5,6,7,8,9)+j;
}

int func1(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j){
  return a+b+c+d+e+f+g+h+i+func2(j,1,2,3,4,5,6,7,8,9);
}

int main(){
  int b = 10;
  int a = func1(1,2,3,4,5,6,7,8,9,b);
  return a;
} 