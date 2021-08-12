FROM schickling/opencv:latest
 
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY . .

RUN g++ -o main $(pkg-config --cflags --libs opencv) main.cpp

CMD [ "./main" ]
