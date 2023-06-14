FROM gcc:latest

WORKDIR /app

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    libsfml-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy the necessary files
COPY . .

# Compile the code
RUN g++ main.cpp -o myapp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CMD ["./myapp"]

# sudo docker build -t myproject .
# sudo docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix myproject