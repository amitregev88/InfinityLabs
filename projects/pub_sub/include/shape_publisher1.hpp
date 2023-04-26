/****************************************************************************/
/*	Project:	ShapePublisher												*/
/*	File:		shape_publisher.hpp 										*/
/*	Date: 		6/01/2023													*/
/*	Name: 		Amit Regev													*/
/*	Version: 	1.00														*/
/****************************************************************************/
#ifndef __SHAPEPUBLISHER_HPP__
#define __SHAPEPUBLISHER_HPP__

#include <netinet/in.h> //sockaddr_in
#include <vector>       //vector
#include <arpa/inet.h>  // inet_addr
#include <algorithm>    //find_if

#include "shape_subscriber.hpp"
#include "interpreter.hpp"

class ShapePublisher
{

public:
    explicit ShapePublisher() = default;
    ~ShapePublisher() noexcept = default;
    ShapePublisher(const ShapePublisher &) = delete;
    ShapePublisher &operator=(const ShapePublisher &) = delete;

    void Init(std::string serverip_);
    void Publish();

private:
    void Parse(int num, struct sockaddr_in client_s);
    void Unsubscribe(size_t port_);
    void Subscribe(Data_ty dtype_, size_t port_, const struct sockaddr_in client_s);
    std::vector<ShapeSubscriber> m_subs;
    struct sockaddr_in m_server_addr;
    std::vector<size_t> m_ports;
    std::vector<int> m_sockets_fd;

    std::string m_serverip;
};

/****************************************************************************/

void ShapePublisher::Init(std::string serverip_)
{
    size_t i = 0;

    while (i < 2)
    {

        m_ports.push_back(5000 + (i * 1000));
        m_serverip = serverip_;
        char buffer[200] = {"\0"};
        struct sockaddr_in client_addr;

        /*init struct sockaddr_in to 0*/
        memset(&m_server_addr, 0, sizeof(m_server_addr));
        memset(&client_addr, 0, sizeof(client_addr));

        // Creating socket file descriptor
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        assert(fd > 0);
        m_sockets_fd.push_back(fd);

        // Filling server information
        m_server_addr.sin_family = AF_INET; // IPv4
        m_server_addr.sin_addr.s_addr = INADDR_ANY;
        m_server_addr.sin_port = htons(m_ports[i]);

        int res = bind(m_sockets_fd[i], (const struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
        assert(res == 0);

        unsigned int len = sizeof(client_addr);

        int num_of_bytes = recvfrom(m_sockets_fd[i], (char *)buffer, 200, MSG_WAITALL, (struct sockaddr *)&client_addr, &len);
        assert(num_of_bytes > 0);

        Parse(std::stoi(buffer), client_addr);

        ++i;
    }
};

void ShapePublisher::Parse(int num, struct sockaddr_in client_s)
{
    if (num % 2 != 0) // incase it is register request
    {
        num /= 10;

        int data_type = num % 10; // 1 - square  2 - circle 3 - both

        num /= 10;

        switch (data_type)
        {
        case 1:
            Subscribe(SQUARE, num, client_s);
            break;

        case 2:
            Subscribe(CIRCLE, num, client_s);
            break;

        case 3:
            Subscribe(BOTH, num, client_s);
            break;

        default:
            std::cout << "invalid request from client\n";
            break;
        }
    }

    else // incase it is uregister request
    {
        int port = num / 10;

        Unsubscribe(port);
    }
};

void ShapePublisher::Subscribe(Data_ty dtype_, size_t port_, const struct sockaddr_in client_s)
{
    ShapeSubscriber sub(dtype_, "127.0.0.1", port_);

    sub.SetSockaddr_in(client_s);

    m_subs.push_back(sub);
};

void ShapePublisher::Unsubscribe(size_t port_)
{
    auto iter = std::find_if(m_subs.begin(), m_subs.end(), [&](const ShapeSubscriber &sub)
                             { return (sub.GetPort() == port_); });

    if (iter != m_subs.end())
    {
        m_subs.erase(iter);
    }
};

void ShapePublisher::Publish()
{

    Interpreter in;

    for (size_t idx = 0; m_subs.size() > idx; ++idx)
    {
        Data_ty dtype = m_subs[idx].GetDataType();

        std::string msg = in.Serialize(dtype);

        struct sockaddr_in tmp_struct = m_subs[idx].GetStruct();

        size_t count = 0;

        while (3 > count)
        {
            ++count;
            sendto(m_sockets_fd[idx], msg.c_str(), msg.size(), 0, (const sockaddr *)&tmp_struct, sizeof(m_subs[idx].GetStruct()));
            
            if (dtype == CIRCLE)
            {
                sleep(1);
            }
            else if (dtype == SQUARE)
            {
                sleep(5);
            }

            else if ((dtype == BOTH))
            {
                sleep(7);
            }
        }
    }
};

#endif //	ifndef __SHAPEPUBLISHER_HPP__
