# Ghost(Linux Fileless Malware)
Ghost is a Linux Fileless Malware that takes advantage of the fork() system call. The malware creates a reverse TCP connection to the attacker system. Once fork() is called, the parent process detaches itself from the terminal, while the child process continues and spawns a remote shell on the attacker system. Finally, the malware removes itself from storage after execution, hence leaving no footprints on the target system. 

## Demo
Target System:

![ghost_fileless](https://github.com/Arjun4522/Ghost_Shell/assets/94633408/fb63ad59-9a57-48df-b67e-bd5a054ed1dd)


Attacker System:

![attacker_ghost](https://github.com/Arjun4522/Ghost_Shell/assets/94633408/2866db7c-5ff0-46ed-984c-13e25ab40b3e)

As it is shown above, the malware deletes itself after execution, however
leaving the reverse shell connection
intact.

## Disclaimer
This repository is intended for educational and informational purposes only. However, the usage of similar code for unauthorized access to computer systems or 
networks is illegal and unethical.
