import socket
from time import sleep

if __name__ == "__main__":
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	s.connect(("127.0.0.1", 8080))
	
	while True:
		msg = input('').encode()
		s.send(msg)
		if msg == b'exit':
			break
		back = s.recv(1024)
		print(str(back))
	s.close()