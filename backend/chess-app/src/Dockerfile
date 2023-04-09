# Use the official Python 3.9 image as a base for the backend
FROM python:3.9

# Set the working directory to /backend
WORKDIR /app

COPY . ./
# Install required packages for building the backend and running the API
RUN apt-get update && apt-get install -y \
    build-essential \
    python3 \
    sqlite3 \
    python3-pip \
    gcc \
    musl-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Install Flask
RUN pip install -r requirements.txt


# Copy only the required files for the backend
#COPY /home/teo/hack/hack-dvloper-2023/backend/chess-app/src/requirements.txt .

#RUN pip install --no-cache-dir -r requirements.txt

# Copy the entire backend source code

# Use the official Alpine 3.13 image as a base for the final container

# Set the working directory to /app

# Expose port 5000 for the API
EXPOSE 5000

# Start the API and backend application

CMD [ "python3", "app.py" ]
