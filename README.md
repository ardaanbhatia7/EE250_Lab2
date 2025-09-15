# Lab 2

## Team Members
- Ardaan Bhatia: ardaanbh@usc.edu
- Kyna Rochlani: rochlani@usc.edu

## Lab Question Answers

Answer for Question 1: 
UDP became unreliable once 50% packet loss was introduced. Several of the messages sent from the client did not arrive at the server. Some numbers ,in our case 6,7,3, just missed the sequence of numbers. This happened because UDP does not implement retransmission, acknowledgments, or error correction. Packets that are dropped in the network are simply lost, and the protocol makes no attempt to recover them, or confirm if they were even reached.

Answer for Question 2:
TCP maintained its reliability even when the 50% packet loss was implimented. All messages that were sent by the client eventually arrived at the server even though some arrived with slight delays. This is because TCP is a connection-oriented protocol that guarantees delivery. It uses acknowledgments and retransmissions to ensure that dropped packets are resent until they are successfully received by the server.

Answer for Question 3:
The speed of TCP communication decreased for certain transmission when the 50% packet loss was implimented. Some numbers took longer to appear at the server compared to the previous loss-free environment. This slowdown is expected because TCP retransmits lost packets and performs congestion control. Each lost packet adds retransmission delay. And TCP also reduces its sending rate when it detects loss further slowing down overall throughput.

Answer for Question 4:
We used LLMs (ChatGPT) to set up and run GitHub and Git on our devices. The LLMs taught us how to collaborate in our team and how to use github to do that by committing and pushing changes, as well as pulling updates from each other’s work. We also used LLMs to understand the cryptic command line errors we encountered when running incorrect or incomplete code during our attempts at solving the lab tasks.