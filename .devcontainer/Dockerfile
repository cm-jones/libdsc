FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-format \
    clang-tidy \
    cmake \
    devscripts \
    debhelper \
    doxygen \
    gcc \
    gdb \
    git \
    lintian \
    linux-tools \
    lldb \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN userdel -f $(getent passwd 1000 | cut -d: -f1) 2>/dev/null || true \
    && groupdel $(getent group 1000 | cut -d: -f1) 2>/dev/null || true \
    && groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set default shell to bash
ENV SHELL=/bin/bash
