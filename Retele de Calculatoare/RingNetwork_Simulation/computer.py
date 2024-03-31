from token_ring import token_ring

class Computer:
    def __init__(self, id:str, ip:str, buffer:str) -> None:
        self.id = id
        self.ip = ip
        self.buffer = buffer

    def __str__(self):
        return f"Computer: id={self.id}, IPv4={self.ip}, Buffer={self.buffer}"

    def check_token(self, token:token_ring)->token_ring:
        """Checks if the computer is the receiver of the message.
        If they are, modify the has_reached_destination attribute and pass the token.
        If not, pass the token without modifying anything."""

        if token.IP_destination == self.ip :
            print(f"Token has reached destination: computer {self.id}. Passing the token to reach the source.")
            token.reached_destination = True
            return token
        else:
            print(f" Computer {self.id} is passing the token.")
            return token
        
    def empty_token(self, token:token_ring)->token_ring:
        """If the computer is the source IP & the token has reached its destination, empties the token.
        If not, pass the token without modifying anything. """

        if token.IP_source == self.ip :
            print(f"Token has reached the source (computer {self.id}) after sending the message. Emptying token.")
            token.is_free = True
            token.buffer = ""
            token.IP_source = ""
            token.IP_destination = ""
            return token
        else:
            print(f" Computer {self.id} is passing the token.")
            return token