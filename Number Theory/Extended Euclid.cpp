int exgcd(int a, int b, int &x, int &y){
  if(!b){ x=1; y=0; return a; }
  long long x1,y1; long long g=exgcd(b,a%b,x1,y1);
  x=y1; y=x1 - (a/b)*y1;
  return g;
}
