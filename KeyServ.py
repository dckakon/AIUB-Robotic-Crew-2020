import socket
import serial


host = '192.168.0.100'
port = 5544

ardConn = serial.Serial("COM9", 9600)

def Conn():
    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    sk.bind((host,port))

    return sk

while True:
        '''try:

            s = Conn()
            s.listen(1)

            conn, client_addr = s.accept()

            print("Connected with: ",cli_addr)

            dat = s.recv(512).encode('utf-8')

            print(dat)

        except:

            print("Waiting on connection")'''
        s = Conn()
        s.listen(1)

        conn, client_addr = s.accept()

        print("Connected with: ",client_addr)
        dat = conn.recv(512).decode('utf-8')

        ardConn.write(dat.encode('utf-8'))

        print(dat)

        s.close()


        
