from functions import *

message = input("Input message:")

if(verify_message(message)):
    parity_matrix=construct_matrix(message)
    print("Parity matrix:")
    print_matrix(parity_matrix)
    for_destination=construct_message_from_matrix(parity_matrix)
    print("Message for destination:",for_destination)
    #Errors:
    changed_message=corupt_message(for_destination)
    print("The new message is:", changed_message)
    check_valid(changed_message)
else: print("Input message is invalid.")



