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

#include "interpreter.hpp"

class ShapeSubscriber
{

public:
    explicit ShapeSubscriber(Data_ty datatype_, std::string serverip_, size_t port_);
    ~ShapeSubscriber() noexcept = default;
    //ShapeSubscriber(const ShapeSubscriber &) = delete;
    //ShapeSubscriber &operator=(const ShapeSubscriber &) = delete;

    void Register();
    void Unregister();
    size_t GetPort() const;
    Data_ty GetDataType() const;
    const struct sockaddr_in GetStruct();


    void SetSockaddr_in(const struct sockaddr_in client_s);

private:
    std::string m_serverip;
    size_t m_port;
    Data_ty m_datatype;
    struct sockaddr_in m_client_addr;
    
    int m_client_sockfd;
    void ListenConnection(struct sockaddr_in server_addr);
};

/****************************************************************************/
ShapeSubscriber::ShapeSubscriber(Data_ty datatype_, std::string serverip_, std::size_t port_)
{
    m_datatype = datatype_;
    m_port = port_;
    m_serverip = serverip_;
   

    /*init struct sockaddr_in to 0*/
    memset(&m_client_addr, 0, sizeof(m_client_addr));
}

void ShapeSubscriber::Register()
{
    std::string msg ;
    std::string port = std::to_string(m_port);

    switch (m_datatype)
    {
    case SQUARE:

        msg = port + "11\0";
        break;

    case CIRCLE:
        msg = port + "21\0";
        break;

    case BOTH:

        msg = port + "31\0";
        break;

    default:
        std::cout << "data type is not exist\n";
        break;
    }

    int fd;
    struct sockaddr_in servaddr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(fd > 0);
    m_client_sockfd = fd;

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_port = htons(m_port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int res = sendto(fd, msg.c_str(), msg.size(), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    assert(res != -1);
    ListenConnection(servaddr);
}

void ShapeSubscriber::Unregister()
{
    std::string msg = m_port + "0\0"; 

    struct sockaddr servaddr;

    int n_bytes_sent = sendto(m_client_sockfd, msg.c_str(), msg.size(), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    assert(n_bytes_sent > 0);

    close(m_client_sockfd);
}

void ShapeSubscriber::ListenConnection(struct sockaddr_in server_addr)
{
    while (true)
    {
        char buffer[200] = {"\0"};
        std:: string msg_from_ser; 
        int len;

        int n_bytes_recived = recvfrom(m_client_sockfd, (char *)buffer , 200, MSG_WAITALL, (struct sockaddr *)&server_addr, (socklen_t *)&len);
        assert(n_bytes_recived > 0);
        
        msg_from_ser = buffer;
 
        Interpreter in;
        Shape *tmp = in.Deserialize(msg_from_ser);
        tmp->Print();
        delete tmp;
    }
}

size_t ShapeSubscriber::GetPort() const
{
    return m_port;
}

Data_ty ShapeSubscriber::GetDataType() const
{
    return m_datatype;
}

const struct sockaddr_in ShapeSubscriber:: GetStruct()
{
    return m_client_addr;
}

void ShapeSubscriber::SetSockaddr_in(const struct sockaddr_in client_s)
{
    memcpy(&m_client_addr, &client_s, sizeof(m_client_addr));
}



#endif //	ifndef __SHAPESUBSCRIBER_HPP__