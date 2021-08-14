# CMPT383 Project

## Overview

A web app that highlights facial features of the person(s) in the uploaded image. 

## Implementation

The frontend of the project that the user interacts with and displays the image is written in Node.js with Express. The facial feature detection is done in C++ with then OpenCV library. There is also a Python client that acts as a bridge between the C++ program and the Express server. It receives the input image and sends it to the C++ program, then receives facial-feature-detected image from the C++ program and sends that back to the server.

## Language Communication

The Python client communicates with the Express server via a REST API. It receives the input image by polling a GET request until and image is uploaded, and sends a POST request containing the modified image from the C++ program.

The Python client calls the C++ program by running it as an executable using **system()** from the **os** module. The C++ program then writes the image to a file which is then sent as bytes in the POST request to the server.

## How to Run
After cloning the repository, run
```
$ docker-compose up --build
```
This should start both the container containing the Express server, and the container that has OpenCV, C++ build tools, and Python. 

The server container will launch a server on **localhost** with port **3000**. The full url is
```
http://localhost:3000
```
Simply navigate to this url in your browser and upload your image.

(A bug I was having was that images were being uploaded in a weird order. If you run into this, just refresh a few times. The image probably isn't being deleted/created/sent properly in the container)