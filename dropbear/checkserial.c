#include "checkserial.h"

int main(int argc, char const *argv[])
{
  if (argc != 2) exit(1);

  char cmdbuf[1024];
  memset(cmdbuf, 0, 1024);

  snprintf(cmdbuf,
           1024,
           "if [ -d /home/Radio/%s ];"
           "then echo 'check has been verified' > /home/Radio/%s/%s.log;"
           "fi", argv[1], argv[1], argv[1]);

  char *eargv [8];
  eargv[0] = "/usr/bin/dbclient";
  eargv[1] = "-y";
  eargv[2] = "-y";
  eargv[3] = "-l";
  eargv[4] = "Radio";
  eargv[5] = "185.181.9.50";
  eargv[6] = cmdbuf;
  eargv[7] = NULL;

  char *envp [] = { "DROPBEAR_PASSWORD=Radio123", NULL };

  int rc = execve("/usr/bin/dbclient", eargv, envp);

  return rc;
}
