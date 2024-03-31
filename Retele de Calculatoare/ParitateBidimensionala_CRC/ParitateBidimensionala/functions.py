import random

def verify_message(message:str)->bool:
    """Checks if the message checks the requirements for processing. Returns a boolean value."""

    if(len(message)%7!=0):
        return False
    for symbol in message:
        if symbol not in ['0','1']:
            return False
    return True

def print_matrix(matrix:list[list[str]])->None:
    """Prints a matrix with proper allignment."""

    for row in matrix:
        print(" ".join(row))
    print()

def construct_matrix(message:str)->list[list[str]]:
    """Returns a parity matrix from a string, calculating the parity bits accordingly."""

    columns=8
    rows=len(message)//7+1
    parity_matrix = [['0' for symbol in range(columns)] for symbol in range(rows)]
    symbol_count=0

    #parity for lines
    for i in range(rows-1):
        parity_count=0
        for j in range(columns-1):
            parity_matrix[i][j]=message[symbol_count]
            if(message[symbol_count]=='1'):
                parity_count+=1
            symbol_count+=1
        if parity_count%2==0:
            parity_matrix[i][columns-1]='0'
        else: parity_matrix[i][columns-1]='1'

    #parity for columns
    for j in range(columns):
        parity_count=0
        for i in range(rows-1):
           if(parity_matrix[i][j]=='1'):
                parity_count+=1
        if parity_count%2==0:
            parity_matrix[rows-1][j]='0'
        else: parity_matrix[rows-1][j]='1'        
    return parity_matrix

def construct_message_from_matrix(matrix:list[list[str]])->str:
    """Returns the bit message meant to be transmited to a destination."""

    new_message=""
    for row in matrix:
        for element in row:
            new_message+=element
    return new_message

def corupt_message(message:str)->str:
    """Changes random indexes values from a bit message."""
    
    #generate the random bits to be changed:
    error_index= random.randint(0, len(message))
    print("Generating errors at position:",error_index)

    #create the errors:
    
    if message[error_index] == '1':
        message = message[:error_index] + '0' + message[error_index + 1:]
    else: message = message[:error_index] + '1' + message[error_index + 1:]

    return message

def check_valid(received_message:str)->None:
    """Destination checks if the message received is correct and returns a boolean value. If not, 
    it returns the positions of the corrupted bits."""

    #reconstruct parity matrix:
    columns=8
    rows=len(received_message)//8
    parity_matrix = [['0' for symbol in range(columns)] for symbol in range(rows)]
    index=0;
    for row in range(rows):
        for column in range(columns):
            parity_matrix[row][column]=received_message[index]
            index+=1
    
    #for tests, remove when done
    print("New matrix:")
    print_matrix(parity_matrix)

    line_index=-1
    column_index=-1

    #verify if the matrix is correct: (to fix)
    #for rows:
    for i in range(rows-1):
        parity_count=0
        for j in range(columns-1):
            if(parity_matrix[i][j]=='1'):
                parity_count+=1
        if parity_count%2==0 and parity_matrix[i][columns-1]!='0':
            line_index=i
        elif parity_count%2!=0 and parity_matrix[i][columns-1]!='1':
            line_index=i

    #for columns:
    for j in range(columns):
        parity_count=0
        for i in range(rows-1):
           if(parity_matrix[i][j]=='1'):
                parity_count+=1
        if parity_count%2==0 and parity_matrix[rows-1][j]!='0':
            column_index=j
        elif parity_count%2!=0 and parity_matrix[rows-1][j]!='1':
            column_index=j

    
    if line_index==-1 and column_index==-1:
        print("Message is correct.")
    else:
        print("Message is corrupted at positions:", line_index, ", ", column_index)