"""
Write a Pythonprogram to compute following computation on matrix:
a)Addition of two matrices     b) Subtraction of two matrices
c) Multiplication of two matrices  d) Transpose of a matrix
"""

from numpy import array

def add(a,b,res):
    for i in range(len(a)):
        for j in range(len(b[0])):
            res[i][j]+=a[i][j]+b[i][j]
    return res

def sub(a,b,res):
    for i in range(len(a)):
        for j in range(len(b[0])):
            res[i][j]+=a[i][j]-b[i][j]
    return res

def mul(a,b,res):
    
    for i in range(len(a)):#number of rows in a
        for j in range(len(b[0])):#number of column in b
            for k in range(len(b)):#number of rows in b
                res[i][j]+=a[i][k]*b[k][j]
    return res

def trans(a):
    result=[]
    for i in range(len(a)):
        for i in range(len(a[0])):
            result.append(0)
    
    res=array(result)
    res1=res.reshape(len(a[0]),len(a))

    for i in range(len(a)):
        for j in range(len(a[0])):
            res1[j][i]=a[i][j]  
    return res1

def get_data():
    print("Enter Data For Matrix 1")
    r1=int(input("Enter No. of Rows:"))
    c1=int(input("Enter No. of Columns:"))

    matrix1=[]
    for i in range(r1):
        for j in range(c1):
            print("Enter Value of ",i,j,":", end=" ")
            a_input=int(input())
            matrix1.append(a_input)

    a=array(matrix1)
    a1=a.reshape(r1,c1)
    print(a1)
    
    print("\nEnter Data For Matrix 2")
    r2=int(input("Enter No. of Rows:"))
    c2=int(input("Enter No. of Columns:"))

    matrix2=[]
    for i in range(r2):
        for j in range(c2):
            print("Enter Value of ",i,j,":", end=" ")
            b_input=int(input())
            matrix2.append(b_input)

    b=array(matrix2)
    b1=b.reshape(r2,c2)
    print(b1)

    result=[]
    for i in range(r1):
        for i in range(c2):
            result.append(0)
    
    res=array(result)
    res1=res.reshape(r1,c2)

    print("\nselect Operation You Want to Do:")
    print("1:Addition\n2:Subtraction\n3:Multiplication\n4:Transpose")

    ch=int(input("\nEnter Your Choice:"))
    if(ch==1):
        if(r1==r2 and c1==c2):
            print(add(a1,b1,res1))
        else:
            print("Enter Valid Matrix")

    if(ch==2):
        if(r1==r2 and c1==c2):
            print(sub(a1,b1,res1))
        else:
            print("Enter Valid Matrix")

    if(ch==3):
        if(r2==c1):
            print(mul(a1,b1,res1))
        else:
            print("Enter valid Matrix")

    if(ch==4):
        print(trans(a1))
        print(trans(b1))
        
def main():
    get_data()

if __name__ == '__main__':
    main()