# NTA_lab2
Docker instruction
- download docker from remote: `docker pull mansteinorguderian/ntasecond:latest`
- run docker from remote: `docker run --rm -it mansteinorguderian/ntasecond:latest`
- build from git repository: `docker build -t 'mansteinorguderian/ntasecond' .`
- run cli: `docker run --rm -it 'mansteinorguderian/ntasecond'`
- stop container: `docker stop $(docker ps | grep "mansteinorguderian/ntasecond" | cut -d " " -f1)`
- remove image: `docker image rm 'mansteinorguderian/ntasecond`
