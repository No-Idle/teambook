vector<int> bxor(vector<int> a,vector<int> b)
{
  assert(p%2==1);int inv2=(p+1)/2;
  int n=0;while((1<<n)<a.size()) ++n;
  a.resize(1<<n);b.resize(1<<n);
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(!(mask & (1<<i))) {int u=a[mask],v=a[mask+(1<<i)];a[mask+(1<<i)]=(u+v)%p;a[mask]=(u-v)%p;}
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(!(mask & (1<<i))) {int u=b[mask],v=b[mask+(1<<i)];b[mask+(1<<i)]=(u+v)%p;b[mask]=(u-v)%p;}
  vector<int> c(1<<n,0);
  for(int mask=0;mask<(1<<n);++mask) {c[mask]=a[mask]*b[mask];c[mask]%=p;}
  for(int i=0;i<n;++i) for(int mask=0;mask<(1<<n);++mask) if(!(mask & (1<<i))) {int u=c[mask],v=c[mask+(1<<i)];c[mask+(1<<i)]=((v-u)*inv2)%p;c[mask]=((u+v)*inv2)%p;}
  return c;
}
