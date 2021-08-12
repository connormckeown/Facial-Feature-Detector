FROM python:latest

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY . .

CMD [ "python", "client.py" ]
