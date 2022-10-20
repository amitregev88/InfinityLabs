/*******************************************************************************
/* Project: OOD File/Dir
/* File: dirs.hpp
/* Name: Amit Regev
/* Date: 15/10/2022
/*******************************************************************************/


class Record
{
public:
    virtual int Permissions(int) = 0;
};

class Directory : public Record
{
public:
    int Permissions(int);
};

class DataFile : public Record
{
public:
    int Permissions(int);
};

