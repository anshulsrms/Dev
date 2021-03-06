/* 
   this class is to implement the domain and IP address resolution. 
      
*/

#ifndef myHostInfo_H
#define myHostInfo_H

#include <string>
using namespace std;

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
    
enum hostType {NAME, ADDRESS};
const int HOST_NAME_LENGTH = 64;

class myHostInfo
{

private:

	
	char searchHostDB;     // search the host database flag
	struct hostent *hostPtr;    // Entry within the host address database

public:

    // Default constructor
    myHostInfo();

    // Retrieves the host entry based on the host name or address
    myHostInfo(string hostName, hostType type);
 
    // Destructor.  Closes the host entry database.
    ~myHostInfo()
    {
		
			endhostent();
		
    }

	

		// Retrieves the next host entry in the database
		char getNextHost();

		// Opens the host entry database
		void openHostDb()
		{
			endhostent();
			searchHostDB = 1;
			sethostent(1);
		}

	

    // Retrieves the hosts IP address
    char* getHostIPAddress() 
    {
        struct in_addr *addr_ptr;
		// the first address in the list of host addresses
        addr_ptr = (struct in_addr *)*hostPtr->h_addr_list;
		// changed the address format to the Internet address in standard dot notation
        return inet_ntoa(*addr_ptr);
    }    
    
    // Retrieves the hosts name
    char* getHostName()
    {
        return hostPtr->h_name;
    }


};

#endif
