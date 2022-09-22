FROM raspbian/stretch AS baseimg
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update \
    && apt-get -y install python3 \
    python3-pip \
    python3-dev 

FROM baseimg AS sensorimg

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /app

ADD . /app/

RUN pip3 install --trusted-host pypi.python.org -r requirements.txt

ENV NAME water_station

CMD ["python3", "main.py"]