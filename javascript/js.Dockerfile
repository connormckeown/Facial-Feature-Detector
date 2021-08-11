FROM node:14-buster

#RUN npm install --build-from-source zeromq@6.0.0-beta.5 
RUN mkdir -p /app
WORKDIR /app

COPY javascript/* .
RUN npm install

CMD node hello.js
