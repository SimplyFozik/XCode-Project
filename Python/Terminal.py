import socket
import Encrypt
import Decrypt
import threading

socketServer = socket.socket()
serverHost = socket.gethostname()
port = 1111
localIP = '127.0.0.1'

socketServer.connect((localIP, port))


def funcSendMessages():
    while (True):
        print("hello")
    

def funcWaitForAnswer():
    while True:
        msg_size_bytes = socketServer.recv(4)  # Receive message size (4 bytes)
        msg_size = int.from_bytes(msg_size_bytes, byteorder='big')  # Convert bytes to integer
        msg = socketServer.recv(msg_size).decode()  # Receive the message based on msg_size
        seed = socketServer.recv(145).decode()  # Receive the seed

        dec_msg = Decrypt.funcDecrypt(seed,msg)

        print(f"Received message: {msg}")
        print(f"Received seed: {seed}")
        print(f"Decrypted Message: {dec_msg}")


thread1 = threading.Thread(target=funcWaitForAnswer, name="Thread1")
#thread2 = threading.Thread(target=funcSendMessages, name="Thread2")


thread1.start()
#thread2.start()


thread1.join()
#thread2.join()
