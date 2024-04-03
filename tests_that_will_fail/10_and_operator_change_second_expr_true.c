int main(){
  int a,b,c;
  a = 5;
  b = 10;
  c = 7;
  if((a < b) && (a = 3)){
    c = 10;
  } else{
    c = 50;
  }
  return c + a;
}
