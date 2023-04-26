/****************************************************************************/
/*	Project:	ShapeSubscriber												*/
/*	File:		shape_subscriber.hpp										*/
/*	Date: 		6/01/2022													*/
/*	Name: 		Amit Regev													*/
/*	Version: 	1.00														*/
/****************************************************************************/
#ifndef __SHAPESUBSCRIBER_HPP__
#define __SHAPESUBSCRIBER_HPP__

#include <netinet/in.h> /*sockaddr_in*/
#include <cstring>      //memset
#include <cassert>      // assert
#include <unistd.h> //close
#include <arpa/inet.h> //inet_addr

#include "interpreter.hpp"

class ShapeSubscriber
{

public:
    explicit ShapeSubscriber(Data_ty datatype_, const std::string& groupip_ = "224.0.0.1", size_t port_ = 5000);
    ~ShapeSubscriber() noexcept = default;

    void Register();
    void Unregister();
    Data_ty GetDataType() const;
    struct sockaddr_in GetStruct();

    void SetSockaddr_in(sockaddr_in client_addr);

private:
    std::string m_groupip;
    size_t m_port;
    Data_ty m_datatype;
    struct in_addr m_localInterface;    
    struct sockaddr_in m_group_addr;    //pubs
    struct sockaddr_in m_client_addr; //sub
    int m_sockfd;
    
    void Listen();
};

/****************************************************************************/
ShapeSubscriber::ShapeSubscriber(Data_ty datatype_,  const std::string& groupip_, std::size_t port_)
{
    m_datatype = datatype_;
    m_port = port_;
    m_groupip = groupip_;

    /*init struct sockaddr_in to 0*/
     memset((char *)&m_group_addr, 0, sizeof(m_group_addr));
}

void ShapeSubscriber::Register()
{
    std::string msg;
    
//The first digit to the right: 1 - register request , 0- unregister request
// The Second digit to the left (if it register request): 1 - squarem , 2 - circle , 3 - both

    switch (m_datatype) 
    {                   
    case SQUARE:

        msg = "11";
        break;

    case CIRCLE:
        msg = "21";
        break;

    case BOTH:

        msg = "31";
        break;

    default:
        std::cout << "data type is not exist\n";
        break;
    }

    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(m_sockfd > 0);

    // Filling pubs group information
    m_group_addr.sin_family = AF_INET; // IPv4
    m_group_addr.sin_addr.s_addr = inet_addr("224.0.0.1");
    m_group_addr.sin_port = htons(m_port);

    {
        char loopch = 0;

        int res = setsockopt(m_sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch));
        assert(res >= 0);
    }

    m_localInterface.s_addr = inet_addr("127.0.0.1");
    
    int res = setsockopt(m_sockfd, IPPROTO_IP, IP_MULTICAST_IF,(char *)&m_localInterface,sizeof(m_localInterface));
    assert(res >= 0);


    res = sendto(m_sockfd, msg.c_str(), msg.size(), 0,(struct sockaddr*)&m_group_addr,sizeof(m_group_addr));
    assert(res > 0);  
    
    Listen(); 
}

//Unregister function is asks from publisher do not send data anymore 
void ShapeSubscriber::Unregister()
{
    std::string msg = "0"; 

    int n_bytes_sent = sendto(m_sockfd, msg.c_str(), msg.size(), 0, (const struct sockaddr *)&m_localInterface, sizeof(m_localInterface));
    assert(n_bytes_sent > 0);

    close(m_sockfd);
}

//Listen function waits for publisher  to get the msg. 
void ShapeSubscriber::Listen()
{
    while (true)
    {
        char buffer[200] = {"\0"};
        std:: string msg_from_ser; 
        int len;

        int n_bytes_recived = recvfrom(m_sockfd, (char *)buffer , 200, MSG_WAITALL, (struct sockaddr *)&m_group_addr, (socklen_t *)&len);
        assert(n_bytes_recived > 0);
        
        msg_from_ser = buffer;

        Interpreter in;
  
        Shape *shape = in.Deserialize(msg_from_ser);
        shape->Print();
        delete shape;
    }
}

Data_ty ShapeSubscriber::GetDataType() const
{
    return m_datatype;
}

struct sockaddr_in ShapeSubscriber:: GetStruct()
{
    return m_client_addr;
}

void ShapeSubscriber::SetSockaddr_in(const struct sockaddr_in client_s)
{
    memcpy(&m_client_addr, &client_s, sizeof(m_client_addr));
}

#endif //	ifndef __SHAPESUBSCRIBER_HPP__
