#include <cstdio>
#include <cstdlib>
#include <list>
using namespace std;

//function to print the solution of the input sudoku after all computations
void print(int **arr){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

//function that returns a 'list' of all possible values from 1 to 9 that can occupy the cell given by 'row' and 'column'
list<int> find(int **arr,int row,int col){
    list<int> poss;
    int possible[9] = {1,1,1,1,1,1,1,1,1};                          //array to keep track of which values are possible; value of the (i-1)th element will be made zero if (i)th element is not possible; initially all elements are set to 'possible'
    for(int i=0;i<9;i++){
        if(arr[row][i]!=0){
            possible[arr[row][i]-1]=0;                              //if a number in the same row as that of the cell has been found, remove that 'number' from the 'possibility list' of the cell
        }
	}
	for(int j=0;j<9;j++){
        if(arr[j][col]!=0){
            possible[arr[j][col]-1]=0;                              //if a number in the same column as that of the cell has been found, remove that 'number' from the 'possibility list' of the cell
        }
	}
	int blockrow=(row/3)*3;                                           //find the first among the group of three rows making up the medium sized 9 squares of 3x3
	int blockcol=(col/3)*3;                                           //find the frst among the group of three columns making up the medium sized 9 squares of 3x3
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
            if(arr[blockrow+i][blockcol+j]!=0){
                possible[arr[blockrow+i][blockcol+j]-1]=0;          //if a number in the same medium sized square of 3x3 as that of the cell has been found, remove that 'number' from the 'possibility list' of the cell
			}
		}
	}
	                                                                  //we now have the final 'possibility list' ready
	for(int k=0;k<9;k++){
        if(possible[k]!=0){
            poss.push_back(k+1);                                    //store the possible values in a 'list' by comparing with the values stored in the array used to keep track of possible values
        }
	}
	return poss;
}

//function which return '1' if the sudoku can be solved else returns '0' by assigning easch value from the 'possibility list' one by one and checking if the modified sudoku can then be solved using recursive function call. If a zero is returned by the recursive call, either the next valu from the 'possibility list' is tried or else 'No solution possible is printed'
int solve(int **arr, int row, int col){
    if(row>=9 || col>=9 ){                                          //if index of row or column is out of bounds i.e. greater than or equal to 9 (zero indexing) return 1 meaning sudoku is solvable and has been solved
        return 1;
    }
	if(arr[row][col]==0){                                             //the cell in question has no value filled in yet
        list<int> possible = find(arr,row,col);                     //'possibility list' is obtained
        if(possible.empty()){
            return 0;                                               //sudoku is unsolvable if 'possibility list' is empty hence return 0
        }
        while(!possible.empty()){                                   //if possibility list is not empty
            int choice=possible.front();                            //take the first element in the list
            possible.pop_front();
            arr[row][col]=choice;                                   //set the cell with the value from the 'possibility list'
            int check=solve(arr,(row*9+col+1)/9,(row*9+col+1)%9);   //check if the modified sudoku is solvable. 'check' is '0' if it is unsolvable meaning either 'no solution exists' or 'the value of the cell has been wrongly set'. 'check' is '1' if it is solvable. The sudoku has already been solved in that case.
            if(check==1){
                return 1;                                           //return 1 if the sudoku has been correctly solved from the input state
            }
        }
        arr[row][col] = 0;                                          //if all elements from the 'posibility list' have been exhausted without getting a valid sudoku solution, set the value of the cell to '0' meaning it is undecided
        return 0;                                                   //then return '0' meaning the sudoku cannot be solved from the configuration
    }else{                                                          //if the cell has already been filled with a number from 1 to 9, return if the modified sudoku cofiguration can be solved or not
        return solve(arr,(row*9+col+1)/9,(row*9+col+1)%9);
    }
}

//main program body
int main(){
	int **arr=new int*[9];
	for(int i=0;i<9;i++){
    arr[i]=new int[9];
	}
	for(int row=0;row<9;row++){
    for(int col=0;col<9;col++){
      scanf("%d",&arr[row][col]);                                   //input each cell value of the sudoku
    }
  }
	if(solve(arr,0,0)){                                               //if sudoku is solved
		print(arr);                                                     //print the solutin
	}else{                                                            //if sudoku cannot be solved
    printf("No solution exists\n");                                 //print no 'no solution exists'
	}
	return 0;
}
