# ps
# Write a program to implement an address book with options given below: a) Create address
# book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit


#!/bin/bash
filename="records.txt"                                      # file where we are going to store record

#  function to create a create a record
function createRecord(){
    read -p $'\nEnter no of students details to be recorded:- ' noOfRecords;
    for((i=0; i<noOfRecords;i++))
    do 
        echo -e "\nDetails for  `expr $i + 1` student"
        read -p $'Enter Name:- ' name
        read -p $'Enter Contact no:- ' contact
        while [ ${#contact} -ne 10 ]
        do
            read -p "Enter valid and unique Contact Number: " contact
        done
        if [ $i -gt 0 ]
        then
            while grep -q $contact $filename
            do
                read -p "Record for following contact no is already present!! Enter  unique Contact Number: " contact
            done
        fi               
        read -p $'Enter City:- ' city
        read -p $'Enter Zip Code:- ' zipcode
        echo -e "$name\t$contact\t$city\t$zipcode" >> "$filename"
        echo -e $"\nADDITION SUCCESSFULL"
    done
}

# function to add a particular record 
function addRecord(){
    echo -e $"\nADDING A RECORD\n"                              
    read -p $'Enter Name:- ' name
    read -p $'Enter Contact no:- ' contact
    while [ ${#contact} -ne 10 ]
    do
        read -p "Enter valid and unique Contact Number: " contact
    done
    while grep -q $contact $filename
    do
        read -p "Record for following contact no is already present!! Enter  unique Contact Number: " contact
    done                 
    read -p $'Enter City:- ' city
    read -p $'Enter Zip Code:- ' zipcode
    echo -e "$name\t$contact\t$city\t$zipcode" >> "$filename"
    echo -e $"\nADDITION SUCCESSFULL"
}

#function to display record
function display(){
    echo -en "\nDISPLAYING RECORD\n"
    if test -f "$filename"
    then
        echo -e "\n"
        while read line
        do
            echo $line
        done < $filename
    else
        echo -e "\nFile not created yet."
    fi
}

# function to search record
function search(){
    read -p $'\n Enter contact number to be searched: ' contact
    while [ ${#contact} -ne 10 ] && grep -q $contact $filename
    do
        read -p "Enter valid  Contact Number: " contact
    done
    if (grep -q $contact $filename) 
    then
        echo -e '\nRecord Found!\n'
        (grep -r -w $contact $filename)
    else
        echo -e $'\nRecord unavailable.'
    fi
}

#function to delete a record
function deleteR(){
    read -p $'\n Enter contact number to be deleted: ' contact
    while [ ${#contact} -ne 10 ] && grep -q $contact $filename
    do
        read -p "Enter valid  Contact Number: " contact
    done
    if (grep -q $contact $filename)
    then
        
        (grep -r -w $contact $filename)
        sed  -i "/$contact/d" $filename
        sed  -i "/^$/d" $filename  
        echo -en $'\nRecord deleted successfully.'
    else
        echo -en $'\nRecord not found.'
    fi
}

# function to update a record
function updateR(){
    read -p $'\n Enter contact Number To Be updated: ' contact
    while [ ${#contact} -ne 10 ] && grep -q $contact $filename
    do
        read -p "Enter valid  Contact Number: " contact
    done
    if (grep -q $contact $filename)
    then
        
        echo $'\nEnter Details :\n'
        read -p $'Enter Name:- ' newName
        read -p $'Enter Contact no:- ' newPhone
        read -p $'Enter City:- ' newCity
        read -p $'Enter Zip Code:- ' newZip
        sed -i "/$contact/c\ $newName\t$newPhone\t$newCity\t$newZip" $filename


    else
        echo -en $'\nRecord not found.'
    fi
}

choice=1
while [ $choice -ne 8 ]
do
    read -p $'\nAddress Book Record\n1.Create Student Record \n2.Add Record\n3.Display Record\n4.Search Record\n5.Delete\n6.Update\n7.Sort\n8.Exit\nEnter Your Choice:- ' choice
    case $choice in 
        1) createRecord ;;
        2) addRecord ;;
        3) display ;;
        4) search ;;
        5) deleteR ;;
        6) updateR ;;
        7) sort $filename ;;
        8) ;;
        *) echo $'\nPlease enter a valid choice.'
    esac
done

# OUPUT
# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 1

# Enter no of students details to be recorded:- 1

# Details for  1 student
# Enter Name:- Abhishek Avati
# Enter Contact no:- 7588103469
# Enter City:- Nashik
# Enter Zip Code:- 422101

# ADDITION SUCCESSFULL

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 2

# ADDING A RECORD

# Enter Name:- Adwait Deshmukh
# Enter Contact no:- 7588704129
# Enter City:- Pune
# Enter Zip Code:- 422001

# ADDITION SUCCESSFULL

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 3

# DISPLAYING RECORD


# Abhishek Avati 7588103469 Nashik 422101
# Adwait Deshmukh 7588704129 Pune 422001

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 4

#  Enter contact number to be searched: 7588103469

# Record Found!

# Abhishek Avati  7588103469      Nashik  422101

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 6

#  Enter contact Number To Be updated: 7588103469

# Enter Details :

# Enter Name:- Abhishek Ajay Avati
# Enter Contact no:- 7588103469
# Enter City:- Nashik Road
# Enter Zip Code:- 422101

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 3

# DISPLAYING RECORD


# Abhishek Ajay Avati 7588103469 Nashik Road 422101
# Adwait Deshmukh 7588704129 Pune 422001

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 5

#  Enter contact number to be deleted: 7588103469
#  Abhishek Ajay Avati    7588103469      Nashik Road     422101

# Record deleted successfully.
# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 7
# Adwait Deshmukh 7588704129      Pune    422001

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 1

# Enter no of students details to be recorded:- 1

# Details for  1 student
# Enter Name:- Prasad Khalkar
# Enter Contact no:- 75881     
# Enter valid and unique Contact Number: 7588704129
# Record for following contact no is already present!! Enter  unique Contact Number:7855704129
# Enter City:- Pune
# Enter Zip Code:- 38

# ADDITION SUCCESSFULL

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 3

# DISPLAYING RECORD


# Adwait Deshmukh 7588704129 Pune 422001
# Prasad Khalkar 7855704129 Pune 38

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 7
# Adwait Deshmukh 7588704129      Pune    422001
# Prasad Khalkar  7855704129      Pune    38

# Address Book Record
# 1.Create Student Record 
# 2.Add Record
# 3.Display Record
# 4.Search Record
# 5.Delete
# 6.Update
# 7.Sort
# 8.Exit
# Enter Your Choice:- 8