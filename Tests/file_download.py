import os
import subprocess


server_address = "localhost"
server_port = 2222

client_process = subprocess.Popen(['xterm', '-e', f'cd ../../Puciolce-server; make; ./server {server_port}; bash'])
server_process = subprocess.Popen(['xterm', '-e', f'cd ../../LTE-Client; make; ./lte_client {server_address} {server_port} true; bash'])