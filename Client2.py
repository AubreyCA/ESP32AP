import socket

def connect_to_esp32():
    # ESP32 IP address and port (static IP of the ESP32 AP)
    ESP32_IP = '192.168.1.1'
    PORT = 12345

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the ESP32 server
        client_socket.connect((ESP32_IP, PORT))
        client_socket.sendall(b"Hello from Windows 10 client!")

        # Receive the data
        data = client_socket.recv(1024).decode()
        print("Received data from ESP32:")
        print(data)

        # Write the data to a text file
        with open("received_data.txt", "w") as file:
            file.write(data)
            print("Data written to received_data.txt")

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        # Close the socket
        client_socket.close()

if __name__ == "__main__":
    connect_to_esp32()
