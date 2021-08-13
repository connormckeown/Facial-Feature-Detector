import socket
import os
from time import sleep

print("hello from client")

mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# continuosly bind the socket until it connects
while mysock.connect_ex(('127.0.0.1', 3000)) != 0:
    print("pyclient: couldn't bind socket")
    sleep(10)


# function that connects to the server and requests the uploaded image
def recvImage():
    cmd = 'GET http://127.0.0.1/image HTTP/1.0\r\n\r\n'.encode()
    mysock.send(cmd)    # request the image 
    image_bytes = b""

    # loop over all the bytes received
    while True:
        data = mysock.recv(5120)
        
        if len(data) < 1:
            break
        
        image_bytes = image_bytes + data
    
    pos = image_bytes.find(b"\r\n\r\n")
    image_bytes = image_bytes[pos+4:]   # trim header
    return image_bytes


# request from the server until an image is received
while True:
    img = recvImage()
    if img.decode(errors='ignore') != 'no image':
        print("pyclient: recieved image")

        # write the bytes to a file
        fhand = open("image.jpg", "wb")
        fhand.write(img)
        fhand.close()

        # call cpp program
        res = os.system('./main sample.jpg')
        print('res=', res)

        # reply to server with classification 
        
        break

    print("pyclient: image not received")
    sleep(10)


mysock.close()