#ifndef DIVERTSOCKET_HH
#define DIVERTSOCKET_HH

/*
=title DivertSocket

=c

DivertSocket(DEVICE, DIVERTPORT, FWRULENUM, PROTOCOL, 
             SADDR/MASK, SPORT, DADDR/MASK, DPORT, [DIRECTION])

=s sources

=d 

DivertSocket sets up a firewall rule according to the input 
parameters, and diverts matching IP packets to it's output port.

DIRECTION can be either "in" or "out" for packets coming into this machine
or going out of this machine.

*/


#include <click/element.hh>

#if defined(__linux__)
# include <getopt.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <linux/types.h>
# include <signal.h>

# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <netinet/udp.h>
# include <net/if.h>
# include <sys/param.h>

# include <linux/types.h>
# include <linux/icmp.h>
# include <linux/ip_fw.h>

# define IPPROTO_DIVERT 254

#endif

class DivertSocket : public Element {

public:

  DivertSocket();
  ~DivertSocket();

  const char *class_name() const     { return "DivertSocket"; }
  const char *processing() const     { return PUSH;}

  DivertSocket *clone() const;
  int configure(const Vector<String> &, ErrorHandler *);
  int initialize(ErrorHandler *errh);
  void uninitialize();

  void selected(int fd);


private:

  bool _have_sport;
  bool _have_dport;
  
  int _fd;
  unsigned char _protocol;
  IPAddress _saddr, _smask, _daddr, _dmask;
  int32_t _sportl, _sporth, _dportl, _dporth, _divertport, _rulenumber;
  String _device, _inout;

#ifdef __linux__
  struct ip_fw fw, fw2;
  struct ip_fwuser ipfu, ipfu2;
  struct ip_fwnew ipfc, ipfc2;


  int fw_sock;
#endif 

  int parse_ports(const String &param, ErrorHandler *errh, 
		  int32_t *sportl, int32_t  *sporth);
  


  
};

#endif

