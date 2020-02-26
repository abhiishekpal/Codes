/*input
1
15
1 1
1 8
2 3
2 5
4 2
4 3
4 5
4 6
4 8
6 3
6 5
7 2
7 6
8 1
8 8 
17
1 2
1 14
2 9
3 4 
3 6
4 7
5 6
5 12
6 10
7 11
7 8
8 9
8 13
9 15
10 11
12 13
14 15



*/

#include <iostream>
#define ll long long int
using namespace std;

struct cord{
	int x,y;
};
struct direction{
	int direc[4];
};

cord expec[100001];
cord poles[100001];
direction fence[100001], fence2[100001];
int arr[100001];

int ans = 0;
void merge(int l,int m,int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    int L[n1], R[n2]; 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j];   
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2){ 
        if(poles[L[i]].x < poles[R[j]].x){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else if(poles[L[i]].x > poles[R[j]].x){ 
            arr[k] = R[j]; 
            j++; 
        } 
        else if(poles[L[i]].x == poles[R[j]].x){ 
            if(poles[L[i]].y < poles[R[j]].y){ 
	            arr[k] = L[i]; 
	            i++; 
	        } 
	        else if(poles[L[i]].y > poles[R[j]].y){ 
	            arr[k] = R[j]; 
	            j++; 
        	}
        } 
       
        k++; 
    }
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2){ 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int l,int r) 
{ 
    if (l < r){ 
        int m = l+(r-l)/2; 
        mergeSort(l, m); 
        mergeSort(m+1, r); 
        merge(l, m, r); 
    } 
} 
void update(int curr_idx, int dir, int idx){
	if(!(fence[curr_idx].direc[(dir+idx)%4]==-1 && fence[fence2[curr_idx].direc[(dir+idx)%4]].direc[((dir+idx)%4+2)%4]==-1)){
		fence[curr_idx].direc[(dir+idx)%4] = -2;
		fence[fence2[curr_idx].direc[(dir+idx)%4]].direc[((dir+idx)+2)%4] = -2;
		ans++;
	}
}
int dfs(int start, int prev_idx, int curr_idx, int dir, int n){
 

	if(fence[prev_idx].direc[(dir+2)%4]<0)
		return 0;
	

	if(dir!=-1)
	fence[prev_idx].direc[(dir+2)%4] = -1;


	if(curr_idx==start && dir!=-1)
		return 1;


	if(dir==-1){
		int val = dfs(start, curr_idx, fence[curr_idx].direc[0], 2, n);
		if(val==1){
			// update(curr_idx, dir, 0);
			if(!(fence[curr_idx].direc[(0)%4]==-1 && fence[fence2[curr_idx].direc[(0)%4]].direc[((0)%4+2)%4]==-1)){
				fence[curr_idx].direc[dir%4] = -2;
				fence[fence2[curr_idx].direc[dir%4]].direc[(dir+2)%4] = -2;
				ans++;
			}
			return 1;
		}
		
	}
	else{
		int val;
		val = dfs(start, curr_idx, fence[curr_idx].direc[(dir+3)%4], ((dir+3)%4+2)%4, n);
		if(val==1){
			update(curr_idx, dir, 3);
			// if(!(fence[curr_idx].direc[(dir+3)%4]==-1 && fence[fence2[curr_idx].direc[(dir+3)%4]].direc[((dir+3)%4+2)%4]==-1)){
			// 	fence[curr_idx].direc[(dir+3)%4] = -2;
			// 	fence[fence2[curr_idx].direc[(dir+3)%4]].direc[((dir+3)%4+2)%4] = -2;
			// 	ans++;
			// }
			
			return 1;
		}
		val = dfs(start, curr_idx, fence[curr_idx].direc[(dir+2)%4], ((dir+2)%4+2)%4, n);
		if(val==1){
			update(curr_idx, dir, 2);
			// if(!(fence[curr_idx].direc[(dir+2)%4]==-1 && fence[fence2[curr_idx].direc[(dir+2)%4]].direc[((dir+2)%4+2)%4]==-1)){
			// 	fence[curr_idx].direc[(dir+2)%4] = -2;
			// 	fence[fence2[curr_idx].direc[(dir+2)%4]].direc[((dir+2)%4+2)%4] = -2;
			// 	ans++;
			// }
			
			return 1;
		}
		val = dfs(start, curr_idx, fence[curr_idx].direc[(dir+1)%4], ((dir+1)%4+2)%4, n);
		if(val==1){
			update(curr_idx, dir, 1);
			// if(!(fence[curr_idx].direc[(dir+1)%4]==-1 && fence[fence2[curr_idx].direc[(dir+1)%4]].direc[((dir+1)%4+2)%4]==-1)){
			// 	fence[curr_idx].direc[(dir+1)%4] = -2;
			// 	fence[fence2[curr_idx].direc[(dir+1)%4]].direc[((dir+1)%4+2)%4] = -2;
			// 	ans++;
			// }
			
			return 1;
		}
		val = dfs(start, curr_idx, fence[curr_idx].direc[(dir)%4], ((dir)%4+2)%4, n);
		if(val==1){
			update(curr_idx, dir, 0);
			// if(!(fence[curr_idx].direc[(dir)%4]==-1 &&  fence[fence2[curr_idx].direc[(dir)%4]].direc[((dir)%4+2)%4]==-1)){
			// 	fence[curr_idx].direc[dir%4] = -2;
			// 	fence[fence2[curr_idx].direc[dir%4]].direc[(dir+2)%4] = -2;
			// 	ans++;
			// }
			
			return 1;
		}
	}
	return 0;

}


int main(){

	ios::sync_with_stdio(false);

	int T;cin>>T;
	int tc=1;
	while(T--){
		
		int n;cin>>n;
		for(int i=0;i<n;i++){
			int x,y;cin>>x>>y;
			poles[i+1].x = x;
			poles[i+1].y = y;
			arr[i] = i+1;
		}
		int m;cin>>m;
		for(int i=0;i<m;i++){
			int a,b;cin>>a>>b;
			expec[i].x = a;
			expec[i].y = b;
			for(int j=0;j<4;j++){
				fence[a].direc[j]=-2;
				fence[b].direc[j]=-2;
			}
		}
		for(int i=0;i<m;i++){
			int a = expec[i].x;
			int b = expec[i].y;                                                                                                                                                                                                                                                                                                                                                                                                                                                     
			int x1 = poles[a].x;
			int y1 = poles[a].y;
			int x2 = poles[b].x;
			int y2 = poles[b].y;
			
			if(x1>x2){
				fence[a].direc[1] = b;
				fence[b].direc[3] = a;
				fence2[a].direc[1] = b;
				fence2[b].direc[3] = a;
			}
			else if(x1<x2){
				fence[a].direc[3] = b;
				fence[b].direc[1] = a;
				fence2[a].direc[3] = b;
				fence2[b].direc[1] = a;
			}
			else if(y1>y2){
				fence[a].direc[2] = b;
				fence[b].direc[0] = a;
				fence2[a].direc[2] = b;
				fence2[b].direc[0] = a;
			}
			else if(y1<y2){
				fence[a].direc[0] = b;
				fence[b].direc[2] = a;
				fence2[a].direc[0] = b;
				fence2[b].direc[2] = a;
			}
		}
		mergeSort(0, n-1);
		ans = 0;

		for(int i=0;i<n;i++){
			int val = dfs(arr[i], -1, arr[i], -1, n);
			fence[arr[i]].direc[0]=-2;
			fence[fence2[arr[i]].direc[0]].direc[2]=-2;
		}
		
		cout<<"#"<<tc<<" "<<m-ans<<endl;
		tc++;

	}
	return 0;
}
