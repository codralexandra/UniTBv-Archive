def verify_message(message:str)->bool:
    """Checks if the message checks the requirements for processing. Returns a boolean value."""

    for symbol in message:
        if symbol not in ['0','1']:
            return False
    return True

def verify_polynomial(c:str)->bool:
    """Checks if the generating polynomial checks the requirements for processing. Returns a boolean value."""
    if(c[0]!='1'):
        return False
    for symbol in c:
        if symbol not in ['0','1']:
            return False
    return True

def get_degree(c:str)->str:
    """Returns the degree (string) of the polynomial (string) received as a parameter."""
    degree=""
    for i in range(len(c)-1):
        degree+='0'
    return degree

def xor(binary_str1:str, binary_str2:str)->str:
    """Returns the XOR result between two binary strings."""
    first_slice=binary_str1[:len(binary_str2)]
    second_slice=binary_str1[-(len(binary_str1)-len(binary_str2)):]
    xor_result = ''.join('1' if a != b else '0' for a, b in zip(first_slice, binary_str2))
    xor_result=xor_result+second_slice
    return eliminate_leading_zeros(xor_result)

def eliminate_leading_zeros(binary_str:str)->str:
    """Removes the '0' at the beginning of the string."""
    result =  binary_str.lstrip('0') or '0'
    return result if result else '0'

def add_binary(str1:str,str2:str)->str:
    """Returns the sum between two binary strings."""
    if not str1:
        return str2
    if not str2:
        return str1

    result = ""
    carry = 0

    max_len = max(len(str1), len(str2))
    str1 = str1.zfill(max_len)
    str2 = str2.zfill(max_len)

    for i in range(-1, -max_len - 1, -1):
        value1 = int(str1[i])
        value2 = int(str2[i])
        total_sum = value1 + value2 + carry

        if total_sum == 0:
            result += '0'
            carry = 0
        elif total_sum == 1:
            result += '1'
            carry = 0
        elif total_sum == 2:
            result += '0'
            carry = 1
        else:
            result += '1'
            carry = 1

    if carry == 1:
        result += '1'

    return result[::-1]

def eliminate_ending_zeros(binary_str:str)->str:
    """Removes the '0' at the end of the string."""
    result = binary_str.rstrip('0')
    return result if result else '0'
        
def destination_xor(str1:str, str2:str)->str:
    last_slice = str1[-len(str2):]
    first_slice = str1[:len(str1)-len(str2)]
    xor_result = ''.join('1' if a != b else '0' for a, b in zip(last_slice, str2))
    xor_result = first_slice + xor_result
    return eliminate_ending_zeros(xor_result)




