FROM debian:stable
RUN apt-get update && apt-get install -y --no-install-recommends \
clang lld wabt \
&& rm -rf /var/lib/apt/lists/*
WORKDIR /work
