#include<iostream>

using namespace std;

int flipsrequired(int len, int k){
  return len/(k+1);
}

int main(){
  int T;cin>>T;

  while(T--){
    int len,k;cin>>len>>k;
    char str[len];cin>>str;

    int shortened_string[len];
    for(int i=0;i<len;i++)
      shortened_string[i] = 0;


    int coun = 1;
    char prev = str[0];
    int idx = 0;
    for(int i=1;i<len;i++){
      if(prev!=str[i]){
        shortened_string[idx] = coun;
        prev = str[i];
        idx++;
        coun=1;
      }
      else{
        coun++;
      }
    }
    shortened_string[idx]=coun;
    

    // check for alternate 1 and 0
    int flips = 0;
    for(int i=0;i<len;i++){
      if(i%2==0 && str[i]!='0')
        flips+=1;
      if(i%2==1 && str[i]!='1')
        flips+=1;
    }
    if(flips<=k){
      cout<<1<<endl;
      continue;
    }


    flips = 0;
    for(int i=0;i<len;i++){
      if(i%2==0 && str[i]!='1')
        flips+=1;
      if(i%2==1 && str[i]!='0')
        flips+=1;
    }
    if(flips<=k){
      cout<<1<<endl;
      continue;
    }

    // check for more the 1 continuos zero and one

    int high = len;
    int low = 2;
    int mid;
    while(low<high){
      // cout<<low<<" "<<high<<endl;
      mid = (low+high)/2;
      int tempk = 0;
      for(int i=0;i<=idx;i++){
        // cout<<i<<" "<<shortened_string[i]<<endl;
        // cout<<i<<" *** "<<flipsrequired(shortened_string[i],mid)<<endl;
        tempk += flipsrequired(shortened_string[i],mid);
      }
      // cout<<mid<<" "<<tempk<<" "<<k<<endl;
      if(tempk<=k){
        high = mid;
      }
      else{
        low = mid+1;
      }
    }

    cout<<high<<endl;

  }

}
