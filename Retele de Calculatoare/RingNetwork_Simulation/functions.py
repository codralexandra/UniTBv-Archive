
from computer import Computer
from token_ring import token_ring
import regex
import random

def read_network(file_path:str)->list:
    """Reads a network of computers from a file. Returns the list of computer objects. 
    If one of the ip addresses does not pass the validation, it returns an empty list."""

    computers = []
    used_ips = set()

    id=1

    with open(file_path, "r") as file :
        for line in file:
            ip, buffer_message = line.split()
            #print(ip," ", buffer_message)
            if is_valid_ipv4(ip) and ip not in used_ips :
                computer = Computer(id,ip, buffer_message)
                computers.append(computer)
                used_ips.add(ip)
                id+=1
            else:
                return []

    return computers


def is_valid_ipv4(ip:str)->bool:
    """Validates if an ip address is a valid IPv4 address. 
    Pattern_IPv4 -> [0-255].[0-255].[0-255].[0-255]"""

    pattern = r"^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
    return regex.match(pattern, ip) is not None


def generate_sender_receiver(network:list[Computer])->tuple:
    """Generates two random ip addresses as sender and receiver from the network list."""
    #add a check for unique IPs here!
    random_computers = random.sample(network,2)
    return tuple(random_computers)

def send_message(network:list[Computer], sender_computer:Computer, receiver_computer:Computer, token:token_ring)->None:
    """Simulates the route and actions of a token in a ring network between two computers."""

    print(f"Sending the message '{sender_computer.buffer}' from computer {sender_computer.id} to computer {receiver_computer.id}.")
    #set the token to go from source to destination
    token = token.set_token(sender_computer.ip,receiver_computer.ip, sender_computer.buffer)
    index = sender_computer.id
    while token.is_free is not True :
        if(token.reached_destination is not True):
            #if the token hasn't reached its destination yet, check if the computer is the destination
            token = network[index-1].check_token(token)
        else: 
            #if the token has reached its destination, check if the computer can empty the token
            token = network[index-1].empty_token(token)
        index+=1
        #if we reach the end of the network, we simulate a circular container (until the source is reached again)
        if index > len(network):
            index=1

