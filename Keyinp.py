from pynput import keyboard
import socket


host = '192.168.43.250'
port = 5544

def Conn():
    sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sk.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    sk.connect((host,port))

    return sk



def on_press(key):
    try:
        print('alphanumeric key {0} pressed'.format(
            key.char))
        
 
        ki = format(key.char)
        s = Conn()

        
        if ki =='r':
            s.send('r'.encode('utf-8'))
            print(ki)
        elif ki == 'f': 
        	s.send('f'.encode('utf-8'))
        	print(ki)
        elif ki == 'w':
        	s.send('w'.encode('utf-8'))
        	print(ki)
        elif ki == 's':
        	s.send('s'.encode('utf-8'))
        	print(ki)
        elif ki == 'q':
        	s.send('q'.encode('utf-8'))
        	print(ki)
        elif ki == 'a':
        	s.send('a'.encode('utf-8'))
        	print(ki)
        elif ki == 'h':
        	s.send('h'.encode('utf-8'))
        	print(ki)
        elif ki == 'g':
        	s.send('g'.encode('utf-8'))
        	print(ki)
        elif ki == 'y':
        	s.send('y'.encode('utf-8'))
        	print(ki)
        elif ki == 'd': 
        	s.send('d'.encode('utf-8'))
        	print(ki)
        elif ki == 'e':
        	s.send('e'.encode('utf-8'))
        	print(ki)
        elif ki == 't':
        	s.send('t'.encode('utf-8'))
        	print(ki)
        elif ki == 'v':
        	s.send('v'.encode('utf-8'))
        	print(ki)
        elif ki == 'k':
        	s.send('k'.encode('utf-8'))
        	print(ki)
        elif ki == '1':
        	s.send('1'.encode('utf-8'))
        	print(ki)
        elif ki == '2':
        	s.send('2'.encode('utf-8'))
        	print(ki)
        elif ki == '3':
        	s.send('3'.encode('utf-8'))
        	print(ki)
        
        s.close()
            
    except AttributeError:
        print('special key {0} pressed'.format(
            key))

        ki = format(key)
        s = Conn()
        

        if ki == "Key.up":
        	s.send('8'.encode('utf-8'))
        	print(ki)
        elif ki == "Key.down":
        	s.send('5'.encode('utf-8'))
        	print(ki)
        elif ki == "Key.left":
        	s.send('4'.encode('utf-8'))
        	print(ki)
        elif ki == "Key.right":
        	s.send('6'.encode('utf-8'))
        	print(ki)
        s.close()

def on_release(key):
    s = Conn()

    s.send('z'.encode('utf-8'))
    s.send('0'.encode('utf-8'))

    s.close()    
    if key == keyboard.Key.esc:
        # Stop listener
        return False

# Collect events until released
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
