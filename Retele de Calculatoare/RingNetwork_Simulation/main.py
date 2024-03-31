from functions import generate_sender_receiver, read_network, send_message
from token_ring import token_ring

#read the network from the input file:
computers = read_network("computers.in")
print("Network:\n")
for computer in computers:
    print(computer)


#simulate 10 messages being sent in the ring network:
if len(computers)>0:
    for iteration in range(10):
        print("-------------------------")
        print(f"Iteration: {iteration}")
        #generate 2 random computers
        token=token_ring()
        sender_computer, receiver_computer = generate_sender_receiver(computers)
        #simulate sending a message between them
        send_message(computers,sender_computer,receiver_computer,token)
        print("-------------------------")
else: print("One of the IP addresses is either not valid or there are duplicate IPv4s in the file.")