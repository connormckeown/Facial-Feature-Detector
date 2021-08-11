FROM gcc:latest
 
RUN mkdir -p /app
WORKDIR /app

COPY cpp/* .
RUN g++ -o hellocpp main.cpp

CMD [ "./hellocpp" ]
