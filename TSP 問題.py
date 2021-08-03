str1=input("please input string1:")
str2=input("please input string2:")

len1=len(str1)
len2=len(str2)

mat=[[0]*(len2+1) for i in range(len1+1)]


for i in range(0,len1+1):
    for j in range(0,len2+1):
        if(i==0 or j==0):
            mat[i][j]=0
        elif(str1[i-1]==str2[j-1]):        #比對一樣的時候
            mat[i][j]=mat[i-1][j-1]+1
        else:                             #比對不一樣的時候
            mat[i][j]=max(mat[i-1][j],mat[i][j-1])
print("動態規劃計算表格:")
print("  ",end='')
for i in range(0,len2):
    print(str2[i],end=' ')
print()            
for i in range(1,len1+1):
    print(str1[i-1],end=' ')
    for j in range(1,len2+1):
        print(mat[i][j],end=' ')
    print()
print()
temp_i=len1
temp_j=len2


result=""    #結果子序列

while(mat[temp_i][temp_j]!=0):
    if(str1[temp_i-1]==str2[temp_j-1]):
        result=result+str1[temp_i-1]
        temp_i=temp_i-1
        temp_j=temp_j-1
    elif(str1[temp_i-1]!=str2[temp_j-1]):
        if(mat[temp_i-1][temp_j]==mat[temp_i][temp_j]):
            temp_i=temp_i-1
        elif(mat[temp_i][temp_j-1]==mat[temp_i][temp_j]):
            temp_j=temp_j-1
print("LCS:",''.join(reversed(result)))





