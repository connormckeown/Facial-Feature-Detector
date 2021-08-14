import socket
import os
from time import sleep
import requests
import base64

print("hello from client")

# sends a GET request to the servers /image 
# returns a requests.Response Object
def recvFromServer():
    url = 'http://localhost:3000/image'
    res = requests.get(url)
    while len(res.content) == 0:
        res = requests.get(url)
        sleep(5)
    print('received bytes from server')
    return res


# sends message msg in a JSON to the server as a POST request
def sendToServer(data):
    url = 'http://localhost:3000/result'
    enc_data = base64.b64encode(data)
    myobj = {'pred': enc_data}
    res = requests.post(url, data = myobj)
    print("sent bytes to server")


while True:
    # receive bytes from server
    res = recvFromServer()

    # save as an image file
    fhand = open("image.jpg", "wb")
    fhand.write(res.content)
    fhand.close()

    # call cpp program for a prediction
    os.system('./main image.jpg')

    # open the prediction image
    data = open("pred.jpg", "rb")

    # send prediction to server
    res = sendToServer(data.read())

