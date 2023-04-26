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
#include "thread_pool.hpp"

class ShapePublisher
{

public:
    explicit ShapePublisher() = default;
    ~ShapePublisher() noexcept = default;
    ShapePublisher(const ShapePublisher &) = delete;
    ShapePublisher &operator=(const ShapePublisher &) = delete;

    void Init();
    void Publish();

private:
    void Parse(int msg, struct sockaddr_in client_s);
    void Unsubscribe(struct sockaddr_in client_s);
    void Subscribe(Data_ty dtype_, struct sockaddr_in client_s);
    static void SchedTask(ShapeSubscriber sub, int socket_fd);
    static void GetRequest(ShapePublisher *this_);

    int m_fd;
    size_t m_port;
    std::vector<ShapeSubscriber> m_subs;
    struct sockaddr_in m_localSock;
    struct ip_mreq m_group;
    // ThreadPool m_tp;
};

/****************************************************************************/
/*init the multicast socket and wait for subscribers registertion*/
void ShapePublisher::Init()
{
    m_port = 5000;
    m_fd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(m_fd > 0);

    int reuse = 1;

    int res = setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
    assert(res >= 0);

    memset((char *)&m_localSock, 0, sizeof(m_localSock));
    m_localSock.sin_family = AF_INET;
    m_localSock.sin_port = htons(m_port);
    m_localSock.sin_addr.s_addr = INADDR_ANY;

    res = bind(m_fd, (struct sockaddr *)&m_localSock, sizeof(m_localSock));
    assert(res >= 0);

    m_group.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    // m_group.imr_interface.s_addr = inet_addr("127.0.0.1");
    res = setsockopt(m_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&m_group, sizeof(m_group));
    assert(res >= 0);

    ThreadPool m_tp(1);

    m_tp.AddTask(std::bind(GetRequest, this));
    m_tp.Run();

    sleep(10);
};

void ShapePublisher::Parse(int msg, struct sockaddr_in client_s)
{
    if (msg % 2 != 0) // incase it is register request
    {

        int data_type = msg / 10; // 1 - square  2 - circle 3 - both

        switch (data_type)
        {
        case 1:
            Subscribe(SQUARE, client_s);
            break;

        case 2:
            Subscribe(CIRCLE, client_s);
            break;

        case 3:
            Subscribe(BOTH, client_s);
            break;

        default:
            std::cout << "invalid request from client\n";
            break;
        }
    }

    else // incase it is uregister request
    {
        Unsubscribe(client_s);
    }
};

void ShapePublisher::Subscribe(Data_ty dtype_, struct sockaddr_in client_s)
{
    ShapeSubscriber sub(dtype_);

    sub.SetSockaddr_in(client_s);

    m_subs.push_back(sub);
};

void ShapePublisher::Unsubscribe(struct sockaddr_in client_s)
{
    auto iter = std::find_if(m_subs.begin(), m_subs.end(), [&](ShapeSubscriber &sub)
                             { return (client_s.sin_addr.s_addr == sub.GetStruct().sin_addr.s_addr); });

    if (iter != m_subs.end())
    {
        m_subs.erase(iter);
    }
};

// publish function is creates threads for publish the data. it ran once.
void ShapePublisher::Publish()
{
    ThreadPool tp(m_subs.size());

    bool is_sub_add = 0;

    while (!m_subs.empty())
    {
        for (size_t idx = 0; m_subs.size() > idx; ++idx)
        {
            if(m_subs[idx].m_is_published == false)
            {
                m_subs[idx].m_is_published = true;
                tp.AddTask(std::bind(SchedTask, m_subs[idx], m_fd));
                is_sub_add = 1;
            }

            //add flag?
        }
        if (is_sub_add == 1)
        {
            tp.Pause(/*static_cast<boost::chrono::milliseconds>(5000)*/);
            is_sub_add = 0;
            sleep(10);
        }

        tp.Run();

            //int value = 50000;
            //auto time = std::chrono::milliseconds(value);

            //sleep (5);
 

        sleep(2);
       
    }

    /* for (size_t idx = 0; m_subs.size() > idx; ++idx)
    {
        tp.AddTask(std::bind(SchedTask, m_subs[idx], m_fd));
    }

    tp.Run();

    sleep(200); */
}

// Schedules the sending of the data.
void ShapePublisher::SchedTask(ShapeSubscriber sub, int socket_fd)
{
    Interpreter in;

    Data_ty dtype = sub.GetDataType();

    std::string msg = in.Serialize(dtype);

    struct sockaddr_in tmp_struct = sub.GetStruct();

    while (true)
    {

        sendto(socket_fd, msg.c_str(), msg.size(), 0, (const sockaddr *)&tmp_struct, sizeof(tmp_struct));

        if (dtype == CIRCLE)
        {
            sleep(1);
        }
        else if (dtype == SQUARE)
        {
            sleep(3);
        }

        else if ((dtype == BOTH))
        {
            sleep(5);
        }
    }
};

void ShapePublisher::GetRequest(ShapePublisher *this_)
{

    while (true)
    {

        char buffer[200] = {"\0"};

        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(client_addr));

        unsigned int len = sizeof(client_addr);

        int num_of_bytes = recvfrom(this_->m_fd, (char *)buffer, 200, MSG_WAITALL, (struct sockaddr *)&client_addr, &len);
        assert(num_of_bytes > 0);

        this_->Parse(std::stoi(buffer), client_addr);
    }
}

#endif //	ifndef __SHAPEPUBLISHER_HPP__
