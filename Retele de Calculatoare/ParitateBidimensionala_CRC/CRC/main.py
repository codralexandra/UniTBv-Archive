from functions import *

message = input("Input binary message:")
if(verify_message(message)):
    generator = input("Input generating polynomial:")
    if(verify_polynomial(generator)):
        if(len(message)>len(generator)):
            #t(x)
            t=message + get_degree(generator)
            #calculare rest
            result=t
            while len(result) >= len(generator):
                result = xor(result, generator)
                print(f"Result: {result}\n")
            print("Final Result:", result)
            #mesaj extins
            extended_message=add_binary(t,result)
            print("Extended message is:", extended_message)
            #verificarea facuta de destinatie
            destination_result=extended_message
            while(len(destination_result) >=len(generator)):
                destination_result=destination_xor(destination_result,generator)
            print(destination_result)
            if(destination_result=='0'):
                print("The message is correct.")
            else: print("The message is incorrect.")
            #test pt mesaj incorect
            #destination_result="10101101110111" #pt mesaj=10101101110110 
            #while(len(destination_result) >=len(generator)):
            #    destination_result=destination_xor(destination_result,generator)
            #print(destination_result)
            #if(destination_result=='0'):
            #    print("The message is correct.")
            #else: print("The message is incorrect.")
        else: print("Generating polynomial is bigger than the message.")
    else: print("The generating polynomial is invalid.")
else: print("The message is invalid.")