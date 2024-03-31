
class token_ring :
    def __init__(self,) -> None:
        """Creates an empty  & free token."""
        self.IP_source = ""
        self.IP_destination = ""
        self.is_free = True
        self.reached_destination = False
        self.buffer = ""

    def set_token(self,computer1:str, computer2: str,buffer:str):
        self.IP_source = computer1
        self.IP_destination = computer2
        self.is_free = False
        self.buffer = buffer
        print("Token set. Message is being sent.")
        return self
