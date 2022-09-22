#ifndef __RCSTRING__
#define __RCSTRING__

class String 
{
    public:

    String(const char *);
    String(Stirng& o_); 
    ~String();

    size_t Length()const;
    const char *Ctor()const;

    private:
    char *m_str;
    void *operator new(size_t);
    static void DecreaseRefIMP(const char *);
    static void IncreaseRefIMP(const char *);
    char *AllocNcopy(const &String);
  

}

String::String(const char *str)
{
    1. calculate len string  for alloc
    
    2. call operator new 

    3. 
    
}

String::~String()
{
    DecreaseRefIMP();
}

String::String(String& )
{
    IncreaseRefIMP();
}

String::operator=(String& _o)
{

    1.if _o.m_str  and  m_str same ->return
     
    2. assignment  m_str =  _o.m_str  



}

static void DecreaseRefIMP(void *)
1. decrease rc_flag by 1; (get to meta data -8) 

2. release m_str;


static void IncreaseRefIMP(void *)

1. increase rc_flag by 1; (get to meta data -8) 

2 m_str receive 




char *AllocNcopy(const &String)
psuedo rc buffer:
1. allocate -> string len + size_t (meta data)
2. copy string to bufer copy + 1
3. set rc_flag to 0
4. return pointer  + sizeof(size_t)


size_t Length()const
{

    same code

}

const char *Ctor()const
{

    same code
}

#endif


