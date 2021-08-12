import socket
from time import sleep

print("hello from pyclient")


# function that connects to the server and requests the uploaded image
def recvImage():
    mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # continuosly bind the socket until it connects
    while mysock.connect_ex(('127.0.0.1', 3000)) != 0:
        print("pyclient: couldn't bind socket")
        sleep(10)

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
    mysock.close()
    return image_bytes


# request from the server until an image is received
while True:
    bytesRx = recvImage()
    if bytesRx.decode(errors='ignore') != 'no image':
        # send bytesRx to cpp program
        print("pyclient: recieved image")

        # reply to server with classification 
        
        break

    print("pyclient: image not received")
    sleep(10)





# send image_bytes to cpp program

# fhand = open("image.jpg", "wb")
# fhand.write(image_bytes)
# fhand.close()

