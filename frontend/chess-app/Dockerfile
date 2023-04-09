# Use the official Node.js 14 image as a base for the frontend
FROM node:14-alpine

# Set the working directory to /frontend
WORKDIR /frontend

# Copy only the required files for the frontend
COPY . ./
RUN npm install

# Build the frontend
RUN npm build

# Install required packages for running the frontend
RUN apk add --no-cache nodejs
RUN apk add --no-cache npm

# Expose port 80 for the frontend
EXPOSE 3000

# Start the frontend application
CMD ["npm", "start"]
