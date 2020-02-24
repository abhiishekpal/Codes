/*input





*/

#include <iostream>
#define ll long long int
using namespace std;

struct cord{
	int x,y;
};
struct dir{
	int dir[4];
};

cord poles[100001];
dir fence[100001];
int arr[100001];


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
        if(cord[L[i]].x < cord[R[j]].x){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else if(cord[L[i]].x > cord[R[j]].x){ 
            arr[k] = R[j]; 
            j++; 
        } 
        else if(cord[L[i]].x == cord[R[j]].x){ 
            if(cord[L[i]].y < cord[R[j]].y){ 
	            arr[k] = L[i]; 
	            i++; 
	        } 
	        else if(cord[L[i]].y > cord[R[j]].y){ 
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

int dfs(int start, int prev_idx, int curr_idx, int dir, int n){


	if(curr_idx==start && dir!=-1){
		return 1;
	}

	if(dir==-1){
		if(fence[curr_idx].dir[0]!=-1 && fence[fence[curr_idx].dir[0]].dir[2]!=-1){
			fence[curr_idx].dir[0] = -1;
			int val = dfs(start, curr_idx, fence[curr_idx].dir[0], 2, n);
			if(val==1){
				return 1;
			}
		}
		else
			return 0;

	}
	else{
		if(fence[curr_idx][(dir+1)%4]!=-1 && fence[fence[curr_idx].dir[(dir+1)%4]].dir[((dir+1)%4+2)%4]!=-1){
			fence[curr_idx].dir[(dir+1)%4]=-1;
			int val = dfs(start, curr_idx, fence[curr_idx][(dir+1)%4], ((dir+1)%4+2)%4, n);
			if(val==1){
				return 1;
			}
		}
		if(fence[curr_idx][(dir+3)%4]!=-1 && fence[fence[curr_idx].dir[(dir+3)%4]].dir[((dir+3)%4+2)%4]!=-1){
			fence[curr_idx].dir[(dir+3)%4]=-1;
			int val = dfs(start, curr_idx, fence[curr_idx][(dir+3)%4], ((dir+3)%4+2)%4, n);
			if(val==1){
				return 1;
			}
		}
		if(fence[idx][(dir+4)%4]!=-1 && fence[fence[curr_idx].dir[(dir+4)%4]].dir[((dir+4)%4+2)%4]!=-1){
			fence[idx].dir[(dir+4)%4]=-1;
			int val = dfs(start, curr_idx, fence[idx][(dir+4)%4], ((dir+4)%4+2)%4, n);
			if(val==1){
				return 1;
			}
		}
		
	}
	return 0;

}

int main(){

	ios::sync_with_stdio(false);

	int T;cin>>T;
	while(T--){
		
		int n;cin>>n;
		for(int i=0;i<n;i++){
			int x,y;cin>>x>>y;
			cord[i+1].x = x;
			cord[i+1].y = y;
			arr[i] = i+1;
		}
		int m;cin>>m;
		for(int i=0;i<m;i++){
			int a,b;cin>>a>>b;
			int x1 = cord[a].x;
			int y1 = cord[a].y;
			int x2 = cord[b].x;
			int y2 = cord[b].y;
			for(int j=0;j<4;j++){
				fence[a].dir[j]=-1;
				fence[b].dir[j]=-1;
			}
			if(x1>x2){
				fence[a].dir[1] = b;
				fence[b].dir[3] = a;
			}
			else if(x1<x2){
				fence.dir[a][3] = b;
				fence.dir[b][1] = a;
			}
			else if(y1>y2){
				fence[a].dir[2] = b;
				fence[b].dir[0] = a;
			}
			else if(y1<y2){
				fence[a].dir[0] = b;
				fence[b].dir[2] = a;
			}
		}
		mergeSort(0, n-1);


		for(int i=0;i<n;i++){
			if(visited[i]==0){

				int val = dfs(i, -1, i, -1, n);

			}
		}


		




	}





	return 0;
}