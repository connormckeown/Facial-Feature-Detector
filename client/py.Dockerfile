FROM schickling/opencv:latest

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY . .

RUN g++ -o main $(pkg-config --cflags --libs opencv) main.cpp
RUN apt-get update && apt-get install -y python-pip
RUN pip install requests

CMD [ "python", "client.py" ]
