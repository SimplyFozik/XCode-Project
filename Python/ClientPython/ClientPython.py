import socket
import Encrypt
import Decrypt
import threading
import time

socketServer = socket.socket()
serverHost = socket.gethostname()
port = 1111
localIP = '127.0.0.1'

socketServer.connect((localIP, port))

clientName = "Python"

def funcSendMessages():
    while True:
        msg = input("Enter message to send: ")
        msg_size = len(msg)
        msg_size_bytes = msg_size.to_bytes(4,"little")
        print(msg_size_bytes)
        seed = Encrypt.funcGenerateSeed()
        str_seed = str(seed)
        str_seed = str_seed[1:]
        str_seed = str_seed.replace(" ",'')
        str_seed = str_seed[0:145]
        
        enc_text = Encrypt.funcEncrypt(seed, msg)

        socketServer.send(msg_size_bytes)
        socketServer.send(enc_text.encode())
        socketServer.send(str_seed.encode())



def funcWaitForAnswer():
    while True:
        msg_size_bytes = socketServer.recv(4)
        print(msg_size_bytes)
        msg_size = int.from_bytes(msg_size_bytes, byteorder='big')
        msg = socketServer.recv(msg_size)
        seed = socketServer.recv(145).decode() 

        dec_msg = Decrypt.funcDecrypt(seed, msg.decode())

        print(f"Received message: {msg.decode()}")
        print(f"Received seed: {seed}")
        print(f"Decrypted Message: {dec_msg}")


thread1 = threading.Thread(target=funcWaitForAnswer, name="Thread1")
thread2 = threading.Thread(target=funcSendMessages, name="Thread2")


thread1.start()
thread2.start()


thread1.join()
thread2.join()
