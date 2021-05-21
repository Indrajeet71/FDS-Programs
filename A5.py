def length(x):
    leng = 0
    for _ in x:
        leng += 1
    return leng
    
def sorting(x):
    length = 0
    for i in x:
        length += 1 
    for i in range(length):
        for j in range(i + 1, length):
            if x[i] > x[j]:
                x[i], x[j] = x[j], x[i]
    return x

def longest_string(string1):
    l = {}
    for i in string1:
        l[i] = l.get(i,0) + length(i)
    maxim = list(l.values())
    maxim = sorting(maxim)
    z = maxim[-1]
    for key, value in l.items(): 
         if z == value :
             return key


def char_Search(string1):
    frequency = {}
    for i in string1:
        for j in i:
            frequency[j] = frequency.get(j, 0) + 1
    z = input("Enter the charecter you want to search for ? ") 
    for key, value in frequency.items(): 
         if z == key: 
             return value

def char_occurence(string1):
    frequency = {}
    for i in string1:
        for j in i:
            frequency[j] = frequency.get(j, 0) + 1
    for key, value in frequency.items(): 
             print("The letter: " , key, " is repeated: ", value, " times \n")

def palindrome (string):
    string = string.lower()
    for _ in string :
        rev_string = string[::-1]
    if string == rev_string:
        print("It is a palindrome")
    else:
        print("Not a palindrome")

def substring_occurnce(x) :
    substring = input("Enter the sub string: ")
    substr_index = x.find(substring,0,length(x))
    return(substr_index)

def main():
    Str = input("Enter first string: ")
    str_list = Str.split(" ")
    print("The longest Word in the string is: ", longest_string(str_list))
    print("The Charecter is repeated: ", char_Search(str_list), " times")
    palindrome(Str)
    char_occurence(str_list)
    

if __name__ == '__main__':
    main()
