#include "checkserial.h"

int main(int argc, char const *argv[])
{
//  if (argc != 2) exit(255);

  //gather serial information
FILE *file = popen("echo $(hostname)-$(cat /proc/cpuinfo | grep Serial | awk '{print $3}')", "r");
char serial[1000];
fgets(serial,1000,file);
  argv[1]=serial;  
  
  char remotecmdbuf[1024];
  memset(remotecmdbuf, 0, 1024);
  snprintf(remotecmdbuf,
           1024,
           "[ -d "VERIFYDIR"%s ] && echo \'"VERIFYSTRING"\'>"VERIFYDIR"%s/%s.log && echo ok || true",
           argv[1], argv[1], argv[1]);

  char localcmdbuf[1024];
  memset(localcmdbuf, 0, 1024);
  snprintf(localcmdbuf,
           1024,
           "vc=$(dbclient -y -y -l "LOGIN" "SERVER" \"%s\" 2>/dev/null); rc=$?; [ $rc -ne 0 ] && exit $rc; [ z$vc = zok ] || exit 2; ",
           remotecmdbuf);

  char *eargv [] = { "/bin/sh", "-c", localcmdbuf, NULL };
  char *envp [] = { "DROPBEAR_PASSWORD="PASSWORD, NULL };

  execve("/bin/sh", eargv, envp);

  return 0;
}
