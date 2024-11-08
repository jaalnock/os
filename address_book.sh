#!bin/bash

ADDRESS_BOOK="addressBook.txt"

create(){
	>"$ADDRESS_BOOK"
	echo "Name | Address | Phone no." >> "$ADDRESS_BOOK"
	echo "Address Book Created Successfully."
}

insert(){
	echo "Enter the name :"
	read NAME
	echo "Enter the address :"
	read ADDRESS
	echo "Enter the phone no :"
	while true
	do
		read PHONE
		len=$(echo -n $PHONE | wc -m)
		if [ $len -eq 10 ]; then
			break;
		else
			echo "Please enter 10 digit mobile number."
		fi
	done
	echo "$NAME | $ADDRESS | $PHONE" >> "$ADDRESS_BOOK"
	echo "Record added successfully."
}

view(){
	if [[ -s "$ADDRESS_BOOK" ]]; then
		echo -e " \nAddress Book :"
		cat "$ADDRESS_BOOK"
	else
		echo "Address book is empty"
	fi
}

delete(){
	echo "Enter the name of the record :"
	read NAME
	if grep -q "^$NAME" "$ADDRESS_BOOK" ; then
		grep -v "^$NAME" "$ADDRESS_BOOK" > temp && mv temp "$ADDRESS_BOOK"
		echo "Record deleted successfully."
	else
		echo "Record not found."
	fi
}

modify(){
	delete
	echo "Enter the new name : "
	read NAME
	echo "Enter the new address :"
	read ADDRESS
	echo "Enter the new phone no :"
	read PHONE
	echo "$NAME | $ADDRESS | $PHONE" >> "$ADDRESS_BOOK"
	echo "Record modified."
}

search(){
	echo "Enter the name of record to search :"
	read NAME
	if grep -q "^$NAME" "$ADDRESS_BOOK" ; then
		grep "^$NAME" "$ADDRESS_BOOK"
	else
		echo "Record not found."
	fi
}

# Main menu
while true; do
    echo -e "\nChoose an option:"
    echo "a) Create address book"
    echo "b) View address book"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Search for a record"
    echo "g) Exit"
    read choice

    case $choice in
        a) create ;;
        b) view ;;
        c) insert ;;
        d) delete ;;
        e) modify ;;
        f) search ;;
        g) echo "Exiting." ; exit 0 ;;
        *) echo "Invalid option, please try again." ;;
    esac
done