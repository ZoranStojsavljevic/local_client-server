// SocketCAN - The official CAN API of the Linux kernel
// https://www.can-cia.org/fileadmin/resources/documents/proceedings/2012_kleine-budde.pdf

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>

/* omitted vital #includes and error checking */
int main(int argc, char **argv) {
  struct ifreq ifr;
  struct sockaddr_can addr;
  struct can_frame frame;
  int s;

  memset(&ifr, 0x0, sizeof(ifr));
  memset(&addr, 0x0, sizeof(addr));
  memset(&frame, 0x0, sizeof(frame));

  /* open CAN_RAW socket */
  s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  /* convert interface sting "can0" into interface index */
  strcpy(ifr.ifr_name, "can0");
  ioctl(s, SIOCGIFINDEX, &ifr);
  /* setup address for bind */
  addr.can_ifindex = ifr.ifr_ifindex;
  addr.can_family = PF_CAN;
  /* bind socket to the can0 interface */
  bind(s, (struct sockaddr *)&addr, sizeof(addr));

  // default the receiving frame to zeros
  memset(&frame, 0x0, sizeof(frame));

  /* first receive, then print the CAN frame */
  read(s, &frame, sizeof(frame));
  printf ("frame CAN   id is %x\n", frame.can_id);
  printf ("frame CAN data is %s\n", frame.data);
  printf ("frame CAN  dcl is %x\n", frame.can_dlc);

  // default the receiving frame to zeros
  memset(&frame, 0x0, sizeof(frame));

  /* first receive, then print the CAN frame */
  read(s, &frame, sizeof(frame));
  printf ("frame CAN   id is %x\n", frame.can_id);
  printf ("frame CAN data is %s\n", frame.data);
  printf ("frame CAN  dcl is %x\n", frame.can_dlc);

  close(s);
  return 0;
}
