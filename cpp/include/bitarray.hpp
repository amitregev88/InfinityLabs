/****************************************************************************/
/*	Project:	BitArray API												*/
/*	File:		bitarray.hpp												*/
/*	Date: 		02/11/2022													*/
/*	Name: 		ILRD25      												*/
/*	Reviewer:	Binyamin													*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __BITARRAY_HPP__
#define __BITARRAY_HPP__

#include <cstddef>     // std::size_t
#include <string>       // string

namespace ilrd
{

template<std::size_t NBITS>
class BitArray
{   // Generated dtor.
private:
    class BitProxy;

public:
    explicit BitArray();

    BitArray& operator>>=(std::size_t);
    BitArray& operator<<=(std::size_t);
    BitArray& operator&=(const BitArray& o_);
    BitArray& operator^=(const BitArray& o_);
    BitArray& operator|=(const BitArray& o_);

    bool operator==(const BitArray& o_) const;
    bool operator!=(const BitArray& o_) const;

    const BitArray operator~() const;
    const BitArray operator&(const BitArray& o_) const;
    const BitArray operator|(const BitArray& o_) const;
    const BitArray operator^(const BitArray& o_) const;

    BitProxy operator[](std::size_t idx_);
    bool operator[](std::size_t idx_) const;

    BitArray& SetAll();
    BitArray& UnsetAll();
    std::size_t CountSet() const;
    std::string ToString();

private:
    std::size_t m_array[NBITS / 64 + ((NBITS % 64) ? (1) : (0))];

    bool Set(std::size_t);
    bool Reset(std::size_t);
    bool Get(std::size_t);

    class BitProxy
    {
    public:
        explicit BitProxy(BitArray&, std::size_t);

        operator bool();
        bool operator=(bool);
        bool operator=(const BitProxy&);
        // To add - operator ~...
    private:
        BitArray *const m_array;
        const std::size_t m_idx;
        m_arri;
        m_biti;
    }; // class BitProxy
};

template<std::size_t NBITS>
bool BitArray<NBITS>:: Set(std::size_t idx_)
{
   

       /*  m_arri = m_idx / 64;

    m_biti = m_idx %64; */
} 
   NBITS/ 
    m_array[]



}
    bool Reset(std::size_t);
    bool Get(std::size_t);















template<std::size_t NBITS>
BitArray<NBITS>::BitArray(): m_array()
{}

template<std::size_t NBITS>
BitArray<NBITS>::BitProxy::BitProxy(BitArray& arr_, std::size_t idx_):m_array(arr_), m_idx(idx_) 
{}


template<std::size_t NBITS>
BitArray<NBITS>::BitProxy::BitProxy(BitArray& arr_, std::size_t idx_):m_array(arr_), m_idx(idx_) 
{}


template<std::size_t NBITS>
BitArray<NBITS>::BitProxy::operator bool()
{
    
    m_array=
    /*  m_arri = m_idx / 64;

    m_biti = m_idx %64; */
} 





template<std::size_t NBITS>
BitArray& BitArray<NBITS>:: operator>>=(std::size_t)
{}

template<std::size_t NBITS>
 BitArray<NBITS>:: operator[](std::size_t idx_)
{



}

template<std::size_t NBITS>
BitArray& BitArray<NBITS>:: operator>>=(std::size_t);






} // namespace ilrd




#endif //	ifndef __BITARRAY_HPP__									

/*********************************End Of Header******************************/
