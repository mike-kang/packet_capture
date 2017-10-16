// ex_wpd_2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#define HAVE_REMOTE
#include "pcap.h"

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#else
#include <winsock.h>
#endif


// Function prototypes
void ifprint(pcap_if_t *d);
char *iptos(u_long in);
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);


int main()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	char source[PCAP_ERRBUF_SIZE + 1];

	printf("Enter the device you want to list:\n"
		"rpcap://              ==> lists interfaces in the local machine\n"
		"rpcap://hostname:port ==> lists interfaces in a remote machine\n"
		"                          (rpcapd daemon must be up and running\n"
		"                           and it must accept 'null' authentication)\n"
		"file://foldername     ==> lists all pcap files in the give folder\n\n"
		"Enter your choice: ");

	fgets(source, PCAP_ERRBUF_SIZE, stdin);
	source[PCAP_ERRBUF_SIZE] = '\0';

	/* Retrieve the interfaces list */
	if (pcap_findalldevs_ex(source, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* Scan the list printing every entry */
	for (d = alldevs; d; d = d->next)
	{
		ifprint(d);
	}

	pcap_freealldevs(alldevs);

	return 1;
}



/* Print all the available information on the given interface */
void ifprint(pcap_if_t *d)
{
	pcap_addr_t *a;
	char ip6str[128];

	/* Name */
	printf("%s\n", d->name);

	/* Description */
	if (d->description)
		printf("\tDescription: %s\n", d->description);

	/* Loopback Address*/
	printf("\tLoopback: %s\n", (d->flags & PCAP_IF_LOOPBACK) ? "yes" : "no");

	/* IP addresses */
	for (a = d->addresses; a; a = a->next) {
		printf("\tAddress Family: #%d\n", a->addr->sa_family);

		switch (a->addr->sa_family)
		{
		case AF_INET:
			printf("\tAddress Family Name: AF_INET\n");
			if (a->addr)
				printf("\tAddress: %s\n", iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
			if (a->netmask)
				printf("\tNetmask: %s\n", iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
			if (a->broadaddr)
				printf("\tBroadcast Address: %s\n", iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
			if (a->dstaddr)
				printf("\tDestination Address: %s\n", iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
			break;

		case AF_INET6:
			printf("\tAddress Family Name: AF_INET6\n");
			if (a->addr)
				printf("\tAddress: %s\n", ip6tos(a->addr, ip6str, sizeof(ip6str)));
			break;

		default:
			printf("\tAddress Family Name: Unknown\n");
			break;
		}
	}
	printf("\n");
}



/* From tcptraceroute, convert a numeric IP address to a string */
#define IPTOSBUFFERS    12
char *iptos(u_long in)
{
	static char output[IPTOSBUFFERS][3 * 4 + 3 + 1];
	static short which;
	u_char *p;

	p = (u_char *)&in;
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
	_snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}

char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
	socklen_t sockaddrlen;

#ifdef WIN32
	sockaddrlen = sizeof(struct sockaddr_in6);
#else
	sockaddrlen = sizeof(struct sockaddr_storage);
#endif

	/*
	if (getnameinfo(sockaddr,
		sockaddrlen,
		address,
		addrlen,
		NULL,
		0,
		NI_NUMERICHOST) != 0) address = NULL;
		*/
	address[0] = 0;
	return address;
}
