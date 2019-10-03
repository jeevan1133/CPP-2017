FROM ubuntu:latest
RUN apt-get update && apt-get install -y build-essential gcc g++ libcurl4-gnutls-dev

WORKDIR /server
COPY htmltitle.cpp /server
CMD ["/bin/bash"]
