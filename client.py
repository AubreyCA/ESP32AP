import socket

def connect_to_esp32():
    # ESP32 IP address and port (replace with the actual IP address of your ESP32)
    ESP32_IP = '192.168.130.137' 
    PORT = 80

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.settimeout(None)

    try:
        # Connect to the ESP32 server
        client_socket.connect((ESP32_IP, PORT))

        # Send an HTTP request
        request = "GET / HTTP/1.1\r\nHost: {}\r\nConnection: close\r\n\r\n".format(ESP32_IP)
        client_socket.send(request.encode())

        # Receive and print the response
        response = client_socket.recv(4096)
        print("Response from ESP32:")
        print(response.decode())

    except Exception as e:
        print(f"An error occurred: {e}")

    finally:
        # Close the socket
        client_socket.close()

if __name__ == "__main__":
    connect_to_esp32()
