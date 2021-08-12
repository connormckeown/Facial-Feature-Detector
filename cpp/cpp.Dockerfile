FROM gcc:latest
 
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY . .
RUN g++ -o hellocpp main.cpp

CMD [ "./hellocpp" ]
