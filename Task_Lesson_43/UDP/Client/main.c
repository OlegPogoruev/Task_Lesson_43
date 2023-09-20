
#include "main.h"


void get_input_string(char *str_in);


int main(void)
{
	struct sockaddr_in sock_client;		// initilaize struct of socket
	int fd;					// deskriptor socket
	int slen;				// len structure socket
	char buf[BUFLEN];
	char temp_buf[BUFLEN];
	int recv_len;				// len received mesage
	
	union{unsigned char bait[2]; unsigned short word;}temp;  //Data union
	
        if ( (fd=socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1){perror("can't socket");return -1;}
        
	slen = 1;
	if( (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &slen, sizeof(slen)) ) != 0){perror("can't option setsockopt"); return(-1);}
	
	/////////////////////////////////////////////////////
	// zero out the structure
	memset((char *) &sock_client, 0, sizeof(sock_client));
	slen = sizeof(sock_client);				// len structure socket
	// init structure
	sock_client.sin_family = AF_INET;
	sock_client.sin_port = htons(DESTINATION_PORT);
	/////////////////////////////////////////////////////
	if (inet_aton(SERVER , &sock_client.sin_addr) == 0){fprintf(stderr, "inet_aton() failed\n");return -1;}

	while(1)
	{
		printf("Enter message : ");
		get_input_string(&buf[28]);
		
		
		
		buf[0] = HEADER_IP_VERSIA_IP | HEADER_IP_LENGHT_IP_HEADER; //VERSIA IPv4 + LENGHT_IP_HEADER 
		buf[1] = HEADER_IP_TYPE_SERVICE;// Type of Service
		
		temp.word = 4*HEADER_IP_LENGHT_IP_HEADER + 8 + strlen(&buf[28]);    // Total Length
		buf[2] = temp.bait[1];
		buf[3] = temp.bait[0];
		
		temp.word = HEADER_IP_IDENTIFICATION;    // Identification
		buf[4] = temp.bait[1];
		buf[5] = temp.bait[0];
		
		temp.word = HEADER_IP_FLAGS_FR_OFFSET;    // Flags and Fragment Offset
		buf[6] = temp.bait[1];
		buf[7] = temp.bait[0];
		
		buf[8] = HEADER_IP_TIME_TO_LIVE;	// Time to Live
		buf[9] = HEADER_IP_TYPE_PROTOCOL;	// Type Protocol Up Level (UDP = 0x11)
		
		buf[10] = 0x00;	// Header Checksum
		buf[11] = 0x00;	// Header Checksum
		
		//Source Address
		buf[12] = 0x00;	// Source Address
		buf[13] = 0x00;	// Source Address
		buf[14] = 0x00;	// Source Address
		buf[15] = 0x00;	// Source Address
		
		//Destination Address
//		buf[16] = 0x00;	// Destination Address
//		buf[17] = 0x00;	// Destination Address
//		buf[18] = 0x00;	// Destination Address
//		buf[19] = 0x00;	// Destination Address
		if (inet_aton(SERVER , (struct in_addr *)&buf[16]) == 0){fprintf(stderr, "inet_aton() failed\n");return -1;}
		
		
		
		
		temp.word = SOURCE_PORT;
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 0] = temp.bait[1];
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 1] = temp.bait[0];
		temp.word = DESTINATION_PORT;
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 2] = temp.bait[1];
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 3] = temp.bait[0];
		temp.word = 8 + strlen(&buf[28]);
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 4] = temp.bait[1];
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 5] = temp.bait[0];
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 6] = 0;
		buf[4*HEADER_IP_LENGHT_IP_HEADER + 7] = 0;
		
		temp.word = 4*HEADER_IP_LENGHT_IP_HEADER + temp.word;
		//send the message
		if (sendto(fd, buf, temp.word , 0 , (struct sockaddr *) &sock_client, slen)==-1){perror("can't sendto");return -1;}//receive a reply and print it
//		if (sendto(buf, temp.word)==-1){perror("can't sendto");return -1;}//receive a reply and print it
		strncpy (temp_buf, &buf[28],BUFLEN - 28);
		
//		sleep(5);
		memset(buf,'\0', BUFLEN);//clear the buffer by filling null, it might have previously received data
		//try to receive send data, this is a blocking call
		if ((recv_len = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen)) == -1){perror("can't recvfrom()");return -1;}
		buf[recv_len] = 0;
		
		
		memset(buf,'\0', BUFLEN);//clear the buffer by filling null, it might have previously received data
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *) &sock_client, &slen)) == -1){perror("can't recvfrom()");return -1;}
		buf[recv_len] = 0;
		
		
		printf("Data: %s\n" , &buf[28]);
		if (strcmp (temp_buf, "exit")==0){break;}
	}

	close(fd);
	return 0;
}



void get_input_string(char *str_in)
{
    int ch = 0;
    int temp_count = 0;
    while ((ch = getchar()) != '\n')
    {
        (*(str_in + temp_count)) = ch;
        ++temp_count;
        if(temp_count > (BUFLEN - 2 ))
        {
//          (*(str_in + temp_count)) = '\n';
//          ++temp_count;
          break;
        }
    }
//    (*(str_in + temp_count)) = '\n';
    (*(str_in + temp_count)) = 0;    
}




