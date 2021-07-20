#include<iostream>
#include<climits>  
#include <algorithm>
#include <vector>   
using namespace std;
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2,vector< vector<int> > &dp,vector< vector<char>> &flag) {
        //  先计算两条字符串的长度
        int m = text1.size();
        int n = text2.size();
        
        //  构建dp矩阵  默认初始值0
	//  这里会多扩建一边和一列  
 	//  因为dp[i][j]的含义是：对于 s1[1..i] 和 s2[1..j]，它们的LCS长度是 dp[i][j]。
	//  所以当i或者j为零时  LCS的长度默认为0
    //  进行比较时也进行标记，分为i行j列，算法是自顶向上的，所以是往上走或者是往左走。
        dp.resize(m+1);
        flag.resize(m+1);
        for(int i = 0; i < dp.size(); ++i){
            dp[i].resize(n + 1);
        }
        for(int i = 0; i < dp.size(); ++i){
            flag[i].resize(n + 1);
        }
            
        //  状态转移
	//  i、j都从1开始遍历  因为下面的操作中都会-1  相当于从0开始  
        for ( int i=1 ; i<m+1 ; i++ ){
            for ( int j=1 ; j<n+1 ; j++ ){
                //  如果text1和text2相同
                //  就在它们的前一位基础上加一
                //  如果不同  只能在之前的两者中去最大
        //        dp[i][j] = (text1[i-1] == text2[j-1]) ? dp[i-1][j-1] + 1 : max( dp[i-1][j] , dp[i][j-1] );
                if (text1[i-1] == text2[j-1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    flag[i][j] = 'c';//相同标记为correct
                }else if( dp[i-1][j]>=dp[i][j-1])//不相同时，划分为两个子序列问题
                {
                    dp[i][j] = dp[i - 1][j];
                    flag[i][j] = 'u';//标记向上（往上走，即i-1）
                }else 
                {
                    dp[i][j] = dp[i][j-1];
                    flag[i][j] = 'l';//标记向左（往上走，即j-1）
                }
            }
        }

        //  返回最终右下角的值
        return dp[m][n];
    }
  
};

  void print_lcs(vector< vector<char>> &flag,string X, int i, int j)
    {
        if(i == 0 || j == 0)
            return;
        if(flag[i][j] == 'c'){
            print_lcs(flag,X,i-1,j-1);
            cout << X[i-1];
        }else if(flag[i][j] == 'u')
            print_lcs(flag,X,i-1,j);//u表示dp[i-1][j]序列更大，往上走，这里把相等情况也归为向上走。
        else
            print_lcs(flag,X,i,j-1);//l表示dp[i][j-1]序列更大，往左走
    }

int main()
{
    string X= "AGGTAB"; 
    string Y = "GXTXAYB";
    Solution mysolution;
    vector<vector<int>> dp;
    vector<vector<char>> flag;
    int LCS=mysolution.longestCommonSubsequence(X, Y,dp,flag);
    cout << "the length is " << LCS << endl;
    print_lcs(flag, X, X.size(), Y.size());
    system("pause");
    return	0;
}
